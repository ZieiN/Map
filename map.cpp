#include "map.h"
#include <cmath>
#include <iomanip>
#include <set>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <iostream>

using namespace std;
Map::Map()
{
    width_ = 1;
    height_ = 1;
    cell_ = new bool *[1];
    cell_[0] = new bool[1];
}
Map::~Map()
{
    for (int i = 0; i < height_; ++i)
    {
        if (width_ > 0)
            delete cell_[i];
    }
    delete cell_;
}
Map::Map(int height, int width)
{
    width_ = width;
    height_ = height;
    cell_ = new bool *[height_];
    for (int i = 0; i < height_; ++i)
    {
        cell_[i] = new bool[width_];
    }
}
Map::Map(int width, int height, bool **cell)
{
    width_ = width;
    height_ = height;
    cell_ = new bool *[height_];
    for (int i = 0; i < height_; ++i)
    {
        cell_[i] = new bool[width_];
        for (int j = 0; j < width; ++j)
        {
            cell_[i][j] = cell[i][j];
        }
    }
}
Map::Map(const Map &other)
{
    width_ = height_ = 0;
    setWidth(other.width_);
    setHeight(other.height_);
    for (int i = 0; i < height_; ++i)
    {
        for (int j = 0; j < width_; ++j)
        {
            cell_[i][j] = other.cell_[i][j];
        }
    }
}
Map &Map::operator=(const Map &mp)
{
    if (this != &mp)
    {
        setMap(mp.getWidth(), mp.getHeight(), mp.getMap());
    }
    return *this;
}
void Map::setMap(int width, int height, bool **cell)
{
    setWidth(width);
    setHeight(height);
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            cell_[i][j] = cell[i][j];
        }
    }
}
int Map::getWidth() const
{
    return width_;
}
void Map::setWidth(int value)
{
    for (int i = 0; i < height_; ++i)
    {
        if (width_ > 0)
            delete cell_[i];
        cell_[i] = new bool[value];
    }
    width_ = value;
}
int Map::getHeight() const
{
    return height_;
}
void Map::setHeight(int value)
{
    for (int i = 0; i < height_; ++i)
    {
        //        if(cell_[i]!=nullptr)
        if (width_ > 0)
            delete cell_[i];
    }
    if (height_ > 0)
        delete cell_;
    cell_ = new bool *[value];
    for (int i = 0; i < value; ++i)
    {
        if (width_ > 0)
            cell_[i] = new bool[width_];
    }
    height_ = value;
}
bool **Map::getMap() const
{
    return cell_;
}
void Map::setCell(int i, int j, bool value)
{
    cell_[i][j] = value;
}
bool Map::getValue(int i, int j) const
{
    return cell_[i][j];
}

bool Map::isIn(int i, int j) const
{
    return i >= 0 && i < height_ && j >= 0 && j < width_;
}

bool Map::cellIsObstacle(int i, int j) const
{
    if (!isIn(i, j))
    {
        std::cerr << "Point is out of the map" << std::endl;
        return true;
    }
    return cell_[i][j];
}

bool Map::isThereLineOfSight(double x0, double x1, double y0, double y1) const
{
    double eps = 1e-9;
    if (cellIsObstacle(x0, y0) || cellIsObstacle(x1, y1))
    {
        return false;
    }
    if (abs(y1 - y0) > abs(x1 - x0))
    {
        if (y1 < y0)
        {
            swap(x1, x0);
            swap(y1, y0);
        }
        double delta = (x1 - x0) / (y1 - y0);
        double intersectX = x0;
        if (abs(intersectX - round(intersectX)) < eps)
        {
            if (intersectX >= round(intersectX))
            {
                if (cellIsObstacle(int(intersectX) - 1, y0))
                {
                    return false;
                }
            }
            else
            {
                if (cellIsObstacle(int(intersectX) + 1, y0))
                {
                    return false;
                }
            }
        }
        intersectX += delta * (ceil(y0) - y0);
        for (int y = ceil(y0); y <= floor(y1); ++y)
        {
            if (cellIsObstacle(int(intersectX), y) || cellIsObstacle(int(intersectX), y - 1))
            {
                return false;
            }
            if (abs(intersectX - round(intersectX)) < eps)
            {
                if (intersectX >= round(intersectX))
                {
                    if (cellIsObstacle(int(intersectX) - 1, y) || cellIsObstacle(int(intersectX) - 1, y - 1))
                    {
                        return false;
                    }
                }
                else
                {
                    if (cellIsObstacle(int(intersectX) + 1, y) || cellIsObstacle(int(intersectX) + 1, y - 1))
                    {
                        return false;
                    }
                }
            }
            intersectX += delta;
        }
    }
    else
    {
        if (x1 < x0)
        {
            swap(x1, x0);
            swap(y1, y0);
        }
        double delta = (y1 - y0) / (x1 - x0);
        double intersectY = y0;
        if (abs(intersectY - round(intersectY)) < eps)
        {
            if (intersectY >= round(intersectY))
            {

                if (cellIsObstacle(x0, int(intersectY) - 1))
                {
                    return false;
                }
            }
            else
            {
                if (cellIsObstacle(x0, int(intersectY) + 1))
                {
                    return false;
                }
            }
        }
        intersectY += delta * (ceil(x0) - x0);
        for (int x = ceil(x0); x <= floor(x1); ++x)
        {
            if (cellIsObstacle(x, int(intersectY)) || cellIsObstacle(x - 1, int(intersectY)))
            {
                return false;
            }
            if (abs(intersectY - round(intersectY)) < eps)
            {
                if (intersectY >= round(intersectY))
                {
                    if (cellIsObstacle(x, int(intersectY) - 1) || cellIsObstacle(x - 1, int(intersectY) - 1))
                    {
                        return false;
                    }
                }
                else
                {
                    if (cellIsObstacle(x, int(intersectY) + 1) || cellIsObstacle(x - 1, int(intersectY) + 1))
                    {
                        return false;
                    }
                }
            }
            intersectY += delta;
        }
    }
    return true;
}

std::set<std::pair<int, int>> Map::retrievCellsOnLine(double x0, double y0, double x1, double y1) const
{
    double eps = 1e-9;
    set<pair<int, int>> cells;
    cells.insert({x0, y0});
    cells.insert({x1, y1});
    if (abs(y1 - y0) > abs(x1 - x0))
    {
        if (y1 < y0)
        {
            swap(x1, x0);
            swap(y1, y0);
        }
        double delta = (x1 - x0) / (y1 - y0);
        double intersectX = x0;
        if (abs(intersectX - round(intersectX)) < eps)
        {
            if (intersectX >= round(intersectX))
            {
                cells.insert({int(intersectX) - 1, y0});
            }
            else
            {
                cells.insert({int(intersectX) + 1, y0});
            }
        }
        intersectX += delta * (ceil(y0) - y0);
        for (int y = ceil(y0); y <= floor(y1); ++y)
        {
            cells.insert({int(intersectX), y});
            cells.insert({int(intersectX), y - 1});
            if (abs(intersectX - round(intersectX)) < eps)
            {
                if (intersectX >= round(intersectX))
                {
                    cells.insert({int(intersectX) - 1, y});
                    cells.insert({int(intersectX) - 1, y - 1});
                }
                else
                {
                    cells.insert({int(intersectX) + 1, y});
                    cells.insert({int(intersectX) + 1, y - 1});
                }
            }
            intersectX += delta;
        }
    }
    else
    {
        if (x1 < x0)
        {
            swap(x1, x0);
            swap(y1, y0);
        }
        double delta = (y1 - y0) / (x1 - x0);
        double intersectY = y0;
        if (abs(intersectY - round(intersectY)) < eps)
        {
            if (intersectY >= round(intersectY))
            {
                cells.insert({x0, int(intersectY) - 1});
            }
            else
            {
                cells.insert({x0, int(intersectY) + 1});
            }
        }
        intersectY += delta * (ceil(x0) - x0);
        for (int x = ceil(x0); x <= floor(x1); ++x)
        {
            cells.insert({x, int(intersectY)});
            cells.insert({x - 1, int(intersectY)});
            if (abs(intersectY - round(intersectY)) < eps)
            {
                if (intersectY >= round(intersectY))
                {
                    cells.insert({x, int(intersectY) - 1});
                    cells.insert({x - 1, int(intersectY) - 1});
                }
                else
                {
                    cells.insert({x, int(intersectY) + 1});
                    cells.insert({x - 1, int(intersectY) + 1});
                }
            }
            intersectY += delta;
        }
    }
    return cells;
}