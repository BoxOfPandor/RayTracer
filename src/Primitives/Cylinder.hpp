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
    /**
     * @class Cylinder
     * @brief Represents a cylinder primitive in 3D space
     *
     * A cylinder is defined by its base center point, direction vector (axis),
     * radius, and height.
     */
    class Cylinder : public IPrimitive {
    public:
        /**
         * @brief Construct a new Cylinder object
         *
         * @param origin The center point of the cylinder's base
         * @param direction The axis direction of the cylinder (will be normalized)
         * @param radius The radius of the cylinder
         * @param height The height of the cylinder
         * @param material The material properties of the cylinder
         */
        Cylinder(const Math::Point3D& origin, const Math::Vector3D& direction,
                double radius, double height, const IMaterial& material);

        /**
         * @brief Default destructor
         */
        ~Cylinder() = default;

        /**
         * @brief Determines if a ray intersects with the cylinder
         *
         * @param ray The ray to check for intersection
         * @return true If the ray intersects the cylinder
         * @return false If the ray does not intersect the cylinder
         */
        bool hits(const Ray& ray) const override;

        /**
         * @brief Calculates the intersection point of a ray with the cylinder
         *
         * @param ray The ray to check for intersection
         * @param t [out] The parameter value at which the ray intersects the cylinder
         * @return true If an intersection is found
         * @return false If no intersection is found
         */
        bool getIntersection(const Ray& ray) const;

        /**
         * @brief Calculates the normal vector at a given point on the cylinder
         *
         * @param point The point on the cylinder surface
         * @return Math::Vector3D The normal vector at the given point
         */
        Math::Vector3D getNormalAt(const Math::Point3D& point) const override;

        /**
         * @brief Translates the cylinder by a given vector
         *
         * @param translation The vector to translate by
         */
        void translate(const Math::Vector3D& translation) override;

        /**
         * @brief Rotates the cylinder around the X-axis
         *
         * @param angle The rotation angle in degrees
         */
        void rotateX(double angle);

        /**
         * @brief Rotates the cylinder around the Y-axis
         *
         * @param angle The rotation angle in degrees
         */
        void rotateY(double angle);

        /**
         * @brief Rotates the cylinder around the Z-axis
         *
         * @param angle The rotation angle in degrees
         */
        void rotateZ(double angle);

        /**
         * @brief Gets the material of the cylinder
         *
         * @return const IMaterial& Reference to the cylinder's material
         */
        const IMaterial& getMaterial() const override;

    private:
        Math::Point3D _origin;     /**< Center of the base */
        Math::Vector3D _direction; /**< Direction/axis of the cylinder (normalized) */
        double _radius;            /**< Radius of the cylinder */
        double _height;            /**< Height of the cylinder */
        const IMaterial& _material; /**< Material properties of the cylinder */
    };
} // namespace RayTracer

#endif // CYLINDER_HPP
