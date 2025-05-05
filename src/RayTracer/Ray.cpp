/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Ray
*/

#include "Ray.hpp"
using namespace RayTracer;
using namespace Math;

Ray::Ray(const Point3D& origin, const Vector3D& direction)
{
    this->_origin = origin;
    this->_direction = direction;
}

Point3D Ray::getOrigin() const
{
    return this->_origin;
}

Vector3D Ray::getDirection() const
{
    return this->_direction;
}

Point3D Ray::at(double t) const
{
    return _origin + _direction * t;
}
