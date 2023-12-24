#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "Particle.h"
#include <list>
class ParticleSystem;

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

	double lifeTime = 60000;

	Particle* model;
	bool fireworks = false;

public:
	ParticleGenerator(){}
	ParticleGenerator(string Name, Vector3 Position, Vector3 PVelocity, Particle* Model, int ParticlesGenerated, int MaxParticles, float GenerationProbability, float Frecuency, Vector3 Velocity = Vector3(0,0,0));
	~ParticleGenerator();

	virtual list<Particle*> generateParticles() = 0;
	virtual list<Particle*> generateFireworks(ParticleSystem* PSYS) = 0;
	void update(float t);

	void setParticle(Particle* model);
	void setNumParticles(int N) { particlesGenerated = N; }
	void setLifeTime(double T) { lifeTime = T; }

	Particle* getModel() { return model; }

	bool isFireworkGenerator() { return fireworks; }
	void setFirework(bool F) { fireworks = F; }
};