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
	Particle* p = new Particle(GetCamera()->getEye());

	switch (type) {
		case bullet:
			p->setMass(2.0f); // 2.0 Kg
			p->setVelocity(GetCamera()->getDir() * (35.0f)); // 35 m/s
			p->setAcceleration(Vector3(0.0f, -1.0f, 0.0f) * 9.8);
			p->setDamping(0.99f);
			p->setLifeTime(10);
			break;
	case canonBall:

			break;
	case laser:

			break;
	default:
			break;
	}
	proyectiles.push_back(p);
}