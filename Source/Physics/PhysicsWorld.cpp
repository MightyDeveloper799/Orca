#include "PhysicsWorld.h"

namespace Orca
{
    PhysicsWorld::PhysicsWorld() {
        collisionConfig = new btDefaultCollisionConfiguration();
        dispatcher = new btCollisionDispatcher(collisionConfig);
        broadphase = new btDbvtBroadphase();
        solver = new btSequentialImpulseConstraintSolver();
        dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);
        dynamicsWorld->setGravity(btVector3(0, -9.81f, 0));
    }

    PhysicsWorld::~PhysicsWorld() {
        delete dynamicsWorld;
        delete solver;
        delete broadphase;
        delete dispatcher;
        delete collisionConfig;
    }
    
    void PhysicsWorld::StepSimulation(float deltaTime) {
        dynamicsWorld->stepSimulation(deltaTime);
    }

    btDiscreteDynamicsWorld* PhysicsWorld::GetWorld() {
        return dynamicsWorld;
    }
}