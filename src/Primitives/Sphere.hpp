/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Sphere
*/

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "src/Math/Point3D.hpp"
#include "src/Math/Vector3D.hpp"
#include "src/Ray.hpp"

namespace RayTracer {
    class Sphere {
    public:
        Sphere();
        Sphere(const Math::Point3D& origin, double radius);
        ~Sphere() = default;

        bool hit(const Ray& ray) const;
    private:
        Math::Point3D _origin;
        double _radius;
    };
} // RayTracer

#endif //SPHERE_HPP
