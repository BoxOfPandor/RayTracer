/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Sphere
*/

#include "IPrimitive.hpp"

#ifndef PLANE_HPP
    #define PLANE_HPP

namespace RayTracer {
    class Plane : public IPrimitive {
        public:
            Plane(const Math::Point3D& origin, const Math::Vector3D& size, const IMaterial& material);
            ~Plane();

            bool hits(const Ray& ray) const;
            Math::Vector3D getNormalAt(const Math::Point3D& point) const;
            bool getIntersection(const Ray &ray) const;
            void translate(const Math::Vector3D& translation);
            void rotateX(double angle);
            void rotateY(double angle);
            void rotateZ(double angle);
            const IMaterial& getMaterial() const;

        private:
            Math::Point3D _origin;
            Math::Vector3D _size;
            const IMaterial& _material;
    };
}

#endif
