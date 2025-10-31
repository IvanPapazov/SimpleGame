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

void ResourceManager::loadSpriteData(const int& id, SpriteData* spriteData)
{
    m_SpriteData[id] = spriteData;
}

Json::Value ResourceManager::getJson(const std::string& id)
{
    return m_JsonFiles.count(id) ? m_JsonFiles[id] : Json::Value();
}

SDL_Texture* ResourceManager::getTexture(const int& id)
{
    return m_Textures.count(id) ? m_Textures[id] : nullptr;
}


SDL_Rect* ResourceManager::getSrcRect(const int& id) const
{    
    SDL_Rect* rect=new SDL_Rect();
    if (m_SpriteData.count(id))
    {
        SpriteData* data = m_SpriteData.at(id);
        rect->w = data->m_FrameWidth;
        rect->h = data->m_FrameHeight;

        const Animation& anim = data->m_Animations.at(data->currentState);
        int frameIndex = static_cast<int>((SDL_GetTicks() / anim.m_FrameSpeed) % anim.m_FrameCount);
        frameIndex += anim.m_StartFrame;
        rect->x = rect->w * frameIndex;
        rect->y = 0;
        return rect;
    }
    return nullptr;
}

