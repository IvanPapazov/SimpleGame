#include <GameObject.h>
#include "../loadTexture.h"


GameObject initializeGameObject(float x, float y, const char* filePath) {
    GameObject object;
    object.setId(1);
    object.setWidth(80.0f);
    object.setHeight(100.0f);
    object.setRigidbody(Rigidbody(x, y));
    object.setTexture(loadTexture(filePath));
    if (!object.getTexture()) {
        std::cerr << "Failed to load player texture!\n";
    }
    return object;
}