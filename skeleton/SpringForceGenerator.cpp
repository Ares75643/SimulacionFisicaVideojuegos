#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(double K, double RestingLength, Particle* Other) {
	k = K;
	restingLength = RestingLength;
	other = Other;
}

void SpringForceGenerator::updateForce(Particle* particle, double t) {
	Vector3 distanceBP = other->getPos() - particle->getPos();

	const float length = distanceBP.normalize();
	const float deltaX = length - restingLength;
	
	Vector3 force = distanceBP * deltaX * k;

	particle->addForce(force);
}