#pragma once
#include "core.hpp"
#include <vector>
#include <list>
#include "RigidBody.h"
#include "RigidBodyGenerator.h"
#include "RigidBodyForceRegistry.h"

using namespace std;

const int MAXRBS = 1000;

class RBSystem {
protected:
	PxScene* scene;
	PxPhysics* physics;

	int numRB;
	list<RigidBody*> rbs;
	list<RigidBody*> rbsToDelete;
	vector<RigidBodyGenerator*> rbGenerators;

	RigidBodyForceRegistry forceRegistry;
	list<ForceGenerator*> forceGenerators;

public:
	RBSystem(PxScene* Scene, PxPhysics* Physics);
	void update(double t);
	void deleteUnusedRB();
	void addRBS(list<RigidBody*> lrb);
};

// SISTEMA, GENERADOR, SR generados a DISTINTAS VELOCIDADES con distintas masas, aplicar alguna fuerxa a sr