#include <SDL.h>
#include <iostream>
#include "window.h"
#include "playerObject.h"

const float GRAVITY = 9.8f;
const float GROUND_Y;

void gravity(Entity object)
{
    //vy += GRAVITY;
    //object.y += vy;

    // Simple ground collision
    if (object.y + object.h >= GROUND_Y) {
        object.y = GROUND_Y - object.h;
       // vy = 0;
    }
}
























































