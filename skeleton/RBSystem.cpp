#include "RBSystem.h"
#include "SceneManager.h"

RBSystem::RBSystem(SceneManager* SM) {
	sMngr = SM;
	scene = sMngr->getScene();
	physics = sMngr->getPhysics();

	numRB = 0;

	forceRegistry = RigidBodyForceRegistry();
}

RBSystem::~RBSystem() {
	clear();
}

void RBSystem::clear() {
	clearRBS();
	rbGenerators.clear();
	forceGenerators.clear();
	forceRegistry.clear();
}

void RBSystem::clearRBS() {
	for (RigidBody* r : rbs)
		rbsToDelete.push_back(r);
	deleteUnusedRB();
}

void RBSystem::update(double t) {
	for (RigidBodyGenerator* g : rbGenerators) { // Generadores de partículas
		addRBS(g->generateBodies());
		g->update(t);
	}
	
	forceRegistry.updateForces(t); // Actualiza las fuerzas ejercidas sobre los RB

	for (RigidBody* rb : rbs) { // RB
		if (rb->isAlive()) { rb->integrate(t); }
		else { rbsToDelete.push_back(rb); }
	}

	deleteUnusedRB();
}

void RBSystem::deleteUnusedRB() {
	for (auto it = rbsToDelete.begin(); it != rbsToDelete.end();) {
		forceRegistry.deleteRigidBodyRegistry(*it);
		rbs.remove(*it);
		delete(*it);
		it = rbsToDelete.erase(it);
		numRB--;
	}
}

void RBSystem::addRBS(list<RigidBody*> lrb) {
	for (RigidBody* r : lrb) {
		if (rbs.size() < MAXRBS) {
			rbs.push_back(r);
			numRB++;
			for (auto fg : forceGenerators) // Añade las particulas al registro de fuerzas 
				forceRegistry.addRegistry(fg, r);
		}
		else {
			delete r;
		}
	}
}

void RBSystem::createGenerators(GeneratorType T) {
	Vector3 pos = Vector3(0, 2, -98);
	switch (T) {
	case g_sphere: {
		RigidBody* model = new RigidBody(scene, physics, Vector3(0, -500, 0), Vector3(-10, 0, 0), Vector3(0, 0, 0), 1, 20, s_sphere, Vector4(0.5, 0, 0.5, 1));
		RigidBodyGenerator* rb = new RigidBodyGenerator(scene, physics, model, pos, Vector3(0, 0, 0), 1, 3);
		rb->setVar(1); rb->setMedian(0);
		rbGenerators.push_back(rb);
		break;
	}
	case g_cube: {
		RigidBody* model = new RigidBody(scene, physics, Vector3(0, -500, 0), Vector3(-10, 0, 0), Vector3(0, 0, 0), 10, 20, s_cube, Vector4(0, 0.5, 0, 1));
		RigidBodyGenerator* rb = new RigidBodyGenerator(scene, physics, model, pos, Vector3(0, 0, 0), 1, 7);
		rb->setVar(1); rb->setMedian(0);
		rbGenerators.push_back(rb);
		break;
	}
	case g_capsule: {
		RigidBody* model = new RigidBody(scene, physics, Vector3(0, -500, 0), Vector3(-10, 0, 0), Vector3(0, 0, 0), 3, 20, s_capsule, Vector4(0.1, 0, 0.5, 1));
		RigidBodyGenerator* rb = new RigidBodyGenerator(scene, physics, model, pos, Vector3(0, 0, 0), 1, 6);
		rb->setVar(1); rb->setMedian(0);
		rbGenerators.push_back(rb);
		break;
	}
	}
}

void RBSystem::shootRB() {
	Vector3 pos = sMngr->getCamera()->getEye() + sMngr->getCamera()->getDir();
	Vector3 dir = sMngr->getCamera()->getDir() * 30;

	RigidBody* model = new RigidBody(scene, physics, pos, dir, Vector3(0, 0, 0), 1, 20, s_sphere, Vector4(1, 0, 0, 1));
	model->setName("bulletN");

	for (auto fg : forceGenerators) // Añade las particulas al registro de fuerzas 
		forceRegistry.addRegistry(fg, model);
	rbs.push_back(model);

	numRB++;
}

void RBSystem::activateWind() {
	WindForceGenerator* wind = new WindForceGenerator(Vector3(0, 0, -10), 0.25, 0.1);
	for (auto r : rbs)
		forceRegistry.addRegistry(wind, r);
}