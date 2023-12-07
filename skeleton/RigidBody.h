#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "PxRigidBody.h"
#include "PxShape.h"
#include <PxPhysicsAPI.h>

class main;

using namespace physx;

class RigidBody {
protected:
	PxTransform transform;
	PxRigidDynamic* solid;
	PxShape* shape;
	RenderItem* render;

	float lifeTime; // s
	bool alive;

public:
	RigidBody(PxScene* scene, PxPhysics* physics,
		const Vector3& Position, const Vector3& Velocity = Vector3(0, 0, 0), const Vector3& Inertia = Vector3(0, 0, 0),
		double Mass = 1, double LifeTime = 30,
		physx::PxGeometry* Geometry = new PxBoxGeometry(1, 1, 1), Vector4 Color = Vector4(0, 0, 0, 1)) {

		transform = physx::PxTransform(Position.x, Position.y, Position.z);
		solid = physics->createRigidDynamic(transform);

		solid->setLinearVelocity(Velocity);
		solid->setAngularVelocity(Vector3(0,0,0));
		solid->setLinearDamping(0.0);
		solid->setMassSpaceInertiaTensor(Inertia);
		solid->setGlobalPose(transform);
		solid->setMass(Mass);

		lifeTime = LifeTime;
		alive = true;

		shape = CreateShape(*Geometry);
		solid->attachShape(*shape);

		PxRigidBodyExt::updateMassAndInertia(*solid, 0.15);
		scene->addActor(*solid);
		render = new RenderItem(shape, solid, Color);
	}

	~RigidBody(){
		DeregisterRenderItem(render);
	}

	void integrate(float t) {
		lifeTime -= t;
		if (lifeTime <= 0) setAlive(false);
	};

	PxRigidDynamic* getRigidDynamic() { return solid; }
	Vector3 getPosition() { solid->getGlobalPose(); }
	Vector3 getLinearVelocity() { return solid->getLinearVelocity(); }
	float getMass() { return solid->getMass(); }
	float getInvMass() { return solid->getInvMass(); }
	double getTime() { return lifeTime; }
	bool isAlive() { return alive; }
	
	
	

	void setPosition(Vector3 Pos) {
		transform = PxTransform(Pos);
		solid->setGlobalPose(transform);
	}
	void setLinearVelocity(Vector3 Vel) { solid->setLinearVelocity(Vel); }
	void addForce(Vector3 F) { solid->addForce(F); }
	void setAlive(bool A = false) { alive = A; }
};
