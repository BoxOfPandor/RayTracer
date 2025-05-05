/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** ISceneLoader.hpp
*/

#ifndef ISCENELOADER_HPP
#define ISCENELOADER_HPP

#include <string>
#include <memory>

namespace RayTracer {

    class Scene;
    class ISceneLoader {
    public:
        virtual ~ISceneLoader() = default;

        /**
         * @brief Load a scene from a file
         * @param filename The path to the scene file
         * @return A unique pointer to the loaded scene
         * @throws std::runtime_error if the scene could not be loaded
         */
        virtual std::unique_ptr<Scene> loadScene(const std::string& filename) const = 0;
    };
} // namespace RayTracer

#endif // ISCENELOADER_HPP
