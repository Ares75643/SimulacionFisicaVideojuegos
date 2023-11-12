#include "WindForceGenerator.h"
WindForceGenerator::WindForceGenerator(const Vector3& W, const float K1, const float K2){
    windVelocity = W;
    k1 = K1;
    k2 = K2;
}

void WindForceGenerator::updateForce(Particle* particle, double t) {
    if (fabs(particle->getInvMass()) < 1e-10) return;
    
    Vector3 v = particle->getVelocity() - windVelocity; 
    float windCoef = v.normalize();
    windCoef = k1 * windCoef + k2 * windCoef * windCoef;
    Vector3 windForce = -v * windCoef;

    particle->addForce(windForce);

    // V1
    //Vector3 v = particle->getVelocity();
    //Vector3 windForce = k1 * (windVelocity - v);
    //particle->addForce(windForce);
}