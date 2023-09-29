#pragma once
#include <vector>
#include <list>
#include "Particle.h"
#include "core.hpp"

using namespace std;

enum ProyectilType { bullet, canonBall, laser };

class SceneManager{
private:
	Camera* camera;
	list<Particle*> proyectiles;

	list<Particle*> particlesToDelete;

	void deleteUnusedParticles();

public:
	SceneManager();
	~SceneManager();
	void update(double t);

	void createProyectile(ProyectilType type);
};