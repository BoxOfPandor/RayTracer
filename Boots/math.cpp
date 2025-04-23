/*
** EPITECH PROJECT, 2025
** OOP
** File description:
** raytracer
*/

#include "math.hpp"

/*****************************************************************************/
// Vector class
Math::Vector3D::Vector3D()
{
    this->_x = 0;
    this->_y = 0;
    this->_z = 0;
}

Math::Vector3D::Vector3D(double x, double y, double z)
{
    this->_x = x;
    this->_y = y;
    this->_z = z;
}

Math::Vector3D::~Vector3D()
{}

double Math::Vector3D::getX()
{
    return this->_x;
}

double Math::Vector3D::getY()
{
    return this->_y;
}

double Math::Vector3D::getZ()
{
    return this->_z;
}

double Math::Vector3D::length()
{
    return sqrt(this->_x * this->_x + this->_y * this->_y + this->_z * this->_z);
}

double Math::Vector3D::dot(Vector3D vec1, Vector3D vec2)
{
    return vec1.getX() * vec2.getX() + vec1.getY() * vec2.getY() + vec1.getZ() * vec2.getZ();
}

/*****************************************************************************/
// Vector operator with Vector
Math::Vector3D Math::Vector3D::operator+(Math::Vector3D other)
{
    return Math::Vector3D(this->_x + other.getX(), this->_y + other.getY(), this->_z + other.getZ());
}

void Math::Vector3D::operator+=(Math::Vector3D other)
{
    this->_x += other.getX();
    this->_y += other.getY();
    this->_z += other.getZ();
}

Math::Vector3D Math::Vector3D::operator-(Math::Vector3D other)
{
    return Math::Vector3D(this->_x - other.getX(), this->_y - other.getY(), this->_z - other.getZ());
}

void Math::Vector3D::operator-=(Math::Vector3D other)
{
    this->_x -= other.getX();
    this->_y -= other.getY();
    this->_z -= other.getZ();
}

Math::Vector3D Math::Vector3D::operator*(Math::Vector3D other)
{
    return Math::Vector3D(this->_x * other.getX(), this->_y * other.getY(), this->_z * other.getZ());
}

void Math::Vector3D::operator*=(Math::Vector3D other)
{
    this->_x *= other.getX();
    this->_y *= other.getY();
    this->_z *= other.getZ();
}

Math::Vector3D Math::Vector3D::operator/(Math::Vector3D other)
{
    return Math::Vector3D(this->_x / other.getX(), this->_y / other.getY(), this->_z / other.getZ());
}

void Math::Vector3D::operator/=(Math::Vector3D other)
{
    this->_x /= other.getX();
    this->_y /= other.getY();
    this->_z /= other.getZ();
}

/*****************************************************************************/
// Vector operator with value
Math::Vector3D Math::Vector3D::operator*(double n)
{
    return Math::Vector3D(this->_x * n, this->_y * n, this->_z * n);
}

void Math::Vector3D::operator*=(double n)
{
    this->_x *= n;
    this->_y *= n;
    this->_z *= n;
}

Math::Vector3D Math::Vector3D::operator/(double n)
{
    return Math::Vector3D(this->_x / n, this->_y / n, this->_z / n);
}

void Math::Vector3D::operator/=(double n)
{
    this->_x /= n;
    this->_y /= n;
    this->_z /= n;
}
/*****************************************************************************/

/*****************************************************************************/
// Point class

Math::Point3D::Point3D()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Math::Point3D::Point3D(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Math::Point3D::~Point3D()
{}

/*****************************************************************************/
// Point operator with Point
Math::Point3D Math::Point3D::operator+(Math::Point3D other)
{
    return Math::Point3D(this->x + other.x, this->y + other.y, this->z + other.z);
}

Math::Point3D Math::Point3D::operator-(Math::Point3D other)
{
    return Math::Point3D(this->x - other.x, this->y - other.y, this->z - other.z);
}

/*****************************************************************************/
// Point operator with Vector
Math::Point3D Math::Point3D::operator+(Math::Vector3D other)
{
    return Math::Point3D(this->x + other.getX(), this->y + other.getY(), this->z + other.getZ());
}

Math::Point3D Math::Point3D::operator-(Math::Vector3D other)
{
    return Math::Point3D(this->x - other.getX(), this->y - other.getY(), this->z - other.getZ());
}
/*****************************************************************************/
