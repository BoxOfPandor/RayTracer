/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** PrimitiveFactory.hpp
*/

#ifndef PRIMITIVEFACTORY_HPP
#define PRIMITIVEFACTORY_HPP

#include "IPrimitive.hpp"
#include "IMaterial.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include <memory>
#include <string>
#include <map>

namespace RayTracer {
    class PrimitiveFactory {
    public:
        /**
         * @brief Creates a primitive of the specified type
         * @param type The type of primitive to create ("sphere", "cylinder", "plane", etc.)
         * @param params Parameters specific to the primitive type
         * @param material The material to apply to the primitive
         * @return A unique pointer to the created primitive
         */
        static std::unique_ptr<IPrimitive> createPrimitive(
            const std::string& type,
            const std::map<std::string, double>& params,
            const IMaterial& material
        );

        /**
         * @brief Creates a material with the specified properties
         * @param color The color of the material
         * @param ambient The ambient reflection coefficient (default: 0.1)
         * @param diffuse The diffuse reflection coefficient (default: 0.7)
         * @param specular The specular reflection coefficient (default: 0.2)
         * @param shininess The shininess factor (default: 50)
         * @return A shared pointer to the created material
         */
        static std::shared_ptr<IMaterial> createMaterial(
            const Math::Vector3D& color,
            double ambient = 0.1,
            double diffuse = 0.7,
            double specular = 0.2,
            double shininess = 50
        );
    };
}

#endif // PRIMITIVEFACTORY_HPP
