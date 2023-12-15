#include "RBSystem.h"
#include "SceneManager.h"

RBSystem::RBSystem(SceneManager* SM) {
	sMngr = SM;
	scene = sMngr->getScene();
	physics = sMngr->getPhysics();

	numRB = 0;

	forceRegistry = RigidBodyForceRegistry();
}

void RBSystem::update(double t) {
	//Generar
	for (RigidBodyGenerator* g : rbGenerators) { //Generadores de partículas
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
	Vector3 pos = sMngr->getCamera()->getEye() + sMngr->getCamera()->getDir() * 50;
	Vector3 perpendicular = Vector3(0, 1, 0).cross(sMngr->getCamera()->getDir());
	switch (T) {
	case g_sphere: {
		RigidBody* model = new RigidBody(scene, physics, Vector3(0, -500, 0), Vector3(-10, 0, 0), Vector3(0, 0, 0), 1, 20, s_sphere, Vector4(1, 0, 1, 1));
		rbGenerators.push_back(new RigidBodyGenerator(scene, physics, model, pos, perpendicular * 20, 1, 0.7));
		break;
	}
	case g_cube: {
		RigidBody* model = new RigidBody(scene, physics, Vector3(0, -500, 0), Vector3(-10, 0, 0), Vector3(0, 0, 0), 10, 20, s_cube, Vector4(1, 1, 0, 1));
		rbGenerators.push_back(new RigidBodyGenerator(scene, physics, model, pos, Vector3(0, 0, 0), 1, 0.7));
		break;
	}
	case g_capsule: {
		RigidBody* model = new RigidBody(scene, physics, Vector3(0, -500, 0), Vector3(-10, 0, 0), Vector3(0, 0, 0), 3, 20, s_capsule, Vector4(0, 1, 0, 1));
		rbGenerators.push_back(new RigidBodyGenerator(scene, physics, model, pos, Vector3(0, 0, 0), 1, 0.7));
		break;
	}
	}
}

void RBSystem::shootRB() {
	Vector3 pos = sMngr->getCamera()->getEye() + sMngr->getCamera()->getDir();
	Vector3 dir = sMngr->getCamera()->getDir() * 30;

	RigidBody* model = new RigidBody(scene, physics, pos, dir, Vector3(0, 0, 0), 1, 20, s_sphere, Vector4(1, 0, 0, 1));

	for (auto fg : forceGenerators) // Añade las particulas al registro de fuerzas 
		forceRegistry.addRegistry(fg, model);
	rbs.push_back(model);

	numRB++;
}
