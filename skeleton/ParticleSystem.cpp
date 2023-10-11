#include "ParticleSystem.h"
#include "SceneManager.h"

ParticleSystem::ParticleSystem(SceneManager* SM) {
	sMngr = SM;
	nParticles = 0;
}

ParticleSystem::~ParticleSystem() {

}

void ParticleSystem::update(double t) {
	//Generadores de partículas
	for (list<ParticleGenerator*>::iterator it = particleGenerators.begin(); it != particleGenerators.end(); it++) {
		for (auto p : (*it)->generateParticles()) {
			particles.push_back(p);
		}
		(*it)->updateTime(t);
	}

	//Particulas
	for (list<Particle*>::iterator it = particles.begin(); it != particles.end(); ++it) {
		if ((*it)->isAlive())
			(*it)->integrate(t);
		else
			particlesToDelete.push_back((*it));
	}
	deleteUnusedParticles();
}

void ParticleSystem::deleteUnusedParticles() {
	for (auto it = particlesToDelete.begin(); it != particlesToDelete.end();) {
		particles.remove(*it);
		delete(*it);
		++it;
		particlesToDelete.pop_front();
	}
}

void ParticleSystem::addParticleGenerator(type T) {
	switch (T) {
	case UNIFORM:
		//particleGenerators.push_back(new UniformParticleGenerator());
		break;

	case GAUSSIAN:
		Particle* p = new Particle(sMngr->getCamera()->getEye(), sMngr->getCamera()->getDir(), Vector3(0, -9.8, 0));

					p->setMass(2.0f);
					p->setSpeed(60.0f);
					p->setDamping(0.99f);
					p->setLifeTime(30);
					p->setSize(2);

		particleGenerators.push_back(new GaussianParticleGenerator("Hola", sMngr->getCamera()->getEye() + Vector3(0, 0, 50), Vector3(0,0,0), p, 5, 1000, 0.99, 0.2));
		break;
	}
}

void ParticleSystem::createProyectile(ProyectilType type) {
	if (particles.size() < MAXPARTICLES) {
		Particle* p = new Particle(sMngr->getCamera()->getEye(), sMngr->getCamera()->getDir(), Vector3(0, -9.8, 0));

		switch (type) {
		case bullet:
			p->setMass(2.0f);
			p->setSpeed(60.0f);
			p->setDamping(0.99f);
			p->setLifeTime(30);
			p->setSize(2);
			break;

		case canonBall:
			p->setMass(200.0f); // 200.0 Kg
			p->setSpeed(80.0f);
			p->setAcceleration(Vector3(0.0f, -25.0f, 0.0f));
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
		particles.push_back(p);

		nParticles++;
	}
}