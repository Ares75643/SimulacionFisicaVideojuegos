#pragma once
#include "ParticleGenerator.h"
class UniformParticleGenerator : public ParticleGenerator {
public:
	virtual list<Particle*> generateParticles();
};