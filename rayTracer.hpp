/*
** EPITECH PROJECT, 2025
** OOP
** File description:
** raytracer
*/

#include "math.hpp"

namespace RayTracer {
    class Ray {
        public:
            Ray();
            Ray(Math::Point3D point, Math::Vector3D vector);
            ~Ray();

            Math::Point3D point;
            Math::Vector3D vector;
    };

    class Sphere {
        public:
            Sphere(double radius, Math::Point3D center);
            ~Sphere();

            bool hits(Ray ray);

            Math::Point3D center;
            double radius;
    };
}
