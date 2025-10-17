#pragma once
#include <SDL.h>

class Components {
public:
    virtual ~Components() = default;
    virtual Components* Clone() const = 0;
    virtual void Update() = 0;
    virtual void HandleAllEvents() {
    }
    virtual int GetComponentId() = 0;
protected:
    static int GetUniqueComponentID() {
        static int lastID = 0;
        return lastID++;
    }
};
