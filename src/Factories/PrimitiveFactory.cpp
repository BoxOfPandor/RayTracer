/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** PrimitiveFactory.cpp
*/

#include "PrimitiveFactory.hpp"
#include "Sphere.hpp"
#include "Cylinder.hpp"
#include "Plane.hpp"
#include <stdexcept>

using namespace RayTracer;
using namespace Math;

std::unique_ptr<IPrimitive> PrimitiveFactory::createPrimitive(
    const std::string& type,
    const std::map<std::string, double>& params,
    const IMaterial& material)
{
    if (type == "sphere") {
        double x = params.count("x") ? params.at("x") : 0.0;
        double y = params.count("y") ? params.at("y") : 0.0;
        double z = params.count("z") ? params.at("z") : 0.0;
        double radius = params.count("r") ? params.at("r") : 1.0;

        Point3D center(x, y, z);
        return std::make_unique<Sphere>(center, radius, material);
    }
    else if (type == "cylinder") {
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
    else if (type == "plane") {
        double x = params.count("x") ? params.at("x") : 0.0;
        double y = params.count("y") ? params.at("y") : 0.0;
        double z = params.count("z") ? params.at("z") : 0.0;

        double normalX = params.count("normalX") ? params.at("normalX") : 0.0;
        double normalY = params.count("normalY") ? params.at("normalY") : 1.0;
        double normalZ = params.count("normalZ") ? params.at("normalZ") : 0.0;

        Point3D point(x, y, z);
        Vector3D normal(normalX, normalY, normalZ);

        return std::make_unique<Plane>(point, normal, material);
    }

    throw std::runtime_error("Unknown primitive type: " + type);
}
