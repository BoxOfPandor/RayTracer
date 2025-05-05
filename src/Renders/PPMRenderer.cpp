/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** PpmRenderer.cpp
*/

#include "PPMRenderer.hpp"
#include "Scene.hpp"
#include <fstream>
#include <iostream>

using namespace RayTracer;
using namespace Math;

bool PPMRenderer::render(const Scene& scene, const std::string& outputFile) const
{
    std::ofstream file(outputFile);
    if (!file.is_open()) {
        std::cerr << "Could not open output file: " << outputFile << std::endl;
        return false;
    }

    int width = scene.getWidth();
    int height = scene.getHeight();

    // PPM header
    file << "P3\n" << width << " " << height << "\n255\n";

    for (int j = height - 1; j >= 0; --j) {
        std::cout << "\rRendering: " << (height - j) * 100 / height << "% " << std::flush;

        for (int i = 0; i < width; ++i) {
            double u = static_cast<double>(i) / (width - 1);
            double v = static_cast<double>(j) / (height - 1);

            Ray ray = scene.getCamera().ray(u, v);
            Vector3D color = scene.traceRay(ray);

            // Convert color from [0,1] to [0,255]
            int r = static_cast<int>(255.99 * color.getX());
            int g = static_cast<int>(255.99 * color.getY());
            int b = static_cast<int>(255.99 * color.getZ());

            file << r << " " << g << " " << b << "\n";
        }
    }

    std::cout << "\rRendering: 100% Complete!     \n";
    return true;
}
