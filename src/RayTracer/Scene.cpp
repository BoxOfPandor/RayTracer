/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Scene.cpp
*/

#include "Scene.hpp"
#include <limits>
#include <algorithm>
#include <ostream>
#include <iostream>

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

    // Material base color at intersection point
    Vector3D materialColor = material.getColor(intersection.point);
    
    // Start with ambient component
    Vector3D ambientComponent = materialColor * material.getAmbient();
    Vector3D finalColor = ambientComponent;
    
    // Debug: Print information about the lights
    static bool debugPrinted = false;
    if (!debugPrinted) {
        std::cout << "==== LIGHT DEBUG INFO ====" << std::endl;
        int lightIndex = 0;
        for (const auto& light : _lights) {
            Vector3D lightColor = light->getColor();
            std::cout << "Light #" << lightIndex++ << " Color: "
                     << "R=" << lightColor.getX() 
                     << ", G=" << lightColor.getY() 
                     << ", B=" << lightColor.getZ() << std::endl;
        }
        std::cout << "=========================" << std::endl;
        debugPrinted = true;
    }

    for (const auto& light : _lights) {
        // Skip if in shadow
        if (light->isShadowed(intersection.point, *this)) {
            continue;
        }
        
        // Get light properties
        Vector3D lightDir = light->getDirection(intersection.point);
        Vector3D lightColor = light->getColor();
        double lightIntensity = light->getIntensity(intersection.point);
        
        // Calculate diffuse factor
        double diffuseFactor = std::max(0.0, Vector3D::dot(intersection.normal, lightDir * -1));
        
        if (diffuseFactor > 0) {
            // Calculate diffuse component (material color * light color)
            Vector3D diffuseComponent = materialColor * lightColor * diffuseFactor * material.getDiffuse() * lightIntensity;
            
            // Calculate specular component
            Vector3D viewDir = ray.getDirection() * -1;
            Vector3D halfwayDir = (viewDir + (lightDir * -1));
            double halfwayLength = halfwayDir.length();
            
            if (halfwayLength > 0.0001) {
                halfwayDir = halfwayDir / halfwayLength; // Normalize
                double specularFactor = std::pow(
                    std::max(0.0, Vector3D::dot(intersection.normal, halfwayDir)), 
                    material.getShininess()
                );
                Vector3D specularComponent = lightColor * specularFactor * material.getSpecular() * lightIntensity;
                
                // Add diffuse and specular to final color
                finalColor = finalColor + diffuseComponent + specularComponent;
            } else {
                // Just add diffuse if we can't calculate specular
                finalColor = finalColor + diffuseComponent;
            }
        }
    }

    // Clamp color values to [0,1]
    return Vector3D(
        std::min(1.0, std::max(0.0, finalColor.getX())),
        std::min(1.0, std::max(0.0, finalColor.getY())),
        std::min(1.0, std::max(0.0, finalColor.getZ()))
    );
}
