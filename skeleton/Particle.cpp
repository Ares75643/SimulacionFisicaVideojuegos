#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acl, float Size, float Mass, float LifeTime, float Damp, Vector4 Color) {
	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	velocity = Vel;
	aceleration = Acl;

	lifeTime = LifeTime;
	size = Size;
	mass = Mass;
	damping = Damp;

	color = Color;
}

void Particle::init() {
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(size)), &pose, color);
	RegisterRenderItem(renderItem);
}

Particle::~Particle() {
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t) {
	velocity += aceleration * t; // Aceleracion
	velocity *= pow(damping, t); // Damping
	pose.p += velocity * t; // Movimiento
	
	// Eliminar part�cula
	lifeTime -= t;
	if (lifeTime < 0) alive = false;
}