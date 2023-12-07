#pragma once
#include "core.hpp"
#include <vector>
#include <list>

using namespace std;

class RBSystem {
protected:
	//list<RigidBody*> rbs;
	//vector<RigidBodyGenerator*> rbGenerators;
public:
	void update(double t);
};

//rigidBody es un SR pero con lifetime, SISTEMA, GENERADOR, SR generaos a DISTINTAS VELOCIDADES con distintas masas, aplicar alguna fuerxa a sr