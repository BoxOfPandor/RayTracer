/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** IMaterial.hpp
*/

#ifndef IMATERIAL_HPP
#define IMATERIAL_HPP

#include "../Math/Vector3D.hpp"
#include "../Math/Point3D.hpp"

namespace RayTracer {

    class IMaterial {
    public:
        virtual ~IMaterial() = default;

        /**
         * @brief Get the color of the material at a specific point
         * @param point The point to get the color at
         * @return The color as a Vector3D (R, G, B)
         */
        virtual Math::Vector3D getColor(const Math::Point3D& point) const = 0;

        /**
         * @brief Get the ambient reflection coefficient
         * @return The ambient reflection coefficient (between 0 and 1)
         */
        virtual double getAmbient() const = 0;

        /**
         * @brief Get the diffuse reflection coefficient
         * @return The diffuse reflection coefficient (between 0 and 1)
         */
        virtual double getDiffuse() const = 0;

        /**
         * @brief Get the specular reflection coefficient
         * @return The specular reflection coefficient (between 0 and 1)
         */
        virtual double getSpecular() const = 0;

        /**
         * @brief Get the shininess of the material
         * @return The shininess (controls the size of specular highlights)
         */
        virtual double getShininess() const = 0;
    };
} // namespace RayTracer

#endif // IMATERIAL_HPP
