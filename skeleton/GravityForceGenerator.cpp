#include "GravityForceGenerator.h"

void GravityForceGenerator::updateForce(Particle* particle, double t){
	if (fabs(particle->getInvMass()) < 1e-10) return; // Comprueba si la particula tiene masa

	particle->addForce(gravity * particle->getMass()); // Aplica la fueza de la gravedad en funcion de la masa
}