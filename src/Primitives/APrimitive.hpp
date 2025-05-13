/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** APrimitive
*/

#include "IPrimitive.hpp"

#ifndef APRIMITIVE_HPP
    #define APRIMITIVE_HPP

namespace RayTracer {
    class APrimitive : public IPrimitive {
        public:
            APrimitive(const Math::Point3D& origin, const IMaterial& material);
            ~APrimitive() = default;

            bool hits(const Ray& ray) const;
            Math::Vector3D getNormalAt(const Math::Point3D& point) const;
            void translate(const Math::Vector3D& translation);
            // void rotateX(double angle);
            // void rotateY(double angle);
            // void rotateZ(double angle);
            const IMaterial& getMaterial() const;

        private:
            Math::Point3D _origin;
            const IMaterial& _material;
    };
}

#endif
