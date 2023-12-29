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
		r->setAlive(false);
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
		scene->removeActor((*(*it)->getRigidDynamic()));
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
	Vector3 pos = Vector3(0, 2, -96);
	switch (T) {
	case g_sphere: {
		RigidBody* model = new RigidBody(scene, physics, Vector3(0, -500, 0), Vector3(-10, 0, 0), Vector3(0, 0, 0), 1, 40, s_sphere, Vector4(0.5, 0, 0.5, 1));
		RigidBodyGenerator* rb = new RigidBodyGenerator(scene, physics, model, pos, Vector3(0, 0, 0), 1, 3);
		rb->setVar(1); rb->setMedian(0);
		rbGenerators.push_back(rb);
		break;
	}
	case g_cube: {
		RigidBody* model = new RigidBody(scene, physics, Vector3(0, -500, 0), Vector3(-10, 0, 0), Vector3(0, 0, 0), 10, 40, s_cube, Vector4(0, 1, 1, 1));
		RigidBodyGenerator* rb = new RigidBodyGenerator(scene, physics, model, pos, Vector3(0, 0, 0), 1, 7);
		rb->setVar(1); rb->setMedian(0);
		rbGenerators.push_back(rb);
		break;
	}
	case g_capsule: {
		RigidBody* model = new RigidBody(scene, physics, Vector3(0, -500, 0), Vector3(-10, 0, 0), Vector3(0, 0, 0), 3, 40, s_capsule, Vector4(1, 1, 0, 1));
		RigidBodyGenerator* rb = new RigidBodyGenerator(scene, physics, model, pos, Vector3(0, 0, 0), 1, 6);
		rb->setVar(1); rb->setMedian(0);
		rbGenerators.push_back(rb);
		break;
	}
	}
}

void RBSystem::shootRB(BulletType T) {
	Vector3 pos = sMngr->getCamera()->getEye() + sMngr->getCamera()->getDir();
	Vector3 dir = sMngr->getCamera()->getDir() * 30;

	RigidBody* model;
	
	if (T == b_normal) {
		model = new RigidBody(scene, physics, pos, dir, Vector3(0, 0, 0), 1, 20, s_sphere);
		model->setName("bulletN");
		model->setColor(Vector4(1, 1, 0, 0));
	}
	else if (T == b_sgravity) {
		model = new RigidBody(scene, physics, pos, dir, Vector3(0, 0, 0), 1, 20, s_minisphere);
		model->setName("bulletSG");
		model->setColor(Vector4(0, 0, 0.5, 0));
	}
	else if (T == b_ugravity) {
		model = new RigidBody(scene, physics, pos, dir, Vector3(0, 0, 0), 1, 20, s_minisphere);
		model->setName("bulletUG");
		model->setColor(Vector4(0.4, 0, 0.4, 0));
	}
	else if (T == b_freeze) {
		model = new RigidBody(scene, physics, pos, dir, Vector3(0, 0, 0), 1, 20, s_minisphere);
		model->setName("bulletF");
		model->setColor(Vector4(0, 0, 0, 0));
	}

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

void RBSystem::superGravity(PxActor* obj) {
	GravityForceGenerator* g = new GravityForceGenerator(Vector3(0, -30, 0));
	RigidBody* r = getRigidBody(obj);
	if (r != nullptr) forceRegistry.addRegistry(g, r);
}

void RBSystem::inverseGravity(PxActor* obj) {
	GravityForceGenerator* g = new GravityForceGenerator(Vector3(0, 30, 0));
	RigidBody* r = getRigidBody(obj);
	if(r != nullptr) forceRegistry.addRegistry(g, r);
}

void RBSystem::freeze(PxActor* obj) {
	RigidBody* r = getRigidBody(obj);
	if (r != nullptr) {
		r->getRigidDynamic()->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
		r->getRigidDynamic()->setLinearVelocity(PxVec3(0.0f, 0.0f, 0.0f));
		r->getRigidDynamic()->setAngularVelocity(PxVec3(0.0f, 0.0f, 0.0f));
	}
}
