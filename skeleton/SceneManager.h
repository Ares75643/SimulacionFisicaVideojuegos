#pragma once
#include <vector>
#include <list>
#include "Particle.h"
#include "ParticleSystem.h"
#include "core.hpp"

using namespace std;

class SceneManager{
private:
	Camera* camera;
	
	ParticleSystem* particleSys;

public:
	SceneManager();
	~SceneManager();
	void update(double t);

	Camera* getCamera() { return camera; }
	ParticleSystem* getParticleSys() { return particleSys; }
};