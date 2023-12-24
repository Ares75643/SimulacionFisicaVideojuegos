#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "PxRigidBody.h"
#include "PxShape.h"
#include <PxPhysicsAPI.h>
#include <PxPhysics.h>

using namespace physx;

enum Shape{s_cube, s_sphere, s_rect, s_capsule, s_minisphere};

class RigidBody {
protected:
	PxScene* scene;

	PxTransform transform;
	PxRigidDynamic* solid;
	PxShape* shape;
	RenderItem* render;

	Shape shapeType;
	float lifeTime; // s
	bool alive;

public:
	RigidBody(PxScene* Scene, PxPhysics* Physics,
		const Vector3& Position, const Vector3& Velocity = Vector3(0, 0, 0), const Vector3& Inertia = Vector3(1, 1, 1),
		double Mass = 1, double LifeTime = 30,
		Shape Shape = s_cube, Vector4 Color = Vector4(0, 0, 0, 1)) {

		scene = Scene;

		transform = physx::PxTransform(Position.x, Position.y, Position.z);
		solid = Physics->createRigidDynamic(transform);

		solid->setLinearVelocity(Velocity);
		solid->setAngularVelocity(Vector3(0,0,0));
		solid->setLinearDamping(0.0);
		solid->setMassSpaceInertiaTensor(Inertia);
		solid->setGlobalPose(transform);
		solid->setMass(Mass);

		lifeTime = LifeTime;
		alive = true;
		shapeType = Shape;
		
		switch (shapeType){
		case s_capsule:
			shape = CreateShape(PxCapsuleGeometry(0.5, 0.5));
			break;
		case s_sphere:
			shape = CreateShape(PxSphereGeometry(0.5));
			break;
		case s_cube:
			shape = CreateShape(PxBoxGeometry(0.5, 0.5, 0.5));
			break;
		case s_rect:
			shape = CreateShape(PxBoxGeometry(0.5, 1, 0.5));
			break;
		case s_minisphere:
			shape = CreateShape(PxSphereGeometry(0.2));
			break;
		}

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
		if (lifeTime <= 0 || transform.p.y <= -500) setAlive(false);
	};

	PxRigidDynamic* getRigidDynamic() { return solid; }
	Vector3 getPosition() { return solid->getGlobalPose().p; }
	Vector3 getLinearVelocity() { return solid->getLinearVelocity(); }
	float getMass() { return solid->getMass(); }
	float getInvMass() { return solid->getInvMass(); }
	double getLifeTime() { return lifeTime; }
	bool isAlive() { return alive; }
	Vector4 getColor() { return render->color; }
	Shape getShape() { return shapeType; }

	void setPosition(Vector3 Pos) {
		transform = PxTransform(Pos);
		solid->setGlobalPose(transform);
	}
	void setLinearVelocity(Vector3 Vel) { solid->setLinearVelocity(Vel); }
	void addForce(Vector3 F) { solid->addForce(F); }
	void setAlive(bool A = false) { alive = A; }
	void setName(char* N) { solid->setName(N); }
	void setColor(Vector4 C) { render->color = C; }
};
