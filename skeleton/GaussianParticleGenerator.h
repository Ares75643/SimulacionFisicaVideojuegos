#pragma once
#include "ParticleGenerator.h"

class GaussianParticleGenerator : public ParticleGenerator {
public:
	virtual list<Particle*> generateParticles();
};