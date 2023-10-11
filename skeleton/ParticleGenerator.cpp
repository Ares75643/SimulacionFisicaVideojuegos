#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(string Name, Vector3 Position, Vector3 Velocity, Particle* Model, int ParticlesGenerated, int MaxParticles, float GenerationProbability, float Frecuency) {
	name = Name;
	position = Position;
	velocity = Velocity;
	model = Model;
	particlesGenerated = ParticlesGenerated;
	maxParticles = MaxParticles;
	generationProbability = generationProbability;
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