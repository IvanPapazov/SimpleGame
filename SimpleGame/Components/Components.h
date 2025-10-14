#pragma once
#include <SDL.h>

class Components {
public:
    virtual ~Components() = default;
    virtual void Update() = 0;
    virtual void HandleAllEvents() = 0;
    virtual int GetComponentId() = 0;
protected:
    static int GetUniqueComponentID() {
        static int lastID = 0;
        return lastID++;
    }
};
