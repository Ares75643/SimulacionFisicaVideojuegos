#pragma once
#include <list>
#include <random>
#include <iostream>
#include "RigidBody.h"

using namespace std;

class RigidBodyGenerator {
private:
	PxScene* scene; 
	PxPhysics* physics;

	int nGen;
	Vector3 pos, vel;
	RigidBody* model;
	float var = 1, median = 0;

	float frecuency;
	float timeUntilNextGeneration;

	bool active;

public:
	RigidBodyGenerator(PxScene* Scene, PxPhysics* Physics, RigidBody* rb, Vector3 Pos, Vector3 Vel = Vector3(0,0,0), int numGen = 1, float Frecuency = 0.2);
	void update(float t);
	std::list<RigidBody*> generateBodies();

	void setModel(RigidBody* rb) { model = rb; };
	void setVar(float V) { var = V; }
	void setMedian(float M) { median = M; }

	float getVar() { return var; }
	float getMedian() { return median; }
};