#pragma once
#include "ForceGenerator.h"
#include "WindForceGenerator.h"
class TornadoForceGenerator : public WindForceGenerator {
protected:
	Vector3 origin;
public:
	TornadoForceGenerator(Vector3 origin, Vector3 windVel, const float& k1, const float& k2 = 0);

	virtual void updateForce(Particle* particle, double t);
};

