#pragma once
#include <list>
#include "Particle.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "core.hpp"
class SceneManager;

using namespace std;

enum type{ UNIFORM, GAUSSIAN };
enum ProyectilType { bullet, canonBall, laser };

const Vector3 GRAVITY = Vector3(0.0f, -10.0f, 0.0f);
const int MAXPARTICLES = 2000;

class ParticleSystem {
private:
	int nParticles;
	list<Particle*> particles;
	list<Particle*> particlesToDelete;

	list<ParticleGenerator*> particleGenerators;

	SceneManager* sMngr;

	void deleteUnusedParticles();

public:
	ParticleSystem(SceneManager* SM);
	~ParticleSystem();
	void update(double t);
	void addParticleGenerator(type T);
	void createProyectile(ProyectilType type);
};