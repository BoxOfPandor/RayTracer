/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** APrimitive
*/

#include "APrimitive.hpp"

using namespace RayTracer;
using namespace Math;

APrimitive::APrimitive(const Math::Point3D& origin, const IMaterial& material)
    : _origin(origin), _material(material)
{}

bool APrimitive::hits(const Ray& ray) const
{
    return getIntersection(ray);
}

Vector3D APrimitive::getNormalAt(const Point3D& point) const
{
    Vector3D normal(
        point.getX() - _origin.getX(),
        point.getY() - _origin.getY(),
        point.getZ() - _origin.getZ()
    );
    double length = normal.length();

    if (length > 0)
        return normal / length;
    return Vector3D(1, 0, 0);
}

void APrimitive::translate(const Vector3D& translation)
{
    _origin = _origin + translation;
}

// void APrimitive::rotateX(double angle)
// {
// }

// void APrimitive::rotateY(double angle)
// {
// }

// void APrimitive::rotateZ(double angle)
// {
// }

const IMaterial& APrimitive::getMaterial() const
{
    return _material;
}
