#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

#include "SceneManager.h"
#include "Particle.h"

std::string display_text = "This is a test";

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
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);
	
	sceneManager = new SceneManager();
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
		case 'U':
			sceneManager->getParticleSys()->addParticleGenerator(UNIFORM);
			break;
		case 'G':
			sceneManager->getParticleSys()->addParticleGenerator(GAUSSIAN);
			break;
		case 'P':
			sceneManager->getParticleSys()->createProyectile(bullet);
			break;
		case 'C':
			sceneManager->getParticleSys()->createProyectile(canonBall);
			break;
		case 'L':
			sceneManager->getParticleSys()->createProyectile(laser);
			break;
		case ' ':
			sceneManager->getParticleSys()->createProyectile(firework);
			break;
		case 'Q':
			sceneManager->getParticleSys()->clear();
			break;
		case 'F':
			sceneManager->getParticleSys()->addParticleGenerator(SNOW);
			break;
		case '1':
			sceneManager->getParticleSys()->addGravity();
			break;
		case '2':
			sceneManager->getParticleSys()->addWind();
			break;
		case '3':
			sceneManager->getParticleSys()->addTornado();
			break;
		case '4':
			sceneManager->getParticleSys()->addExplosion();
			break;
		case '5':
			sceneManager->getParticleSys()->addSpring(S_DEFAULT);
			break;
		case '6':
			sceneManager->getParticleSys()->addSpring(S_STATIC);
			break;
		case '7':
			sceneManager->getParticleSys()->addSpring(S_SLINKY);
			break;
		case '8':
			sceneManager->getParticleSys()->activateBuoyancy();
			break;
		case 'E':
			sceneManager->getParticleSys()->explosionParticles();
			break;
		case 'K':
			sceneManager->getParticleSys()->addKToAllSprings();
			break;
		case '+':
			sceneManager->getParticleSys()->addTestMass(5);
			break;
		case '-':
			sceneManager->getParticleSys()->addTestMass(-5);
			break;

		default:
			break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2) {
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
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