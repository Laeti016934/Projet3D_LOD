// -------------------------------------------
// based on gMini : a minimal OpenGL/GLUT
// application for 3D graphics.
// Copyright (C) 2006-2026 Tamy Boubekeur,
// Noura Faraj, Nicolas Lutz
// All rights reserved.
// -------------------------------------------

// -------------------------------------------
// This code is not entirely clean
// (too many global variables for instance,
// structures in main.cpp), it is
// for learning purposes only.
// -------------------------------------------

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>

#include <float.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "application.h"

// ------------------------------------
// GLUT function implementations
// GLUT is an OpenGL helper which allows to create window systems for OpenGL applications,
// implementing both display and input management.
// GLUT requires several functions to be given as function pointers to determine its behaviour,
// such as how to draw, what to do when nothing happens, how to handle keys or mouse movement.
// ------------------------------------

Scene g_mainScene;

// ------------------------------------

int main(int argc, char ** argv)
{
    if (argc > 2) {
        exit (EXIT_FAILURE);
    }

    //Creating the dictionary of the scene
    Mesh sphereMesh;
    sphereMesh.load("data/unit_sphere_n.off");
    Scene::MeshID sphereID = g_mainScene.addMesh(sphereMesh);

    Mesh squareMesh;
    squareMesh.load("data/unit_square_n.off");
    Scene::MeshID squareID = g_mainScene.addMesh(squareMesh);

    //Creating the scene
    g_mainScene.camera().zoom(0.5);
    ObjectInstance sphereInstance(sphereID, ObjectInstance::Sphere);
    ObjectInstance squareInstance(squareID, ObjectInstance::Square);

    squareInstance.setScaling(glm::vec3(5.0f, 5.0f, 1.0f));
    squareInstance.setRotation(glm::vec3(-M_PI/2.0f, 0.0f, 0.f));
    squareInstance.setTranslation(glm::vec3(0.f, -1.0f, 0.f));
    Scene::ObjectInstanceID sphereInstanceID = g_mainScene.uploadObjectInstance(sphereInstance);
    Scene::ObjectInstanceID squareInstanceID = g_mainScene.uploadObjectInstance(squareInstance);

    //ObjectInstance &square = g_mainScene.objectInstance(squareInstanceID); //If you want to retrive a reference to the object after it has been uploaded


    Application app(argc, argv);
    app.setScene(&g_mainScene);

    glutMainLoop ();

    return EXIT_SUCCESS;
}

