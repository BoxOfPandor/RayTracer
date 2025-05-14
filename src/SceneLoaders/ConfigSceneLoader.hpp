/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** ConfigSceneLoader
*/

#ifndef CONFIGSCENELOADER_HPP
#define CONFIGSCENELOADER_HPP

#include "ISceneLoader.hpp"
#include "Point3D.hpp"
#include "Rectangle3D.hpp"
#include "IMaterial.hpp"
#include "SceneBuilder.hpp"
#include <libconfig.h++>
#include <vector>
#include <memory>
#include <string>
#include <map>

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
        
        // These methods now take SceneBuilder instead of Scene
        void parsePrimitives(const libconfig::Setting& primitivesSettings,
                     SceneBuilder& builder) const;
        void parseLights(const libconfig::Setting& lightsSettings,
                         SceneBuilder& builder) const;

        // Helpers for primitives
        void parseSpheres(const libconfig::Setting& spheres, SceneBuilder& builder,
                         std::vector<std::shared_ptr<IMaterial>>& materials) const;
        void parsePlanes(const libconfig::Setting& planes, SceneBuilder& builder,
                        std::vector<std::shared_ptr<IMaterial>>& materials) const;
        void parseCylinders(const libconfig::Setting& cylinders, SceneBuilder& builder,
                           std::vector<std::shared_ptr<IMaterial>>& materials) const;
    };
}

#endif // CONFIGSCENELOADER_HPP
