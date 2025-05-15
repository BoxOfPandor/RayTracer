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
    double length = direction.length();
    if (length > 0) {
        _direction = direction / length;
    } else {
        _direction = Vector3D(0, 0, -1);
    }
}

Vector3D DirectionalLight::getDirection(const Point3D& point) const
{
    // The direction of a directional light is constant and does not depend on the point
    // But maintant interface consistency
    (void)point;
    return _direction;
}

double DirectionalLight::getIntensity(const Point3D& point) const
{
    // The direction of a directional light is constant and does not depend on the point
    // But maintant interface consistency
    (void)point;
    return _intensity;
}

Vector3D DirectionalLight::getColor() const
{
    return _color;
}

bool DirectionalLight::isShadowed(const Point3D& point, const Scene& scene) const
{
    Ray shadowRay(point, _direction * -1);

    for (const auto& primitive : scene.getPrimitives()) {
        if (primitive->hits(shadowRay)) {
            return true;
        }
    }
    return false;
}
