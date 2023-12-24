#pragma once
#include "core.hpp"
#include <vector>
#include <list>
#include "RigidBody.h"
#include "RigidBodyGenerator.h"
#include "RigidBodyForceRegistry.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "TornadoForceGenerator.h"
#include "ExplosionForceGenerator.h"
class SceneManager;

using namespace std;

const int MAXRBS = 1000;

enum BulletType { b_normal, b_sgravity, b_ugravity, b_freeze};
enum GeneratorType {g_sphere, g_capsule, g_cube};

class RBSystem {
protected:
	PxScene* scene;
	PxPhysics* physics;
	SceneManager* sMngr;

	int numRB;
	list<RigidBody*> rbs;
	list<RigidBody*> rbsToDelete;
	vector<RigidBodyGenerator*> rbGenerators;

	RigidBodyForceRegistry forceRegistry;
	list<ForceGenerator*> forceGenerators;

public:
	RBSystem(SceneManager* SM);
	~RBSystem();
	void clear();
	void clearRBS();
	void update(double t);
	void deleteUnusedRB();
	void addRBS(list<RigidBody*> lrb);

	void createGenerators(GeneratorType T);
	void shootRB(BulletType T);

	void activateWind();

	void superGravity(PxActor* obj);
	void inverseGravity(PxActor* obj);

	void freeze(PxActor* obj);

	void addGravity() {
		GravityForceGenerator* g = new GravityForceGenerator(Vector3(0, 20, 0));
		for (auto rb : rbs)
			forceRegistry.addRegistry(g, rb);
	}
	void addWind() {
		WindForceGenerator* wind = new WindForceGenerator(Vector3(-60, 0, 0), 0.25, 0.1);
		for (auto rb : rbs)
			forceRegistry.addRegistry(wind, rb);
	}
	void addTornado() {
		TornadoForceGenerator* t = new TornadoForceGenerator(Vector3(0, 0, 0), Vector3(-60, 0, 0), 2, 0.25, 0.1);
		for (auto rb : rbs)
			forceRegistry.addRegistry(t, rb);
	}
	void addExplosion(Vector3 Pos = Vector3(0, 0, 0)) {
		ExplosionForceGenerator* megumin = new ExplosionForceGenerator(Pos, 50, 10, 0.005);
		for (auto rb : rbs)
			forceRegistry.addRegistry(megumin, rb);
	}

	void destroyRigidBody(PxActor* obj) {
		PxActor* act;
		RigidBody* p = nullptr;

		auto i = rbs.begin();

		while (p == nullptr && i != rbs.end()) {
			act = (*i)->getRigidDynamic();

			if (obj == act) {
				p = (*i);
				(*i)->setAlive(false);
			}

			else ++i;
		}
	}

	RigidBody* getRigidBody(PxActor* obj) {
		PxActor* act;
		RigidBody* p = nullptr;

		auto i = rbs.begin();

		while (i != rbs.end()) {
			act = (*i)->getRigidDynamic();

			if (obj == act) {
				return (*i);
			}
			else ++i;
		}
		return nullptr;
	}
};