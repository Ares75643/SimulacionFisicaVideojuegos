#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

class Particle {
public:
	Particle(Vector3 Pos, Vector3 Vel = Vector3(0, 0, 0), Vector3 Acl = Vector3(0, 0, 0), 
			 Vector4 Color = Vector4(0, 0, 255, 255));
	~Particle();

	void integrate(double t);

private:
	Vector3 aceleration;
	Vector3 velocity;
	float damping = 0.998f;

	physx::PxTransform pose;
	RenderItem* renderItem;
};