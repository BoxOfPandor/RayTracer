/*
** EPITECH PROJECT, 2025
** B_OOP_400_LIL_4_1_raytracer_thibault_pouch
** File description:
** Tile.cpp
*/

#include "Tile.hpp"

using namespace RayTracer;

Tile::Tile()
    : _startX(0), _startY(0), _endX(0), _endY(0)
{
}

Tile::Tile(int startX, int startY, int endX, int endY)
    : _startX(startX), _startY(startY), _endX(endX), _endY(endY)
{
}

int Tile::getStartX() const
{
    return _startX;
}

int Tile::getStartY() const
{
    return _startY;
}

int Tile::getEndX() const
{
    return _endX;
}

int Tile::getEndY() const
{
    return _endY;
}

void Tile::setStartX(int startX)
{
    _startX = startX;
}

void Tile::setStartY(int startY)
{
    _startY = startY;
}

void Tile::setEndX(int endX)
{
    _endX = endX;
}

void Tile::setEndY(int endY)
{
    _endY = endY;
}
