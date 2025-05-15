/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** ILight.hpp
*/

#ifndef ILIGHT_HPP
#define ILIGHT_HPP

#include "Vector3D.hpp"
#include "Point3D.hpp"
#include "Ray.hpp"

namespace RayTracer {
    class Scene;

    class ILight {
    public:
        virtual ~ILight() = default;

        /**
         * @brief Get the direction of the light from a given point
         * @param point The point to get the direction from
         * @return The direction vector of the light
         */
        virtual Math::Vector3D getDirection() const = 0;

        /**
         * @brief Get the intensity of the light at a given point
         * @param point The point to get the intensity at
         * @return The intensity of the light (between 0 and 1)
         */
        virtual double getIntensity() const = 0;

        /**
         * @brief Get the color of the light
         * @return The color of the light as a Vector3D (R, G, B)
         */
        virtual Math::Vector3D getColor() const = 0;

        /**
         * @brief Check if the light is blocked by an object in the scene
         * @param point The point to check from
         * @param scene The scene containing all primitives
         * @return true if the light is blocked, false otherwise
         */
        virtual bool isShadowed(const Math::Point3D& point, const Scene& scene) const = 0;
    };
} // namespace RayTracer

#endif // ILIGHT_HPP
