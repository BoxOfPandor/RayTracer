/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Plane
*/

#include "Plane.hpp"

using namespace RayTracer;

Plane::Plane(const Math::Point3D& origin, const Math::Point3D& size, const IMaterial& material)
    : APrimitive(origin, material), _origin(origin), _size(size), _material(material)
{}

Plane::~Plane()
{}

bool Plane::getIntersection(const Ray &ray) const
{
    (void)ray;
    return false;
}
