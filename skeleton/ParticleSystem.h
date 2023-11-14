#pragma once
#include <list>
#include "Particle.h"
#include "Firework.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "ParticleForceRegistry.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "TornadoForceGenerator.h"
#include "ExplosionForceGenerator.h"
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
		GravityForceGenerator* g = new GravityForceGenerator(Vector3(0, 9.8, 0));
		for (auto p : particles)
			forceRegistry.addRegistry(g, p);
	}
	void addWind() {
		WindForceGenerator* wind = new WindForceGenerator(Vector3(-60, 0, 0), 0.25, 0.1);
		for (auto p : particles)
			forceRegistry.addRegistry(wind, p);
	}
	void addTornado() {
		TornadoForceGenerator* t = new TornadoForceGenerator(Vector3(0,0,0),Vector3(-60, 0, 0), 2, 0.25, 0.1);
		for (auto p : particles)
			forceRegistry.addRegistry(t, p);
	}
	void addExplosion() {
		ExplosionForceGenerator* megumin = new ExplosionForceGenerator(Vector3(0, 0, 0));
			for (auto p : particles)
				forceRegistry.addRegistry(megumin, p);
	}

	void explosionParticles();
};