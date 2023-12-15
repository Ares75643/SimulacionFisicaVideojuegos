#include "SceneManager.h"

SceneManager::SceneManager(PxScene* Scene, PxPhysics* Physics) {
	camera = GetCamera();
	scene = Scene;
	physics = Physics;

	particleSys = new ParticleSystem(this);
	rbSys = new RBSystem(this);
}

SceneManager::~SceneManager() {
	delete(particleSys);
}

void SceneManager::update(double t) {
	particleSys->update(t);
	rbSys->update(t);
}

void SceneManager::StartGame() {
	camera->setEye(Vector3(0, 1.5, 0));
	camera->setDir(Vector3(0, 0, -1));
}
