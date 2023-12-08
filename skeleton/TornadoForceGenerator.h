#pragma once
#include "ForceGenerator.h"
#include "WindForceGenerator.h"
class TornadoForceGenerator : public WindForceGenerator {
protected:
	Vector3 origin;
	int k; // Constante proporcional a la fuerza del torbellino

public:
	TornadoForceGenerator(Vector3 Origin, Vector3 WindVel, const float K = 1, const float K1 = 0.25, const float K2 = 0);

	virtual void updateForce(Particle* particle, double t);
	virtual void updateForce(RigidBody* rb, double t);
};

