#pragma once
#include <list>
#include "GaussianParticleGenerator.h"
#include "ParticleGenerator.h"
#include "Particle.h"
class ParticleSystem;

class Firework : public Particle {
protected:
	ParticleSystem* pSys;
	int type;
	list<shared_ptr<Particle>> particles;

	void SummonParticles(list<Particle*>* l, GaussianParticleGenerator* g, int N, Vector4 Color, float Size);

public:
	Firework(Vector3 Pos, Vector3 Vel = Vector3(0, 0, 0), Vector3 Acl = Vector3(0, 0, 0),
		float Size = 1, float Mass = 1, float LifeTime = 5, float Damp = 0.998f,
		Vector4 Color = Vector4(0, 0, 255, 255), int Type = 0, ParticleSystem* PSYS = nullptr);

	virtual void integrate(double t);
	list<Particle*> explode();
	virtual Particle* clone() const;
};