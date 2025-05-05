/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** main.cpp
*/

#include "Camera.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "FlatMaterial.hpp"
#include "DirectionalLight.hpp"
#include "PPMRenderer.hpp"
#include <iostream>
#include <memory>

using namespace RayTracer;
using namespace Math;

int main()
{
    try {
        // Create a camera
        Point3D cameraOrigin(0, 0, 0);
        Rectangle3D screen(Point3D(-1, -1, -2), Vector3D(2, 0, 0), Vector3D(0, 2, 0));
        Camera camera(cameraOrigin, screen);

        // Create a scene
        Scene scene(camera, 800, 600);

        // Create materials
        auto redMaterial = std::make_shared<FlatMaterial>(Vector3D(1.0, 0.2, 0.2));

        // Add primitives to the scene
        auto sphere = std::make_unique<Sphere>(Point3D(0, 0, -5), 1.0, *redMaterial);
        scene.addPrimitive(std::move(sphere));

        // Add lights to the scene
        auto light = std::make_unique<DirectionalLight>(
            Vector3D(-1, -1, -1), // Direction
            Vector3D(1, 1, 1),    // White light
            1.0                   // Full intensity
        );
        scene.addLight(std::move(light));

        // Render the scene
        PPMRenderer renderer;
        if (!renderer.render(scene, "output.ppm")) {
            std::cerr << "Failed to render the scene" << std::endl;
            return 1;
        }

        std::cout << "Scene rendered successfully to output.ppm" << std::endl;
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
