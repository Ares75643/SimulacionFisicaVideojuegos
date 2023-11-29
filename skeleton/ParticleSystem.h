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
#include "SpringForceGenerator.h"
#include "StaticSpringForceGenerator.h"
#include "BuoyancyForceGenerator.h"
#include "core.hpp"
#include <iostream>
#include <map>
class SceneManager;

using namespace std;

enum ParticleGeneratorType{ UNIFORM, GAUSSIAN, SNOW };
enum ProyectilType { bullet, canonBall, laser, firework };
enum SpringTipe { S_DEFAULT, S_STATIC, S_SLINKY};

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
		TornadoForceGenerator* t = new TornadoForceGenerator(Vector3(0, 0, 0), Vector3(-60, 0, 0), 2, 0.25, 0.1);
		for (auto p : particles)
			forceRegistry.addRegistry(t, p);
	}
	void addExplosion() {
		ExplosionForceGenerator* megumin = new ExplosionForceGenerator(Vector3(0, 0, 0));
		for (auto p : particles)
			forceRegistry.addRegistry(megumin, p);
	}

	void explosionParticles();

	void addSpring(SpringTipe T);

	void addKToAllSprings() {
		for (auto FG : forceRegistry.getRegistry()) {
			SpringForceGenerator* SF = static_cast<SpringForceGenerator*>(FG.first);
			if (SF != nullptr) {
				SF->addK(100);
			}
		}
	}
	void activateBuoyancy(){
		BuoyancyForceGenerator* water = new BuoyancyForceGenerator(1, 100, 997);
		Particle* p = new Particle(Vector3(0, 10, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 1);
		p->setMass(10);
		p->setShape(p_cube);
		p->setLifeTime(40);
		p->init();

		nParticles++;

		particles.push_back(p);
		forceGenerators.push_back(water);

		for (auto fg : forceGenerators) // Añade las particulas al registro de fuerzas 
			forceRegistry.addRegistry(fg, p);
	}
};