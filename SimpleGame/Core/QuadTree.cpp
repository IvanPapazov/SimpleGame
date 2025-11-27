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
	   col->GetX(),
	   col->GetY(),
	   col->GetWidth(),
	   col->GetHeight()
	};
}

bool QuadTree::Insert(GameObject* obj) {
	Rect objBox = GetBoundingBox(obj);

	if (!Intersects(boundary, objBox))
		return false;

	if (!divided && objects.size() < CAPACITY) {
		objects.push_back(obj);
		return true;
	}

	if (!divided)
		Subdivide();

	if (northeast->Contains(objBox)) 
		return northeast->Insert(obj);
	if (northwest->Contains(objBox))
		return northwest->Insert(obj);
	if (southeast->Contains(objBox))
		return southeast->Insert(obj);
	if (southwest->Contains(objBox))
		return southwest->Insert(obj);

	objects.push_back(obj);
	return true;
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

bool QuadTree::Contains(const Rect& obj) const {
	return (obj.m_X >= boundary.m_X &&
		obj.m_Y >= boundary.m_Y &&
		obj.m_X + obj.m_W <= boundary.m_X + boundary.m_W &&
		obj.m_Y + obj.m_H <= boundary.m_Y + boundary.m_H);
}



void QuadTree::Query(const Rect& range, std::vector<GameObject*>& found) {
	if (!Intersects(this->boundary, range)) return;

	for (auto* obj : objects) {
		if (obj->HasComponent<CollisionComponent>())
		{
			Rect objBox = GetBoundingBox(obj);
			if (Intersects(range, objBox)) {
				found.push_back(obj);
			}
		}
	}

	if (divided) {
		northeast->Query(range, found);
		northwest->Query(range, found);
		southeast->Query(range, found);
		southwest->Query(range, found);
	}
}

bool QuadTree::Intersects(const Rect& a, const Rect& b) {
	return !(a.m_X + a.m_W < b.m_X ||
		a.m_X > b.m_X + b.m_W ||
		a.m_Y + a.m_H < b.m_Y ||
		a.m_Y > b.m_Y + b.m_H);
}

