#pragma once
#include "stdafx.h"
#include <SDL.h>
#include <Core/Component.h>
#include <Game/GameObject.h>

class CollisionComponent : public Component
{
private:
    float m_X, m_Y;
    float m_Width, m_Height;

    bool m_LeftCollision = true;
    bool m_RightCollision = true;
    bool m_BottomCollision = true;
    bool m_TopCollision = true;
    bool m_Hit = false;
    bool m_HitPast = false;
    bool m_HitDetected = false;
    bool m_DoorCollision = false;

    bool CheckCollision(CollisionComponent* a, CollisionComponent* b);
    void HandleCollision(GameObject* b, CollisionComponent* colA, CollisionComponent* colB);
    void CheckLeftCollision(GameObject* b, CollisionComponent* colA, const SDL_Rect& bounds);
    void CheckRightCollision(GameObject* b, CollisionComponent* colA, const SDL_Rect& bounds);
    void CheckTopCollision(GameObject* b, CollisionComponent* colA, CollisionComponent* colB, const SDL_Rect& bounds);
    void CheckBottomCollision(GameObject* b, CollisionComponent* colA, const SDL_Rect& bounds);

public:
    CollisionComponent(float x, float y, float w, float h)
        : m_X(x), m_Y(y), m_Width(w), m_Height(h) {}

    ~CollisionComponent() override = default;

    void Update() override;

    bool LeftCollision() const { return m_LeftCollision; }
    bool RightCollision() const { return m_RightCollision; }
    bool BottomCollision() const { return m_BottomCollision; }
    bool TopCollision() const { return m_TopCollision; }
    bool IsHit() const { return m_Hit; }
    bool IsHitPast() const { return m_HitPast; }
    bool DoorCollision() const { return m_DoorCollision; }
    bool IsHitDetected() const { return m_HitDetected;}


    void SetHitDetected(bool value) { m_HitDetected = value;}
    void SetLeftCollision(bool value) { m_LeftCollision = value; }
    void SetRightCollision(bool value) { m_RightCollision = value; }
    void SetBottomCollision(bool value) { m_BottomCollision = value; }
    void SetTopCollision(bool value) { m_TopCollision = value; }
    void SetHitPast(bool value) { m_HitPast = value; }
    void SetHit(bool value);
    void SetDoorCollision(bool value) { m_DoorCollision = value; }

    float GetX() const { return m_X; }
    float GetY() const { return m_Y; }
    float GetWidth() const { return m_Width; }
    float GetHeight() const { return m_Height; }
};
