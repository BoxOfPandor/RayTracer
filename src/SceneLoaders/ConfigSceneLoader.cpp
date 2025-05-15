/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** ConfigSceneLoader
*/

#include "ConfigSceneLoader.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"
#include "Cylinder.hpp"
#include "FlatMaterial.hpp"
#include "DirectionalLight.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <map>
#include "LightFactory.hpp"
#include "PrimitiveFactory.hpp"
#include "MaterialFactory.hpp"
#include "SceneBuilder.hpp"

using namespace RayTracer;
using namespace libconfig;
using namespace Math;

std::unique_ptr<Scene> ConfigSceneLoader::loadScene(const std::string& filename) const
{
    Config config;

    try {
        config.readFile(filename.c_str());
    } catch(const FileIOException&) {
        throw std::runtime_error("Cannot open scene file: " + filename);
    } catch(const ParseException& e) {
        throw std::runtime_error("Parse error in scene file " + filename +
                               " at line " + std::to_string(e.getLine()) +
                               ": " + e.getError());
    }
    
    SceneBuilder builder;
    
    int width = 800, height = 600;
    Point3D position(0, 0, 0);
    Rectangle3D screen;

    if (config.exists("camera")) {
        parseCamera(config.lookup("camera"), width, height, position, screen);
    }

    Camera camera(position, screen);
    builder.setCamera(camera).setResolution(width, height);

    if (config.exists("primitives")) {
        parsePrimitives(config.lookup("primitives"), builder);
    }

    if (config.exists("lights")) {
        parseLights(config.lookup("lights"), builder);
    }

    return builder.build();
}

void ConfigSceneLoader::parseCamera(const Setting& cameraSettings,
                                  int& width, int& height,
                                  Point3D& position,
                                  Rectangle3D& screen) const
{
    if (cameraSettings.exists("resolution")) {
        const Setting& resolution = cameraSettings["resolution"];
        resolution.lookupValue("width", width);
        resolution.lookupValue("height", height);
    }

    double posX = 0, posY = 0, posZ = 0;
    if (cameraSettings.exists("position")) {
        const Setting& pos = cameraSettings["position"];
        pos.lookupValue("x", posX);
        pos.lookupValue("y", posY);
        pos.lookupValue("z", posZ);
    }
    position = Point3D(posX, posY, posZ);

    double fov = 72.0;
    cameraSettings.lookupValue("fieldOfView", fov);

    double aspectRatio = static_cast<double>(width) / height;
    double distance = 1.0;
    double screenHeight = 2.0 * distance * tan(fov * M_PI / 360.0);
    double screenWidth = screenHeight * aspectRatio;

    Point3D screenOrigin(-screenWidth/2, -screenHeight/2, -distance);
    Vector3D bottomSide(screenWidth, 0, 0);
    Vector3D leftSide(0, screenHeight, 0);
    screen = Rectangle3D(screenOrigin, bottomSide, leftSide);
}

void ConfigSceneLoader::parsePrimitives(const Setting& primitivesSettings, SceneBuilder& builder) const
{
    static std::vector<std::shared_ptr<IMaterial>> materials;
    
    if (primitivesSettings.exists("spheres")) {
        const Setting& spheres = primitivesSettings["spheres"];
        for (int i = 0; i < spheres.getLength(); ++i) {
            parseSphere(spheres[i], builder, materials);
        }
    }
    
    if (primitivesSettings.exists("cylinders")) {
        const Setting& cylinders = primitivesSettings["cylinders"];
        for (int i = 0; i < cylinders.getLength(); ++i) {
            parseCylinder(cylinders[i], builder, materials);
        }
    }
    
    if (primitivesSettings.exists("planes")) {
        const Setting& planes = primitivesSettings["planes"];
        for (int i = 0; i < planes.getLength(); ++i) {
            parsePlane(planes[i], builder, materials);
        }
    }
}

void ConfigSceneLoader::parseLights(const Setting& lightsSettings, SceneBuilder& builder) const
{
    double ambient = 0.1;
    double diffuse = 0.7;

    if (lightsSettings.exists("ambient"))
        lightsSettings.lookupValue("ambient", ambient);
    if (lightsSettings.exists("diffuse"))
        lightsSettings.lookupValue("diffuse", diffuse);

    if (lightsSettings.exists("directional")) {
        const Setting& lights = lightsSettings["directional"];
        for (int i = 0; i < lights.getLength(); ++i) {
            parseDirectionalLight(lights[i], builder);
        }
    }
    
    if (lightsSettings.exists("ambient_light")) {
        const Setting& ambientLights = lightsSettings["ambient_light"];
        for (int i = 0; i < ambientLights.getLength(); ++i) {
            parseAmbientLight(ambientLights[i], builder);
        }
    }
    
    if (lightsSettings.exists("point")) {
        std::cout << "Point lights found but not implemented yet" << std::endl;
    }
}

void ConfigSceneLoader::parsePlane(const Setting& plane, SceneBuilder& builder,
                                 std::vector<std::shared_ptr<IMaterial>>& materials) const
{
    double x = 0.0, y = 0.0, z = 0.0;
    if (plane.exists("x")) plane.lookupValue("x", x);
    if (plane.exists("y")) plane.lookupValue("y", y);
    if (plane.exists("z")) plane.lookupValue("z", z);
    
    double normalX = 0.0, normalY = 1.0, normalZ = 0.0;
    if (plane.exists("normal")) {
        const Setting& normal = plane["normal"];
        if (normal.exists("x")) normal.lookupValue("x", normalX);
        if (normal.exists("y")) normal.lookupValue("y", normalY);
        if (normal.exists("z")) normal.lookupValue("z", normalZ);
    }
    
    Vector3D color = parseColor(plane);
    std::map<std::string, double> materialParams = parseMaterialProperties(plane);
    
    auto material = MaterialFactory::createMaterial("flat", color, materialParams);
    materials.push_back(material);
    
    std::map<std::string, double> params;
    params["x"] = x;
    params["y"] = y;
    params["z"] = z;
    params["normalX"] = normalX;
    params["normalY"] = normalY;
    params["normalZ"] = normalZ;
    
    auto planeObj = PrimitiveFactory::createPrimitive("plane", params, *material);
    builder.addPrimitive(std::move(planeObj));
}

void ConfigSceneLoader::parseSphere(const Setting& sphere, SceneBuilder& builder, 
                                  std::vector<std::shared_ptr<IMaterial>>& materials) const
{
    double x = 0.0, y = 0.0, z = 0.0;
    if (sphere.exists("x")) sphere.lookupValue("x", x);
    if (sphere.exists("y")) sphere.lookupValue("y", y);
    if (sphere.exists("z")) sphere.lookupValue("z", z);
    
    double radius = 1.0;
    if (sphere.exists("r")) sphere.lookupValue("r", radius);
    
    Vector3D color = parseColor(sphere);
    std::map<std::string, double> materialParams = parseMaterialProperties(sphere);
    
    auto material = MaterialFactory::createMaterial("flat", color, materialParams);
    materials.push_back(material); // Store material to keep it alive
    
    auto sphereObj = std::make_unique<Sphere>(
        Math::Point3D(x, y, z), radius, *material
    );
    
    builder.addPrimitive(std::move(sphereObj));
}

void ConfigSceneLoader::parseCylinder(const Setting& cylinder, SceneBuilder& builder,
                                    std::vector<std::shared_ptr<IMaterial>>& materials) const
{
    double x = 0.0, y = 0.0, z = 0.0;
    if (cylinder.exists("x")) cylinder.lookupValue("x", x);
    if (cylinder.exists("y")) cylinder.lookupValue("y", y);
    if (cylinder.exists("z")) cylinder.lookupValue("z", z);
    
    double dirX = 0.0, dirY = 1.0, dirZ = 0.0;
    if (cylinder.exists("direction")) {
        const Setting& dir = cylinder["direction"];
        if (dir.exists("x")) dir.lookupValue("x", dirX);
        if (dir.exists("y")) dir.lookupValue("y", dirY);
        if (dir.exists("z")) dir.lookupValue("z", dirZ);
    }
    
    double radius = 1.0, height = 1.0;
    if (cylinder.exists("r")) cylinder.lookupValue("r", radius);
    if (cylinder.exists("height")) cylinder.lookupValue("height", height);
    
    Vector3D color = parseColor(cylinder);
    std::map<std::string, double> materialParams = parseMaterialProperties(cylinder);
    
    auto material = MaterialFactory::createMaterial("flat", color, materialParams);
    materials.push_back(material);
    
    auto cylinderObj = std::make_unique<Cylinder>(
        Math::Point3D(x, y, z), 
        Math::Vector3D(dirX, dirY, dirZ),
        radius, 
        height, 
        *material
    );
    
    builder.addPrimitive(std::move(cylinderObj));
}

void ConfigSceneLoader::parseDirectionalLight(const Setting& light, SceneBuilder& builder) const
{
    std::map<std::string, double> params;
    double x = 0, y = -1, z = 0, intensity = 1.0;
    
    if (light.exists("direction")) {
        const Setting& dir = light["direction"];
        if (dir.exists("x")) { dir.lookupValue("x", x); params["x"] = x; }
        if (dir.exists("y")) { dir.lookupValue("y", y); params["y"] = y; }
        if (dir.exists("z")) { dir.lookupValue("z", z); params["z"] = z; }
    } else {
        if (light.exists("x")) { light.lookupValue("x", x); params["x"] = x; }
        if (light.exists("y")) { light.lookupValue("y", y); params["y"] = y; }
        if (light.exists("z")) { light.lookupValue("z", z); params["z"] = z; }
    }
    
    light.lookupValue("intensity", intensity);
    params["intensity"] = intensity;
    
    Vector3D color = parseColor(light);
    
    try {
        auto dirLight = LightFactory::createLight("directional", params, color);
        builder.addLight(std::move(dirLight));
    } catch (const std::exception& e) {
        std::cerr << "Error creating directional light: " << e.what() << std::endl;
        throw;
    }
}

void ConfigSceneLoader::parseAmbientLight(const libconfig::Setting& light, SceneBuilder& builder) const
{
    std::map<std::string, double> params;
    double intensity = 1.0;
    
    if (light.exists("intensity")) {
        light.lookupValue("intensity", intensity);
        params["intensity"] = intensity;
    }
    
    Vector3D color = parseColor(light);
    
    try {
        auto ambientLight = LightFactory::createLight("ambient", params, color);
        builder.addLight(std::move(ambientLight));
    } catch (const std::exception& e) {
        std::cerr << "Error creating ambient light: " << e.what() << std::endl;
        throw;
    }
}

Math::Vector3D ConfigSceneLoader::parseColor(const Setting& setting) const
{
    double r = 1.0, g = 1.0, b = 1.0;
    
    if (setting.exists("color")) {
        const Setting& color = setting["color"];
        int redInt = 255, greenInt = 255, blueInt = 255;
        
        if (color.exists("r")) color.lookupValue("r", redInt);
        if (color.exists("g")) color.lookupValue("g", greenInt);
        if (color.exists("b")) color.lookupValue("b", blueInt);
        
        r = redInt / 255.0;
        g = greenInt / 255.0;
        b = blueInt / 255.0;
    }
    
    return Vector3D(r, g, b);
}

std::map<std::string, double> ConfigSceneLoader::parseMaterialProperties(const Setting& setting) const
{
    std::map<std::string, double> materialParams;
    double ambient = 0.1, diffuse = 0.7, specular = 0.2, shininess = 50.0;
    
    if (setting.exists("material")) {
        const Setting& matSettings = setting["material"];
        if (matSettings.exists("ambient")) matSettings.lookupValue("ambient", ambient);
        if (matSettings.exists("diffuse")) matSettings.lookupValue("diffuse", diffuse);
        if (matSettings.exists("specular")) matSettings.lookupValue("specular", specular);
        if (matSettings.exists("shininess")) matSettings.lookupValue("shininess", shininess);
    }
    
    materialParams["ambient"] = ambient;
    materialParams["diffuse"] = diffuse;
    materialParams["specular"] = specular;
    materialParams["shininess"] = shininess;
    
    return materialParams;
}
