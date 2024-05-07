//
// Created by vlad on 10/29/23.
//
#pragma once
#include <vector>
#include <optional>

namespace apex_sdk
{
    class BaseEntity;
    class EntityList
    {
    public:
        static std::optional<BaseEntity> GetEntity(size_t index);
        static std::optional<BaseEntity> GetLocalPlayer();
        static std::vector<BaseEntity> GetAllEntities();
        static std::vector<BaseEntity> GetVisibleEnemies();
    };

} // apex_legends