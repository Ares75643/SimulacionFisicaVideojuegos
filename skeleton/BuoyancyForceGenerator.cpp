#include "BuoyancyForceGenerator.h"

BuoyancyForceGenerator::BuoyancyForceGenerator(float Height, float Volume, float LiquidDensity) {
	height = Height;
	volume = Volume;
	liquidDensity = LiquidDensity;

	liquidParticle = new Particle(Vector3(0,0,0), Vector3(0,0,0), Vector3(0,0,0));
	liquidParticle->setSize(100);
	liquidParticle->setShape(p_plane);
	liquidParticle->init();
}

BuoyancyForceGenerator::~BuoyancyForceGenerator() {
	delete(liquidParticle);
}

void BuoyancyForceGenerator::updateForce(Particle* particle, double t) {
	if (fabs(particle->getInvMass()) < 1e-10) return;
	else {
		const float h = particle->getPos().y;
		const float h0 = liquidParticle->getPos().y;

		Vector3 BuoyancyForce(0, 0, 0);
		float inmersed = 0.0f;
		if (h - h0 > height * 0.5f) {
			inmersed = 0.0f;
		}
		else if (h0 - h > height * 0.5f) {
			inmersed = 1.0f;
		}
		else {
			inmersed = (h0 - h) / height + 0.5f;
		}

		BuoyancyForce.y = liquidDensity * volume * inmersed * gravity;

		particle->addForce(BuoyancyForce);
	}
}