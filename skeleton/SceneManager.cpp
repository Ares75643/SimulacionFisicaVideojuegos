#include "SceneManager.h"

SceneManager::SceneManager(PxScene* Scene, PxPhysics* Physics) {
	camera = GetCamera();
	scene = Scene;
	physics = Physics;

	particleSys = new ParticleSystem(this);
	rbSys = new RBSystem(scene, physics);
}

SceneManager::~SceneManager() {
	delete(particleSys);
}

void SceneManager::update(double t) {
	particleSys->update(t);
	rbSys->update(t);
}