#include "UniformParticleGenerator.h"

std::default_random_engine uGenerator;

UniformParticleGenerator::UniformParticleGenerator(string Name, Vector3 Position, Vector3 PVelocity, Particle* Model, int ParticlesGenerated, int MaxParticles, float GenerationProbability, float Frecuency, Vector3 Velocity)
	: ParticleGenerator(Name, Position, PVelocity, Model, ParticlesGenerated, MaxParticles, GenerationProbability, Frecuency, Velocity) {
}

UniformParticleGenerator::~UniformParticleGenerator() {

}

list<Particle*> UniformParticleGenerator::generateParticles() {
	std::uniform_real_distribution<float> distribution(median, var); // Se contruye aqui para poder cambiar los parametros
	list<Particle*> generated;

	if (active && timeUntilNextGeneration <= 0) { // Si debe generar (tiempo y activo)
		for (int i = 0; i < particlesGenerated; i++) { // Numero de generación
			if (generationProbability * 100 >= (rand() % 100 + 1)) { // Probabilidad de generar
				Particle* p = model->clone();
				p->setPosition(position + Vector3(distribution(uGenerator), distribution(uGenerator), distribution(uGenerator)));
				p->setVelocity(pVelocity + Vector3(distribution(uGenerator), distribution(uGenerator), distribution(uGenerator)));
				p->setAcceleration(Vector3(0, 0, 0));
				p->setLifeTime(p->getLifeTime() + distribution(uGenerator) * 0.5);
				p->init();
				generated.push_back(p);
			}
		}
		timeUntilNextGeneration = frecuency; // Actualiza el tiempo hasta la generación
	}
	return generated;
}

list<Particle*> UniformParticleGenerator::generateFireworks(ParticleSystem* PSYS) {
	std::normal_distribution<float> distribution(median, var); // Se contruye aqui para poder cambiar los parametros
	list<Particle*> generated;

	if (active && timeUntilNextGeneration <= 0) { // Si debe generar (tiempo y activo)
		for (int i = 0; i < particlesGenerated; i++) { // Numero de generación
			if (generationProbability * 100 >= (rand() % 100 + 1)) { // Probabilidad de generar
				Firework* f = new Firework(model->getPos(), model->getVelocity(), model->getAcceleration(),
					model->getSize(), model->getMass(), model->getLifeTime(), model->getDamping(),
					model->getColor(), rand() % 3, PSYS);

				f->setPosition(position + Vector3(distribution(uGenerator), distribution(uGenerator), distribution(uGenerator)));
				f->setVelocity(pVelocity + Vector3(distribution(uGenerator), distribution(uGenerator), distribution(uGenerator)));
				f->setAcceleration(Vector3(0, -9.8, 0));
				f->setLifeTime(f->getLifeTime() + distribution(uGenerator) * 0.05);
				f->setType();

				f->init();
				generated.push_back(f);
			}
		}
		timeUntilNextGeneration = frecuency; // Actualiza el tiempo hasta la generación
	}
	return generated;
}