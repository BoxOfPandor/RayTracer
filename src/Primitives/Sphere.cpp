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

