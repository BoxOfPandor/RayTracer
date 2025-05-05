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
    : _origin(origin), _radius(radius), _material(material)
{
}

bool Sphere::hits(const Ray& ray) const
{
    double t;
    return getIntersection(ray, t);
}

bool Sphere::getIntersection(const Ray& ray, double& t) const
{
    Vector3D originToSphere(
        ray.getOrigin().getX() - _origin.getX(),
        ray.getOrigin().getY() - _origin.getY(),
        ray.getOrigin().getZ() - _origin.getZ()
    );

    double a = Vector3D::dot(ray.getDirection(), ray.getDirection());
    double b = 2.0 * Vector3D::dot(ray.getDirection(), originToSphere);
    double c = Vector3D::dot(originToSphere, originToSphere) - _radius * _radius;

    double discriminant = (b * b) - 4 * a * c;

    if (discriminant < 0) {
        return false;
    }

    double sqrtDiscriminant = std::sqrt(discriminant);
    double t1 = (-b - sqrtDiscriminant) / (2 * a);
    double t2 = (-b + sqrtDiscriminant) / (2 * a);

    if (t1 > 0.001) {
        t = t1;
        return true;
    }
    if (t2 > 0.001) {
        t = t2;
        return true;
    }
    
    return false;
}

Vector3D Sphere::getNormalAt(const Point3D& point) const
{
    Vector3D normal(
        point.getX() - _origin.getX(),
        point.getY() - _origin.getY(),
        point.getZ() - _origin.getZ()
    );
    
    double length = normal.length();
    if (length > 0) {
        return normal / length;
    }
    
    return Vector3D(1, 0, 0);
}

void Sphere::translate(const Vector3D& translation)
{
    _origin = _origin + translation;
}

void Sphere::rotateX(double angle)
{
}

void Sphere::rotateY(double angle)
{
}

void Sphere::rotateZ(double angle)
{
}

const IMaterial& Sphere::getMaterial() const
{
    return _material;
}
