#pragma once
#include "ParticleGenerator.h"

class GaussianParticleGenerator : public ParticleGenerator {
public:
	GaussianParticleGenerator(string Name, Vector3 Position, Vector3 Velocity, Particle* Model, int ParticlesGenerated, int MaxParticles, float GenerationProbability, float Frecuency);
	~GaussianParticleGenerator();
	virtual list<Particle*> generateParticles();
};