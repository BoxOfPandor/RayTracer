/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** FlatMaterial.cpp
*/

#include "FlatMaterial.hpp"
using namespace RayTracer;
using namespace Math;

FlatMaterial::FlatMaterial(const Vector3D& color, double ambient,
                          double diffuse, double specular, double shininess)
    : _color(color), _ambient(ambient), _diffuse(diffuse),
      _specular(specular), _shininess(shininess)
{
}

Vector3D FlatMaterial::getColor(const Point3D& point) const
{
    (void)point;
    return _color;
}

double FlatMaterial::getAmbient() const
{
    return _ambient;
}

double FlatMaterial::getDiffuse() const
{
    return _diffuse;
}

double FlatMaterial::getSpecular() const
{
    return _specular;
}

double FlatMaterial::getShininess() const
{
    return _shininess;
}