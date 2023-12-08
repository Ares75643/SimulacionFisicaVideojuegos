#pragma once
#include "Particle.h"
#include "RigidBody.h"
#include <iostream>
using namespace std;

class ForceGenerator{
public:
	ForceGenerator();
	~ForceGenerator();
	virtual void updateForce(Particle* p, double t);
	virtual void updateForce(RigidBody* rb, double t);
};