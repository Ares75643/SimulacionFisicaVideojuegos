#include "ParticleForceRegistry.h"

ParticleForceRegistry::ParticleForceRegistry() {

}

ParticleForceRegistry::~ParticleForceRegistry() {
	clear();
}

void ParticleForceRegistry::clear() {
	registry.clear();
}

void ParticleForceRegistry::addRegistry(ForceGenerator* f, Particle* p) {
	registry.insert({ f, p });
}

void ParticleForceRegistry::deleteParticleRegistry(Particle* p) {
	for (auto it = registry.begin(); it != registry.end(); ) {
		if (it->second == p) { it = registry.erase(it); }
		else { it++; }
	}
}

void ParticleForceRegistry::deleteForceRegistry(ForceGenerator* f) {
	for (auto it = registry.begin(); it != registry.end(); ) {
		if (it->first == f) { it = registry.erase(it); }
		else { it++; }
	}
}

void ParticleForceRegistry::updateForces(double t) {
	for (auto fp : registry) {
		fp.first->updateForce(fp.second, t);
	}
}