/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** SceneBuilder.cpp
*/

#include "SceneBuilder.hpp"

using namespace RayTracer;

SceneBuilder::SceneBuilder() : _width(800), _height(600)
{
    _camera = Camera();
}

SceneBuilder& SceneBuilder::setCamera(const Camera& camera)
{
    _camera = camera;
    return *this;
}

SceneBuilder& SceneBuilder::setResolution(int width, int height)
{
    _width = width;
    _height = height;
    return *this;
}

SceneBuilder& SceneBuilder::addPrimitive(std::unique_ptr<IPrimitive> primitive)
{
    _primitives.push_back(std::move(primitive));
    return *this;
}

SceneBuilder& SceneBuilder::addLight(std::unique_ptr<ILight> light)
{
    _lights.push_back(std::move(light));
    return *this;
}

std::unique_ptr<Scene> SceneBuilder::build()
{
    auto scene = std::make_unique<Scene>(_camera, _width, _height);
    
    for (auto& primitive : _primitives) {
        scene->addPrimitive(std::move(primitive));
    }
    _primitives.clear();
    
    for (auto& light : _lights) {
        scene->addLight(std::move(light));
    }
    _lights.clear();
    
    return scene;
}

void SceneBuilder::reset()
{
    _camera = Camera();
    _width = 800;
    _height = 600;
    _primitives.clear();
    _lights.clear();
}
