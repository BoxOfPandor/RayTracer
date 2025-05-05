/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Rectangle3D
*/

#include "Rectangle3D.hpp"
using namespace RayTracer;
using namespace Math;

Rectangle3D::Rectangle3D()
{
    this->_origin = Point3D(0, 0, 0);
    this->_bottom_side = Vector3D(1, 0, 0);
    this->_left_side = Vector3D(0, 1, 0);
}

Rectangle3D::Rectangle3D(const Point3D& origin, const Vector3D& bottom_side, const Vector3D& left_side)
{
    this->_origin = origin;
    this->_bottom_side = bottom_side;
    this->_left_side = left_side;
}

Point3D Rectangle3D::getOrigin() const
{
    return this->_origin;
}

Vector3D Rectangle3D::getBottomSide() const
{
    return this->_bottom_side;
}

Vector3D Rectangle3D::getLeftSide() const
{
    return this->_left_side;
}

Point3D Rectangle3D::pointAt(double u, double v) const
{
    return _origin + _bottom_side * u + _left_side * v;
}