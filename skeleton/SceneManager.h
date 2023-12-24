#pragma once
#include <vector>
#include <list>
#include "Particle.h"
#include "ParticleSystem.h"
#include "RBSystem.h"
#include "core.hpp"

using namespace std;

const int NEVENTS = 5;
enum EventType { _nShot, _ugShot, _sgShot, _fShot, _wind };

typedef struct {
	double timeUntilActivation;
	double delayTime;
}Event;

class SceneManager{
private:
	Camera* camera;
	PxScene* scene;
	PxPhysics* physics;
	
	ParticleSystem* particleSys;
	RBSystem* rbSys;

	int lifes;

	bool alive;
	double timeAlive;

	const double TIMEBETWEENPHASES = 5; // Segundos entre fases (TREINTA ESTÁ BIEN)
	int phase;

	Event events[NEVENTS] = {
		{0, 0.5},
		{0, 2},
		{0, 2},
		{5, 8},
		{5, 10}
	};

public:
	SceneManager(PxScene* Scene, PxPhysics* Physics);
	~SceneManager();
	void update(double t);

	Camera* getCamera() { return camera; }
	PxScene* getScene() { return scene; }
	PxPhysics* getPhysics() { return physics; }

	ParticleSystem* getParticleSys() { return particleSys; }
	RBSystem* getRBSys() { return rbSys; }

	bool isAlive() { return alive; }

	void StartGame();
	void Damage();
	void EndGame();

	bool isEventAvaliable(EventType e) { return events[e].timeUntilActivation <= 0; }
	void activateEvent(EventType e);
};