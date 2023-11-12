#include "ParticleSystem.h"
#include "SceneManager.h"

ParticleSystem::ParticleSystem(SceneManager* SM) {
	sMngr = SM;
	nParticles = 0;
	forceRegistry = ParticleForceRegistry();
	
	forceGenerators.push_back(new GravityForceGenerator(Vector3(0, -9.8, 0))); // Gravedad
}

ParticleSystem::~ParticleSystem() {
	for (Particle* p : particles) { particlesToDelete.push_back(p); }
	deleteUnusedParticles();
	particleGenerators.clear();
	forceGenerators.clear();
	forceRegistry.clear();
}

void ParticleSystem::clear() {
	for (Particle* p : particles) { particlesToDelete.push_back(p); }
	deleteUnusedParticles();
	particleGenerators.clear();
	forceGenerators.clear();
	forceRegistry.clear();

	forceGenerators.push_back(new GravityForceGenerator(Vector3(0, -9.8, 0))); // Inicializa de nuevo la gravedad
}

void ParticleSystem::update(double t) {
	for (ParticleGenerator* g : particleGenerators) { //Generadores de partículas
		addParticles(g->generateParticles());
		g->update(t);
	}

	forceRegistry.updateForces(t); // Actualiza las fuerzas ejercidas sobre las particulas

	for (Particle* p : particles) { // Particulas
		if (p->isAlive()) { p->integrate(t); }
		else { particlesToDelete.push_back(p); }
	}

	deleteUnusedParticles();
	cout << nParticles << endl;
}

void ParticleSystem::deleteUnusedParticles() {
  	for (auto it = particlesToDelete.begin(); it != particlesToDelete.end();) {
		particles.remove(*it);
		delete(*it);
		it = particlesToDelete.erase(it);
		nParticles--;
	}
}

void ParticleSystem::addParticleGenerator(ParticleGeneratorType T) {
	switch (T) {
	case UNIFORM: {
		Particle* p = new Particle(sMngr->getCamera()->getEye(), sMngr->getCamera()->getDir(), GRAVITY);
		p->setMass(4.0f);
		p->setSpeed(60.0f);
		p->setDamping(0.998f);
		p->setLifeTime(13);
		p->setSize(3);
		p->setColor(Vector4(1, 0, 0, 1));

		Vector3 perpendicular = Vector3(0, 1, 0).cross(sMngr->getCamera()->getDir());
		particleGenerators.push_back(new UniformParticleGenerator("G", sMngr->getCamera()->getEye() + sMngr->getCamera()->getDir() * 50, perpendicular * 25, p, 5, 1000, 0.99, 0.2));
		break;
	}
	case GAUSSIAN: {
		Particle* p = new Particle(sMngr->getCamera()->getEye(), sMngr->getCamera()->getDir(), GRAVITY);
		p->setMass(2.0f);
		p->setSpeed(60.0f);
		p->setDamping(0.998f);
		p->setLifeTime(10);
		p->setSize(2);
		p->setColor(Vector4(0, 0.1, 0.7, 1));

		Vector3 perpendicular = Vector3(0, 1, 0).cross(sMngr->getCamera()->getDir());
		particleGenerators.push_back(new GaussianParticleGenerator("G", sMngr->getCamera()->getEye() + sMngr->getCamera()->getDir() * 50, perpendicular * 25, p, 5, 1000, 0.99, 0.2));
		break;
	}
	case SNOW: {
		Particle* p = new Particle(sMngr->getCamera()->getEye(), sMngr->getCamera()->getDir(), Vector3(0, -3, 0));
		p->setMass(2.0f);
		p->setSpeed(0.001);
		p->setDamping(0.998f);
		p->setLifeTime(7);
		p->setSize(0.6);
		p->setColor(Vector4(1, 1, 1, 0.1));

		Vector3 perpendicular = Vector3(0, 1, 0).cross(sMngr->getCamera()->getDir());
		GaussianParticleGenerator* snow = new GaussianParticleGenerator("G", sMngr->getCamera()->getEye() + Vector3(0, 50, 0), perpendicular * 10, p, 20, 1000, 0.99, 0.2);
		snow->changeDistribution(5, 10);
		particleGenerators.push_back(snow);
		break;
	}
	}
}

void ParticleSystem::addParticles(list<Particle*> ptcls) {
	for (Particle* p : ptcls) {
		if (particles.size() < MAXPARTICLES) {
			particles.push_back(p);
			nParticles++;

			if (forceGenerators.size() > 1) {
				int i = 0;
			}
			for (auto fg : forceGenerators) { // Añade las particulas al registro de fuerzas 
				forceRegistry.addRegistry(fg, p);
			}
		}
		else {
			delete p;
		}
	}
}

void ParticleSystem::createProyectile(ProyectilType T) {
	if (particles.size() < MAXPARTICLES) {
		Particle* p = new Particle(sMngr->getCamera()->getEye(), sMngr->getCamera()->getDir(), Vector3(0, -9.8, 0));

		switch (T) {
		case bullet: {
			p->setMass(2.0f);
			p->setSpeed(60.0f);
			p->setDamping(0.99f);
			p->setLifeTime(5);
			p->setSize(2);
			p->setColor(Vector4(0, 0, 1, 1));
			break;
		}
		case canonBall: {
			p->setMass(800.0f);
			p->setSpeed(80.0f);
			p->setAcceleration(Vector3(0.0f, -25.0f, 0.0f));
			p->setDamping(0.99f);
			p->setLifeTime(5);
			p->setSize(5);
			p->setColor(Vector4(1, 0, 0, 1));
			break;
		}
		case laser: {
			p->setMass(0.001f);
			p->setSpeed(100.0f);
			p->setAcceleration(Vector3(0.0f, 0.0f, 0.0f)); // No gravity
			p->setDamping(0.99f);
			p->setLifeTime(5);
			p->setSize(0.2f);
			p->setColor(Vector4(0, 1, 1, 1));
			break;
		}
		case firework: {
			Vector3 Pos = sMngr->getCamera()->getEye() + sMngr->getCamera()->getDir() * 50 - Vector3(0, 20, 0);
			Vector4 Color = Vector4(0, 255, 0, 255);
			int t = rand()%4;
			p = new Firework(Pos, Vector3(0, 45, 0), Vector3(0, -10, 0), 1, 0.05, 2.5, 0.998, Color, t, this);
			break;
		}
		default:
			break;
		}
		p->init();
		particles.push_back(p);
		nParticles++;

		
		for (auto fg : forceGenerators) // Añade las particulas al registro de fuerzas 
			forceRegistry.addRegistry(fg, p);
		
	}
}