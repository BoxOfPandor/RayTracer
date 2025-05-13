/*
** EPITECH PROJECT, 2025
** B-OOP-400-LIL-4-1-raytracer-thibault.pouch
** File description:
** ConfigSceneLoader
*/

#ifndef CONFIGSCENELOADER_HPP
#define CONFIGSCENELOADER_HPP

#include "ISceneLoader.hpp"
#include "Point3D.hpp"
#include "Rectangle3D.hpp"
#include "IMaterial.hpp"
#include <libconfig.h++>
#include <vector>
#include <memory>
#include <string>

namespace RayTracer {
    class Scene;
    
    class ConfigSceneLoader : public ISceneLoader {
    public:
        ConfigSceneLoader() = default;
        ~ConfigSceneLoader() = default;

        std::unique_ptr<Scene> loadScene(const std::string& filename) const override;

    private:
        // Helper methods for different components
        void parseCamera(const libconfig::Setting& cameraSettings,
                         int& width, int& height, Math::Point3D& position,
                         Rectangle3D& screen) const;
        void parsePrimitives(const libconfig::Setting& primitivesSettings,
                     Scene& scene) const;
        void parseLights(const libconfig::Setting& lightsSettings,
                         Scene& scene) const;

        // Helpers for primitives
        void parseSpheres(const libconfig::Setting& spheres, Scene& scene,
                         std::vector<std::shared_ptr<IMaterial>>& materials) const;
        void parsePlanes(const libconfig::Setting& planes, Scene& scene,
                        std::vector<std::shared_ptr<IMaterial>>& materials) const;
        void parseCylinders(const libconfig::Setting& cylinders, Scene& scene,
                           std::vector<std::shared_ptr<IMaterial>>& materials) const;

        
        // Helpers for lights
        void parsePointLights(const libconfig::Setting& lights, Scene& scene) const;
        void parseDirectionalLights(const libconfig::Setting& lights, Scene& scene) const;
    };
}

#endif // CONFIGSCENELOADER_HPP
