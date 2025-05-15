/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** LightFactory.cpp
*/

#include "LightFactory.hpp"
#include "DirectionalLight.hpp"

#include <stdexcept>
#include <map>

using namespace RayTracer;
using namespace Math;

std::unique_ptr<ILight> LightFactory::createLight(
    const std::string& type,
    const std::map<std::string, double>& params,
    const Math::Vector3D& color)
{
    if (type == "directional") {
        double x = params.count("x") ? params.at("x") : 0.0;
        double y = params.count("y") ? params.at("y") : -1.0;
        double z = params.count("z") ? params.at("z") : 0.0;
        double intensity = params.count("intensity") ? params.at("intensity") : 1.0;

        Vector3D direction(x, y, z);
        return std::make_unique<DirectionalLight>(direction, color, intensity);
    }

    throw std::runtime_error("Unknown light type: " + type);
}
