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
	delete(rbSys);
}

void SceneManager::update(double t) {
	if (alive) {
		particleSys->update(t);
		rbSys->update(t);

		timeAlive += t;
		if (timeAlive >= phase * TIMEBETWEENPHASES) {
			phase++;
			particleSys->celebrationFireworks();
		}
	}

	cout << "LifeTime: " << timeAlive << " Phase: " << phase << " Lifes: " << lifes << endl;
}

void SceneManager::StartGame() {
	// Set Player Position
	camera->setEye(Vector3(0, 1.5, -2));
	camera->setDir(Vector3(0, 0, -1));

	// Initial Parameters
	alive = true;
	timeAlive = 0;
	phase = 1;
	lifes = 3;

	// First Obstacles
	rbSys->createGenerators(g_sphere);
	rbSys->createGenerators(g_capsule);
	rbSys->createGenerators(g_cube);
}

void SceneManager::Damage() {
	--lifes;
	if (lifes <= 0) {
		EndGame();
	}
	else {
		rbSys->clearRBS();
		particleSys->hurtParticles();
	}
}

void SceneManager::EndGame() {
	// Set Player Position
	camera->setEye(Vector3(0, 1.5, -2));
	camera->setDir(Vector3(0, 0, -1));

	// Update Parameters
	alive = false;

	// Clear Scene
	rbSys->clear();
	particleSys->clear();
}