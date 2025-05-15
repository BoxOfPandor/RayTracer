/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** SceneBuilder.hpp
*/

#ifndef SCENEBUILDER_HPP
#define SCENEBUILDER_HPP

#include "Scene.hpp"
#include "Camera.hpp"
#include "IPrimitive.hpp"
#include "ILight.hpp"
#include <memory>
#include <vector>

namespace RayTracer {
    class SceneBuilder {
    public:
        SceneBuilder();
        ~SceneBuilder() = default;

        // Building methods
        SceneBuilder& setCamera(const Camera& camera);
        SceneBuilder& setResolution(int width, int height);
        SceneBuilder& addPrimitive(std::unique_ptr<IPrimitive> primitive);
        SceneBuilder& addLight(std::unique_ptr<ILight> light);

        // Build the final scene
        std::unique_ptr<Scene> build();

        // Reset the builder to start fresh
        void reset();

    private:
        Camera _camera;
        int _width;
        int _height;
        std::vector<std::unique_ptr<IPrimitive>> _primitives;
        std::vector<std::unique_ptr<ILight>> _lights;
    };
}

#endif // SCENEBUILDER_HPP
