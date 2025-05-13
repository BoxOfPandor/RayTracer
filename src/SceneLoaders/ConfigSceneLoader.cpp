/*
** EPITECH PROJECT, 2025
** B-OOP-400-LIL-4-1-raytracer-thibault.pouch
** File description:
** ConfigSceneLoader
*/

#include "ConfigSceneLoader.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"
#include "FlatMaterial.hpp"
#include "DirectionalLight.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>

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

    int width = 800, height = 600;
    Point3D position(0, 0, 0);
    Rectangle3D screen;

    if (config.exists("camera")) {
        parseCamera(config.lookup("camera"), width, height, position, screen);
    }

    Camera camera(position, screen);
    auto scene = std::make_unique<Scene>(camera, width, height);

    if (config.exists("primitives")) {
        parsePrimitives(config.lookup("primitives"), *scene);
    }

    if (config.exists("lights")) {
        parseLights(config.lookup("lights"), *scene);
    }

    return scene;
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

void ConfigSceneLoader::parsePrimitives(const Setting& primitivesSettings, Scene& scene) const
{
    static std::vector<std::shared_ptr<IMaterial>> materials;

    if (primitivesSettings.exists("spheres"))
        parseSpheres(primitivesSettings["spheres"], scene, materials);

    if (primitivesSettings.exists("planes"))
        parsePlanes(primitivesSettings["planes"], scene, materials);
}

void ConfigSceneLoader::parseSpheres(const Setting& spheres, Scene& scene,
                                    std::vector<std::shared_ptr<IMaterial>>& materials) const
{
    for (int i = 0; i < spheres.getLength(); ++i) {
        const Setting& sphere = spheres[i];

        double x = 0, y = 0, z = 0, r = 1;
        sphere.lookupValue("x", x);
        sphere.lookupValue("y", y);
        sphere.lookupValue("z", z);
        sphere.lookupValue("r", r);

        int red = 255, green = 255, blue = 255;
        if (sphere.exists("color")) {
            const Setting& color = sphere["color"];
            color.lookupValue("r", red);
            color.lookupValue("g", green);
            color.lookupValue("b", blue);
        }

        auto material = std::make_shared<FlatMaterial>(
            Vector3D(red/255.0, green/255.0, blue/255.0)
        );
        materials.push_back(material);

        auto sphereObj = std::make_unique<Sphere>(
            Point3D(x, y, z), r, *material
        );

        scene.addPrimitive(std::move(sphereObj));
    }
}

void ConfigSceneLoader::parsePlanes(const Setting& planes, Scene& scene,
                                  std::vector<std::shared_ptr<IMaterial>>& materials) const
{
    // Will be implemented when Plane class is available
    (void)planes;
    (void)scene;
    (void)materials;
}

void ConfigSceneLoader::parseLights(const Setting& lightsSettings, Scene& scene) const
{
    double ambient = 0.1;
    double diffuse = 0.7;

    if (lightsSettings.exists("ambient"))
        lightsSettings.lookupValue("ambient", ambient);
    if (lightsSettings.exists("diffuse"))
        lightsSettings.lookupValue("diffuse", diffuse);

    if (lightsSettings.exists("point")) {
        parsePointLights(lightsSettings["point"], scene);
    }

    if (lightsSettings.exists("directional")) {
        parseDirectionalLights(lightsSettings["directional"], scene);
    }
}

void ConfigSceneLoader::parsePointLights(const Setting& lights, Scene& scene) const
{

}

void ConfigSceneLoader::parseDirectionalLights(const Setting& lights, Scene& scene) const
{
    for (int i = 0; i < lights.getLength(); ++i) {
        const Setting& light = lights[i];

        double x = 0, y = 0, z = -1;
        double r = 1.0, g = 1.0, b = 1.0;
        double intensity = 1.0;

        if (light.exists("x")) light.lookupValue("x", x);
        if (light.exists("y")) light.lookupValue("y", y);
        if (light.exists("z")) light.lookupValue("z", z);

        if (light.exists("color")) {
            const Setting& color = light["color"];
            if (color.exists("r")) color.lookupValue("r", r);
            if (color.exists("g")) color.lookupValue("g", g);
            if (color.exists("b")) color.lookupValue("b", b);

            r /= 255.0;
            g /= 255.0;
            b /= 255.0;
        }

        light.lookupValue("intensity", intensity);

        auto dirLight = std::make_unique<DirectionalLight>(
            Math::Vector3D(x, y, z),
            Math::Vector3D(r, g, b),
            intensity
        );

        scene.addLight(std::move(dirLight));
    }
}
