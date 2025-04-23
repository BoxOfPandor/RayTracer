/*
** EPITECH PROJECT, 2025
** B-OOP-400-LIL-4-1-raytracer-thibault.pouch
** File description:
** Vector3D
*/

#include "Vector3D.hpp"
using namespace Math;

Vector3D::Vector3D()
{
    this->_x = 0;
    this->_y = 0;
    this->_z = 0;
}

Vector3D::Vector3D(double x, double y, double z)
{
    this->_x = x;
    this->_y = y;
    this->_z = z;
}

double Vector3D::getX() const
{
    return this->_x;
}

double Vector3D::getY() const
{
    return this->_y;
}

double Vector3D::getZ() const
{
    return this->_z;
}

double Vector3D::length() const
{
    return sqrt(this->_x * this->_x + this->_y * this->_y + this->_z * this->_z);
}

double Vector3D::dot(const Vector3D& vec1, const Vector3D& vec2)
{
    return vec1.getX() * vec2.getX() + vec1.getY() * vec2.getY() + vec1.getZ() * vec2.getZ();
}

Vector3D Vector3D::operator*(double n) const
{
    return {this->_x * n, this->_y * n, this->_z * n};
}

void Vector3D::operator*=(double n)
{
    this->_x *= n;
    this->_y *= n;
    this->_z *= n;
}

Vector3D Vector3D::operator/(double n) const
{
    return {this->_x / n, this->_y / n, this->_z / n};
}

void Vector3D::operator/=(double n)
{
    this->_x /= n;
    this->_y /= n;
    this->_z /= n;
}

Vector3D Vector3D::operator+(const Vector3D& other) const
{
    return {this->_x + other._x, this->_y + other._y, this->_z + other._z};
}

void Vector3D::operator+=(const Vector3D& other)
{
    this->_x += other._x;
    this->_y += other._y;
    this->_z += other._z;
}

Vector3D Vector3D::operator-(const Vector3D& other) const
{
    return {this->_x - other._x, this->_y - other._y, this->_z - other._z};
}

void Vector3D::operator-=(const Vector3D& other)
{
    this->_x -= other._x;
    this->_y -= other._y;
    this->_z -= other._z;
}

Vector3D Vector3D::operator*(const Vector3D& other) const
{
    return {this->_x * other._x, this->_y * other._y, this->_z * other._z};
}

void Vector3D::operator*=(const Vector3D& other)
{
    this->_x *= other._x;
    this->_y *= other._y;
    this->_z *= other._z;
}

Vector3D Vector3D::operator/(const Vector3D& other) const
{
    return {this->_x / other._x, this->_y / other._y, this->_z / other._z};
}

void Vector3D::operator/=(const Vector3D& other)
{
    this->_x /= other._x;
    this->_y /= other._y;
    this->_z /= other._z;
}
