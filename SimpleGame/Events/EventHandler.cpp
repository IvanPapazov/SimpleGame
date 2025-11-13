#include "stdafx.h"
#include "EventHandler.h"


EventHandler& EventHandler::getInstance()
{
    static EventHandler ms_Instance;
    return ms_Instance;
}


void EventHandler::Notify(const Event& event, GameObject* context)
{
    auto it = m_Handlers.find(std::type_index(typeid(event)));
    if (it == m_Handlers.end()) return;

    for (const auto& entry : it->second) {
        if (entry.target == context || context == nullptr) {
            if (!entry.condition || entry.condition(event)) {
                entry.handler(event);
            }
        }
    }
}
