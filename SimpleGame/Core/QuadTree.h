#pragma once
#include <vector>
#include <memory>
#include <Game/GameObject.h>

struct Rect {
    float m_X, m_Y, m_W, m_H;

    bool Contains(float px, float py) const {
        return px >= m_X && px <= m_X + m_W &&
            py >= m_Y && py <= m_Y + m_H;
    }

    bool Intersects(const Rect& other) const {
        return !(m_X + m_W < other.m_X || other.m_X + other.m_W < m_X ||
            m_Y + m_H < other.m_Y || other.m_Y + other.m_H < m_Y);
    }
};

class QuadTree {
private:
    static const int CAPACITY = 4;
    Rect boundary;
    std::vector<GameObject*> objects;
    bool divided = false;

    std::unique_ptr<QuadTree> northeast;
    std::unique_ptr<QuadTree> northwest;
    std::unique_ptr<QuadTree> southeast;
    std::unique_ptr<QuadTree> southwest;

public:
    QuadTree(Rect boundary);

    bool Insert(GameObject* obj);
    void Query(const Rect& range, std::vector<GameObject*>& found);
    void Subdivide();
    void Clear();
    Rect GetBoundingBox(GameObject* obj) const;
};
