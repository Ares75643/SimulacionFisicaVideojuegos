#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

class Particle {
public:
	Particle(Vector3 Pos, Vector3 Vel = Vector3(0, 0, 0), Vector3 Acl = Vector3(0, 0, 0), float Mass = 1, float LifeTime = 30, 
		float Damp = 0.998f, Vector4 Color = Vector4(0, 0, 255, 255));
	~Particle();

	void integrate(double t);

	void setMass(float M) { mass = M; }
	void setDamping(float D) { damping = D; }
	void setPosition(Vector3 P) { pose = physx::PxTransform(P.x, P.y, P.z); }
	void setVelocity(Vector3 V) { velocity = V; }
	void setAcceleration(Vector3 A) { aceleration = A; }
	void setLifeTime(float T) { lifeTime = T; }

	bool isAlive() { return alive; }

private:
	Vector3 aceleration;
	Vector3 velocity;
	float damping;
	float mass;

	float lifeTime;
	bool alive;

	physx::PxTransform pose;
	RenderItem* renderItem;
};