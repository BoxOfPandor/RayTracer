/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** MaterialFactory.hpp
*/

#ifndef MATERIALFACTORY_HPP
#define MATERIALFACTORY_HPP

#include "IMaterial.hpp"
#include "Vector3D.hpp"
#include <memory>
#include <string>
#include <map>

namespace RayTracer {
    class MaterialFactory {
    public:
        static std::shared_ptr<IMaterial> createMaterial(
            const std::string& type,
            const Math::Vector3D& color,
            const std::map<std::string, double>& params = {});
    };
}

#endif // MATERIALFACTORY_HPP
