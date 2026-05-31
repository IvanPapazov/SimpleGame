#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <Core/GameObjectManager.h>
#include <Core/DatabaseInitializer.h>
#include <Core/UserAccount.h>
#include <Components/RenderComponent.h>
#include <Core/ResourceManager.h>
#include <Core/QuadTree.h>
#include <Events/EventHandler.h>
#include <SDL_test_font.h>
//#include <Core/LevelGenerator.h>

GameObjectManager& gameObjectManager = GameObjectManager::getInstance();
EventHandler& g_EventHandler = EventHandler::getInstance();
ResourceManager& g_ResourceManager = ResourceManager::getInstance();
//LevelGenerator& g_LevelGenerator = LevelGenerator::getInstance();

Game& Game::getInstance()
{
    static Game ms_Instance;
    return ms_Instance;
}

bool Game::IsInitialized()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        m_IsRunning = false;
        return false;
    }

    m_Window = SDL_CreateWindow("Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GetScreenWidth(), GetScreenHeight(), SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (!m_Window)
    {
        std::cerr << "Window creation failed! SDL_Error: " << SDL_GetError() << std::endl;
        m_IsRunning = false;
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_Renderer)
    {
        std::cerr << "Renderer creation failed! SDL_Error: " << SDL_GetError() << std::endl;
        m_IsRunning = false;
        return false;
    }

    g_ResourceManager.loadJson("objectsInfo", "jsons/ObjectsInfoFile.json");

    g_ResourceManager.loadJson("player", "jsons/PlayerFile.json");
    g_ResourceManager.loadJson("enemy", "jsons/EnemyFile.json");
    g_ResourceManager.loadJson("terrain", "jsons/TerrainFile.json");
    g_ResourceManager.loadJson("background", "jsons/BackgroundFile.json");
    g_ResourceManager.loadJson("pathways", "jsons/PathwaysFile.json");
    g_ResourceManager.loadJson("doors", "jsons/DoorsFile.json");
    g_ResourceManager.loadJson("hearts", "jsons/HeartsFile.json");
    g_ResourceManager.loadJson("textures", "jsons/TexturesFile.json");
    g_ResourceManager.loadJson("sprite", "jsons/SpriteDataFile.json");
    g_ResourceManager.loadJson("menu", "jsons/MenuFile.json");
    g_ResourceManager.loadJson("login", "jsons/LoginFile.json");

    //g_LevelGenerator.CreateLevel();

    Rect worldBounds = { 0, 0, GetScreenWidth(), GetScreenHeight() };
    qt = std::make_unique<QuadTree>(worldBounds);

    m_IsRunning = true;

    // Equivalent to Startup.cs: EnsureCreated() + SeedUsers()
    m_Database.Open("game.db");
    m_Database.EnsureCreated();
    DatabaseInitializer::Seed(m_Database);

    return true;
}

void Game::RequestLevelChange(const std::string& levelName) {
    m_RequestedLevel = levelName;
    m_LevelChangeRequested = true;
}

void Game::RequestReturnToMenu() {
    m_ReturnToMenu = true;
    m_IsRunning = false;
}

void Game::SaveDeathRecord()
{
    // Parse level number from e.g. "level_2" -> 2
    int levelNum = 1;
    auto pos = m_CurrentLevel.rfind('_');
    if (pos != std::string::npos)
        levelNum = std::stoi(m_CurrentLevel.substr(pos + 1));

    // Get today's date as YYYY-MM-DD
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
    localtime_s(&tm, &t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");

    // Use the currently logged-in user, fall back to "Player1" if none
    std::string loggedIn = m_Database.UA_GetLoggedInUsername();
    if (loggedIn.empty())
        loggedIn = "Player1";

    PlayerProgress record;
    record.username = loggedIn;
    record.maxLevel = levelNum;
    record.date     = oss.str();
    m_Database.Insert(record);

    // Print all records to the terminal
    std::cout << "\n--- PlayerProgress table ---\n";
    std::cout << "Id | Username | MaxLevel | Date\n";
    std::cout << "---+----------+----------+----------\n";
    for (const auto& row : m_Database.GetAll())
    {
        std::cout << row.id << "  | "
                  << row.username << "  | "
                  << row.maxLevel << "        | "
                  << row.date << "\n";
    }
    std::cout << "----------------------------\n";
}

void Game::LoadLevel(const std::string& levelName)
{
    auto terrains = m_Info.ReadInfoTerrain(levelName);
    for (auto& [key, object] : terrains) {
        gameObjectManager.AddGameObject(std::move(object));
    }
    auto pathways = m_Info.ReadInfoPathways(levelName);
    for (auto& [key, object] : pathways) {
        gameObjectManager.AddGameObject(std::move(object));
    }
    auto doors = m_Info.ReadInfoDoors(levelName);
    for (auto& [key, object] : doors) {
        gameObjectManager.AddGameObject(std::move(object));

    }
    auto players = m_Info.ReadInfoPlayer("level_1");
    for (auto& [key, object] : players) {
        gameObjectManager.AddGameObject(std::move(object));
    }
    auto enemies = m_Info.ReadInfoEnemy(levelName);
    for (auto& [key, object] : enemies) {
        gameObjectManager.AddGameObject(std::move(object));

    }
}

void Game::Shutdown()
{
    if (m_Renderer)
    {
        SDL_DestroyRenderer(m_Renderer);
        m_Renderer = nullptr;
    }

    if (m_Window)
    {
        SDL_DestroyWindow(m_Window);
        m_Window = nullptr;
    }

    SDL_Quit();
}

bool Game::RunMainMenu()
{
    // Load textures and background for the menu
    m_Info.ReadTextures();
    m_Info.ReadInfoBackground();

    // Read board data from MenuFile.json
    Json::Value menuData = g_ResourceManager.getJson("menu");
    Json::Value& board = menuData["Board"];
    int boardTexId  = board["id"].asInt();
    int startTexId  = menuData["Start"]["id"].asInt();
    int loginTexId  = menuData["Login"]["id"].asInt();
    int stopTexId   = menuData["Stop"]["id"].asInt();
    float scaleX = GetScreenWidth()  / 2560.0f;
    float scaleY = GetScreenHeight() / 1300.0f;
    int boardW = static_cast<int>(board["width"].asFloat()  * scaleX);
    int boardH = static_cast<int>(board["height"].asFloat() * scaleY);
    int boardX = (GetScreenWidth()  - boardW) / 2;
    int boardY = (GetScreenHeight() - boardH) / 2;
    SDL_Rect boardRect = { boardX, boardY, boardW, boardH };

    // Three evenly-spaced buttons inside the board
    int btnW = static_cast<int>(menuData["Start"]["width"].asFloat()  * scaleX);
    int btnH = static_cast<int>(menuData["Start"]["height"].asFloat() * scaleY);
    int btnX = boardX + (boardW - btnW) / 2;
    SDL_Rect playBtn  = { btnX, boardY + boardH * 2 / 10, btnW, btnH };
    SDL_Rect loginBtn = { btnX, boardY + boardH * 4 / 10, btnW, btnH };

    int exitBtnW = static_cast<int>(menuData["Stop"]["width"].asFloat()  * scaleX);
    int exitBtnH = static_cast<int>(menuData["Stop"]["height"].asFloat() * scaleY);
    int exitBtnX = boardX + (boardW - exitBtnW) / 2;
    SDL_Rect exitBtn = { exitBtnX, boardY + boardH * 6 / 10, exitBtnW, exitBtnH };

    bool menuRunning = true;
    bool playSelected = false;

    while (menuRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                menuRunning = false;
                playSelected = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                int mx = event.button.x;
                int my = event.button.y;

                if (mx >= playBtn.x && mx <= playBtn.x + playBtn.w &&
                    my >= playBtn.y && my <= playBtn.y + playBtn.h)
                {
                    playSelected = true;
                    menuRunning = false;
                }
                else if (mx >= loginBtn.x && mx <= loginBtn.x + loginBtn.w &&
                         my >= loginBtn.y && my <= loginBtn.y + loginBtn.h)
                {
                    // Open login menu; if cancelled we just stay in main menu loop
                    RunLoginMenu();
                }
                else if (mx >= exitBtn.x && mx <= exitBtn.x + exitBtn.w &&
                         my >= exitBtn.y && my <= exitBtn.y + exitBtn.h)
                {
                    playSelected = false;
                    menuRunning = false;
                }
            }
        }

        SDL_RenderClear(m_Renderer);

        // Draw level background
        if (RenderComponent::GetOffScreenCombinedTexture())
        {
            SDL_Rect dst = { 0, 0, GetScreenWidth(), GetScreenHeight() };
            SDL_RenderCopy(m_Renderer, RenderComponent::GetOffScreenCombinedTexture(), nullptr, &dst);
        }

        // Draw centered menu board texture
        SDL_Texture* boardTex = g_ResourceManager.getTexture(boardTexId);
        if (boardTex)
            SDL_RenderCopy(m_Renderer, boardTex, nullptr, &boardRect);

        // Play button
        SDL_Texture* startTex = g_ResourceManager.getTexture(startTexId);
        if (startTex)
            SDL_RenderCopy(m_Renderer, startTex, nullptr, &playBtn);
        else
        {
            SDL_SetRenderDrawColor(m_Renderer, 50, 180, 50, 255);
            SDL_RenderFillRect(m_Renderer, &playBtn);
        }

        // Login button
        SDL_Texture* loginTex = g_ResourceManager.getTexture(loginTexId);
        if (loginTex)
            SDL_RenderCopy(m_Renderer, loginTex, nullptr, &loginBtn);
        else
        {
            SDL_SetRenderDrawColor(m_Renderer, 50, 120, 200, 255);
            SDL_RenderFillRect(m_Renderer, &loginBtn);
        }

        // Exit button
        SDL_Texture* stopTex = g_ResourceManager.getTexture(stopTexId);
        if (stopTex)
            SDL_RenderCopy(m_Renderer, stopTex, nullptr, &exitBtn);
        else
        {
            SDL_SetRenderDrawColor(m_Renderer, 180, 50, 50, 255);
            SDL_RenderFillRect(m_Renderer, &exitBtn);
        }

        SDL_RenderPresent(m_Renderer);
    }

    return playSelected;
}

bool Game::RunLoginMenu()
{
    Json::Value loginData = g_ResourceManager.getJson("login");
    Json::Value& board = loginData["Board"];
    int boardTexId   = board["id"].asInt();
    int fieldTexId   = loginData["Username"]["id"].asInt();
    int applyTexId   = loginData["Apply"]["id"].asInt();
    int cancelTexId  = loginData["Cancel"]["id"].asInt();
    float scaleX = GetScreenWidth()  / 2560.0f;
    float scaleY = GetScreenHeight() / 1300.0f;

    int boardW = static_cast<int>(board["width"].asFloat()  * scaleX);
    int boardH = static_cast<int>(board["height"].asFloat() * scaleY);
    int boardX = (GetScreenWidth()  - boardW) / 2;
    int boardY = (GetScreenHeight() - boardH) / 2;
    SDL_Rect boardRect = { boardX, boardY, boardW, boardH };

    int fieldW = static_cast<int>(loginData["Username"]["width"].asFloat()  * scaleX);
    int fieldH = static_cast<int>(loginData["Username"]["height"].asFloat() * scaleY);
    int fieldX = boardX + (boardW - fieldW) / 2;
    SDL_Rect userRect = { fieldX, boardY + boardH * 25 / 100, fieldW, fieldH };
    SDL_Rect passRect = { fieldX, boardY + boardH * 50 / 100, fieldW, fieldH };

    int btnW = static_cast<int>(loginData["Apply"]["width"].asFloat()  * scaleX);
    int btnH = static_cast<int>(loginData["Apply"]["height"].asFloat() * scaleY);
    int applyOffX  = static_cast<int>(loginData["Apply"]["x"].asFloat()  * scaleX);
    int applyOffY  = static_cast<int>(loginData["Apply"]["y"].asFloat()  * scaleY);
    int cancelOffX = static_cast<int>(loginData["Cancel"]["x"].asFloat() * scaleX);
    int cancelOffY = static_cast<int>(loginData["Cancel"]["y"].asFloat() * scaleY);
    SDL_Rect cancelRect = { boardX + boardW / 20          + cancelOffX, boardY + boardH * 78 / 100 + cancelOffY, btnW, btnH };
    SDL_Rect applyRect  = { boardX + boardW - btnW - boardW / 20 + applyOffX, boardY + boardH * 78 / 100 + applyOffY, btnW, btnH };

    std::string usernameText;
    std::string passwordText;
    std::string displayPassword; // shows '*' characters
    bool focusUsername = false;
    bool focusPassword = false;

    SDL_StartTextInput();

    bool menuRunning = true;
    bool result = false; // true = applied successfully

    while (menuRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                menuRunning = false;
                result = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                int mx = event.button.x;
                int my = event.button.y;

                // Toggle text field focus
                focusUsername = (mx >= userRect.x && mx <= userRect.x + userRect.w &&
                                 my >= userRect.y && my <= userRect.y + userRect.h);
                focusPassword = (mx >= passRect.x && mx <= passRect.x + passRect.w &&
                                 my >= passRect.y && my <= passRect.y + passRect.h);

                // Cancel button
                if (mx >= cancelRect.x && mx <= cancelRect.x + cancelRect.w &&
                    my >= cancelRect.y && my <= cancelRect.y + cancelRect.h)
                {
                    menuRunning = false;
                    result = false;
                }
                // Apply button
                else if (mx >= applyRect.x && mx <= applyRect.x + applyRect.w &&
                         my >= applyRect.y && my <= applyRect.y + applyRect.h)
                {
                    if (!usernameText.empty() && !passwordText.empty())
                    {
                        UserAccount existing = m_Database.UA_GetByUsername(usernameText);

                        if (existing.id == 0)
                        {
                            // New user — insert and log in
                            UserAccount newAcc;
                            newAcc.username = usernameText;
                            newAcc.password = passwordText;
                            newAcc.entered  = false;
                            m_Database.UA_Insert(newAcc);
                            m_Database.UA_SetEntered(usernameText);
                            menuRunning = false;
                            result = true;
                        }
                        else if (existing.password == passwordText)
                        {
                            // Existing user, correct password — log in
                            m_Database.UA_SetEntered(usernameText);
                            menuRunning = false;
                            result = true;
                        }
                        // else: username exists but wrong password — do nothing

                        // Print UserAccount table to terminal
                        std::cout << "\n--- UserAccount table ---\n";
                        std::cout << "Id | Username | Password | Entered\n";
                        std::cout << "---+----------+----------+--------\n";
                        for (const auto& row : m_Database.UA_GetAll())
                        {
                            std::cout << row.id       << "  | "
                                      << row.username << "  | "
                                      << row.password << "  | "
                                      << (row.entered ? "true" : "false") << "\n";
                        }
                        std::cout << "-------------------------\n";
                    }
                }
            }
            else if (event.type == SDL_TEXTINPUT)
            {
                if (focusUsername)
                    usernameText += event.text.text;
                else if (focusPassword)
                {
                    passwordText    += event.text.text;
                    displayPassword += '*';
                }
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_BACKSPACE)
                {
                    if (focusUsername && !usernameText.empty())
                        usernameText.pop_back();
                    else if (focusPassword && !passwordText.empty())
                    {
                        passwordText.pop_back();
                        displayPassword.pop_back();
                    }
                }
                else if (event.key.keysym.sym == SDLK_TAB)
                {
                    // Tab switches focus between fields
                    if (focusUsername) { focusUsername = false; focusPassword = true; }
                    else               { focusPassword = false; focusUsername = true; }
                }
            }
        }

        SDL_RenderClear(m_Renderer);

        // Background
        if (RenderComponent::GetOffScreenCombinedTexture())
        {
            SDL_Rect dst = { 0, 0, GetScreenWidth(), GetScreenHeight() };
            SDL_RenderCopy(m_Renderer, RenderComponent::GetOffScreenCombinedTexture(), nullptr, &dst);
        }

        // Board
        SDL_Texture* boardTex = g_ResourceManager.getTexture(boardTexId);
        if (boardTex)
            SDL_RenderCopy(m_Renderer, boardTex, nullptr, &boardRect);

        // Username field background
        SDL_Texture* fieldTex = g_ResourceManager.getTexture(fieldTexId);
        if (fieldTex)
        {
            SDL_RenderCopy(m_Renderer, fieldTex, nullptr, &userRect);
            SDL_RenderCopy(m_Renderer, fieldTex, nullptr, &passRect);
        }
        else
        {
            SDL_Color userColor = focusUsername ? SDL_Color{200,200,255,255} : SDL_Color{230,230,230,255};
            SDL_Color passColor = focusPassword ? SDL_Color{200,200,255,255} : SDL_Color{230,230,230,255};
            SDL_SetRenderDrawColor(m_Renderer, userColor.r, userColor.g, userColor.b, userColor.a);
            SDL_RenderFillRect(m_Renderer, &userRect);
            SDL_SetRenderDrawColor(m_Renderer, passColor.r, passColor.g, passColor.b, passColor.a);
            SDL_RenderFillRect(m_Renderer, &passRect);
        }

        // Focus highlight border
        SDL_SetRenderDrawColor(m_Renderer, 80, 140, 255, 255);
        if (focusUsername) SDL_RenderDrawRect(m_Renderer, &userRect);
        if (focusPassword) SDL_RenderDrawRect(m_Renderer, &passRect);

        // ── Text rendering helper ─────────────────────────────────────────
        // SDL test font: each char is 8 px wide, FONT_LINE_HEIGHT px tall
        const float fs = 2.0f;                          // font scale factor
        const int   CW = 8;                             // base char width
        const int   CH = FONT_LINE_HEIGHT;              // base char height (14)
        const int   scaledCW = (int)(CW * fs);
        const int   scaledCH = (int)(CH * fs);

        // Lambda: draw text centred inside a rect, with optional blinking cursor
        auto drawField = [&](const SDL_Rect& rect, const std::string& text,
                             const char* placeholder, bool focused)
        {
            bool showPlaceholder = text.empty() && !focused;

            // Choose color and string to render
            const char* str = showPlaceholder ? placeholder : text.c_str();
            SDL_Color color = showPlaceholder
                ? SDL_Color{150, 150, 150, 255}   // grey placeholder
                : SDL_Color{ 20,  20,  20, 255};  // dark text

            int strLen = (int)strlen(str);
            int textPixW = strLen * scaledCW;

            // Clamp to field width so text never overflows visually
            float drawX = ((float)rect.x + (rect.w - textPixW) / 2.0f) / fs;
            float drawY = ((float)rect.y + (rect.h - scaledCH)  / 2.0f) / fs;

            SDL_RenderSetScale(m_Renderer, fs, fs);
            SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, 255);
            if (strLen > 0)
                SDLTest_DrawString(m_Renderer, drawX, drawY, str);
            SDL_RenderSetScale(m_Renderer, 1.0f, 1.0f);

            // Blinking cursor (only on the actual typed text side, not placeholder)
            if (focused && !showPlaceholder && (SDL_GetTicks() % 1000 < 500))
            {
                int cx = rect.x + (rect.w - textPixW) / 2 + textPixW + 2;
                int cy = rect.y + (rect.h - scaledCH) / 2;
                SDL_Rect cursor = { cx, cy, 3, scaledCH };
                SDL_SetRenderDrawColor(m_Renderer, 20, 20, 20, 255);
                SDL_RenderFillRect(m_Renderer, &cursor);
            }
            // Empty field + focused: cursor at centre
            if (focused && text.empty() && (SDL_GetTicks() % 1000 < 500))
            {
                int cx = rect.x + rect.w / 2;
                int cy = rect.y + (rect.h - scaledCH) / 2;
                SDL_Rect cursor = { cx, cy, 3, scaledCH };
                SDL_SetRenderDrawColor(m_Renderer, 20, 20, 20, 255);
                SDL_RenderFillRect(m_Renderer, &cursor);
            }
        };

        drawField(userRect, usernameText,    "Username", focusUsername);
        drawField(passRect, displayPassword, "Password", focusPassword);
        // ─────────────────────────────────────────────────────────────────

        // Cancel button
        SDL_Texture* cancelTex = g_ResourceManager.getTexture(cancelTexId);
        if (cancelTex)
            SDL_RenderCopy(m_Renderer, cancelTex, nullptr, &cancelRect);
        else
        {
            SDL_SetRenderDrawColor(m_Renderer, 180, 50, 50, 255);
            SDL_RenderFillRect(m_Renderer, &cancelRect);
        }

        // Apply button
        SDL_Texture* applyTex = g_ResourceManager.getTexture(applyTexId);
        if (applyTex)
            SDL_RenderCopy(m_Renderer, applyTex, nullptr, &applyRect);
        else
        {
            SDL_SetRenderDrawColor(m_Renderer, 50, 180, 50, 255);
            SDL_RenderFillRect(m_Renderer, &applyRect);
        }

        SDL_RenderPresent(m_Renderer);
    }

    SDL_StopTextInput();
    return result;
}

void Game::Run()
{
    gameObjectManager.RemoveAllGameObject();
    m_IsRunning = true;
    m_Info.ReadTextures();
    m_Info.ReadSpriteData();
    m_Info.ReadInfoBackground();
    LoadLevel("level_1");
    m_LastFrameTime = SDL_GetPerformanceCounter();

    while (m_IsRunning) {
        SDL_Event event;
        std::vector<int> toRemove;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                m_IsRunning = false;
            }
        }

        SDL_RenderClear(m_Renderer);

        Uint64 start = SDL_GetPerformanceCounter();
        Uint64 frameTime = start - m_LastFrameTime;
        m_dt = (frameTime / static_cast<float>(SDL_GetPerformanceFrequency())) * 100.0f;
        m_LastFrameTime = start;

        if (RenderComponent::GetOffScreenCombinedTexture())
        {
            SDL_Rect dst = { 0, 0, GetScreenWidth(), GetScreenHeight() };
            SDL_RenderCopy(m_Renderer, RenderComponent::GetOffScreenCombinedTexture(), nullptr, &dst);
        }

        if (m_LevelChangeRequested) {
            gameObjectManager.RemoveAllGameObject();
            LoadLevel(m_RequestedLevel);

            m_LevelChangeRequested = false;
        }

        if (qt) {
            qt->Clear();
            for (auto& [key, obj] : gameObjectManager.m_gameObjects) {
                qt->Insert(obj.get());
            }
        }

        gameObjectManager.UpdateAllGameObject();

        for (const auto& [key, obj] : gameObjectManager.m_gameObjects) {
            if (obj && !obj->GetIsActive()) {
                g_EventHandler.Unsubscribe(obj.get());
                toRemove.push_back(obj->GetId());
            }
        }
        for (int id : toRemove) {
            gameObjectManager.RemoveGameObject(id);
        }

       

        SDL_RenderPresent(m_Renderer);
    }
}
