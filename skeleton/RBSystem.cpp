#include "RBSystem.h"

RBSystem::RBSystem(PxScene* Scene, PxPhysics* Physics) {
	scene = Scene;
	physics = Physics;

	numRB = 0;

	RigidBody* model = new RigidBody(scene, physics, Vector3(0, 10, 0), Vector3(-10, 0, 0), Vector3(0, 0, 0), 30, 30, s_cube, Vector4(1, 1, 0, 1));
	rbGenerators.push_back(new RigidBodyGenerator(scene, physics, model, Vector3(0, 20 ,0), Vector3(0, 0, 0), 1, 0.7));
}

void RBSystem::update(double t) {
	//Generar
	for (RigidBodyGenerator* g : rbGenerators) { //Generadores de partículas
		addRBS(g->generateBodies());
		g->update(t);
	}
	
	//forceRegistry.updateForces(t); // Actualiza las fuerzas ejercidas sobre las particulas

	for (RigidBody* rb : rbs) { // Particulas
		if (rb->isAlive() || rb->getPosition().y > -500) { rb->integrate(t); }
		else { 
			//forceRegistry.delete
			delete(rb);
		}
	}
}

void RBSystem::addRBS(list<RigidBody*> lrb) {
	for (RigidBody* r : lrb) {
		if (rbs.size() < MAXRBS) {
			rbs.push_back(r);
			numRB++;
			//for (auto fg : forceGenerators) // Añade las particulas al registro de fuerzas 
			//	forceRegistry.addRegistry(fg, p);
		}
		else {
			delete r;
		}
	}
}