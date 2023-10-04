#pragma once
#include <set>
class Map
{
public:
    Map();
    ~Map();
    Map(int, int);
    Map(int, int, bool **);
    Map(const Map &);
    Map &operator=(const Map &);
    int getWidth() const;
    void setWidth(int value);
    int getHeight() const;
    void setHeight(int value);
    bool **getMap() const;
    void setMap(int, int, bool **);
    void setCell(int i, int j, bool value);
    bool cellIsObstacle(int i, int j) const;
    bool isThereLineOfSight(double x0, double y0, double x1, double y1) const;
    bool getValue(int i, int j) const;
    bool isIn(int i, int j) const;
    std::set<std::pair<int, int>> retrievCellsOnLine(double x0, double y0, double x1, double y1) const;

    //    AgentController agent_;
private:
    int width_, height_;
    bool **cell_;
};