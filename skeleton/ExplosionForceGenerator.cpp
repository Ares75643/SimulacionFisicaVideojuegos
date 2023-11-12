#include "ExplosionForceGenerator.h"

ExplosionForceGenerator::ExplosionForceGenerator(Vector3 Origin, float K, float Radius, float Time) {
	origin = Origin;
	k = K;
	r = Radius;
	time = Time;
}

void ExplosionForceGenerator::updateForce(Particle* particle, double t){
	if (fabs(particle->getInvMass()) < 1e-10) return; // Comprueba si la particula tiene masa

	float distance = (particle->getPos() - origin).magnitude(); // Distancia del radio a la partícula
	if (distance < r) { // Comprueba si está dentro del radio de explosión
		float intensity = k / (r * r); // Intensidad
		float T = exp(-t / time); // Exp

		Vector3 explosionForce = intensity * (particle->getPos() - origin) * T;
		particle->addForce(explosionForce);
	}
}