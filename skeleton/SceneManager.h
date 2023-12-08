#pragma once
#include <vector>
#include <list>
#include "Particle.h"
#include "ParticleSystem.h"
#include "RBSystem.h"
#include "core.hpp"

using namespace std;

class SceneManager{
private:
	Camera* camera;
	PxScene* scene;
	PxPhysics* physics;
	
	ParticleSystem* particleSys;
	RBSystem* rbSys;

public:
	SceneManager(PxScene* Scene, PxPhysics* Physics);
	~SceneManager();
	void update(double t);

	Camera* getCamera() { return camera; }
	ParticleSystem* getParticleSys() { return particleSys; }
};