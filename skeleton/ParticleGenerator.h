#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "Particle.h"
#include <list>

using namespace std;

class ParticleGenerator {
private:
	string name;
	Vector3 pos, vel;
	double generationProbability;
	int nParticles;
	int maxParticles = 200;
	Particle* model;

public:
	ParticleGenerator();
	ParticleGenerator(string Name, Vector3 Pos, Vector3 Vel, double GenerationProbability, Particle* model);
	~ParticleGenerator();
	void setParticle(Particle* model);
	virtual list<Particle*> generateParticles() = 0;
};