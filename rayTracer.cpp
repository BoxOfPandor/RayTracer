/*
** EPITECH PROJECT, 2025
** OOP
** File description:
** raytracer
*/

#include "rayTracer.hpp"

/*****************************************************************************/
// Ray class
RayTracer::Ray::Ray()
{
    this->point = Math::Point3D();
    this->vector = Math::Vector3D();
}

RayTracer::Ray::Ray(Math::Point3D point, Math::Vector3D vector)
{
    this->point = point;
    this->vector = vector;
}

RayTracer::Ray::~Ray()
{}
/*****************************************************************************/

/*****************************************************************************/
// Sphere class

RayTracer::Sphere::Sphere(double radius, Math::Point3D center)
{
    this->radius = radius;
    this->center = center;
}

RayTracer::Sphere::~Sphere()
{}

bool RayTracer::Sphere::hits(Ray ray)
{}
/*****************************************************************************/
