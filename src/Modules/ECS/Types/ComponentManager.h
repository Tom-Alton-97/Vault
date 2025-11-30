#pragma once

#include <unordered_map>
#include <memory>
#include <typeindex>
#include <vector>
#include <stdexcept>

#include "ComponentArray.h"
#include "ComponentArrayBase.h"
#include "Entity.h"
#include "Singleton.h"

namespace ECS_System
{
    using ComponentTypeID = std::size_t;

    class ComponentManager : public Singleton<ComponentManager>
    {
    public:
        template<typename T>
        void registerComponent()
        {
            auto typeIndex = std::type_index(typeid(T));
            if (componentArrays.find(typeIndex) == componentArrays.end())
            {
                componentArrays[typeIndex] = std::make_unique<ComponentArray<T>>();
            }
        }

        template<typename T>
        void addComponent(EntityID entity, const T& component)
        {
            getComponentArray<T>().insert(entity, component);
        }

        template<typename T>
        void removeComponent(EntityID entity)
        {
            getComponentArray<T>().remove(entity);
        }

        template<typename T>
        T& getComponent(EntityID entity)
        {
            return getComponentArray<T>().get(entity);
        }

        template<typename T>
        const std::vector<EntityID>& getEntitiesWithComponent()
        {
            return getComponentArray<T>().getEntities();
        }

        void Reset()
        {
            componentArrays.clear();
        }
        void destructor() noexcept override {};

    private:
        friend struct std::default_delete<ComponentManager>;
        friend class Singleton<ComponentManager>;

        std::unordered_map<std::type_index, std::unique_ptr<ComponentArrayBase>> componentArrays;

        template<typename T>
        ComponentArray<T>& getComponentArray()
        {
            auto typeIndex = std::type_index(typeid(T));
            auto it = componentArrays.find(typeIndex);
            if (it == componentArrays.end())
                throw std::runtime_error("Component type not registered.");

            return *static_cast<ComponentArray<T>*>(it->second.get());
        }
    };
}