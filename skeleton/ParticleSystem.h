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
		GravityForceGenerator* g = new GravityForceGenerator(Vector3(0, -9.8, 0));
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
				SF->addK(50);
			}
		}
	}
	void subKToAllSprings() {
		for (auto FG : forceRegistry.getRegistry()) {
			SpringForceGenerator* SF = static_cast<SpringForceGenerator*>(FG.first);
			if (SF != nullptr) {
				if (SF->getK() -10 > 0) SF->addK(-10);
			}
		}
	}
	void activateBuoyancy(){
		BuoyancyForceGenerator* water = new BuoyancyForceGenerator(6, 20, 1);
		Particle* p = new Particle(Vector3(0, 20, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 1);
		p->setMass(1);
		p->setShape(p_cube);
		p->setLifeTime(1000);
		p->setColor(Vector4(1, 0, 0, 1));
		p->init();

		Particle* p1 = new Particle(Vector3(10, 20, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 1);
		p1->setMass(20);
		p1->setShape(p_cube);
		p1->setLifeTime(1000);
		p1->setColor(Vector4(1, 1, 0, 1));
		p1->init();

		Particle* p2 = new Particle(Vector3(20, 10, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 1);
		p2->setMass(2);
		p2->setShape(p_cube);
		p2->setLifeTime(1000);
		p2->setColor(Vector4(0, 1, 0, 1));
		p2->init();

		Particle* p3 = new Particle(Vector3(30, 10, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 1);
		p3->setMass(12);
		p3->setSize(4);
		p3->setShape(p_cube);
		p3->setLifeTime(1000);
		p3->setColor(Vector4(0, 1, 1, 1));
		p3->init();

		nParticles+=4;

		particles.push_back(p);
		particles.push_back(p1);
		particles.push_back(p2);
		particles.push_back(p3);
		forceGenerators.push_back(water);

		buoyancyTest = p2;

		for (auto fg : forceGenerators) { // Añade las particulas al registro de fuerzas 
			forceRegistry.addRegistry(fg, p);
			forceRegistry.addRegistry(fg, p1);
			forceRegistry.addRegistry(fg, p2);
			forceRegistry.addRegistry(fg, p3);
		}
	}

	private:
		Particle* buoyancyTest = nullptr;

		public:
		void addTestMass(int M) { 
			if (buoyancyTest != nullptr) {
				if (buoyancyTest->getMass() + M > 0) {
					buoyancyTest->setMass(buoyancyTest->getMass() + M);
					cout << buoyancyTest->getMass() << endl;
				}
			}
		}

};