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
#include "ConfigSceneLoader.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <cstring>

using namespace RayTracer;
using namespace Math;

void printUsage(const char* programName)
{
    std::cout << "Usage: " << programName << " [options] [scene_file]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --ppm <output.ppm>     Render to PPM file" << std::endl;
    std::cout << "  --sfml <output.png>    Render with SFML (real-time display + PNG output)" << std::endl;
    std::cout << "  --threads <num>        Number of rendering threads (SFML only, default: auto)" << std::endl;
    std::cout << "  --help                 Display this help message" << std::endl;
    std::cout << "If scene_file is provided, loads the scene from that file" << std::endl;
}

int main(int argc, char* argv[])
{
    try {
        bool useSFML = false;
        std::string outputFile = "output.ppm";
        int numThreads = 0;
        std::string sceneFile = "default_scene.cfg";
        bool useSceneFile = false;

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
            else if (argv[i][0] != '-') {
                sceneFile = argv[i];
                useSceneFile = true;
            }
            else {
                std::cerr << "Unknown argument: " << argv[i] << std::endl;
                printUsage(argv[0]);
                return 1;
            }
        }

        // Create scene from file or default
        std::unique_ptr<Scene> scene;

        if (useSceneFile) {
            std::cout << "Loading scene from file: " << sceneFile << std::endl;
            ConfigSceneLoader sceneLoader;
            try {
                scene = sceneLoader.loadScene(sceneFile);
                std::cout << "Scene loaded successfully" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error loading scene: " << e.what() << std::endl;
                return 1;
            }
        } else {
            std::cerr << "Need a config scene file" << std::endl;
            return 84;
        }

        // Render the scene with the selected renderer
        if (useSFML) {
            std::cout << "Rendering with SFML renderer..." << std::endl;
            SFMLRenderer renderer(numThreads);
            if (!renderer.render(*scene, outputFile)) {
                std::cerr << "Failed to render the scene with SFML" << std::endl;
                return 1;
            }
            std::cout << "Scene rendered successfully to " << outputFile << std::endl;
        } else {
            std::cout << "Rendering with PPM renderer..." << std::endl;
            PPMRenderer renderer;
            if (!renderer.render(*scene, outputFile)) {
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
