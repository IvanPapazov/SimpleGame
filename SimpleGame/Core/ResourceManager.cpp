#include "stdafx.h"
#include "ResourceManager.h"
#include <fstream>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <Game/Game.h>

ResourceManager& ResourceManager::getInstance()
{
    static ResourceManager ms_Instance;
    return ms_Instance;
}

std::string ResourceManager::getCurrentState(int id) const {
    auto it = m_SpriteData.find(id);
    return (it != m_SpriteData.end()) ? it->second->m_CurrentState : "";
}

void ResourceManager::setCurrentState(int id, const std::string& state) {
    auto it = m_SpriteData.find(id);
    if (it != m_SpriteData.end()) {
        it->second->m_CurrentState = state;
    }
}

bool ResourceManager::loadJson(const std::string& id, const std::string& filePath)
{
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Could not open JSON\n";
        return false;
    }

    Json::Value root;
    Json::CharReaderBuilder builder;
    std::string errs;

    if (!Json::parseFromStream(builder, file, &root, &errs)) {
        SDL_Log("Failed to parse JSON: %s", errs.c_str());
        return false;
    }

    m_JsonFiles[id] = root;
    return true;
}

Json::Value ResourceManager::getJson(const std::string& id)
{
    return m_JsonFiles.count(id) ? m_JsonFiles[id] : Json::Value();
}

void ResourceManager::setJson(const std::string& id, const Json::Value& json)
{
    m_JsonFiles[id] = json;
}

bool ResourceManager::loadTexture(const int& id, const std::string& filePath)
{
    if (m_Textures.count(id)) {
        return true;
    }

    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        SDL_Log("Failed to load image %s: %s", filePath.c_str(), IMG_GetError());
        return false;
    }

    SDL_Texture* m_Texture = SDL_CreateTextureFromSurface(Game::getInstance().GetRenderer(), surface);
    SDL_FreeSurface(surface);

    if (m_Texture) {
        m_Textures[id] = m_Texture;
        return true;
    }
    else {
        SDL_Log("Failed to create texture: %s", SDL_GetError());
        return false;
    }
}

SDL_Texture* ResourceManager::getTexture(const int& id)
{
    return m_Textures.count(id) ? m_Textures[id] : nullptr;
}

void ResourceManager::loadSpriteData(const int& id, std::unique_ptr<SpriteData> spriteData)
{
    m_SpriteData[id] = std::move(spriteData);
}

SDL_Rect* ResourceManager::getSrcRect(const int& id) const
{
    auto it = m_SpriteData.find(id);
    if (it == m_SpriteData.end()) return nullptr;

    const SpriteData* data = it->second.get();
    auto rect = std::make_unique<SDL_Rect>();

    rect->w = data->m_FrameWidth;
    rect->h = data->m_FrameHeight;

    const Animation& anim = data->m_Animations.at(data->m_CurrentState);
    int frameIndex = static_cast<int>((SDL_GetTicks() / anim.m_FrameSpeed) % anim.m_FrameCount);
    frameIndex += anim.m_StartFrame;
    rect->x = rect->w * frameIndex;
    rect->y = 0;

    return rect.release();
}
