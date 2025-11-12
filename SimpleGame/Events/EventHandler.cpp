#include "stdafx.h"
#include "EventHandler.h"


EventHandler& EventHandler::getInstance()
{
    static EventHandler ms_Instance;
    return ms_Instance;
}

void EventHandler::Unsubscribe(GameObject* target) {
    if (!target) return;

    for (auto& [type, vec] : m_Handlers) {
        for (auto it = vec.begin(); it != vec.begin() + std::distance(vec.begin(), vec.end()); ) {
            if (it->target == target) {
                it = vec.erase(it);
            }
            else {
                ++it;
            }
        }
    }
}



void EventHandler::Notify(const Event& event, GameObject* context)
{
    auto it = m_Handlers.find(std::type_index(typeid(event)));
    if (it != m_Handlers.end()) {
        for (auto& entry : it->second) {
            if (!entry.target || !context) continue;
            if(entry.target == context)
            {
                entry.handler(event);
            }
        }
    }
}