/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Sphere
*/

#include "APrimitive.hpp"

#ifndef PLANE_HPP
    #define PLANE_HPP

namespace RayTracer {
    class Plane : public APrimitive {
        public:
            Plane(const Math::Point3D& origin, const Math::Point3D& size, const IMaterial& material);
            ~Plane();

            Math::Vector3D getNormalAt(const Math::Point3D& point) const;
            bool getIntersection(const Ray &ray) const;

        private:
            Math::Point3D _origin;
            Math::Point3D _size;
            const IMaterial& _material;
    };
}

#endif
