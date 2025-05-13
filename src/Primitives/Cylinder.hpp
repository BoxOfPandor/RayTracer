/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Cylinder
*/

#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include "IPrimitive.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Ray.hpp"
#include "IMaterial.hpp"

namespace RayTracer {
    class Cylinder : public IPrimitive {
    public:
        Cylinder(const Math::Point3D& origin, const Math::Vector3D& direction,
                double radius, double height, const IMaterial& material);
        ~Cylinder() = default;

        bool hits(const Ray& ray) const override;
        bool getIntersection(const Ray& ray, double& t) const override;
        Math::Vector3D getNormalAt(const Math::Point3D& point) const override;
        void translate(const Math::Vector3D& translation) override;
        void rotateX(double angle) override;
        void rotateY(double angle) override;
        void rotateZ(double angle) override;
        const IMaterial& getMaterial() const override;

    private:
        Math::Point3D _origin;   // Center of the base
        Math::Vector3D _direction; // Direction/axis of the cylinder (normalized)
        double _radius;
        double _height;
        const IMaterial& _material;
    };
} // namespace RayTracer

#endif // CYLINDER_HPP
