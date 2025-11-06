#include "stdafx.h" 
#include "QuadTree.h"
#include <Components/RigidBodyComponent.h>
#include <Components/CollisionComponent.h>

QuadTree::QuadTree(Rect boundary) : boundary(boundary) {}

void QuadTree::Clear() {
	objects.clear();
	if (divided) {
		northeast->Clear();
		northwest->Clear();
		southeast->Clear();
		southwest->Clear();

		northeast.reset();
		northwest.reset();
		southeast.reset();
		southwest.reset();

		divided = false;
	}
}

Rect QuadTree::GetBoundingBox(GameObject* obj) const {

	CollisionComponent* col = obj->GetComponent<CollisionComponent>();
	if (!col) return Rect{ 0, 0, 0, 0 };

	return Rect{
	   col->getX(),
	   col->getY(),
	   col->getWidth(),
	   col->getHeight()
	};
}

bool QuadTree::Insert(GameObject* obj) {
	Rect objBox = GetBoundingBox(obj);
	if (!boundary.Intersects(objBox)) return false;

	if (objects.size() < CAPACITY) {
		objects.push_back(obj);
		return true;
	}

	if (!divided) Subdivide();

	return (northeast->Insert(obj) || northwest->Insert(obj) ||
		southeast->Insert(obj) || southwest->Insert(obj));
}

void QuadTree::Subdivide() {
	float x = boundary.m_X;
	float y = boundary.m_Y;
	float w = boundary.m_W / 2.0f;
	float h = boundary.m_H / 2.0f;

	northeast = std::make_unique<QuadTree>(Rect{ x + w, y, w, h });
	northwest = std::make_unique<QuadTree>(Rect{ x, y, w, h });
	southeast = std::make_unique<QuadTree>(Rect{ x + w, y + h, w, h });
	southwest = std::make_unique<QuadTree>(Rect{ x, y + h, w, h });

	divided = true;
}

void QuadTree::Query(const Rect& range, std::vector<GameObject*>& found) {
	if (!boundary.Intersects(range)) return;

	for (auto* obj : objects) {
		Rect objBox = GetBoundingBox(obj);
		if (range.Intersects(objBox)) {
			found.push_back(obj);
		}
	}

	if (divided) {
		northeast->Query(range, found);
		northwest->Query(range, found);
		southeast->Query(range, found);
		southwest->Query(range, found);
	}
}
