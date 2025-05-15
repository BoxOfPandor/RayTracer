/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Intersection.hpp
*/

#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include "IPrimitive.hpp"
#include "Vector3D.hpp"
#include "Point3D.hpp"

namespace RayTracer {
    class Intersection {
    public:
        Intersection();
        Intersection(const IPrimitive* primitive, double distance,
                     const Math::Point3D& point, const Math::Vector3D& normal);
        ~Intersection() = default;

        const IPrimitive* getPrimitive() const;
        double getDistance() const;
        const Math::Point3D& getPoint() const;
        const Math::Vector3D& getNormal() const;

        void setPrimitive(const IPrimitive* primitive);
        void setDistance(double distance);
        void setPoint(const Math::Point3D& point);
        void setNormal(const Math::Vector3D& normal);

    private:
        const IPrimitive* _primitive;
        double _distance;
        Math::Point3D _point;
        Math::Vector3D _normal;
    };
} // namespace RayTracer

#endif // INTERSECTION_HPP
