#include "SceneManager.h"

SceneManager::SceneManager() {
	camera = GetCamera();
	particleSys = new ParticleSystem(this);
}

SceneManager::~SceneManager() {
	delete(particleSys);
}

void SceneManager::update(double t) {
	particleSys->update(t);
}