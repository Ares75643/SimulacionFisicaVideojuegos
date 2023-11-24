#pragma once
#include <map>
#include "Particle.h"
#include "ForceGenerator.h"

using namespace std;

class ParticleForceRegistry {
private:
	multimap<ForceGenerator*, Particle*> registry;

public:
	ParticleForceRegistry();
	~ParticleForceRegistry();
	void clear();
	void addRegistry(ForceGenerator* f, Particle* p);
	void deleteParticleRegistry(Particle* p);
	void deleteForceRegistry(ForceGenerator* f);
	void updateForces(double t);
	multimap<ForceGenerator*, Particle*> const & getRegistry() { return registry; }
};