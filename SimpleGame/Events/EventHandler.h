#pragma once
#include <Events/Event.h>
#include <functional>

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

    //template<typename EventType>
    //void Unsubscribe(GameObject* target) {
    //    if (!target) return;
    //    auto it = m_Handlers.find(std::type_index(typeid(EventType)));
    //    if (it != m_Handlers.end()) {
    //        auto& vec = it->second;
    //        vec.erase(
    //            std::remove_if(vec.begin(), vec.end(),
    //                [target](const HandlerEntry& entry) {
    //                    return entry.target == target;
    //                }),
    //            vec.end()
    //                    );
    //    }
    //}

    void Notify(const Event& event, GameObject* context);

private:
    struct HandlerEntry {
        GameObject* target;
        Handler handler;
        std::function<bool(const Event&)> condition;
    };

    std::unordered_map<std::type_index, std::vector<HandlerEntry>> m_Handlers;
};

