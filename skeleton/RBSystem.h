#pragma once
#include "core.hpp"
#include <vector>
#include <list>
#include "RigidBody.h"
#include "RigidBodyGenerator.h"
#include "RigidBodyForceRegistry.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "TornadoForceGenerator.h"
#include "ExplosionForceGenerator.h"
class SceneManager;

using namespace std;

const int MAXRBS = 1000;

enum GeneratorType {g_sphere, g_capsule, g_cube};

class RBSystem {
protected:
	PxScene* scene;
	PxPhysics* physics;
	SceneManager* sMngr;

	int numRB;
	list<RigidBody*> rbs;
	list<RigidBody*> rbsToDelete;
	vector<RigidBodyGenerator*> rbGenerators;

	RigidBodyForceRegistry forceRegistry;
	list<ForceGenerator*> forceGenerators;

public:
	RBSystem(SceneManager* SM);
	void update(double t);
	void deleteUnusedRB();
	void addRBS(list<RigidBody*> lrb);

	void createGenerators(GeneratorType T);
	void shootRB();

	void addGravity() {
		GravityForceGenerator* g = new GravityForceGenerator(Vector3(0, 20, 0));
		for (auto rb : rbs)
			forceRegistry.addRegistry(g, rb);
	}
	void addWind() {
		WindForceGenerator* wind = new WindForceGenerator(Vector3(-60, 0, 0), 0.25, 0.1);
		for (auto rb : rbs)
			forceRegistry.addRegistry(wind, rb);
	}
	void addTornado() {
		TornadoForceGenerator* t = new TornadoForceGenerator(Vector3(0, 0, 0), Vector3(-60, 0, 0), 2, 0.25, 0.1);
		for (auto rb : rbs)
			forceRegistry.addRegistry(t, rb);
	}
	void addExplosion() {
		ExplosionForceGenerator* megumin = new ExplosionForceGenerator(Vector3(0, 0, 0));
		for (auto rb : rbs)
			forceRegistry.addRegistry(megumin, rb);
	}
};

// aplicar alguna fuerxa a sr