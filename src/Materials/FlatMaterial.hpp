/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** FlatMaterial.hpp
*/

#ifndef FLATMATERIAL_HPP
#define FLATMATERIAL_HPP

#include "IMaterial.hpp"

namespace RayTracer {
    class FlatMaterial : public IMaterial {
    public:
        FlatMaterial(const Math::Vector3D& color, double ambient = 0.1,
                    double diffuse = 0.7, double specular = 0.2, double shininess = 50);

        Math::Vector3D getColor() const override;
        double getAmbient() const override;
        double getDiffuse() const override;
        double getSpecular() const override;
        double getShininess() const override;

    private:
        Math::Vector3D _color;
        double _ambient;
        double _diffuse;
        double _specular;
        double _shininess;
    };
}

#endif // FLATMATERIAL_HPP
