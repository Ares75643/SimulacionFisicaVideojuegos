#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(string Name, Vector3 Position, Vector3 Velocity, Particle* Model, int ParticlesGenerated, int MaxParticles, float GenerationProbability, float Frecuency)
	: ParticleGenerator(Name, Position, Velocity, Model, ParticlesGenerated, MaxParticles, GenerationProbability, Frecuency) {
}

GaussianParticleGenerator::~GaussianParticleGenerator() {
}

list<Particle*> GaussianParticleGenerator::generateParticles() {

	list<Particle*> generated;

	if (active && timeUntilNextGeneration <= 0) {
		for (int i = 0; i < particlesGenerated; i++) {
			Vector3 pos = Vector3(position.x, position.y, position.z);
			Vector3 vel = Vector3(0, 0, 0);
			Vector3 acl = Vector3(0, -9.8, 0);

			Particle* p = new Particle(pos, vel, acl, model->getSize(), model->getMass(), model->getLifeTime(), model->getDamping(), model->getColor());
			p->init();
			generated.push_back(p);
		}
		timeUntilNextGeneration = frecuency;
	}

	return generated;
}