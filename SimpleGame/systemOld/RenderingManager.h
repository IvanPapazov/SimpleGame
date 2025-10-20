//#pragma once
//#include <SDL.h>
//#include <iostream>
//#include <unordered_map>
//
//const int g_ScreenWidth = 800;
//const int g_ScreenHeight = 600;
//
//class RenderingManager
//{
//public:
//    static RenderingManager& getInstance();
//
//    bool IsInitialized();
//    void Close();
//
//    SDL_Renderer* GetRenderer() const 
//    {
//        return m_Renderer; 
//    }
//    SDL_Window* GetWindow() const 
//    {
//        return m_Window;
//    }
//
//private:
//    RenderingManager() = default;
//    ~RenderingManager() = default;
//    RenderingManager(const RenderingManager& rm) = delete;
//    RenderingManager(RenderingManager&& rm) = delete;
//
//    SDL_Window* m_Window = nullptr;
//    SDL_Renderer* m_Renderer = nullptr;
//
//};