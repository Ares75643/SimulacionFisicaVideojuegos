#pragma once
#include "ParticleGenerator.h"
#include "ParticleSystem.h"
#include <random>

class UniformParticleGenerator : public ParticleGenerator {
private:
	float median = 0, var = 2;
public:
	UniformParticleGenerator(string Name, Vector3 Position, Vector3 PVelocity, Particle* Model, int ParticlesGenerated, int MaxParticles, float GenerationProbability, float Frecuency, Vector3 Velocity = Vector3(0, 0, 0));
	~UniformParticleGenerator();
	virtual list<Particle*> generateParticles();

	list<Particle*> generateFireworks(ParticleSystem* PSYS);

	void changeDistribution(float M, float V) { median = M; var = V; }
	float getVar() { return var; }
	float getMedian() { return median; }
};