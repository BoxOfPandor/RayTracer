/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** IRenderer.hpp
*/

#ifndef IRENDERER_HPP
#define IRENDERER_HPP

#include <string>

namespace RayTracer {
    class Scene;

    class IRenderer {
    public:
        virtual ~IRenderer() = default;

        /**
         * @brief Render the scene to a file
         * @param scene The scene to render
         * @param outputFile The output file path
         * @return true if rendering was successful, false otherwise
         */
        virtual bool render(const Scene& scene, const std::string& outputFile) const = 0;
    };
} // namespace RayTracer

#endif // IRENDERER_HPP