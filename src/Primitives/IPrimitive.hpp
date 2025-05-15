/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** IPrimitive.hpp
*/

#ifndef IPRIMITIVE_HPP
#define IPRIMITIVE_HPP

#include "Vector3D.hpp"
#include "Point3D.hpp"
#include "Ray.hpp"

namespace RayTracer {
    class IMaterial;

    class IPrimitive {
    public:
        virtual ~IPrimitive() = default;

        /**
         * @brief Check if a ray hits this primitive
         * @param ray The ray to check
         * @return true if the ray hits the primitive, false otherwise
         */
        virtual bool hits(const Ray& ray) const = 0;

        /**
         * @brief Get the intersection point between the ray and the primitive
         * @param ray The ray to check
         * @param t Output parameter that will contain the distance from ray origin
         * @return true if there is an intersection, false otherwise
         */
        virtual bool getIntersection(const Ray& ray, double& t) const = 0;

        /**
         * @brief Get the normal vector at an intersection point
         * @param point The intersection point
         * @return The normal vector at this point
         */
        virtual Math::Vector3D getNormalAt(const Math::Point3D& point) const = 0;

        /**
         * @brief Apply translation transformation to the primitive
         * @param translation Vector representing the translation
         */
        virtual void translate(const Math::Vector3D& translation) = 0;

        /**
         * @brief Apply rotation transformation to the primitive around X axis
         * @param angle Rotation angle in degrees
         */
        virtual void rotateX(double angle) = 0;

        /**
         * @brief Apply rotation transformation to the primitive around Y axis
         * @param angle Rotation angle in degrees
         */
        virtual void rotateY(double angle) = 0;

        /**
         * @brief Apply rotation transformation to the primitive around Z axis
         * @param angle Rotation angle in degrees
         */
        virtual void rotateZ(double angle) = 0;

        /**
         * @brief Get the material of the primitive
         * @return The material of the primitive
         */
        virtual const IMaterial& getMaterial() const = 0;
    };
} // namespace RayTracer

#endif // IPRIMITIVE_HPP