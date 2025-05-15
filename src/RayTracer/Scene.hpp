/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Scene.hpp
*/

#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <memory>
#include "Camera.hpp"
#include "IPrimitive.hpp"
#include "ILight.hpp"
#include "IMaterial.hpp"
#include "FlatMaterial.hpp"
#include "Intersection.hpp"

namespace RayTracer {
    class Scene {
    public:
        Scene(const Camera& camera, int width, int height);
        ~Scene() = default;

        void addPrimitive(std::unique_ptr<IPrimitive> primitive);
        void addLight(std::unique_ptr<ILight> light);

        const Camera& getCamera() const;
        int getWidth() const;
        int getHeight() const;
        const std::vector<std::unique_ptr<IPrimitive>>& getPrimitives() const;
        const std::vector<std::unique_ptr<ILight>>& getLights() const;

        Math::Vector3D traceRay(const Ray& ray, int depth = 0) const;

    private:
        Camera _camera;
        int _width;
        int _height;
        std::vector<std::unique_ptr<IPrimitive>> _primitives;
        std::vector<std::unique_ptr<ILight>> _lights;

        bool findClosestIntersection(const Ray& ray, Intersection& result) const;
    };
}

#endif // SCENE_HPP
