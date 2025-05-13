/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Sphere
*/

#include "Sphere.hpp"
#include <cmath>

using namespace RayTracer;
using namespace Math;

Sphere::Sphere(const Math::Point3D& origin, double radius, const IMaterial& material)
    : APrimitive(origin, material), _origin(origin), _radius(radius), _material(material)
{}

Sphere::~Sphere()
{}

bool Sphere::getIntersection(const Ray& ray) const
{
    Vector3D originToAPrimitive(
        ray.getOrigin().getX() - _origin.getX(),
        ray.getOrigin().getY() - _origin.getY(),
        ray.getOrigin().getZ() - _origin.getZ()
    );

    double a = Vector3D::dot(ray.getDirection(), ray.getDirection());
    double b = 2.0 * Vector3D::dot(ray.getDirection(), originToAPrimitive);
    double c = Vector3D::dot(originToAPrimitive, originToAPrimitive) - _radius * _radius;

    double discriminant = (b * b) - 4 * a * c;

    if (discriminant < 0)
        return false;

    double sqrtDiscriminant = std::sqrt(discriminant);
    double t1 = (-b - sqrtDiscriminant) / (2 * a);
    double t2 = (-b + sqrtDiscriminant) / (2 * a);

    if (t1 > 0.001 || t2 > 0.001)
        return true;
    
    return false;
}
