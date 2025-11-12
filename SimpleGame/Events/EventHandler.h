#pragma once
#include <Events/Event.h>
#include <functional>

class EventHandler
{
public:
    static EventHandler& getInstance();

    using Handler = std::function<void(const Event&)>;

    template<typename EventType>
    void Subscribe(GameObject* target, Handler handler)
    {
        auto& handlers = m_Handlers[std::type_index(typeid(EventType))];
        handlers.push_back({
            target, std::move(handler)
            });
    }

    void Unsubscribe(GameObject* target);
    void Notify(const Event& event, GameObject* context);

private:
    struct HandlerEntry {
        GameObject* target;
        Handler handler;
    };

    std::unordered_map<std::type_index, std::vector<HandlerEntry>> m_Handlers;
};

