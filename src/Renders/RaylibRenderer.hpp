/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** RaylibRenderer.hpp
*/

#ifndef RAYLIBRENDERER_HPP
#define RAYLIBRENDERER_HPP

#include <atomic>
#include <mutex>
#include <thread>
#include <vector>
#include <string>
#include <cstdint>
#include "IRenderer.hpp"
#include "Tile.hpp"

namespace RayTracer {
    class RaylibRenderer : public IRenderer {
    public:
        explicit RaylibRenderer(int numThreads = 0);
        ~RaylibRenderer() override = default;

        bool render(const Scene& scene, const std::string& outputFile) const override;

    private:
        std::vector<Tile> createTiles(int width, int height, int tileSize) const;

        void renderTile(const Scene& scene,
                        std::vector<std::uint8_t>& pixels,
                        const Tile& tile,
                        std::atomic<int>& tilesCompleted,
                        int totalTiles,
                        int width,
                        int height) const;

        void saveToFile(const std::vector<std::uint8_t>& pixels,
                        int width,
                        int height,
                        const std::string& outputFile) const;

        int _numThreads;
        static constexpr int TILE_SIZE = 32;
        mutable std::mutex _displayMutex;
    };
}

#endif // RAYLIBRENDERER_HPP
