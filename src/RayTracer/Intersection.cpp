/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Intersection.cpp
*/

#include "Intersection.hpp"

using namespace RayTracer;
using namespace Math;

Intersection::Intersection()
    : _primitive(nullptr), _distance(0.0), _point(), _normal()
{
}

Intersection::Intersection(const IPrimitive* primitive, double distance,
                         const Point3D& point, const Vector3D& normal)
    : _primitive(primitive), _distance(distance), _point(point), _normal(normal)
{
}

const IPrimitive* Intersection::getPrimitive() const
{
    return _primitive;
}

double Intersection::getDistance() const
{
    return _distance;
}

const Point3D& Intersection::getPoint() const
{
    return _point;
}

const Vector3D& Intersection::getNormal() const
{
    return _normal;
}

void Intersection::setPrimitive(const IPrimitive* primitive)
{
    _primitive = primitive;
}

void Intersection::setDistance(double distance)
{
    _distance = distance;
}

void Intersection::setPoint(const Point3D& point)
{
    _point = point;
}

void Intersection::setNormal(const Vector3D& normal)
{
    _normal = normal;
}
