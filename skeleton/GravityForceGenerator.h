#pragma once
#include "ForceGenerator.h"
class GravityForceGenerator : public ForceGenerator{
protected:
	Vector3 gravity;
public:
	GravityForceGenerator() {};
	GravityForceGenerator(const Vector3& Gravity) { gravity = Gravity; };
	~GravityForceGenerator() {};

	virtual void updateForce(Particle* particle, double t);

	inline void setGravity(const Vector3& G) {gravity = G;}
	inline Vector3 getGravity() { return gravity; }
};

