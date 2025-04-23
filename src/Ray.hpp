/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Ray
*/

#ifndef RAY_HPP_
#define RAY_HPP_

#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"

namespace RayTracer {
    class Ray {
    public:
        Ray(const Math::Point3D& origin, const Math::Vector3D& direction);
        Ray() = default;

        Math::Point3D getOrigin();
        Math::Vector3D getDirection();

        Math::Point3D at(double t) const;
    private:
        Math::Point3D _origin;
        Math::Vector3D _direction;
    };
} // namespace RayTracer

#endif // RAY_HPP_