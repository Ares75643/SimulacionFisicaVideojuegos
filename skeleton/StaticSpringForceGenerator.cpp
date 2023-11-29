#include "StaticSpringForceGenerator.h"

StaticSpringForceGenerator::StaticSpringForceGenerator(double K, double RestingLength, const Vector3& AnchorPos) : SpringForceGenerator(K, RestingLength, nullptr) {
	other = new Particle(AnchorPos, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.5, 1e6, 60.0, 0, Vector4(0, 0, 0, 1));
	other->setShape(p_cube);
	other->init();
}

StaticSpringForceGenerator::~StaticSpringForceGenerator() {
	delete other;
}
