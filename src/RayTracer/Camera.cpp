/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Camera
*/

#include "Camera.hpp"
using namespace RayTracer;
using namespace Math;

Camera::Camera()
{
    this->_origin = Point3D(0, 0, 0);
    this->_screen = Rectangle3D(Point3D(-1, -1, -1), Vector3D(2, 0, 0), Vector3D(0, 2, 0));
}

Camera::Camera(const Math::Point3D& origin, double screenDistance, int imageWidth, int imageHeight)
    : _origin(origin)
{
    double aspectRatio = static_cast<double>(imageWidth) / imageHeight;
    double width = 2.0;
    double height = width / aspectRatio;

    _screen = Rectangle3D(
        Point3D(-width/2, -height/2, -screenDistance),
        Vector3D(width, 0, 0),
        Vector3D(0, height, 0)
    );
}

Camera::Camera(const Math::Point3D& origin, const Rectangle3D& screen)
    : _origin(origin), _screen(screen)
{
}

Camera::Camera(const Camera& other)
{
    this->_origin = other._origin;
    this->_screen = other._screen;
}

Camera& Camera::operator=(const Camera& other)
{
    if (this != &other) {
        this->_origin = other._origin;
        this->_screen = other._screen;
    }
    return *this;
}

Ray Camera::ray(double u, double v) const
{
    Point3D pointOnScreen = _screen.pointAt(u, v);

    Vector3D direction(
        pointOnScreen.getX() - _origin.getX(),
        pointOnScreen.getY() - _origin.getY(),
        pointOnScreen.getZ() - _origin.getZ()
    );

    return Ray(_origin, direction);
}

Point3D Camera::getOrigin() const
{
    return this->_origin;
}

Rectangle3D Camera::getScreen() const
{
    return this->_screen;
}

void Camera::setOrigin(const Point3D& origin)
{
    this->_origin = origin;
}

void Camera::setScreen(const Rectangle3D& screen)
{
    this->_screen = screen;
}

void Camera::updateScreenForDimensions(int width, int height)
{
    double aspectRatio = static_cast<double>(width) / height;
    double screenWidth = 2.0;
    double screenHeight = screenWidth / aspectRatio;
    double screenDistance = _screen.getOrigin().getZ();

    _screen = Rectangle3D(
        Point3D(-screenWidth/2, -screenHeight/2, screenDistance),
        Vector3D(screenWidth, 0, 0),
        Vector3D(0, screenHeight, 0)
    );
}
