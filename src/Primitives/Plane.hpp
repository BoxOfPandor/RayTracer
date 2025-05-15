/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Plane
*/

#ifndef PLANE_HPP
#define PLANE_HPP

#include "IPrimitive.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Ray.hpp"
#include "IMaterial.hpp"

namespace RayTracer {
    class Plane : public IPrimitive {
    public:
        Plane(const Math::Point3D& point, const Math::Vector3D& normal, const IMaterial& material);
        ~Plane() = default;

        bool hits(const Ray& ray) const override;
        bool getIntersection(const Ray& ray, double& t) const override;
        Math::Vector3D getNormalAt(const Math::Point3D& point) const override;
        void translate(const Math::Vector3D& translation) override;
        void rotateX(double angle) override;
        void rotateY(double angle) override;
        void rotateZ(double angle) override;
        const IMaterial& getMaterial() const override;

    private:
        Math::Point3D _point;
        Math::Vector3D _normal;
        const IMaterial& _material;
    };
} // namespace RayTracer

#endif // PLANE_HPP
