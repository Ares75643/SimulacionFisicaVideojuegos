#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

#include "SceneManager.h"
#include "Particle.h"
#include "RigidBody.h"

std::string display_text = " ";

using namespace physx;
using namespace std;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

SceneManager* sceneManager;

// Initialize physics engine
void initPhysics(bool interactive) {
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, 0.0f, 1.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	
	////SUELO
	PxRigidStatic* platform = gPhysics->createRigidStatic(PxTransform{ 0,0,-50 });
	PxShape* shape = CreateShape(PxBoxGeometry(5, 0.2, 50));
	platform->attachShape(*shape);
	gScene->addActor(*platform);
	RenderItem* item = new RenderItem(shape, platform, Vector4(0.5, 0.5, 1, 1));
	//TECHO
	/*platform = gPhysics->createRigidStatic(PxTransform{ 0,5,-50 });
	shape = CreateShape(PxBoxGeometry(4, 0.2, 50));
	platform->attachShape(*shape);
	gScene->addActor(*platform);
	item = new RenderItem(shape, platform, Vector4(0.5, 0.5, 1, 1));*/
	//PARED1
	platform = gPhysics->createRigidStatic(PxTransform{ -5, 2.5, -50 });
	shape = CreateShape(PxBoxGeometry(0.2, 2.5, 50));
	platform->attachShape(*shape);
	gScene->addActor(*platform);
	item = new RenderItem(shape, platform, Vector4(0.2, 0, 1, 0));
	//PARED2
	platform = gPhysics->createRigidStatic(PxTransform{ 5, 2.5, -50 });
	shape = CreateShape(PxBoxGeometry(0.2, 2.5, 50));
	platform->attachShape(*shape);
	gScene->addActor(*platform);
	item = new RenderItem(shape, platform, Vector4(0.2, 0, 1, 0));
	//DEADLINE
	platform = gPhysics->createRigidStatic(PxTransform{ 0, 2.5, 0 });
	shape = CreateShape(PxBoxGeometry(4, 2.5, 0.2));
	platform->attachShape(*shape);
	platform->setName("deathLine");
	gScene->addActor(*platform);
	item = new RenderItem(shape, platform, Vector4(1, 0, 0, 1));
	//SPAWNER
	platform = gPhysics->createRigidStatic(PxTransform{ 0, 2.5, -100 });
	shape = CreateShape(PxBoxGeometry(4, 2.5, 0.2));
	platform->attachShape(*shape);
	gScene->addActor(*platform);
	item = new RenderItem(shape, platform, Vector4(0, 1, 0, 1));

	sceneManager = new SceneManager(gScene, gPhysics);
	sceneManager->StartGame();
}

// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds

void stepPhysics(bool interactive, double t) {
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	sceneManager->update(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive) {
	PX_UNUSED(interactive);

	delete(sceneManager); // Elimina toda la escena

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera) {
	PX_UNUSED(camera);

	switch(toupper(key)) {
	
		case ' ':
			sceneManager->getParticleSys()->createProyectile(firework);
			break;

		// Habilities 
		case '1': // H1 Viento que aleja todos los obstaculos (no elimina ninguno pero sirve para recolocar o ganar tiempo)
			sceneManager->getRBSys()->activateWind();
			break;
		case '2':
			sceneManager->getParticleSys()->addWind();
			sceneManager->getRBSys()->addWind();
			break;
		case '3':
			sceneManager->getParticleSys()->addTornado();
			sceneManager->getRBSys()->addTornado();
			break;
		case '4':
			sceneManager->getParticleSys()->addExplosion();
			sceneManager->getRBSys()->addExplosion();
			break;

		case 'Z':
			sceneManager->getRBSys()->shootRB(b_normal);
			break;
		case 'X':
			sceneManager->getRBSys()->shootRB(b_sgravity);
			break;
		case 'C':
			sceneManager->getRBSys()->shootRB(b_ugravity);
			break;

		default: // Si se ha muerto pulsar cualquier tecla (que no tenga otro uso) reinicia el juego
			if (!sceneManager->isAlive()) sceneManager->StartGame();
			break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2) {
	if (!sceneManager->isAlive() || actor1 == nullptr || actor2 == nullptr) return;

	PX_UNUSED(actor1);
	PX_UNUSED(actor2);

	// Gestion de colision con balas
	if (actor1->getName() == "bulletN" && actor2->getName() == "obstacle") {
		sceneManager->getRBSys()->destroyRigidBody(actor1);
	}
	else if (actor1->getName() == "bulletUG" && actor2->getName() == "obstacle") {
		sceneManager->getRBSys()->inverseGravity(actor2);
		sceneManager->getRBSys()->destroyRigidBody(actor1);
	}
	else if (actor1->getName() == "bulletSG" && actor2->getName() == "obstacle") {
		sceneManager->getRBSys()->superGravity(actor2);
		sceneManager->getRBSys()->destroyRigidBody(actor1);
	}

	// Daño
	if (actor2->getName() == "deathLine" && actor1->getName() == "obstacle") {
		sceneManager->getRBSys()->destroyRigidBody(actor1);
		sceneManager->Damage();
	}
}

int main(int, const char*const*) {
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}