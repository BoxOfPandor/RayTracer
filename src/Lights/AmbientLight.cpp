/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** AmbientLight.cpp
*/

#include "AmbientLight.hpp"
#include "Scene.hpp"

using namespace RayTracer;
using namespace Math;

AmbientLight::AmbientLight(const Vector3D& color, double intensity)
    : _color(color), _intensity(intensity)
{
}

Vector3D AmbientLight::getDirection(const Point3D& point) const
{
    // Ambient light has no specific direction, but we return an arbitrary
    // normalized vector to satisfy the interface
    (void)point;
    return Vector3D(0, 0, -1);
}

double AmbientLight::getIntensity(const Point3D& point) const
{
    // Ambient light has constant intensity regardless of position
    (void)point;
    return _intensity;
}

Vector3D AmbientLight::getColor() const
{
    return _color;
}

bool AmbientLight::isShadowed(const Point3D& point, const Scene& scene) const
{
    // Ambient light doesn't cast shadows, it affects all surfaces equally
    (void)point;
    (void)scene;
    return false;
}
