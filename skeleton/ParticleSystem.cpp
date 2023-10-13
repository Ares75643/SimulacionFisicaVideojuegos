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
	for (ParticleGenerator* g : particleGenerators) {
		for (auto p : g->generateParticles()) {
			particles.push_back(p);
		}
		g->update(t);
	}

	//Particulas
	for (Particle* p : particles) {
		if (p->isAlive())
			p->integrate(t);
		else
			particlesToDelete.push_back(p);
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
		p->setLifeTime(10);
		p->setSize(2);
		p->setColor(Vector4(0, 30, 190, 255));

		Vector3 perpendicular = Vector3(0, 1, 0).cross(sMngr->getCamera()->getDir());
		particleGenerators.push_back(new GaussianParticleGenerator("G", sMngr->getCamera()->getEye() + sMngr->getCamera()->getDir()*50, perpendicular * 25, p, 5, 1000, 0.99, 0.2, perpendicular*(-5)));
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