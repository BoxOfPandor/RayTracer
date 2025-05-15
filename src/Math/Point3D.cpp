/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Point3D
*/

#include "Point3D.hpp"
using namespace Math;

Point3D::Point3D()
{
    this->_x = 0;
    this->_y = 0;
    this->_z = 0;
}

Point3D::Point3D(double x, double y, double z)
{
    this->_x = x;
    this->_y = y;
    this->_z = z;
}

double Point3D::getX() const
{
    return this->_x;
}

double Point3D::getY() const
{
    return this->_y;
}

double Point3D::getZ() const
{
    return this->_z;
}

Point3D Point3D::operator+(Vector3D other) const
{
    return {this->_x + other.getX(), this->_y + other.getY(), this->_z + other.getZ()};
}

Point3D Point3D::operator+(Point3D other) const
{
    return {this->_x + other.getX(), this->_y + other.getY(), this->_z + other.getZ()};
}

Point3D Point3D::operator-(Vector3D other) const
{
    return {this->_x - other.getX(), this->_y - other.getY(), this->_z - other.getZ()};
}

Point3D Point3D::operator-(Point3D other) const
{
    return {this->_x - other.getX(), this->_y - other.getY(), this->_z - other.getZ()};
}

Point3D Point3D::operator*(double other) const
{
    return {this->_x * other, this->_y * other, this->_z * other};
}
