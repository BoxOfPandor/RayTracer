/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** DirectionalLight.hpp
*/

#ifndef DIRECTIONALLIGHT_HPP
#define DIRECTIONALLIGHT_HPP

#include "ILight.hpp"

namespace RayTracer {
    /**
     * @brief Represents a directional light source in the scene
     *
     * A directional light emits light rays in a specific direction.
     * The light rays are parallel and come from an infinitely distant source,
     * similar to sunlight.
     */
    class DirectionalLight : public ILight {
    public:
        /**
         * @brief Construct a new Directional Light
         *
         * @param direction The direction from which the light is coming (will be normalized)
         * @param color The color of the light
         * @param intensity The intensity of the light, default is 1.0
         */
        DirectionalLight(const Math::Vector3D& direction, const Math::Vector3D& color, double intensity = 1.0);

        /**
         * @brief Get the direction of light rays at a specific point
         *
         * @param point The point at which to calculate the light direction
         * @return Math::Vector3D The normalized direction vector
         */
        Math::Vector3D getDirection() const;

        /**
         * @brief Get the intensity of the light at a specific point
         *
         * @param point The point at which to calculate the light intensity
         * @return double The intensity value at the given point
         */
        double getIntensity() const;

        /**
         * @brief Get the color of the light
         *
         * @return Math::Vector3D The RGB color vector of the light
         */
        Math::Vector3D getColor() const override;

        /**
         * @brief Determine if a point is in shadow relative to this light
         *
         * @param point The point to check for shadows
         * @param scene The scene containing all primitives for shadow testing
         * @return true If the point is in shadow
         * @return false If the point is not in shadow
         */
        bool isShadowed(const Math::Point3D& point, const Scene& scene) const override;

    private:
        Math::Vector3D _direction;
        Math::Vector3D _color;
        double _intensity;
    };
}

#endif // DIRECTIONALLIGHT_HPP

