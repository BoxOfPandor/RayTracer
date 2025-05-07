/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** SFMLRenderer.cpp
*/

#include "SFMLRenderer.hpp"
#include "Scene.hpp"
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>

using namespace RayTracer;
using namespace Math;

SFMLRenderer::SFMLRenderer(int numThreads) : _numThreads(numThreads)
{
    if (_numThreads <= 0) {
        _numThreads = std::thread::hardware_concurrency();
        if (_numThreads == 0) {
            _numThreads = 4;
        }
    }
}

std::vector<SFMLRenderer::Tile> SFMLRenderer::createTiles(int width, int height, int tileSize) const
{
    std::vector<Tile> tiles;

    for (int y = 0; y < height; y += tileSize) {
        for (int x = 0; x < width; x += tileSize) {
            Tile tile;
            tile.startX = x;
            tile.startY = y;
            tile.endX = std::min(x + tileSize, width);
            tile.endY = std::min(y + tileSize, height);
            tiles.push_back(tile);
        }
    }

    return tiles;
}

void SFMLRenderer::renderTile(const Scene& scene, sf::Image& image, const Tile& tile,
                             std::atomic<int>& tilesCompleted, int totalTiles) const
{
    (void)totalTiles;

    const int width = scene.getWidth();
    const int height = scene.getHeight();

    for (int y = tile.startY; y < tile.endY; ++y) {
        for (int x = tile.startX; x < tile.endX; ++x) {
            double u = static_cast<double>(x) / (width - 1);
            double v = static_cast<double>(y) / (height - 1);

            Ray ray = scene.getCamera().ray(u, v);

            Vector3D color = scene.traceRay(ray);

            sf::Color pixelColor(
                static_cast<sf::Uint8>(std::min(255.0, std::max(0.0, color.getX() * 255.0))),
                static_cast<sf::Uint8>(std::min(255.0, std::max(0.0, color.getY() * 255.0))),
                static_cast<sf::Uint8>(std::min(255.0, std::max(0.0, color.getZ() * 255.0))),
                255
            );

            image.setPixel(x, height - 1 - y, pixelColor);
        }
    }

    ++tilesCompleted;
}

void SFMLRenderer::handleEvents(sf::RenderWindow& window) const
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
    }
}

void SFMLRenderer::updateDisplay(sf::RenderWindow& window, const sf::Texture& texture) const
{
    sf::Sprite sprite(texture);
    window.clear();
    window.draw(sprite);
    window.display();
}

void SFMLRenderer::saveToFile(const sf::Image& image, const std::string& outputFile) const
{
    if (!image.saveToFile(outputFile)) {
        std::cerr << "Failed to save image to " << outputFile << std::endl;
    }
    else {
        std::cout << "Image successfully saved to " << outputFile << std::endl;
    }
}

bool SFMLRenderer::render(const Scene& scene, const std::string& outputFile) const
{
    const int width = scene.getWidth();
    const int height = scene.getHeight();

    sf::RenderWindow window(sf::VideoMode(width, height), "RayTracer Rendering");
    window.setFramerateLimit(30);

    sf::Image image;
    image.create(width, height, sf::Color::Black);

    sf::Texture texture;
    texture.create(width, height);

    std::vector<Tile> tiles = createTiles(width, height, TILE_SIZE);
    const int totalTiles = tiles.size();

    std::atomic<int> tilesCompleted(0);

    std::vector<std::thread> threads;
    threads.reserve(_numThreads);

    int tilesPerThread = (totalTiles + _numThreads - 1) / _numThreads;

    auto startTime = std::chrono::high_resolution_clock::now();
    bool renderingComplete = false;
    bool imageSaved = false;

    for (int threadId = 0; threadId < _numThreads; ++threadId) {
        int startTile = threadId * tilesPerThread;
        int endTile = std::min((threadId + 1) * tilesPerThread, totalTiles);

        threads.emplace_back([this, &scene, &image, &tiles, &tilesCompleted, startTile, endTile, totalTiles]() {
            for (int tileIdx = startTile; tileIdx < endTile; ++tileIdx) {
                renderTile(scene, image, tiles[tileIdx], tilesCompleted, totalTiles);
            }
        });
    }

    while (window.isOpen()) {
        handleEvents(window);

        int completed = tilesCompleted.load();

        float progress = static_cast<float>(completed) / totalTiles;

        if (completed == totalTiles && !renderingComplete) {
            auto endTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

            std::cout << "Rendering completed in " << (duration / 1000.0) << " seconds" << std::endl;
            window.setTitle("RayTracer - Rendering complete (100%) - Press Esc to exit");
            renderingComplete = true;

            if (!imageSaved) {
                saveToFile(image, outputFile);
                imageSaved = true;
            }
        }

        if (!renderingComplete) {
            window.setTitle("RayTracer Rendering - " +
                          std::to_string(static_cast<int>(progress * 100)) + "%");
        }

        {
            std::lock_guard<std::mutex> lock(_displayMutex);
            texture.update(image);
        }

        updateDisplay(window, texture);

        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }

    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    return true;
}
