#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acl, float Size, float Mass, float LifeTime, float Damp, Vector4 Color, P_SHAPE Shape) {
	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	force = Vector3(0,0,0);
	velocity = Vel;
	aceleration = Acl;

	lifeTime = LifeTime;
	size = Size;
	mass = Mass;
	damping = Damp;

	if (mass > 0) { invMass = (1 / mass); }
	else { invMass = INTMAX_MAX; }

	color = Color;
	shape = Shape;
	alive = true;
}

void Particle::init() {
	if(shape == p_sphere)
		renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(size)), &pose, color);
	else if(shape == p_cube)
		renderItem = new RenderItem(CreateShape(physx::PxBoxGeometry(size, size, size)), &pose, color);
	else if (shape == p_plane)
		renderItem = new RenderItem(CreateShape(physx::PxBoxGeometry(size, 6, size)), &pose, color);
}

Particle::~Particle() {
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t) {
	aceleration = force * invMass;

	velocity += aceleration * t; // Aceleracion
	velocity *= pow(damping, t); // Damping
	pose.p += velocity * t; // Movimiento
	
	// Eliminar partícula
	lifeTime -= t;
	if (lifeTime < 0) alive = false;

	clearAcum(); // La fuerza ejercida sobre la particula se calcula cada frame

	//std::cout << getPos().x << " " << getPos().y << " " << getPos().z << std::endl;
}