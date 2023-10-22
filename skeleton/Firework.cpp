#include "Firework.h"
#include "ParticleSystem.h"

Firework::Firework(Vector3 Pos, Vector3 Vel, Vector3 Acl,
	float Size, float Mass, float LifeTime, float Damp, Vector4 Color, int Type, ParticleSystem* PSYS)
	: Particle(Pos, Vel, Acl, Size, Mass, LifeTime, Damp, Color) {
	type = Type;
	pSys = PSYS;
}

Firework::~Firework() {

}

void Firework::integrate(double t) {
	Particle::integrate(t);
	if (!alive) { pSys->addParticles(explode()); }
}

list<Particle*> Firework::explode() {
	GaussianParticleGenerator* g = new GaussianParticleGenerator("FireworkSpread", pose.p, velocity * 3, clone(), 5, 100, 1, 0);
	
	list<Particle*> pList; 
	switch (type){
	case 0:
		g->changeDistribution(10, 4);
		SummonParticles(&pList, g, 5, Vector4(1, 0, 0, 1), 0.5);
		SummonParticles(&pList, g, 6, Vector4(1, 1, 0, 1), 1);
		SummonParticles(&pList, g, 3, Vector4(1, 1, 1, 1), 0.7);
		break;
	case 1:
		g->changeDistribution(15, 6);
		SummonParticles(&pList, g, 5, Vector4(0, 0, 1, 1), 0.3);
		SummonParticles(&pList, g, 6, Vector4(0, 1, 0, 1), 0.2);
		SummonParticles(&pList, g, 3, Vector4(1, 0, 1, 1), 0.6);
		break;
	case 2:
		g->changeDistribution(8, 3);
		SummonParticles(&pList, g, 5, Vector4(0.5, 0, 0.5, 1), 0.8);
		SummonParticles(&pList, g, 6, Vector4(0, 0.6, 0, 1), 1);
		SummonParticles(&pList, g, 3, Vector4(0.3, 0.7, 0, 1), 1.2);
		break;

	case 3:
		g->changeDistribution(5, 4);
		SummonFireworks(&pList, g, 7, Vector4(1, 1, 1, 1), 0.2, (rand()%3));
		break;

	default:
		break;
	}

	return pList;
}

Particle* Firework::clone() const {
	return new Firework(Vector3(pose.p.x, pose.p.y, pose.p.z), velocity, aceleration, size, mass, lifeTime, damping, color);
}

void Firework::SummonParticles(list<Particle*>* l, GaussianParticleGenerator* g, int N, Vector4 Color, float Size) {
	Particle* p = new Particle(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), Size, 1, 2);
	p->setColor(Color);
	g->setParticle(p);
	g->setNumParticles(N);

	for (auto pt : g->generateParticles()) { l->push_back(pt); }
}

void Firework::SummonFireworks(list<Particle*>* l, GaussianParticleGenerator* g, int N, Vector4 Color, float Size, int Type) {
	Particle* f = new Firework(getPos(), Vector3(0, 30, 0), Vector3(0, -4.8, 0), Size, 1, 2, 0.998, Color, Type, pSys);
	g->setParticle(f);
	g->setNumParticles(N);

	for (auto p : g->generateFireworks(pSys)) { l->push_back(p); }
}