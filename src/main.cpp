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
#include "SFMLRenderer.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <cstring>

using namespace RayTracer;
using namespace Math;

void printUsage(const char* programName)
{
    std::cout << "Usage: " << programName << " [options]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --ppm <output.ppm>     Render to PPM file" << std::endl;
    std::cout << "  --sfml <output.png>    Render with SFML (real-time display + PNG output)" << std::endl;
    std::cout << "  --threads <num>        Number of rendering threads (SFML only, default: auto)" << std::endl;
    std::cout << "  --help                 Display this help message" << std::endl;
}

int main(int argc, char* argv[])
{
    try {
        bool useSFML = false;
        std::string outputFile = "output.ppm";
        int numThreads = 0;

        // Parse command line arguments
        for (int i = 1; i < argc; ++i) {
            if (strcmp(argv[i], "--ppm") == 0 && i + 1 < argc) {
                useSFML = false;
                outputFile = argv[++i];
            }
            else if (strcmp(argv[i], "--sfml") == 0 && i + 1 < argc) {
                useSFML = true;
                outputFile = argv[++i];
            }
            else if (strcmp(argv[i], "--threads") == 0 && i + 1 < argc) {
                numThreads = std::stoi(argv[++i]);
            }
            else if (strcmp(argv[i], "--help") == 0) {
                printUsage(argv[0]);
                return 0;
            }
            else {
                std::cerr << "Unknown argument: " << argv[i] << std::endl;
                printUsage(argv[0]);
                return 1;
            }
        }

        // Create a camera
        Point3D cameraOrigin(0, 0, 0);
        Rectangle3D screen(Point3D(-1, -1, -2), Vector3D(2, 0, 0), Vector3D(0, 2, 0));
        Camera camera(cameraOrigin, screen);

        // Create a scene
        Scene scene(camera, 1920, 1080);

        // Create materials
        auto redMaterial = std::make_shared<FlatMaterial>(Vector3D(1.0, 0.2, 0.2));
        auto blueMaterial = std::make_shared<FlatMaterial>(Vector3D(0.2, 0.2, 1.0));
        auto greenMaterial = std::make_shared<FlatMaterial>(Vector3D(0.2, 1.0, 0.2));
        auto yellowMaterial = std::make_shared<FlatMaterial>(Vector3D(1.0, 1.0, 0.2));

        // Add primitives to the scene
        auto sphere1 = std::make_unique<Sphere>(Point3D(0, 0, -5), 1.0, *redMaterial);
        auto sphere2 = std::make_unique<Sphere>(Point3D(2, 0, -7), 1.0, *blueMaterial);
        auto sphere3 = std::make_unique<Sphere>(Point3D(-2, 0, -7), 1.0, *greenMaterial);
        auto sphere4 = std::make_unique<Sphere>(Point3D(0, -2, -5), 1.0, *yellowMaterial);

        scene.addPrimitive(std::move(sphere1));
        scene.addPrimitive(std::move(sphere2));
        scene.addPrimitive(std::move(sphere3));
        scene.addPrimitive(std::move(sphere4));

        // Add lights to the scene
        auto light1 = std::make_unique<DirectionalLight>(
            Vector3D(-1, -1, -1), // Direction
            Vector3D(1, 1, 1),    // White light
            0.7                   // Intensity
        );

        auto light2 = std::make_unique<DirectionalLight>(
            Vector3D(1, -0.5, -0.5), // Direction
            Vector3D(0.5, 0.5, 0.8), // Blueish light
            0.3                      // Lower intensity
        );

        scene.addLight(std::move(light1));
        scene.addLight(std::move(light2));

        // Render the scene with the selected renderer
        if (useSFML) {
            std::cout << "Rendering with SFML renderer..." << std::endl;
            SFMLRenderer renderer(numThreads);
            if (!renderer.render(scene, outputFile)) {
                std::cerr << "Failed to render the scene with SFML" << std::endl;
                return 1;
            }
            std::cout << "Scene rendered successfully to " << outputFile << std::endl;
        } else {
            std::cout << "Rendering with PPM renderer..." << std::endl;
            PPMRenderer renderer;
            if (!renderer.render(scene, outputFile)) {
                std::cerr << "Failed to render the scene to PPM" << std::endl;
                return 1;
            }
            std::cout << "Scene rendered successfully to " << outputFile << std::endl;
        }

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
