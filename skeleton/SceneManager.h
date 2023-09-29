#pragma once
#include <vector>
#include "Particle.h"
#include "core.hpp"

using namespace std;

enum ProyectilType { bullet, canonBall, laser };

class SceneManager{
private:
	Camera* camera;
	vector<Particle*> proyectiles;
public:
	SceneManager();
	~SceneManager();
	void update(double t);

	void createProyectile(ProyectilType type);
};