/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Sphere
*/

#include "Sphere.hpp"
using namespace RayTracer;

Sphere::Sphere()
{
    this->_origin = Math::Point3D(0, 0, 0);
    this->_radius = 10;
}

Sphere::Sphere(const Math::Point3D& origin, double radius)
{
    this->_origin = origin;
    this->_radius = radius;
}

bool Sphere::hit(const Ray& ray) const
{
    Math::Vector3D originToSphere(
        ray.getOrigin().getX() - _origin.getX(),
        ray.getOrigin().getY() - _origin.getY(),
        ray.getOrigin().getZ() - _origin.getZ()
    );

    double a = Math::Vector3D::dot(ray.getDirection(), ray.getDirection());
    double b = 2.0 * Math::Vector3D::dot(ray.getDirection(), originToSphere);
    double c = Math::Vector3D::dot(originToSphere, originToSphere) - _radius * _radius;

    double discriminant = (b * b) - 4 * a * c;

    return discriminant >= 0;
}