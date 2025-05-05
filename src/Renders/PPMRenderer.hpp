/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** PpmRenderer.hpp
*/

#ifndef PPMRENDERER_HPP
#define PPMRENDERER_HPP

#include "IRenderer.hpp"

namespace RayTracer {
    class PPMRenderer : public IRenderer {
    public:
        PPMRenderer() = default;
        ~PPMRenderer() = default;

        bool render(const Scene& scene, const std::string& outputFile) const override;
    };
}

#endif // PPMRENDERER_HPP

