/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** AmbientLight.hpp
*/

#ifndef AMBIENTLIGHT_HPP
#define AMBIENTLIGHT_HPP

#include "ILight.hpp"

namespace RayTracer {
    /**
     * @brief Represents an ambient light source in the scene
     *
     * An ambient light illuminates all surfaces uniformly from all directions,
     * similar to a mini sun. It doesn't cast shadows and provides base illumination.
     */
    class AmbientLight : public ILight {
    public:
        /**
         * @brief Construct a new Ambient Light
         *
         * @param color The color of the light
         * @param intensity The intensity of the light, default is 1.0
         */
        AmbientLight(const Math::Vector3D& color, double intensity = 1.0);

        Math::Vector3D getDirection(const Math::Point3D& point) const override;
        double getIntensity(const Math::Point3D& point) const override;
        Math::Vector3D getColor() const override;
        bool isShadowed(const Math::Point3D& point, const Scene& scene) const override;

    private:
        Math::Vector3D _color;
        double _intensity;
    };
}

#endif // AMBIENTLIGHT_HPP
