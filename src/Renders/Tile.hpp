/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Tile.hpp
*/

#ifndef TILE_HPP
#define TILE_HPP

namespace RayTracer {
    class Tile {
    public:
        Tile();
        Tile(int startX, int startY, int endX, int endY);
        ~Tile() = default;

        // Getters
        int getStartX() const;
        int getStartY() const;
        int getEndX() const;
        int getEndY() const;

        // Setters
        void setStartX(int startX);
        void setStartY(int startY);
        void setEndX(int endX);
        void setEndY(int endY);

    private:
        int _startX;
        int _startY;
        int _endX;
        int _endY;
    };
} // namespace RayTracer

#endif // TILE_HPP
