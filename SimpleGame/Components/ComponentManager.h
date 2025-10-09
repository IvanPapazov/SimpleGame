#pragma once
#include <RenderingManager.h>
class ComponentManager
{
private:
	Uint64 m_Now = SDL_GetPerformanceCounter();
	Uint64 m_Last = 0;
    
public:
    ComponentManager();

    GameObject* CreateGameObject(RenderingManager& ms_RendererManager);

    Uint64 GetNow() const { return m_Now; }
    Uint64 GetLast() const { return m_Last; }

    void SetNow(Uint64 now) { m_Now = now; }
    void SetLast(Uint64 last) { m_Last = last; }
};

