/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Plane
*/

#include "Plane.hpp"

using namespace RayTracer;
using namespace Math;

Plane::Plane(const Math::Point3D& origin, const Math::Point3D& size, const IMaterial& material)
    : APrimitive(origin, material), _origin(origin), _size(size), _material(material)
{}

Plane::~Plane()
{}

bool Plane::getIntersection(const Ray &ray) const
{
    double denom = Vector3D::dot(ray.getDirection(), this->getNormalAt());

    if (std::abs(denom) < 1e-6)
        return false;

    Vector3D originToPlane = _origin - ray.getOrigin();
    int t = Vector3D::dot(originToPlane, this->getNormalAt()) / denom;

    if (t >= 0.001)
        return true;

    return false;
}
