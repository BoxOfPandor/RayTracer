/*
** EPITECH PROJECT, 2025
** B-OOP-400-LIL-4-1-raytracer-thibault.pouch
** File description:
** Vector3D
*/

#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP
#include <cmath>

namespace Math {
    class Vector3D {
    public:
        Vector3D();
        Vector3D(double x, double y, double z);
        ~Vector3D() = default;

        double getX() const;
        double getY() const;
        double getZ() const;

        double length() const;
        static double dot(const Vector3D& vec1, const Vector3D& vec2);
        Vector3D normalize() const;
        Vector3D cross(const Vector3D& v) const;

        Vector3D operator+(const Vector3D& other) const;
        void operator+=(const Vector3D& other);
        Vector3D operator-(const Vector3D& other) const;
        void operator-=(const Vector3D& other);
        Vector3D operator*(const Vector3D& other) const;
        void operator*=(const Vector3D& other);
        Vector3D operator/(const Vector3D& other) const;
        void operator/=(const Vector3D& other);

        Vector3D operator*(double n) const;
        void operator*=(double n);
        Vector3D operator/(double n) const;
        void operator/=(double n);

    private:
        double _x;
        double _y;
        double _z;
    };
} // Math

#endif //VECTOR3D_HPP
