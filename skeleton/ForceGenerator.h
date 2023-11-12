#pragma once
#include "Particle.h"

class ForceGenerator{
public:
	ForceGenerator();
	~ForceGenerator();
	virtual void updateForce(Particle* p, double t);
};