#pragma once
#include "core.hpp"
#include <vector>
#include <list>
#include "RigidBody.h"
#include "RigidBodyGenerator.h"
#include "RigidBodyForceRegistry.h"
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
};

// aplicar alguna fuerxa a sr