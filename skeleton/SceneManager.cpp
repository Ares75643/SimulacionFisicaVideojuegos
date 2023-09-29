#include "SceneManager.h"

SceneManager::SceneManager() {
	camera = GetCamera();
}

SceneManager::~SceneManager() {

}

void SceneManager::update(double t) {
	for (list<Particle*>::iterator it = proyectiles.begin(); it != proyectiles.end(); ++it) {
		(*it)->integrate(t);
		
		if (!(*it)->isAlive()) particlesToDelete.push_back((*it));
	}
	deleteUnusedParticles();
}

void SceneManager::deleteUnusedParticles() {
	for (auto it = particlesToDelete.begin(); it != particlesToDelete.end();) {
		proyectiles.remove(*it);
		delete(*it);
		++it;
		particlesToDelete.pop_front();
	}
}

void SceneManager::createProyectile(ProyectilType type) {
	Particle* p = new Particle(camera->getEye(), camera->getDir(), Vector3(0, -9.8, 0));

	switch (type) {
		case bullet:
			p->setMass(2.0f);
			p->setSpeed(60.0f); 
			p->setDamping(0.99f);
			p->setLifeTime(40);
			p->setSize(2);
			break;

	case canonBall:
			p->setMass(200.0f); // 200.0 Kg
			p->setSpeed(80.0f);
			p->setAcceleration(Vector3(0.0f, -20.0f, 0.0f));
			p->setDamping(0.99f);
			p->setSize(5);
			p->setColor(Vector4(255, 0, 0, 255));
			break;

	case laser:
			p->setMass(0.1f); // almost no weight
			p->setSpeed(100.0f); 
			p->setAcceleration(Vector3(0.0f, 0.0f, 0.0f)); // No gravity
			p->setDamping(0.99f);
			p->setSize(0.2f);
			p->setColor(Vector4(0, 255, 255, 100));
			break;

	default:
			break;
	}
	p->init();
	proyectiles.push_back(p);
}