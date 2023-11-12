#include "TornadoForceGenerator.h"

TornadoForceGenerator::TornadoForceGenerator(Vector3 Origin, Vector3 windVel, const float& k1, const float& k2) {
	WindForceGenerator(windVel, k1, k2);
	origin = Origin;
}

void TornadoForceGenerator::updateForce(Particle* particle, double t){
	if (fabs(particle->getInvMass()) < 1e-10) return; // Comprueva si la particula tiene masa
	
	Vector3 pos = particle->getPos();
	Vector3 tForce;
	tForce.x = -(pos.z - origin.z);
	tForce.y = 50 - pos.y - origin.y;
	tForce.z = pos.x - origin.x;

	tForce *= k1;

	particle->addForce(tForce);
}