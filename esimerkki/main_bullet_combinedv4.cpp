/*

GRAFIIKKAOHJELMOINTI
Metropolia AMK, 2016

The following libraries are available in this project:

OpenGL		(graphics)				https://www.opengl.org/
GLU			(OpenGL utilities)		https://www.opengl.org/resources/libraries/
GLEW		(OpenGL extensions)		http://glew.sourceforge.net/
GLM			(OpenGL mathematics)	http://glm.g-truc.net/0.9.8/index.html
SDL2		(windowing, event)		https://www.libsdl.org/
SDL2_image	(image loading)			https://www.libsdl.org/projects/SDL_image/
SDK2_mixer	(audio mixer)			https://www.libsdl.org/projects/SDL_mixer/
Bullet		(3D physics)			http://bulletphysics.org/wordpress/
Box2D		(2D physics)			http://box2d.org/

*/

#include <chrono>
#include <iostream>
#include <list>

#include <btBulletDynamicsCommon.h>

#include "esimerkki.h"

void ground();
void cube();
void floor_tile();
void shoot_ball();
float floor_tile_y_offset = 5.0f;
float floor_tile_xz_offset = 5.f;
float ground_offset = 100.0f;
float number = 0.5f;
int const number_of_bodies = 200;
//int const rows = 10;
int const height = 150;
int const columns = 3;
int const rows = 3;
int const number_of_floor_tiles = 50;
float sphere_radius = 1.0f;

namespace
{
    double const RAD2DEG = 180.0 / M_PI;

}

int main(int argc, char* argv[])
{
    if (!init()) return 1;

    //
    // OpenGL initializations, see esimerkki.h for defines.
    //
    glClearColor(CLEAR_COLOR);
    glColor3f(DRAW_COLOR);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 3.0, 10000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_TEXTURE_2D);

    GLuint tex;
    glGenTextures(1, &tex);
    if (!tex)
        return 1;
    glBindTexture(GL_TEXTURE_2D, tex);

    SDL_Surface *tex_image;
    tex_image = IMG_Load("wood.jpg");
    if (!tex_image)
    {
        SDL_Quit();
        return 1;
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    gluBuild2DMipmaps(
        GL_TEXTURE_2D,
        3,
        tex_image->w,
        tex_image->h,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        tex_image->pixels);

    if (glGetError())
        return 1;

    // Maailma
    auto* broadphase = new btDbvtBroadphase();

    auto* collisionConfiguration = new btDefaultCollisionConfiguration();
    auto* dispatcher             = new btCollisionDispatcher(collisionConfiguration);
    auto* solver                 = new btSequentialImpulseConstraintSolver;
    auto* dynamicsWorld          = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

    dynamicsWorld->setGravity(btVector3(0, -10, 0));

    auto* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
    auto* sphereShape = new btSphereShape(sphere_radius);

    auto* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState,
                                                               groundShape,
                                                               btVector3(0, 0, 0));
    auto* groundRigidBody = new btRigidBody(groundRigidBodyCI);

    dynamicsWorld->addRigidBody(groundRigidBody);

    //btRigidBody* bodies[number_of_bodies];
    //for (int j = 0; j < rows; ++j)
    //    for (int i = 0; i < number_of_bodies/rows; ++i)
    //    {
    //    
    //        auto* dynamicBox = new btBoxShape(btVector3(number, number, number));
    //        btDefaultMotionState* fallMotionState = new btDefaultMotionState(
    //            btTransform(btQuaternion(0, 0, 0, 1), btVector3(j*number*2.5f, i*number*2.5f, 0))
    //        );
    //        btScalar mass = 0.5;
    //        btVector3 fallInertia(0, 0, 0);
    //        dynamicBox->calculateLocalInertia(mass, fallInertia);
    //        btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, dynamicBox, fallInertia);
    //        auto* boxRigidBody = new btRigidBody(fallRigidBodyCI);
    //        boxRigidBody->setAngularVelocity(btVector3(0, 0, 0));
    //        boxRigidBody->setFriction(100.0f);
    //        boxRigidBody->setRestitution(0);
    //        bodies[i+j*number_of_bodies/rows] = boxRigidBody;
    //        dynamicsWorld->addRigidBody(boxRigidBody);
    //    }

    btRigidBody* bodies[columns*rows*height];
    for (int k = 0; k < columns; ++k)
        for (int j = 0; j < rows; ++j)
            for (int i = 0; i < height; ++i)
            {

                auto* dynamicBox = new btBoxShape(btVector3(number, number, number));
                btDefaultMotionState* fallMotionState = new btDefaultMotionState(
                    btTransform(btQuaternion(0, 0, 0, 1), btVector3(j*number*2.5f, i*number*2.5f, k*number*2.5f))
                );
                btScalar mass = 1;
                btVector3 fallInertia(0, 0, 0);
                dynamicBox->calculateLocalInertia(mass, fallInertia);
                btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, dynamicBox, fallInertia);
                auto* boxRigidBody = new btRigidBody(fallRigidBodyCI);
                boxRigidBody->setAngularVelocity(btVector3(0, 0, 0));
                boxRigidBody->setFriction(100.0f);
                boxRigidBody->setRestitution(1.2);
                bodies[i + j*height + k*rows*height] = boxRigidBody;
                dynamicsWorld->addRigidBody(boxRigidBody);
            }

    //btRigidBody* bodies[rows*height*columns];
    //for (int k = 0; k < columns; ++k)
    //    for (int j = 0; j < rows; ++j)
    //        for (int i = 0; i < height; ++i)
    //        {

    //            auto* dynamicBox = new btBoxShape(btVector3(number, number, number));
    //            btDefaultMotionState* fallMotionState = new btDefaultMotionState(
    //                btTransform(btQuaternion(0, 0, 0, 1), btVector3(j * 3 * number*2.5f, i*number*2.5f, k * 3 * number*2.5f))
    //            );
    //            btScalar mass = 1;
    //            btVector3 fallInertia(0, 0, 0);
    //            dynamicBox->calculateLocalInertia(mass, fallInertia);
    //            btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, dynamicBox, fallInertia);
    //            auto* boxRigidBody = new btRigidBody(fallRigidBodyCI);
    //            boxRigidBody->setAngularVelocity(btVector3(0, 0, 0));
    //            boxRigidBody->setFriction(5.0f);
    //            boxRigidBody->setRestitution(0.1);
    //            bodies[i + j*height + k*rows*height] = boxRigidBody;
    //            dynamicsWorld->addRigidBody(boxRigidBody);
    //        }

    btDefaultMotionState* sphereMotionState =
        new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-10, 40, -40)));
    btScalar sphere_mass = 1000;
    btVector3 fallInertia(0, 0, 0);
    sphereShape->calculateLocalInertia(sphere_mass, fallInertia);
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(sphere_mass, sphereMotionState, sphereShape, fallInertia);
    btRigidBody* sphereRigidBody = new btRigidBody(fallRigidBodyCI);
    dynamicsWorld->addRigidBody(sphereRigidBody);
    sphereRigidBody->setFriction(2.0);
    //sphereRigidBody->setAngularVelocity(btVector3(-100.f,0, -10.f));
    //sphereRigidBody->setLinearVelocity(btVector3(100.f, 0, 100.f));
    //sphereRigidBody->setAngularVelocity(btVector3(-100.0f, 0, -30.0f));
    //sphereRigidBody->setLinearVelocity(btVector3(0.0f, 0, -100.0f));
    sphereRigidBody->setLinearFactor(btVector3(0, 0, 0));
    sphereRigidBody->setAngularFactor(btVector3(0, 0, 0));

    //sphereRigidBody->setLinearVelocity(btVector3(0, 0, -20));

    //btRigidBody* floor_tiles[number_of_floor_tiles];
    //for (int i = 0; i < number_of_floor_tiles; ++i)
    //{
    //    auto* dynamicBox = new btBoxShape(btVector3(number * floor_tile_xz_offset, number / floor_tile_y_offset, number * floor_tile_xz_offset));
    //    btDefaultMotionState* fallMotionState = new btDefaultMotionState(
    //        btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, i*number, 0))
    //    );
    //    btScalar mass = 100;
    //    btVector3 fallInertia(0, 0, 0);
    //    dynamicBox->calculateLocalInertia(mass, fallInertia);
    //    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, dynamicBox, fallInertia);
    //    auto* boxRigidBody = new btRigidBody(fallRigidBodyCI);
    //    boxRigidBody->setAngularVelocity(btVector3(0, 0, 0));
    //    boxRigidBody->setFriction(100.0f);
    //    boxRigidBody->setRestitution(0);
    //    floor_tiles[i] = boxRigidBody;
    //    dynamicsWorld->addRigidBody(boxRigidBody);
    //}

    //
    // Main rendering loop.
    //
    float radius = sphereShape->getRadius();
    btTransform sphere_trans;
    btTransform ground_trans;
    btTransform box_trans;
    int         x, y, z;
    btVector3   pos;
    SDL_Event   event;
    float camera_movement = 0;
    double elapsed_seconds = 0;
    bool ball_shot = 0;
    bool ball_turned = 0;
    float lookAtX = 40 - camera_movement;
    float lookAtY = 1;
    float lookAtZ = 40 - camera_movement;
    float lookAtYEye = 60 + camera_movement * 9;
    while (true)
    {
        auto start = std::chrono::steady_clock::now();
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //dynamicsWorld->stepSimulation(1 / 60.f, 10);

        dynamicsWorld->stepSimulation(1 / 60.f, 10, 1 / 70.f);

            // ***************************************
            // Your OpenGL rendering code starts here!
            // ***************************************
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            float lookAtX = 40 - camera_movement;
            float lookAtY = 1;
            float lookAtZ = 40 - camera_movement;
            float lookAtYEye = 60 + camera_movement * 9;
            if (lookAtX <= 0.7f)
                lookAtX = 0.1f;
            if (lookAtZ <= 0.7f)
            {
                lookAtZ = 0.1f;
            }
            if (lookAtYEye >= 500.f)
                lookAtYEye = 500.0f;
            gluLookAt(lookAtX , 1, lookAtZ, 0, lookAtYEye, 0, 0, 1, 0);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glEnable(GL_DEPTH_TEST);
            camera_movement += 0.08f;

            //groundRigidBody->getMotionState()->getWorldTransform(ground_trans);
            //
            //btTransform t_ground;
            //float m_ground[16];
            //if (groundRigidBody->getMotionState())
            //    groundRigidBody->getMotionState()->getWorldTransform(t_ground);
            //else
            //    t_ground = groundRigidBody->getWorldTransform();
            //t_ground.getOpenGLMatrix(m_ground);

            //glPushMatrix();
            //glMultMatrixf(m_ground);
            //ground();
            //glPopMatrix();

            //for (int i = 0; i < number_of_bodies; ++i)
            //{
            //    bodies[i]->getMotionState()->getWorldTransform(box_trans);

            //    btTransform t;
            //    float m[16];
            //    if (bodies[i]->getMotionState())
            //        bodies[i]->getMotionState()->getWorldTransform(t);
            //    else
            //        t = bodies[i]->getWorldTransform();
            //    t.getOpenGLMatrix(m);

            //    glPushMatrix();
            //    glMultMatrixf(m);
            //    cube();
            //    glPopMatrix();
            //}

            for (int i = 0; i < columns*rows*height; ++i)
            {

                bodies[i]->getMotionState()->getWorldTransform(box_trans);
                    btTransform t;
                    float m[16];
                    if (bodies[i]->getMotionState())
                        bodies[i]->getMotionState()->getWorldTransform(t);
                    else
                        t = bodies[i]->getWorldTransform();
                    t.getOpenGLMatrix(m);

                    glPushMatrix();
                    glMultMatrixf(m);
                    cube();
                    glPopMatrix();

            }


            //if (elapsed_seconds > 2.0f)
            //{
            //    sphereRigidBody->setLinearFactor(btVector3(1, 1, 1));
            //    sphereRigidBody->setAngularFactor(btVector3(1, 1, 1));
            //    sphereRigidBody->setDamping(0, 0);
            //    sphereRigidBody->getMotionState()->getWorldTransform(sphere_trans);
            //    //btVector3 pos = sphere_trans.getOrigin();
            //    //btVector3 vel = sphereRigidBody->getLinearVelocity();
            //    //btVector3 ang_vel = sphereRigidBody->getAngularVelocity();
            //    //if ((pos.getZ() < -20.0f && ball_turned == 0) || (pos.getZ() > 30.0f && ball_turned == 1))
            //    //{
            //    //    sphereRigidBody->setLinearVelocity(btVector3(vel.getX() + 2.5f, vel.getY(), -vel.getZ()));
            //    //    sphereRigidBody->setAngularVelocity(btVector3(-ang_vel.getX(), -ang_vel.getY(), -ang_vel.getZ()));
            //    //    ball_turned = !ball_turned;
            //    //}

            //    sphereRigidBody->getMotionState()->getWorldTransform(sphere_trans);

            //    btTransform t;
            //    float m[16];
            //    if (sphereRigidBody->getMotionState())
            //        sphereRigidBody->getMotionState()->getWorldTransform(t);
            //    else
            //        t = sphereRigidBody->getWorldTransform();
            //    t.getOpenGLMatrix(m);

            //    glPushMatrix();
            //    glMultMatrixf(m);
            //    shoot_ball();
            //    glPopMatrix();
            //    ball_shot = 1;
            //}



            //for (int i = 0; i < number_of_floor_tiles; ++i)
            //{
            //    floor_tiles[i]->getMotionState()->getWorldTransform(box_trans);

            //    btTransform t;
            //    float m[16];
            //    if (floor_tiles[i]->getMotionState())
            //        floor_tiles[i]->getMotionState()->getWorldTransform(t);
            //    else
            //        t = floor_tiles[i]->getWorldTransform();
            //    t.getOpenGLMatrix(m);

            //    glPushMatrix();
            //    glMultMatrixf(m);
            //    floor_tile();
            //    glPopMatrix();
            //}

            // ***************************************
            // ...and ends here.
            // ***************************************

            SDL_GL_SetSwapInterval(1);
            SDL_GL_SwapWindow(window);
            auto finish = std::chrono::steady_clock::now();
            elapsed_seconds += std::chrono::duration_cast<
                std::chrono::duration<double> >(finish - start).count();
    }
    //for (int i = 0; i < number_of_bodies; ++i)
    //{
    //    dynamicsWorld->removeRigidBody(bodies[i]);
    //    delete bodies[i]->getMotionState();
    //    delete bodies[i];
    //}

    for (int i = 0; i < columns*rows*height; ++i)
    {
        dynamicsWorld->removeRigidBody(bodies[i]);
        delete bodies[i]->getMotionState();
        delete bodies[i];
    }
    //for (int i = 0; i < number_of_floor_tiles; ++i)
    //{
    //    dynamicsWorld->removeRigidBody(floor_tiles[i]);
    //    delete floor_tiles[i]->getMotionState();
    //    delete floor_tiles[i];
    //}

    delete sphereShape;
    delete groundShape;
    delete dynamicsWorld;
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;

    if (!fini()) return 1;
    return 0;
}

void cube()
{
    float y = number;
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 0.0); glVertex3f(number, -y, number);
    glTexCoord2f(1.0, 1.0); glVertex3f(number, y, number);
    glTexCoord2f(0.0, 1.0); glVertex3f(-number, y, number);
    glTexCoord2f(0.0, 0.0); glVertex3f(-number, -y, number);

    glTexCoord2f(1.0, 1.0); glVertex3f(number, y, -number);
    glTexCoord2f(0.0, 1.0); glVertex3f(number, y, number);
    glTexCoord2f(0.0, 0.0); glVertex3f(number, -y, number);
    glTexCoord2f(1.0, 0.0); glVertex3f(number, -y, -number);

    glTexCoord2f(0.0, 0.0); glVertex3f(-number, y, number);
    glTexCoord2f(1.0, 0.0); glVertex3f(number, y, number);
    glTexCoord2f(1.0, 1.0); glVertex3f(number, y, -number);
    glTexCoord2f(0.0, 1.0); glVertex3f(-number, y, -number);

    glTexCoord2f(1.0, 0.0); glVertex3f(-number, -y, number);
    glTexCoord2f(1.0, 1.0); glVertex3f(-number, y, number);
    glTexCoord2f(0.0, 1.0); glVertex3f(-number, y, -number);
    glTexCoord2f(0.0, 0.0); glVertex3f(-number, -y, -number);

    glTexCoord2f(1.0, 1.0); glVertex3f(number, -y, number);
    glTexCoord2f(0.0, 1.0); glVertex3f(-number, -y, number);
    glTexCoord2f(0.0, 0.0); glVertex3f(-number, -y, -number);
    glTexCoord2f(1.0, 0.0); glVertex3f(number, -y, -number);

    glTexCoord2f(0.0, 1.0); glVertex3f(number, y, -number);
    glTexCoord2f(0.0, 0.0); glVertex3f(number, -y, -number);
    glTexCoord2f(1.0, 0.0); glVertex3f(-number, -y, -number);
    glTexCoord2f(1.0, 1.0); glVertex3f(-number, y, -number);
    glEnd();
}

void floor_tile()
{
    glBegin(GL_QUADS);
    //front
    glTexCoord2f(1.0, 0.0); glVertex3f(number * floor_tile_xz_offset, -number / floor_tile_y_offset, number * floor_tile_xz_offset);
    glTexCoord2f(1.0, 1.0); glVertex3f(number * floor_tile_xz_offset, number / floor_tile_y_offset, number * floor_tile_xz_offset);
    glTexCoord2f(0.0, 1.0); glVertex3f(-number * floor_tile_xz_offset, number / floor_tile_y_offset, number * floor_tile_xz_offset);
    glTexCoord2f(0.0, 0.0); glVertex3f(-number * floor_tile_xz_offset, -number / floor_tile_y_offset, number * floor_tile_xz_offset);

    //Right
    glTexCoord2f(1.0, 1.0); glVertex3f(number * floor_tile_xz_offset, number / floor_tile_y_offset, -number * floor_tile_xz_offset);
    glTexCoord2f(0.0, 1.0); glVertex3f(number * floor_tile_xz_offset, number / floor_tile_y_offset, number * floor_tile_xz_offset);
    glTexCoord2f(0.0, 0.0); glVertex3f(number * floor_tile_xz_offset, -number / floor_tile_y_offset, number * floor_tile_xz_offset);
    glTexCoord2f(1.0, 0.0); glVertex3f(number * floor_tile_xz_offset, -number / floor_tile_y_offset, -number * floor_tile_xz_offset);

    //Top
    glTexCoord2f(0.0, 0.0); glVertex3f(-number * floor_tile_xz_offset, number / floor_tile_y_offset, number * floor_tile_xz_offset);
    glTexCoord2f(1.0, 0.0); glVertex3f(number * floor_tile_xz_offset, number / floor_tile_y_offset, number * floor_tile_xz_offset);
    glTexCoord2f(1.0, 1.0); glVertex3f(number * floor_tile_xz_offset, number / floor_tile_y_offset, -number * floor_tile_xz_offset);
    glTexCoord2f(0.0, 1.0); glVertex3f(-number * floor_tile_xz_offset, number / floor_tile_y_offset, -number * floor_tile_xz_offset);

    //Left
    glTexCoord2f(1.0, 0.0); glVertex3f(-number * floor_tile_xz_offset, -number / floor_tile_y_offset, number * floor_tile_xz_offset);
    glTexCoord2f(1.0, 1.0); glVertex3f(-number * floor_tile_xz_offset, number / floor_tile_y_offset, number * floor_tile_xz_offset);
    glTexCoord2f(0.0, 1.0); glVertex3f(-number * floor_tile_xz_offset, number / floor_tile_y_offset, -number * floor_tile_xz_offset);
    glTexCoord2f(0.0, 0.0); glVertex3f(-number * floor_tile_xz_offset, -number / floor_tile_y_offset, -number * floor_tile_xz_offset);

    //Bottom
    glTexCoord2f(1.0, 1.0); glVertex3f(number * floor_tile_xz_offset, -number / floor_tile_y_offset, number * floor_tile_xz_offset);
    glTexCoord2f(0.0, 1.0); glVertex3f(-number * floor_tile_xz_offset, -number / floor_tile_y_offset, number * floor_tile_xz_offset);
    glTexCoord2f(0.0, 0.0); glVertex3f(-number * floor_tile_xz_offset, -number / floor_tile_y_offset, -number * floor_tile_xz_offset);
    glTexCoord2f(1.0, 0.0); glVertex3f(number * floor_tile_xz_offset, -number / floor_tile_y_offset, -number * floor_tile_xz_offset);

    //Back
    glTexCoord2f(0.0, 1.0); glVertex3f(number * floor_tile_xz_offset, number / floor_tile_y_offset, -number * floor_tile_xz_offset);
    glTexCoord2f(0.0, 0.0); glVertex3f(number * floor_tile_xz_offset, -number / floor_tile_y_offset, -number * floor_tile_xz_offset);
    glTexCoord2f(1.0, 0.0); glVertex3f(-number * floor_tile_xz_offset, -number / floor_tile_y_offset, -number * floor_tile_xz_offset);
    glTexCoord2f(1.0, 1.0); glVertex3f(-number * floor_tile_xz_offset, number / floor_tile_y_offset, -number * floor_tile_xz_offset);
    glEnd();
}

void shoot_ball()
{
    GLUquadric *quad;
    quad = gluNewQuadric();
    gluSphere(quad, sphere_radius, 100, 20);
}

void ground()
{
    glBegin(GL_QUADS);
    glColor4f(0.5f, 0.5f, 0.5f, 0.0f);
    glTexCoord2f(0.0, 0.0); glVertex3f(-ground_offset, 0, ground_offset);
    glTexCoord2f(1.0, 0.0); glVertex3f(ground_offset, 0, ground_offset);
    glTexCoord2f(1.0, 1.0); glVertex3f(ground_offset, 0, -ground_offset);
    glTexCoord2f(0.0, 1.0); glVertex3f(-ground_offset, 0, -ground_offset);
    glColor3f(0.8f, 0.8f, 0.8f);
    glEnd();
}