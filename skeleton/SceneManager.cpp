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
	particleSys->update(t);
	rbSys->update(t);

	if (alive) {
		timeAlive += t;
		if (timeAlive >= phase * TIMEBETWEENPHASES) {
			phase++;
			particleSys->celebrationFireworks();
		}
	}

	for (int i = 0; i < NEVENTS; ++i)
		events[i].timeUntilActivation -= t;

	cout << "LifeTime: " << timeAlive << " Phase: " << phase << " Lifes: " << lifes << endl;
	//cout << "NBullet: " << events[_nShot].timeUntilActivation << " UGBullet: " << events[_ugShot].timeUntilActivation << " SGBullet: " << events[_sgShot].timeUntilActivation << endl;
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
	if (--lifes <= 0) {
		EndGame();
	}
	else {
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

void SceneManager::activateEvent(EventType e) {
	if (isEventAvaliable(e)) {
		switch (e) {
		case _wind:
			rbSys->activateWind();
			break;
		case _nShot:
			rbSys->shootRB(b_normal);
			break;
		case _sgShot:
			rbSys->shootRB(b_sgravity);
			break;
		case _ugShot:
			rbSys->shootRB(b_ugravity);
			break;
		case _fShot:
			rbSys->shootRB(b_freeze);
			break;
		}
		events[e].timeUntilActivation = events[e].delayTime;
	}
}
