#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "Particle.h"
#include <list>

using namespace std;

class ParticleGenerator {
protected:
	string name;
	Vector3 position, velocity; // Propiedades del generador
	Vector3 pVelocity; // Propiedades de las partículas

	bool active;

	int nParticles;
	int maxParticles;
	int particlesGenerated;

	float frecuency;
	float timeUntilNextGeneration;
	double generationProbability;

	Particle* model;

public:
	ParticleGenerator(){}
	ParticleGenerator(string Name, Vector3 Position, Vector3 PVelocity, Particle* Model, int ParticlesGenerated, int MaxParticles, float GenerationProbability, float Frecuency, Vector3 Velocity = Vector3(0,0,0));
	~ParticleGenerator();

	void setParticle(Particle* model);
	virtual list<Particle*> generateParticles() = 0;
	void update(float t);
};