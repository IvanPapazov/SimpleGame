#pragma once
#include "stdafx.h"
#include <string>
#include <SDL.h>
#include <unordered_map>
#include <memory>

struct Animation {
    int m_StartFrame;
    int m_FrameCount;
    int m_FrameSpeed;
};

struct SpriteData {
    std::string m_CurrentState = "Idle";
    int m_FrameWidth;
    int m_FrameHeight;
    std::unordered_map<std::string, Animation> m_Animations;
};

class ResourceManager
{
private:
    std::unordered_map<std::string, Json::Value> m_JsonFiles;
    std::unordered_map<int, SDL_Texture*> m_Textures;
    std::unordered_map<int, std::unique_ptr<SpriteData>> m_SpriteData;

public:
    ResourceManager() = default;
    ~ResourceManager() = default;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;

    static ResourceManager& getInstance();

    bool loadJson(const std::string& id, const std::string& filePath);
    Json::Value getJson(const std::string& id);

    void setJson(const std::string& id, const Json::Value& json);

    bool loadTexture(const int& id, const std::string& filePath);
    SDL_Texture* getTexture(const int& id);

    void loadSpriteData(const int& id, std::unique_ptr<SpriteData> spriteData);
    SDL_Rect* getSrcRect(const int& id) const;

    std::string getCurrentState(int id) const;
    void setCurrentState(int id, const std::string& state);
};
