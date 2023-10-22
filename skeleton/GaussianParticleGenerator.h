#pragma once
#include "ParticleGenerator.h"
#include <random>
class Firework;
class ParticleSystem;

class GaussianParticleGenerator : public ParticleGenerator {
private:
	float median = 0, var = 2;
public:
	GaussianParticleGenerator(string Name, Vector3 Position, Vector3 PVelocity, Particle* Model, int ParticlesGenerated, int MaxParticles, float GenerationProbability, float Frecuency, Vector3 Velocity= Vector3(0,0,0));
	~GaussianParticleGenerator();
	virtual list<Particle*> generateParticles();
	virtual list<Particle*> generateFireworks(ParticleSystem* PSYS);

	void changeDistribution(float M, float V) { median = M; var = V; }
	float getVar() { return var; }
	float getMedian() { return median; }
};