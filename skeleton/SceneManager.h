#pragma once
#include <vector>
#include <list>
#include "Particle.h"
#include "ParticleSystem.h"
#include "core.hpp"

using namespace std;

enum ProyectilType { bullet, canonBall, laser };

class SceneManager{
private:
	Camera* camera;
	list<Particle*> proyectiles;
	list<Particle*> particlesToDelete;

	ParticleSystem* particleSys;

	int nParticles = 0;
	const int MAXPARTICLES = 200;

	void deleteUnusedParticles();

public:
	SceneManager();
	~SceneManager();
	void update(double t);

	void createProyectile(ProyectilType type);
};