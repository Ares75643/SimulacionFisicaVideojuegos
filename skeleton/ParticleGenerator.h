#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "Particle.h"
#include <list>

using namespace std;

class ParticleGenerator {
protected:
	string name;
	Vector3 position, velocity;
	double generationProbability;
	int nParticles;
	int maxParticles;
	int particlesGenerated;
	float frecuency;
	float timeUntilNextGeneration;
	Particle* model;
	bool active;

public:
	ParticleGenerator(){}
	ParticleGenerator(string Name, Vector3 Position, Vector3 Velocity, Particle* Model, int ParticlesGenerated, int MaxParticles, float GenerationProbability, float Frecuency);
	~ParticleGenerator();

	void setParticle(Particle* model);
	virtual list<Particle*> generateParticles() = 0;
	void updateTime(float t) { timeUntilNextGeneration -= t; }
};