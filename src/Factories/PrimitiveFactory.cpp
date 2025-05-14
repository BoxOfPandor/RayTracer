/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** PrimitiveFactory.cpp
*/

#include "PrimitiveFactory.hpp"
#include "Sphere.hpp"
#include "Cylinder.hpp"
#include <stdexcept>

using namespace RayTracer;
using namespace Math;

std::unique_ptr<IPrimitive> PrimitiveFactory::createPrimitive(
    const std::string& type,
    const std::map<std::string, double>& params,
    const IMaterial& material)
{
    if (type == "sphere") {
        // Extract sphere parameters
        double x = params.count("x") ? params.at("x") : 0.0;
        double y = params.count("y") ? params.at("y") : 0.0;
        double z = params.count("z") ? params.at("z") : 0.0;
        double radius = params.count("r") ? params.at("r") : 1.0;

        Point3D center(x, y, z);
        return std::make_unique<Sphere>(center, radius, material);
    }
    else if (type == "cylinder") {
        // Extract cylinder parameters
        double x = params.count("x") ? params.at("x") : 0.0;
        double y = params.count("y") ? params.at("y") : 0.0;
        double z = params.count("z") ? params.at("z") : 0.0;

        double dirX = params.count("dirX") ? params.at("dirX") : 0.0;
        double dirY = params.count("dirY") ? params.at("dirY") : 1.0;
        double dirZ = params.count("dirZ") ? params.at("dirZ") : 0.0;

        double radius = params.count("r") ? params.at("r") : 1.0;
        double height = params.count("height") ? params.at("height") : 1.0;

        Point3D origin(x, y, z);
        Vector3D direction(dirX, dirY, dirZ);

        return std::make_unique<Cylinder>(origin, direction, radius, height, material);
    }
    // Add additional primitive types here as needed

    throw std::runtime_error("Unknown primitive type: " + type);
}
