#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() {

}

ParticleSystem::~ParticleSystem() {

}

void ParticleSystem::update(double t) {
	//Generadores de partículas
	for (list<ParticleGenerator*>::iterator it = particleGenerators.begin(); it != particleGenerators.end(); it++) {
		(*it)->generateParticles();
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
		particleGenerators.push_back(new UniformParticleGenerator());
		break;

	case GAUSSIAN:
		particleGenerators.push_back(new GaussianParticleGenerator());
		break;

	default:
		break;
	}
}