#pragma once
#include <list>
#include "Particle.h"
#include "Firework.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "core.hpp"
#include <iostream>
class SceneManager;

using namespace std;

enum type{ UNIFORM, GAUSSIAN, SNOW };
enum ProyectilType { bullet, canonBall, laser, firework };

const Vector3 GRAVITY = Vector3(0.0f, -10.0f, 0.0f);
const int MAXPARTICLES = 3000;

class ParticleSystem {
private:
	int nParticles;
	list<Particle*> particles;
	list<Particle*> particlesToDelete;

	list<ParticleGenerator*> particleGenerators;

	SceneManager* sMngr;


public:
	ParticleSystem(SceneManager* SM);
	~ParticleSystem();
	void clear();
	void deleteUnusedParticles();
	void update(double t);
	void addParticleGenerator(type T);
	void addParticles(list<Particle*> ptcls);
	void createProyectile(ProyectilType type);
};