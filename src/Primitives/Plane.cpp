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
    : _origin(origin), _size(size), _material(material)
{}

Plane::~Plane()
{}

bool Plane::hits(const Ray& ray) const
{
    return getIntersection(ray);
}

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

Vector3D Plane::getNormalAt(const Point3D& point) const
{
    return Vector3D(0, 0, 0);
}

void Plane::translate(const Math::Vector3D& translation)
{
    _origin = _origin + translation;
}

void Plane::rotateX(double angle)
{
    Vector3D axis = Vector3D(1, 0, 0).normalize();
    _origin = _origin * std::cos(angle) +
              axis.cross(_origin) * std::sin(angle) +
              axis * axis.dot(_origin) * (1 - std::cos(angle));
}

void Plane::rotateY(double angle)
{
    Vector3D axis = Vector3D(0, 1, 0).normalize();
    _origin = _origin * std::cos(angle) +
              axis.cross(_origin) * std::sin(angle) +
              axis * axis.dot(_origin) * (1 - std::cos(angle));
}

void Plane::rotateZ(double angle)
{
    Vector3D axis = Vector3D(0, 0, 1).normalize();
    _origin = _origin * std::cos(angle) +
              axis.cross(_origin) * std::sin(angle) +
              axis * axis.dot(_origin) * (1 - std::cos(angle));
}

const IMaterial& Plane::getMaterial() const
{
    return _material;
}
