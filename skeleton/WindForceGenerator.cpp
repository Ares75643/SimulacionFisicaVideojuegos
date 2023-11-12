#include "WindForceGenerator.h"
WindForceGenerator::WindForceGenerator(const Vector3& W, const float K1, const float K2){
    windVelocity = W;
    k1 = K1;
    k2 = K2;
}

void WindForceGenerator::updateForce(Particle* particle, double t) {
    if (fabs(particle->getInvMass()) < 1e-10) return;
    
    Vector3 v = particle->getVelocity(); 
    float wCoef = v.normalize();

    wCoef = k1 * wCoef + k2 * wCoef * wCoef;
    Vector3 windForce = -v * wCoef;

    particle->addForce(windForce);
}