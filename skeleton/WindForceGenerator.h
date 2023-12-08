#pragma once
#include "ForceGenerator.h"
class WindForceGenerator : public ForceGenerator {
protected:
    Vector3 windVelocity;
    float k1, k2; // Coef velocity y velocity cuadrado

public:
    WindForceGenerator(){}
    WindForceGenerator(const Vector3& W, const float K1 = 0.25, const float K2 = 0);
    virtual void updateForce(Particle* particle, double t);
    virtual void updateForce(RigidBody* rb, double t);

    float getK1() { return k1; }
    float getK2() { return k2; }

    inline void setK(float K1, float K2) { k1 = K1; k2 = K2; }
    void setK1(float K) { k1 = K; }
    void setK2(float K) { k2 = K; }
    inline void setWind(const Vector3& W) { windVelocity = W; }
};
