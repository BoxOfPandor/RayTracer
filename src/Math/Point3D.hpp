/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Point3D
*/

#ifndef POINT3D_HPP
#define POINT3D_HPP

#include "Vector3D.hpp"

namespace Math {
    class Point3D {
    public:
        Point3D();
        Point3D(double x, double y, double z);
        ~Point3D() = default;

        double getX() const;
        double getY() const;
        double getZ() const;

        Point3D operator+(Vector3D other) const;
        Point3D operator+(Point3D other) const;
        Point3D operator-(Vector3D other) const;
        Point3D operator-(Point3D other) const;
        Point3D operator*(double other) const;

    private:
        double _x;
        double _y;
        double _z;
    };
} // Math

#endif //POINT3D_HPP
