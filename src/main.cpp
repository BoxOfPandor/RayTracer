/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** main.cpp
*/

#include "ConfigSceneLoader.hpp"
#include "PPMRenderer.hpp"
#include "Scene.hpp"
#include <iostream>
#include <string>

using namespace RayTracer;

void printUsage()
{
    std::cout << "USAGE: ./raytracer <SCENE_FILE>" << std::endl;
    std::cout << "SCENE_FILE: scene configuration file" << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc != 2 || std::string(argv[1]) == "--help") {
        printUsage();
        return (argc != 2) ? 84 : 0;
    }

    try {
        ConfigSceneLoader sceneLoader;
        auto scene = sceneLoader.loadScene(argv[1]);

        PPMRenderer renderer;
        if (!renderer.render(*scene, "output.ppm")) {
            std::cerr << "Failed to render scene" << std::endl;
            return 84;
        }

        std::cout << "Scene rendered to output.ppm" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }
}
