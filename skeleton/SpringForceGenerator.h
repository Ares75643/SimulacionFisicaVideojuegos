#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class SpringForceGenerator : public ForceGenerator {
protected:
	double k;
	double restingLength;
	Particle* other;
public:
	SpringForceGenerator(double K, double RestingLength, Particle* Other);
	~SpringForceGenerator(){}
	void updateForce(Particle* particle, double t);

	Particle* getOther() { return other; }
	double getK() { return k; }

	inline void setK(double K) { k = K; }
	inline void addK(double K) { k += K; }
};