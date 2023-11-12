#include "TornadoForceGenerator.h"

TornadoForceGenerator::TornadoForceGenerator(Vector3 Origin, Vector3 WindVel, const float K, const float K1, const float K2) : WindForceGenerator(WindVel, K1, K2) {
	origin = Origin;
	k = K;
}

void TornadoForceGenerator::updateForce(Particle* particle, double t){
	if (fabs(particle->getInvMass()) < 1e-10) return; // Comprueva si la particula tiene masa
	
	windVelocity = k * Vector3(-(particle->getPos().z - origin.z), 50 - (particle->getPos().y - origin.y), particle->getPos().x - origin.x);
	Vector3 v = particle->getVelocity() - windVelocity;
	float tCoef = v.normalize();
	tCoef = k1 * tCoef + k2 * tCoef * tCoef;
	Vector3 tForce = -v * tCoef;

	particle->addForce(tForce);
}

