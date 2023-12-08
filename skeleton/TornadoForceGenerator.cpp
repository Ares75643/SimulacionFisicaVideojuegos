#include "TornadoForceGenerator.h"

TornadoForceGenerator::TornadoForceGenerator(Vector3 Origin, Vector3 WindVel, const float K, const float K1, const float K2) : WindForceGenerator(WindVel, K1, K2) {
	origin = Origin;
	k = K;
}

void TornadoForceGenerator::updateForce(Particle* particle, double t){
	if (fabs(particle->getInvMass()) < 1e-10) return; // Comprueba si la particula tiene masa
	
	// Calcula la velocidad del viento
	windVelocity = k * Vector3(-(particle->getPos().z - origin.z), 50 - (particle->getPos().y - origin.y), particle->getPos().x - origin.x); 
	// Aplica el updateForce del WindGenerator
	Vector3 v = particle->getVelocity() - windVelocity;
	float tCoef = v.normalize();
	tCoef = k1 * tCoef + k2 * tCoef * tCoef;
	Vector3 tForce = -v * tCoef;

	particle->addForce(tForce);
}

void TornadoForceGenerator::updateForce(RigidBody* rb, double t) {
	if (fabs(rb->getInvMass()) < 1e-10) return; // Comprueba si la particula tiene masa

	// Calcula la velocidad del viento
	windVelocity = k * Vector3(-(rb->getPosition().z - origin.z), 50 - (rb->getPosition().y - origin.y), rb->getPosition().x - origin.x);
	// Aplica el updateForce del WindGenerator
	Vector3 v = rb->getLinearVelocity() - windVelocity;
	float tCoef = v.normalize();
	tCoef = k1 * tCoef + k2 * tCoef * tCoef;
	Vector3 tForce = -v * tCoef;

	rb->addForce(tForce);
}
