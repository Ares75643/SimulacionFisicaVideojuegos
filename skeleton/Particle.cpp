#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acl, float Mass, float LifeTime, float Damp, Vector4 Color) {
	velocity = Vel;
	aceleration = Acl;
	lifeTime = LifeTime;
	damping = Damp;
	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(10)), &pose, Color);
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