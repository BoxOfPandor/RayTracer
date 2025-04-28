/*
** EPITECH PROJECT, 2025
** OOP
** File description:
** raytracer
*/

#include <cmath>

namespace Math {
    class Vector3D {
        public:
            Vector3D();
            Vector3D(double x, double y, double z);
            ~Vector3D();

            double getX();
            double getY();
            double getZ();

            double length();
            double dot(Vector3D vec1, Vector3D vec2);

            void translate(Math::Vector3D vec);
            void rotateX(double degree);
            void rotateY(double degree);
            void rotateZ(double degree);

            Vector3D operator+(Vector3D other);
            void operator+=(Vector3D other);
            Vector3D operator-(Vector3D other);
            void operator-=(Vector3D other);
            Vector3D operator*(Vector3D other);
            void operator*=(Vector3D other);
            Vector3D operator/(Vector3D other);
            void operator/=(Vector3D other);

            Vector3D operator*(double n);
            void operator*=(double n);
            Vector3D operator/(double n);
            void operator/=(double n);

        private:
            double _x;
            double _y;
            double _z;
    };

    class Point3D {
        public:
            Point3D();
            Point3D(double x, double y, double z);
            ~Point3D();

            Point3D operator+(Vector3D other);
            Point3D operator+(Point3D other);
            Point3D operator-(Vector3D other);
            Point3D operator-(Point3D other);

            double x;
            double y;
            double z;
    };
}
