/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** RaylibRenderer.cpp
*/

#include "RaylibRenderer.hpp"
#include "Scene.hpp"
#include "Ray.hpp"
#include "Camera.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <optional>
#include <vector>

// raylib C header
extern "C" {
#include <raylib.h>
}

using namespace RayTracer;
using namespace Math;

RaylibRenderer::RaylibRenderer(int numThreads) : _numThreads(numThreads)
{
    if (_numThreads <= 0) {
        _numThreads = std::thread::hardware_concurrency();
        if (_numThreads == 0) {
            _numThreads = 4;
        }
    }
}

std::vector<Tile> RaylibRenderer::createTiles(int width, int height, int tileSize) const
{
    std::vector<Tile> tiles;
    for (int y = 0; y < height; y += tileSize) {
        for (int x = 0; x < width; x += tileSize) {
            tiles.emplace_back(x, y, std::min(x + tileSize, width), std::min(y + tileSize, height));
        }
    }
    return tiles;
}

static inline unsigned char clamp255(double v)
{
    if (v < 0.0) return 0;
    if (v > 1.0) return 255;
    return static_cast<unsigned char>(v * 255.0);
}

void RaylibRenderer::renderTile(const Scene& scene,
                                std::vector<std::uint8_t>& pixels,
                                const Tile& tile,
                                std::atomic<int>& tilesCompleted,
                                int totalTiles,
                                int width,
                                int height) const
{
    (void)totalTiles;

    for (int y = tile.getStartY(); y < tile.getEndY(); ++y) {
        for (int x = tile.getStartX(); x < tile.getEndX(); ++x) {
            double u = static_cast<double>(x) / (width - 1);
            double v = static_cast<double>(y) / (height - 1);

            Ray ray = scene.getCamera().ray(u, v);
            Vector3D color = scene.traceRay(ray);

            unsigned char r = clamp255(color.getX());
            unsigned char g = clamp255(color.getY());
            unsigned char b = clamp255(color.getZ());
            unsigned char a = 255;

            // raylib Image uses top-left origin. Our previous SFML flipped vertically when writing.
            // Keep consistent by flipping Y here so final display matches PPM.
            int flippedY = height - 1 - y;
            size_t idx = (static_cast<size_t>(flippedY) * width + x) * 4;
            pixels[idx + 0] = r;
            pixels[idx + 1] = g;
            pixels[idx + 2] = b;
            pixels[idx + 3] = a;
        }
    }

    ++tilesCompleted;
}

void RaylibRenderer::saveToFile(const std::vector<std::uint8_t>& pixels,
                                int width,
                                int height,
                                const std::string& outputFile) const
{
    Image img = { const_cast<unsigned char*>(pixels.data()), width, height, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 };
    if (ExportImage(img, outputFile.c_str()) == false) {
        std::cerr << "Failed to save image to " << outputFile << std::endl;
    } else {
        std::cout << "Image successfully saved to " << outputFile << std::endl;
    }
}

bool RaylibRenderer::render(const Scene& scene, const std::string& outputFile) const
{
    const int width = scene.getWidth();
    const int height = scene.getHeight();

    InitWindow(width, height, "RayTracer Rendering (raylib)");
    SetTargetFPS(30);

    // RGBA buffer
    std::vector<std::uint8_t> pixels(static_cast<size_t>(width) * height * 4, 0);

    // Create initial image/texture
    Image img = { pixels.data(), width, height, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 };
    Texture2D texture = LoadTextureFromImage(img);

    std::vector<Tile> tiles = createTiles(width, height, TILE_SIZE);
    const int totalTiles = static_cast<int>(tiles.size());

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

        threads.emplace_back([this, &scene, &pixels, &tiles, &tilesCompleted, startTile, endTile, totalTiles, width, height]() {
            for (int tileIdx = startTile; tileIdx < endTile; ++tileIdx) {
                renderTile(scene, pixels, tiles[tileIdx], tilesCompleted, totalTiles, width, height);
            }
        });
    }

    while (!WindowShouldClose()) {
        int completed = tilesCompleted.load();
        float progress = static_cast<float>(completed) / totalTiles;

        if (completed == totalTiles && !renderingComplete) {
            auto endTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
            std::cout << "Rendering completed in " << (duration / 1000.0) << " seconds" << std::endl;
            SetWindowTitle("RayTracer - Rendering complete (100%) - Press Esc to exit");
            renderingComplete = true;

            if (!imageSaved) {
                saveToFile(pixels, width, height, outputFile);
                imageSaved = true;
            }
        }

        if (!renderingComplete) {
            std::string title = "RayTracer Rendering - " + std::to_string(static_cast<int>(progress * 100)) + "%";
            SetWindowTitle(title.c_str());
        }

        {
            std::lock_guard<std::mutex> lock(_displayMutex);
            // Update GPU texture with latest CPU pixel buffer
            UpdateTexture(texture, pixels.data());
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(texture, 0, 0, WHITE);
        EndDrawing();
    }

    for (auto& th : threads) if (th.joinable()) th.join();

    UnloadTexture(texture);
    CloseWindow();

    return true;
}
