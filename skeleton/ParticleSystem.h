#pragma once
#include <list>
#include "Particle.h"
#include "Firework.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "ParticleForceRegistry.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "core.hpp"
#include <iostream>
#include <map>
class SceneManager;

using namespace std;

enum ParticleGeneratorType{ UNIFORM, GAUSSIAN, SNOW };
enum ProyectilType { bullet, canonBall, laser, firework };

const Vector3 GRAVITY = Vector3(0.0f, -10.0f, 0.0f);
const int MAXPARTICLES = 3000;

class ParticleSystem {
private:
	int nParticles;
	list<Particle*> particles;
	list<Particle*> particlesToDelete;
	ParticleForceRegistry forceRegistry;

	list<ParticleGenerator*> particleGenerators;
	list<ForceGenerator*> forceGenerators;

	SceneManager* sMngr;

public:
	ParticleSystem(SceneManager* SM);
	~ParticleSystem();
	void clear();
	void deleteUnusedParticles();
	void update(double t);
	void addParticleGenerator(ParticleGeneratorType T);
	void addParticles(list<Particle*> ptcls);
	void createProyectile(ProyectilType T);

	void addGravity() {
		Vector3 V = Vector3(-10, 0, 0);
		WindForceGenerator* g = new WindForceGenerator(V);
		forceGenerators.push_back(g);
		for (auto p : particles)
			forceRegistry.addRegistry(g, p);
	}
};