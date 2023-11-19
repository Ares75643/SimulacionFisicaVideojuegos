#pragma once
#include "SpringForceGenerator.h"
class StaticSpringForceGenerator : public SpringForceGenerator {
public:
	StaticSpringForceGenerator(double K, double RestingLength, const Vector3& AnchorPos);
	~StaticSpringForceGenerator();
};