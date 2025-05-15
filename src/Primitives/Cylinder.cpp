/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Cylinder
*/

#include "Cylinder.hpp"
#include <cmath>
#include <algorithm>

using namespace RayTracer;
using namespace Math;

Cylinder::Cylinder(const Math::Point3D& origin, const Math::Vector3D& direction,
                  double radius, double height, const IMaterial& material)
    : _origin(origin), _radius(radius), _height(height), _material(material)
{
    double length = direction.length();
    if (length > 0) {
        _direction = direction / length;
    } else {
        _direction = Vector3D(0, 1, 0);
    }
}

bool Cylinder::hits(const Ray& ray) const
{
    return getIntersection(ray);
}

bool Cylinder::getIntersection(const Ray& ray) const
{
    const Vector3D& rayDir = ray.getDirection();
    const Point3D& rayOrigin = ray.getOrigin();

    Vector3D rayOriginToCylinder = Vector3D(
        rayOrigin.getX() - _origin.getX(),
        rayOrigin.getY() - _origin.getY(),
        rayOrigin.getZ() - _origin.getZ()
    );

    double a = Vector3D::dot(rayDir, rayDir) - std::pow(Vector3D::dot(rayDir, _direction), 2);
    double b = 2.0 * (Vector3D::dot(rayOriginToCylinder, rayDir) -
                     (Vector3D::dot(rayOriginToCylinder, _direction) * Vector3D::dot(rayDir, _direction)));
    double c = Vector3D::dot(rayOriginToCylinder, rayOriginToCylinder) -
              std::pow(Vector3D::dot(rayOriginToCylinder, _direction), 2) -
              _radius * _radius;

    if (std::abs(a) < 0.0001) {
        return false;
    }

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return false;
    }

    double sqrtDiscriminant = std::sqrt(discriminant);
    double t1 = (-b - sqrtDiscriminant) / (2 * a);
    double t2 = (-b + sqrtDiscriminant) / (2 * a);

    if (t1 > t2) {
        std::swap(t1, t2);
    }

    double t_hit = t1 > 0.001 ? t1 : t2;
    if (t_hit < 0.001) {
        return false;
    }

    Point3D hitPoint = ray.at(t_hit);

    Vector3D hitToOrigin = Vector3D(
        hitPoint.getX() - _origin.getX(),
        hitPoint.getY() - _origin.getY(),
        hitPoint.getZ() - _origin.getZ()
    );

    double axisDistance = Vector3D::dot(hitToOrigin, _direction);

    if (axisDistance < 0 || axisDistance > _height) {
        if (t2 > 0.001) {
            t_hit = t2;
            hitPoint = ray.at(t_hit);
            hitToOrigin = Vector3D(
                hitPoint.getX() - _origin.getX(),
                hitPoint.getY() - _origin.getY(),
                hitPoint.getZ() - _origin.getZ()
            );
            axisDistance = Vector3D::dot(hitToOrigin, _direction);

            if (axisDistance < 0 || axisDistance > _height) {
                return false;
            }
        } else {
            return false;
        }
    }

    return true;
}

Math::Vector3D Cylinder::getNormalAt(const Math::Point3D& point) const
{
    Vector3D originToPoint(
        point.getX() - _origin.getX(),
        point.getY() - _origin.getY(),
        point.getZ() - _origin.getZ()
    );

    double projection = Vector3D::dot(originToPoint, _direction);

    Point3D axisPoint = _origin + _direction * projection;

    Vector3D normal(
        point.getX() - axisPoint.getX(),
        point.getY() - axisPoint.getY(),
        point.getZ() - axisPoint.getZ()
    );

    double length = normal.length();
    if (length > 0) {
        return normal / length;
    }

    return Vector3D(1, 0, 0);
}

void Cylinder::translate(const Math::Vector3D& translation)
{
    _origin = _origin + translation;
}

void Cylinder::rotateX(double angle)
{
    double radians = angle * M_PI / 180.0;
    double cosA = std::cos(radians);
    double sinA = std::sin(radians);

    double y = _direction.getY();
    double z = _direction.getZ();

    Vector3D newDirection(
        _direction.getX(),
        y * cosA - z * sinA,
        y * sinA + z * cosA
    );

    double length = newDirection.length();
    if (length > 0) {
        _direction = newDirection / length;
    }
}

void Cylinder::rotateY(double angle)
{
    double radians = angle * M_PI / 180.0;
    double cosA = std::cos(radians);
    double sinA = std::sin(radians);

    double x = _direction.getX();
    double z = _direction.getZ();

    Vector3D newDirection(
        x * cosA + z * sinA,
        _direction.getY(),
        -x * sinA + z * cosA
    );

    double length = newDirection.length();
    if (length > 0) {
        _direction = newDirection / length;
    }
}

void Cylinder::rotateZ(double angle)
{
    double radians = angle * M_PI / 180.0;
    double cosA = std::cos(radians);
    double sinA = std::sin(radians);

    double x = _direction.getX();
    double y = _direction.getY();

    Vector3D newDirection(
        x * cosA - y * sinA,
        x * sinA + y * cosA,
        _direction.getZ()
    );

    double length = newDirection.length();
    if (length > 0) {
        _direction = newDirection / length;
    }
}

const IMaterial& Cylinder::getMaterial() const
{
    return _material;
}
