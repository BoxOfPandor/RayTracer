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
#include "Tile.hpp"
#include <SFML/Graphics.hpp>

namespace RayTracer {
    class SFMLRenderer : public IRenderer {
    public:
        /**
         * @brief Constructor for the SFML renderer
         * @param numThreads Number of threads to use for rendering (0 for auto-detection)
         */
        SFMLRenderer(int numThreads = 0);

        /**
         * @brief Destructor for the SFML renderer
         */
        ~SFMLRenderer() = default;

        /**
         * @brief Render the scene to a file
         * @param scene The scene to render
         * @param outputFile Path to the output file
         * @return True if rendering was successful
         */
        bool render(const Scene& scene, const std::string& outputFile) const override;

    private:
        /**
         * @brief Render a specific tile of the image
         * @param scene The scene to render
         * @param image The image to render to
         * @param tile The tile boundaries to render
         * @param tilesCompleted Atomic counter for completed tiles
         * @param totalTiles Total number of tiles
         */
        void renderTile(const Scene& scene, sf::Image& image, const Tile& tile,
                       std::atomic<int>& tilesCompleted, int totalTiles) const;

        /**
         * @brief Create rendering tiles for multi-threaded rendering
         * @param width Width of the image
         * @param height Height of the image
         * @param tileSize Size of each tile
         * @return Vector of tiles
         */
        std::vector<Tile> createTiles(int width, int height, int tileSize) const;

        /**
         * @brief Handle window events
         * @param window The SFML window
         */
        void handleEvents(sf::RenderWindow& window) const;

        /**
         * @brief Update the window display
         * @param window The SFML window
         * @param texture The texture to display
         */
        void updateDisplay(sf::RenderWindow& window, const sf::Texture& texture) const;

        /**
         * @brief Save the rendered image to a file
         * @param image The image to save
         * @param outputFile Path to the output file
         */
        void saveToFile(const sf::Image& image, const std::string& outputFile) const;

        int _numThreads;
        static constexpr int TILE_SIZE = 32;
        mutable std::mutex _displayMutex;
    };
}

#endif // SFMLRENDERER_HPP
