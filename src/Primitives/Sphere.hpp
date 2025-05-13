/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Sphere
*/

#include "APrimitive.hpp"

#ifndef SPHERE_HPP
    #define SPHERE_HPP

namespace RayTracer {
    class Sphere : public APrimitive {
        public:
            Sphere(const Math::Point3D& origin, double radius, const IMaterial& material);
            ~Sphere();

            bool getIntersection(const Ray& ray) const;

        private:
            Math::Point3D _origin;
            double _radius;
            const IMaterial& _material;
    };
}

#endif
