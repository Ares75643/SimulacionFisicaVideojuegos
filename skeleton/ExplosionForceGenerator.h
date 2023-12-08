#pragma once
#include <cmath>
#include "ForceGenerator.h"

class ExplosionForceGenerator : public ForceGenerator {
protected:
	Vector3 origin;
	float k; // Intensidad de la explosion
	float r; // Radio de la explosion
	float time; // Tiempo de explosión

public:
	ExplosionForceGenerator(Vector3 Origin, float K = 5000, float Radius = 50, float Time = 0.1);
	virtual void updateForce(Particle* particle, double t);
	virtual void updateForce(RigidBody* rb, double t);
};