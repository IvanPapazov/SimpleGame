#pragma once
#include <vector>
#include <memory>
#include <Game/GameObject.h>

struct Rect {
    float m_X, m_Y, m_W, m_H;
};

class QuadTree {
private:
    static const int CAPACITY = 10;
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
    bool Intersects(const Rect& a, const Rect& b);
    void Subdivide();
    void Clear();
    Rect GetBoundingBox(GameObject* obj) const;
};
