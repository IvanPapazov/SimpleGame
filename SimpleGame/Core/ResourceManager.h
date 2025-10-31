#pragma once
#include "stdafx.h"
#include <string>
#include <SDL.h>
#include <unordered_map>


struct Animation {
    int m_StartFrame;
    int m_FrameCount;
    int m_FrameSpeed; 
};

struct SpriteData {
    std::string currentState = "RunLeft";
    int m_FrameWidth;
    int m_FrameHeight;
    std::unordered_map<std::string, Animation> m_Animations;
};

class ResourceManager
{
private:
    std::unordered_map<std::string, Json::Value> m_JsonFiles;
    std::unordered_map<int, SDL_Texture*> m_Textures;
    std::unordered_map<int, SpriteData*> m_SpriteData;

public:
    ResourceManager() = default;
    ~ResourceManager() = default;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;

    static ResourceManager& getInstance();

    bool loadJson(const std::string& id, const std::string& filePath);
    Json::Value getJson(const std::string& id);

    bool loadTexture(const int& id, const std::string& filePath);
    SDL_Texture* getTexture(const int& id);

    void loadSpriteData(const int& id, SpriteData* spriteData);
    SDL_Rect* getSrcRect(const int& id) const;

    void setCurrentState(int id, const std::string& state) {
        if (m_SpriteData.count(id)) m_SpriteData.at(id)->currentState = state;
    }

};
