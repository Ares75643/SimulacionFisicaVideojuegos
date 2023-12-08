#pragma once
#include "core.hpp"
#include <vector>
#include <list>
#include "RigidBody.h"
#include "RigidBodyGenerator.h"

using namespace std;

const int MAXRBS = 1000;

class RBSystem {
protected:
	PxScene* scene;
	PxPhysics* physics;

	int numRB;
	list<RigidBody*> rbs;
	vector<RigidBodyGenerator*> rbGenerators;


public:
	RBSystem(PxScene* Scene, PxPhysics* Physics);
	void update(double t);
	void addRBS(list<RigidBody*> lrb);
};

// SISTEMA, GENERADOR, SR generaos a DISTINTAS VELOCIDADES con distintas masas, aplicar alguna fuerxa a sr