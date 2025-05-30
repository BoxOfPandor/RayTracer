/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Camera
*/

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Point3D.hpp"
#include "Rectangle3D.hpp"
#include "Ray.hpp"

namespace RayTracer {
    class Camera {
    public:
        Camera();
        Camera(const Math::Point3D& origin, const Rectangle3D& screen);
        Camera(const Math::Point3D& origin, double screenDistance, int imageWidth, int imageHeight);
        Camera(const Camera& other);
        ~Camera() = default;

        Math::Point3D getOrigin() const;
        Rectangle3D getScreen() const;
        void setOrigin(const Math::Point3D& origin);
        void setScreen(const Rectangle3D& screen);
        void updateScreenForDimensions(int width, int height);

        Camera& operator=(const Camera& other);
        Ray ray(double u, double v) const;

    private:
        Math::Point3D _origin;
        Rectangle3D _screen;
    };
} // namespace RayTracer

#endif // CAMERA_HPP
