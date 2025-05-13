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
    class DirectionalLight : public ILight {
    public:
        DirectionalLight(const Math::Vector3D& direction, const Math::Vector3D& color, double intensity = 1.0);

        Math::Vector3D getDirection() const override;
        double getIntensity() const override;
        Math::Vector3D getColor() const override;
        bool isShadowed(const Math::Point3D& point, const Scene& scene) const override;

    private:
        Math::Vector3D _direction;
        Math::Vector3D _color;
        double _intensity;
    };
}

#endif // DIRECTIONALLIGHT_HPP

