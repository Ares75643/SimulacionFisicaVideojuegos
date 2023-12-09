#include "RigidBodyGenerator.h"
default_random_engine generatorRB;

RigidBodyGenerator::RigidBodyGenerator(PxScene* Scene, PxPhysics* Physics, RigidBody* rb, Vector3 Pos, Vector3 Vel, int numGen, float Frecuency) {
	scene = Scene;
	physics = Physics;
	model = rb;
	pos = Pos; vel = Vel;
	nGen = numGen;
	active = true;
	frecuency = Frecuency;
	timeUntilNextGeneration = frecuency;
}

void RigidBodyGenerator::update(float t) {
	timeUntilNextGeneration -= t;
}

list<RigidBody*> RigidBodyGenerator::generateBodies(){
	list<RigidBody*> listRB;
	if (model != nullptr) {
		if (active && timeUntilNextGeneration <= 0) { // Si debe generar (tiempo y activo)
			for (int i = 0; i < nGen; i++) {
				normal_distribution<float> d(median, var); // Se contruye aqui para poder cambiar los parametros

				Vector3 posicion = pos + Vector3(d(generatorRB), d(generatorRB), d(generatorRB));
				Vector3 velocidad = vel + Vector3(d(generatorRB), d(generatorRB), d(generatorRB));

				RigidBody* rb = new RigidBody(scene, physics, posicion, velocidad, Vector3(0, 0, 0), model->getMass(), model->getLifeTime(), model->getShape(), model->getColor());

				listRB.push_back(rb);
			}
			timeUntilNextGeneration = frecuency; // Actualiza el tiempo hasta la generación
		}
	}
	return listRB;
}