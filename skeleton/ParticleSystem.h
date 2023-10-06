#pragma once
#include <list>
#include "Particle.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "core.hpp"

using namespace std;

enum type{ UNIFORM, GAUSSIAN };

const Vector3 GRAVITY = Vector3(0.0f, -10.0f, 0.0f);

class ParticleSystem {
private:
	list<Particle*> particles;
	list<Particle*> particlesToDelete;

	list<ParticleGenerator*> particleGenerators;

	void deleteUnusedParticles();

public:
	ParticleSystem();
	~ParticleSystem();
	void update(double t);
	void addParticleGenerator(type T);
};