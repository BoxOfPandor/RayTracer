/*
** EPITECH PROJECT, 2025
** Minimal scene editor UI (raylib)
*/

#ifndef EDITOR_APP_HPP
#define EDITOR_APP_HPP

#include <memory>
#include <string>

namespace RayTracer {
    class Scene;

    class EditorApp {
    public:
        EditorApp();
        ~EditorApp();

        // Run the editor until user closes the window
        // Returns true on clean exit
        bool run(std::unique_ptr<Scene> scene);

    private:
        struct ViewCamera {
            float distance = 6.0f;   // orbit distance
            float yaw = 0.0f;        // radians
            float pitch = 0.25f;     // radians
        } _viewCam;

        // Panels sizes (pixels)
        int _leftPanelWidth = 260;
        int _rightPanelWidth = 320;
        int _topBarHeight = 40;

        // Selection index in hierarchy (flat for now)
        int _selectedIndex = -1;

        void drawTopBar();
        void drawHierarchy(const Scene& scene);
        void drawProperties(const Scene& scene);
        void drawViewport(const Scene& scene);
    };
}

#endif // EDITOR_APP_HPP
