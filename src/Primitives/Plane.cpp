/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Plane
*/

#include "Plane.hpp"
#include <cmath>

using namespace RayTracer;
using namespace Math;

Plane::Plane(const Math::Point3D& point, const Math::Vector3D& normal, const IMaterial& material)
    : _point(point), _material(material)
{
    double length = normal.length();
    if (length > 0) {
        _normal = normal / length;  // Normalize the normal vector
    } else {
        _normal = Vector3D(0, 1, 0);  // Default to up direction if given zero vector
    }
}

bool Plane::hits(const Ray& ray) const
{
    double t;
    return getIntersection(ray, t);
}

bool Plane::getIntersection(const Ray& ray, double& t) const
{
    // Calculate dot product of normal and ray direction
    double denom = Vector3D::dot(_normal, ray.getDirection());
    
    // If the ray is parallel to the plane (or nearly so), there's no intersection
    if (std::abs(denom) < 0.0001) {
        return false;
    }
    
    // Calculate the vector from ray origin to a point on the plane
    Vector3D pointToRayOrigin(
        _point.getX() - ray.getOrigin().getX(),
        _point.getY() - ray.getOrigin().getY(),
        _point.getZ() - ray.getOrigin().getZ()
    );
    
    // Calculate the intersection parameter
    t = Vector3D::dot(pointToRayOrigin, _normal) / denom;
    
    // Check if the intersection is in front of the ray
    return t > 0.001;
}

Vector3D Plane::getNormalAt(const Point3D& point) const
{
    // The normal is constant for the entire plane
    (void)point;  // Unused parameter
    return _normal;
}

void Plane::translate(const Vector3D& translation)
{
    // Move the point on the plane by the translation vector
    _point = _point + translation;
}

void Plane::rotateX(double angle)
{
    double radians = angle * M_PI / 180.0;
    double cosA = std::cos(radians);
    double sinA = std::sin(radians);
    
    double y = _normal.getY();
    double z = _normal.getZ();
    
    Vector3D newNormal(
        _normal.getX(),
        y * cosA - z * sinA,
        y * sinA + z * cosA
    );
    
    double length = newNormal.length();
    if (length > 0) {
        _normal = newNormal / length;
    }
}

void Plane::rotateY(double angle)
{
    double radians = angle * M_PI / 180.0;
    double cosA = std::cos(radians);
    double sinA = std::sin(radians);
    
    double x = _normal.getX();
    double z = _normal.getZ();
    
    Vector3D newNormal(
        x * cosA + z * sinA,
        _normal.getY(),
        -x * sinA + z * cosA
    );
    
    double length = newNormal.length();
    if (length > 0) {
        _normal = newNormal / length;
    }
}

void Plane::rotateZ(double angle)
{
    double radians = angle * M_PI / 180.0;
    double cosA = std::cos(radians);
    double sinA = std::sin(radians);
    
    double x = _normal.getX();
    double y = _normal.getY();
    
    Vector3D newNormal(
        x * cosA - y * sinA,
        x * sinA + y * cosA,
        _normal.getZ()
    );
    
    double length = newNormal.length();
    if (length > 0) {
        _normal = newNormal / length;
    }
}

const IMaterial& Plane::getMaterial() const
{
    return _material;
}
