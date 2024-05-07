//
// Created by vlad on 10/29/23.
//

#include "apex_sdk/EntityList.h"
#include "apex_sdk/MemoryManagerSinglton.h"
#include "apex_sdk/BaseEntity.h"
#include "apex_sdk/Offsets.h"



namespace apex_sdk
{

    std::optional<BaseEntity> apex_sdk::EntityList::GetLocalPlayer()
    {
        static auto base = Memory::Get().GetModuleBaseAddressByName("r5apex.exe").value();

        auto plocalPlayerAddr = Memory::Get().ReadMemory<uintptr_t>(base+OFFSET_LOCAL_ENT);

        if (plocalPlayerAddr.value_or(0) == 0)
            return std::nullopt;

        return apex_sdk::BaseEntity(plocalPlayerAddr.value());
    }

    std::optional<BaseEntity> apex_sdk::EntityList::GetEntity(size_t index)
    {
        static auto base = Memory::Get().GetModuleBaseAddressByName("r5apex.exe").value();
        auto addr = Memory::Get().ReadMemory<uintptr_t>(base+OFFSET_ENTITYLIST +( index << 5));

        if (!addr.value_or(0))
            return std::nullopt;

        return apex_sdk::BaseEntity(addr.value());
    }

    std::vector<BaseEntity> EntityList::GetAllEntities()
    {
        const auto localPlayer = EntityList::GetLocalPlayer();

        if (!localPlayer)
            return {};

        std::vector<BaseEntity> entities;

        for (int i = 0; i < 200; i++)
        {
            auto ent = GetEntity(i);

            if (ent and ent->GetVtable() == localPlayer->GetVtable())
                entities.push_back(ent.value());
        }

        return entities;
    }
}