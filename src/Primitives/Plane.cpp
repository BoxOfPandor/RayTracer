/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Plane
*/

#include "Plane.hpp"

using namespace RayTracer;
using namespace Math;

Plane::Plane(const Math::Point3D& origin, const Math::Vector3D& size, const IMaterial& material)
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
    double denom = Vector3D::dot(_size, ray.getDirection());

    if (std::abs(denom) < 1e-6)
        return false;

    Point3D originToPlanePoint = _origin - ray.getOrigin();
    Vector3D originToPlaneVec = {
        originToPlanePoint.getX(),
        originToPlanePoint.getY(),
        originToPlanePoint.getZ()
    };
    double t = Vector3D::dot(_size, originToPlaneVec) / denom;

    if (t < 0)
        return false;
    return true;
}

Vector3D Plane::getNormalAt(const Math::Point3D& point) const
{
    (void)point;
    return _size;
}

void Plane::translate(const Math::Vector3D& translation)
{
    _origin = _origin + translation;
}

void Plane::rotateX(double angle)
{
    Vector3D axis = Vector3D(1, 0, 0).normalize();
    Vector3D originVec = {_origin.getX(), _origin.getY(), _origin.getZ()};
    _origin = _origin * std::cos(angle) +
              axis.cross(originVec) * std::sin(angle) +
              axis * axis.dot(axis, originVec) * (1 - std::cos(angle));
}

void Plane::rotateY(double angle)
{
    Vector3D axis = Vector3D(0, 1, 0).normalize();
    Vector3D originVec = {_origin.getX(), _origin.getY(), _origin.getZ()};
    _origin = _origin * std::cos(angle) +
              axis.cross(originVec) * std::sin(angle) +
              axis * axis.dot(axis, originVec) * (1 - std::cos(angle));
}

void Plane::rotateZ(double angle)
{
    Vector3D axis = Vector3D(0, 0, 1).normalize();
    Vector3D originVec = {_origin.getX(), _origin.getY(), _origin.getZ()};
    _origin = _origin * std::cos(angle) +
              axis.cross(originVec) * std::sin(angle) +
              axis * axis.dot(axis, originVec) * (1 - std::cos(angle));
}

const IMaterial& Plane::getMaterial() const
{
    return _material;
}
