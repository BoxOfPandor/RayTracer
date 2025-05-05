/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** DirectionalLight.cpp
*/

#include "DirectionalLight.hpp"
#include "Scene.hpp"
#include "IPrimitive.hpp"
#include <cmath>

using namespace RayTracer;
using namespace Math;

DirectionalLight::DirectionalLight(const Vector3D& direction, const Vector3D& color, double intensity)
    : _color(color), _intensity(intensity)
{
    // Normalizing the direction vector
    double length = direction.length();
    if (length > 0) {
        _direction = direction / length;
    } else {
        _direction = Vector3D(0, 0, -1); // Default direction if provided vector is zero
    }
}

Vector3D DirectionalLight::getDirection(const Point3D& point) const
{
    return _direction;
}

double DirectionalLight::getIntensity(const Point3D& point) const
{
    return _intensity;
}

Vector3D DirectionalLight::getColor() const
{
    return _color;
}

bool DirectionalLight::isShadowed(const Point3D& point, const Scene& scene) const
{
    Ray shadowRay(point, _direction * -1); // Ray in opposite direction of light

    for (const auto& primitive : scene.getPrimitives()) {
        if (primitive->hits(shadowRay)) {
            return true;
        }
    }
    return false;
}
