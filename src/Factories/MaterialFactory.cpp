/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** MaterialFactory.cpp
*/

#include "MaterialFactory.hpp"
#include "FlatMaterial.hpp"
#include <stdexcept>

using namespace RayTracer;
using namespace Math;

std::shared_ptr<IMaterial> MaterialFactory::createMaterial(
    const std::string& type,
    const Vector3D& color,
    const std::map<std::string, double>& params)
{
    if (type == "flat") {
        double ambient = params.count("ambient") ? params.at("ambient") : 0.1;
        double diffuse = params.count("diffuse") ? params.at("diffuse") : 0.7;
        double specular = params.count("specular") ? params.at("specular") : 0.2;
        double shininess = params.count("shininess") ? params.at("shininess") : 50.0;
        
        return std::make_shared<FlatMaterial>(color, ambient, diffuse, specular, shininess);
    }
    // Add other material types here as needed
    
    throw std::runtime_error("Unknown material type: " + type);
}
