/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Rectangle3D
*/

#ifndef RECTANGLE3D_HPP
#define RECTANGLE3D_HPP

#include "src/Math/Point3D.hpp"
#include "src/Math/Vector3D.hpp"

namespace RayTracer {
    class Rectangle3D {
    public:
        Rectangle3D();
        Rectangle3D(const Math::Point3D& origin, const Math::Vector3D& bottom_side, const Math::Vector3D& left_side);
        ~Rectangle3D() = default;

        Math::Point3D pointAt(double u, double v) const;

        Math::Point3D getOrigin() const;
        Math::Vector3D getBottomSide() const;
        Math::Vector3D getLeftSide() const;

    private:
        Math::Point3D _origin;
        Math::Vector3D _bottom_side;
        Math::Vector3D _left_side;
    };
} // namespace RayTracer

#endif // RECTANGLE3D_HPP