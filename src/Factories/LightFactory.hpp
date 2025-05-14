/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** LightFactory.hpp
*/

#ifndef LIGHTFACTORY_HPP
#define LIGHTFACTORY_HPP

#include "ILight.hpp"
#include <memory>
#include <string>
#include <map>

namespace RayTracer {
    class LightFactory {
    public:
        /**
         * @brief Creates a light of the specified type
         * @param type The type of light to create ("directional", "point", etc.)
         * @param params Parameters specific to the light type
         * @return A unique pointer to the created light
         */
        static std::unique_ptr<ILight> createLight(const std::string& type, 
                                                  const std::map<std::string, double>& params,
                                                  const Math::Vector3D& color);
    };
}

#endif // LIGHTFACTORY_HPP
