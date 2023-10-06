#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

class Particle {
public:
	Particle(Vector3 Pos, Vector3 Vel = Vector3(0, 0, 0), Vector3 Acl = Vector3(0, 0, 0), 
		float Size = 1, float Mass = 1, float LifeTime = 25, float Damp = 0.998f, 
		Vector4 Color = Vector4(0, 0, 255, 255));
	~Particle();

	void init();
	void integrate(double t);

	void setMass(float M) { mass = M; }
	void setDamping(float D) { damping = D; }
	void setPosition(Vector3 P) { pose = physx::PxTransform(P.x, P.y, P.z); }
	void setVelocity(Vector3 V) { velocity = V; }
	void setSpeed(float S) { velocity = velocity.getNormalized() * S; }
	void setAcceleration(Vector3 A) { aceleration = A; }
	void setLifeTime(float T) { lifeTime = T; }
	void setColor(Vector4 C) { color = C; }
	void setSize(float S) { size = S; }

	bool isAlive() { return alive; }

private:
	Vector3 aceleration; // m/s2
	Vector3 velocity; // m/s
	float size; // m
	float mass; // Kg
	float damping;

	float lifeTime; // s
	bool alive;

	Vector4 color;

	physx::PxTransform pose;
	RenderItem* renderItem;
};