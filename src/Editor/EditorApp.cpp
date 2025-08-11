/*
** EPITECH PROJECT, 2025
** Minimal scene editor UI (raylib)
*/

#include "EditorApp.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "IPrimitive.hpp"
#include "ILight.hpp"

#include <cmath>
#include <memory>
#include <string>
#include <vector>
#include <iostream>

extern "C" {
#include <raylib.h>
}

using namespace RayTracer;

EditorApp::EditorApp() {}
EditorApp::~EditorApp() {}

static Vector3 SphericalToCartesian(float distance, float yaw, float pitch)
{
    float cp = cosf(pitch);
    return { distance * cp * cosf(yaw), distance * sinf(pitch), distance * cp * sinf(yaw) };
}

bool EditorApp::run(std::unique_ptr<Scene> scene)
{
    if (!scene) return false;

    // Open the editor window to fill the current monitor
    int monitor = GetCurrentMonitor();
    int initialW = GetMonitorWidth(monitor);
    int initialH = GetMonitorHeight(monitor);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT | FLAG_WINDOW_MAXIMIZED);
    InitWindow(initialW, initialH, "RayTracer Editor");
    // Ensure window is positioned at top-left; on macOS this will maximize nicely
    SetWindowPosition(0, 0);
    SetTargetFPS(60);

    // Try loading a professional UI font if present (optional assets/fonts/Inter.ttf)
    // Fallback to default if not found
    if (FileExists("assets/fonts/Inter.ttf")) {
        std::cout << "Loaded custom font: assets/fonts/Inter.ttf" << std::endl;
        _font = LoadFontEx("assets/fonts/Inter.ttf", 20, nullptr, 0);
    } else {
        std::cout << "Loaded default font" << std::endl;
        _font = GetFontDefault();
    }

    bool running = true;
    while (running && !WindowShouldClose()) {
        // Input: orbit controls on viewport area only
        int winW = GetScreenWidth();
        int winH = GetScreenHeight();
        Rectangle topBar = {0, 0, (float)winW, (float)_topBarHeight};
        Rectangle leftPanel = {0, (float)_topBarHeight, (float)_leftPanelWidth, (float)(winH - _topBarHeight)};
        Rectangle rightPanel = {(float)(winW - _rightPanelWidth), (float)_topBarHeight, (float)_rightPanelWidth, (float)(winH - _topBarHeight)};
        Rectangle viewport = {(float)_leftPanelWidth, (float)_topBarHeight, (float)(winW - _leftPanelWidth - _rightPanelWidth), (float)(winH - _topBarHeight)};

        Vector2 mouse = GetMousePosition();
        bool mouseInViewport = CheckCollisionPointRec(mouse, viewport);

        if (mouseInViewport) {
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                Vector2 delta = GetMouseDelta();
                _viewCam.yaw   += delta.x * 0.005f;
                _viewCam.pitch += -delta.y * 0.005f;
                const float eps = 0.01f;
                if (_viewCam.pitch > 1.55f) _viewCam.pitch = 1.55f;
                if (_viewCam.pitch < -1.55f) _viewCam.pitch = -1.55f;
            }
            float wheel = GetMouseWheelMove();
            if (wheel != 0.0f) {
                _viewCam.distance *= (wheel > 0) ? 0.9f : 1.1f;
                if (_viewCam.distance < 1.0f) _viewCam.distance = 1.0f;
                if (_viewCam.distance > 100.0f) _viewCam.distance = 100.0f;
            }
        }

        BeginDrawing();
        ClearBackground((Color){25, 25, 28, 255});

    // Top bar
    DrawRectangleRec(topBar, (Color){45, 45, 50, 255});
    drawText("File: [Load] [Export]  |  Render: [Raylib] [PPM]  |  Mode: Editor (Orbit)", 10, 10, 18, RAYWHITE);

        // Left hierarchy panel
    DrawRectangleRec(leftPanel, (Color){35, 35, 40, 255});
        drawHierarchy(*scene);

        // Right properties panel
    DrawRectangleRec(rightPanel, (Color){35, 35, 40, 255});
        drawProperties(*scene);

        // Center viewport
        DrawRectangleRec(viewport, (Color){20, 20, 23, 255});

        // 3D View
        {
            // Configure a basic orbital camera around origin
            Vector3 camPos = SphericalToCartesian(_viewCam.distance, _viewCam.yaw, _viewCam.pitch);
            Camera3D cam = {0};
            cam.position = camPos;
            cam.target = {0.0f, 0.0f, 0.0f};
            cam.up = {0.0f, 1.0f, 0.0f};
            cam.fovy = 60.0f;
            cam.projection = CAMERA_PERSPECTIVE;

            // Limit drawing to viewport with scissor
            BeginScissorMode((int)viewport.x, (int)viewport.y, (int)viewport.width, (int)viewport.height);
            BeginMode3D(cam);

            // Grid/Floor
            DrawGrid(20, 1.0f);

            // Draw simple debug representations for scene entities (no raytracing):
            // - Primitives: draw their bounding spheres or points
            int idx = 0;
            for (const auto& primPtr : scene->getPrimitives()) {
                Color c = (idx == _selectedIndex) ? RED : GREEN;
                // Naive proxy: draw a small sphere at primitive center if available
                // We don't know center; just draw at origin for now or skip
                // Extend later by adding a getAABB/getCenter to IPrimitive
                DrawSphere((Vector3){0, 0, 0}, 0.05f, c);
                idx++;
            }

            // Lights: draw arrows for directionals
            idx = 0;
            for (const auto& lightPtr : scene->getLights()) {
                Color c = (idx == _selectedIndex) ? YELLOW : SKYBLUE;
                // Without RTTI/types, draw a small sphere near origin to visualize
                DrawSphere((Vector3){0.2f + 0.1f*idx, 0.2f, 0}, 0.04f, c);
                idx++;
            }

            // Camera gizmo
            DrawCube((Vector3){-0.2f, 0.1f, 0}, 0.06f, 0.04f, 0.04f, ORANGE);

            EndMode3D();
            EndScissorMode();
        }

        EndDrawing();
    }
    CloseWindow();
    return true;
}

void EditorApp::drawTopBar() {}

void EditorApp::drawHierarchy(const Scene& scene)
{
    int x = 12;
    int y = _topBarHeight + 12;
    drawText("Hierarchy", x, y, 20, RAYWHITE);
    y += 28;

    drawText("- Camera", x, y, 18, LIGHTGRAY); y += 24;

    drawText("- Primitives", x, y, 18, LIGHTGRAY); y += 24;
    int i = 0;
    for (const auto& prim : scene.getPrimitives()) {
        Color c = (_selectedIndex == i) ? RAYWHITE : GRAY;
        const char* typeName = prim ? prim->getTypeName() : "primitive";
        drawText(TextFormat("  * %s %d", typeName, i), x, y, 16, c);
        y += 20;
        i++;
    }

    drawText("- Lights", x, y, 18, LIGHTGRAY); y += 24;
    i = 0;
    for (const auto& _ : scene.getLights()) {
        (void)_; // unused
        Color c = (_selectedIndex == i) ? RAYWHITE : GRAY;
        drawText(TextFormat("  * Light %d", i), x, y, 16, c);
        y += 20;
        i++;
    }
}

void EditorApp::drawProperties(const Scene& scene)
{
    int x = GetScreenWidth() - _rightPanelWidth + 12;
    int y = _topBarHeight + 12;
    drawText("Properties", x, y, 20, RAYWHITE);
    y += 28;

    drawText(TextFormat("Orbit: dist=%.2f yaw=%.2f pitch=%.2f", _viewCam.distance, _viewCam.yaw, _viewCam.pitch), x, y, 16, GRAY);
    y += 22;
    drawText("(Editable fields coming soon)", x, y, 16, DARKGRAY);
}

void EditorApp::drawViewport(const Scene& scene) { (void)scene; }

void EditorApp::drawText(const char* text, int x, int y, float size, Color color)
{
    if (_font.baseSize > 0) {
        DrawTextEx(_font, text, (Vector2){(float)x, (float)y}, size, _fontSpacing, color);
    } else {
        DrawText(text, x, y, (int)size, color);
    }
}
