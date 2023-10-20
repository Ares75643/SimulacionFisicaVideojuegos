#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

class Particle {
public:
	Particle(Vector3 Pos, Vector3 Vel = Vector3(0, 0, 0), Vector3 Acl = Vector3(0, 0, 0), 
		float Size = 1, float Mass = 1, float LifeTime = 25, float Damp = 0.998f, 
		Vector4 Color = Vector4(0, 0, 1, 1));
	~Particle();

	void init();
	virtual void integrate(double t);

	inline void setPosition(Vector3 P) { pose = physx::PxTransform(P.x, P.y, P.z); }
	inline void setVelocity(Vector3 V) { velocity = V; }
	inline void setSpeed(float S) { velocity = velocity.getNormalized() * S; }
	inline void setAcceleration(Vector3 A) { aceleration = A; }
	inline void setMass(float M) { mass = M; }
	inline void setDamping(float D) { damping = D; }
	inline void setLifeTime(float T) { lifeTime = T; }
	inline void setSize(float S) { size = S; }
	inline void setColor(Vector4 C) { color = C; }

	inline Vector3 getPos() { return Vector3(pose.p.x, pose.p.y, pose.p.z); }
	inline Vector3 getVelocity() { return velocity; }
	inline float getSpeed() { return velocity.magnitude(); }
	inline Vector3 getAcceleration() { return aceleration; }
	inline float getMass() { return mass; }
	inline float getDamping(){ return damping; }
	inline float getLifeTime(){ return lifeTime; }
	inline float getSize() { return size; }
	inline Vector4 getColor() { return color; }

	inline bool isAlive() { return alive; }

	inline Particle* clone() { return new Particle(pose.p, velocity, aceleration, size, mass, lifeTime, damping, color); }

protected:
	Vector3 aceleration; // m/s^2
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