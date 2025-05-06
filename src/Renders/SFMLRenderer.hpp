/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** SFMLRenderer.hpp
*/

#ifndef SFMLRENDERER_HPP
#define SFMLRENDERER_HPP

#include <atomic>
#include <mutex>
#include <thread>
#include <vector>
#include <string>
#include <iostream>
#include <locale>
#include <codecvt>
#include "IRenderer.hpp"
#include <SFML/Graphics.hpp>

namespace RayTracer {
    class SFMLRenderer : public IRenderer {
    public:
        SFMLRenderer(int numThreads = 0);
        ~SFMLRenderer() = default;

        bool render(const Scene& scene, const std::string& outputFile) const override;

    private:
        struct Tile {
            int startX;
            int startY;
            int endX;
            int endY;
        };

        void renderTile(const Scene& scene, sf::Image& image, const Tile& tile, 
                       std::atomic<int>& tilesCompleted, int totalTiles) const;
        std::vector<Tile> createTiles(int width, int height, int tileSize) const;
        void handleEvents(sf::RenderWindow& window) const;
        void updateDisplay(sf::RenderWindow& window, const sf::Texture& texture) const;
        void saveToFile(const sf::Image& image, const std::string& outputFile) const;

        int _numThreads;
        static constexpr int TILE_SIZE = 32;  // Size of rendering tiles
        mutable std::mutex _displayMutex;
    };
}

#endif // SFMLRENDERER_HPP