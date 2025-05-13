/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Scene.cpp
*/

#include "Scene.hpp"
#include <limits>
#include <algorithm>

using namespace RayTracer;
using namespace Math;

Scene::Scene(const Camera& camera, int width, int height)
    : _camera(camera), _width(width), _height(height)
{
}

void Scene::addPrimitive(std::unique_ptr<IPrimitive> primitive)
{
    _primitives.push_back(std::move(primitive));
}

void Scene::addLight(std::unique_ptr<ILight> light)
{
    _lights.push_back(std::move(light));
}

const Camera& Scene::getCamera() const
{
    return _camera;
}

int Scene::getWidth() const
{
    return _width;
}

int Scene::getHeight() const
{
    return _height;
}

const std::vector<std::unique_ptr<IPrimitive>>& Scene::getPrimitives() const
{
    return _primitives;
}

const std::vector<std::unique_ptr<ILight>>& Scene::getLights() const
{
    return _lights;
}

bool Scene::findClosestIntersection(const Ray& ray, Intersection& result) const
{
    double closestT = std::numeric_limits<double>::max();
    bool found = false;

    for (const auto& primitive : _primitives) {
        double t;
        if (primitive->getIntersection(ray) && t < closestT) {
            closestT = t;
            result.primitive = primitive.get();
            result.distance = t;
            result.point = ray.at(t);
            result.normal = primitive->getNormalAt(result.point);
            found = true;
        }
    }

    return found;
}

Vector3D Scene::traceRay(const Ray& ray, int depth) const
{
    // Base case: maximum recursion depth reached
    if (depth > 5) {
        return Vector3D(0, 0, 0);
    }

    Intersection intersection;
    if (!findClosestIntersection(ray, intersection)) {
        return Vector3D(0.05, 0.05, 0.1); // Background color
    }

    // Get material of the intersected object
    const IMaterial& material = intersection.primitive->getMaterial();

    // Calculate lighting
    Vector3D color = material.getColor() * material.getAmbient();

    for (const auto& light : _lights) {
        if (!light->isShadowed(intersection.point, *this)) {
            Vector3D lightDir = light->getDirection();
            double diffuseIntensity = std::max(0.0, Vector3D::dot(intersection.normal, lightDir * -1));

            if (diffuseIntensity > 0) {
                // Diffuse lighting
                Vector3D diffuse = material.getColor() * diffuseIntensity * material.getDiffuse();

                // Specular lighting
                Vector3D viewDir = ray.getDirection() * -1;
                Vector3D halfwayDir = (viewDir + (lightDir * -1)) / (viewDir + (lightDir * -1)).length();
                double specularIntensity = std::pow(std::max(0.0, Vector3D::dot(intersection.normal, halfwayDir)), material.getShininess());
                Vector3D specular = light->getColor() * specularIntensity * material.getSpecular();

                color = color + (diffuse + specular) * light->getIntensity() * light->getColor();
            }
        }
    }

    // Clamp color values to [0,1]
    return Vector3D(
        std::min(1.0, std::max(0.0, color.getX())),
        std::min(1.0, std::max(0.0, color.getY())),
        std::min(1.0, std::max(0.0, color.getZ()))
    );
}

