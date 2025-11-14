#pragma once
#include <unordered_map>
#include <typeindex>
#include <vector>
#include <functional>
#include <Events/Event.h>

class EventHandler
{
public:
    static EventHandler& getInstance();

    using Handler = std::function<void(const Event&)>;

    template<typename EventType>
    void Subscribe(GameObject* target, Handler handler, std::function<bool(const Event&)> condition = nullptr)
    {
        auto& handlers = m_Handlers[std::type_index(typeid(EventType))];
        handlers.push_back({ target, std::move(handler), std::move(condition) });
    }

    
    void Unsubscribe(GameObject* target) {
        for (auto it = m_Handlers.begin(); it != m_Handlers.end(); )
        {
            auto& vec = it->second;

            vec.erase(
                std::remove_if(vec.begin(), vec.end(),
                    [target](const HandlerEntry& entry) {
                        return entry.target == target;
                    }),
                vec.end()
                        );

            if (vec.empty()) {
                it = m_Handlers.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    void Notify(const Event& event, GameObject* context);

private:
    struct HandlerEntry {
        GameObject* target;
        Handler handler;
        std::function<bool(const Event&)> condition;
    };

    std::unordered_map<std::type_index, std::vector<HandlerEntry>> m_Handlers;
};

