#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(string Name, Vector3 Position, Vector3 PVelocity, Particle* Model, int ParticlesGenerated, int MaxParticles, float GenerationProbability, float Frecuency, Vector3 Velocity) {
	name = Name;
	position = Position;
	velocity = Velocity;
	pVelocity = PVelocity;
	model = Model;
	particlesGenerated = ParticlesGenerated;
	maxParticles = MaxParticles;
	generationProbability = GenerationProbability;
	frecuency = Frecuency;
	timeUntilNextGeneration = Frecuency;

	nParticles = 0;
	active = true;
}

ParticleGenerator::~ParticleGenerator() {
	delete(model);
}

void ParticleGenerator::setParticle(Particle* Model) {
	delete(model);
	model = Model;
}

void ParticleGenerator::update(float t) {
	//velocity += aceleration * t; // Aceleracion
	//velocity *= pow(damping, t); // Damping
	position += velocity * t; // Movimiento

	timeUntilNextGeneration -= t;
}