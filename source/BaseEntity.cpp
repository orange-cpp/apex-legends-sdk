//
// Created by vlad on 10/29/23.
//

#include "apex_sdk/BaseEntity.h"
#include "apex_sdk/MemoryManagerSinglton.h"
#include "apex_sdk/Offsets.h"
#include "apex_sdk/EntityList.h"
namespace apex_sdk
{
    int BaseEntity::GetHealth() const
    {
        return Memory::Get().ReadMemory<int>(m_pHandle+OFFSET_HEALTH).value();
    }

    int BaseEntity::GetShieldValue() const
    {
        return Memory::Get().ReadMemory<int>(m_pHandle+OFFSET_SHIELD).value();
    }

    uml::Vector3 BaseEntity::GetOrigin() const
    {
        return Memory::Get().ReadMemory<uml::Vector3>(m_pHandle+OFFSET_ORIGIN).value();
    }

    float BaseEntity::LastVisibleTime() const
    {
        return Memory::Get().ReadMemory<float>(m_pHandle+OFFSET_VISIBLE_TIME).value();
    }

    uml::Vector3 BaseEntity::GetBonePosition(int iBone) const
    {
        struct Bone {
            uint8_t _pad1[0xCC];
            float x;
            uint8_t _pad2[0xC];
            float y;
            uint8_t _pad3[0xC];
            float z;
        };
        auto pBoneMatrix = Memory::Get().ReadMemory<uintptr_t>(m_pHandle + OFFSET_BONES).value();
        const auto bone =  Memory::Get().ReadMemory<Bone>(pBoneMatrix + iBone * 0x30);

        return GetOrigin() + uml::Vector3{bone->x, bone->y, bone->z};
    }

    int BaseEntity::GetTeamNumber() const
    {
        return Memory::Get().ReadMemory<int>(m_pHandle+OFFSET_TEAM).value();
    }

    bool BaseEntity::IsAlive() const
    {
        const auto health = GetHealth();

        return !Memory::Get().ReadMemory<bool>(m_pHandle+OFFSET_LIFE_STATE).value() and health > 0 and health <= 100;
    }

    bool BaseEntity::IsKnockedout() const
    {
        return Memory::Get().ReadMemory<bool>(m_pHandle + OFFSET_BLEED_OUT_STATE).value();
    }

    void BaseEntity::SetViewAngles(const uml::Vector3 &other)
    {
        if (std::abs(other.x) > 89 || std::abs(other.y) > 180)
            return;

        Memory::Get().WriteMemory<uml::Vector3>(m_pHandle + OFFSET_VIEWANGLES, other);
    }

    uml::Vector3 BaseEntity::GetCameraPosition() const
    {
        return Memory::Get().ReadMemory<uml::Vector3>(m_pHandle + OFFSET_CAMERAPOS).value();
    }

    uml::Vector3 BaseEntity::GetViewAngles() const
    {
        return Memory::Get().ReadMemory<uml::Vector3>(m_pHandle + OFFSET_VIEWANGLES).value();
    }

    std::optional<Weapon> BaseEntity::GetActiveWeapon() const
    {
        uintptr_t actWeaponID = Memory::Get().ReadMemory<uintptr_t>(m_pHandle + OFFSET_WEAPON).value() & 0xFFFF;
        auto currentWeapon = EntityList::GetEntity(actWeaponID);

        if (!currentWeapon)
            return std::nullopt;

        return Weapon(currentWeapon->m_pHandle);
    }

    uintptr_t BaseEntity::GetVtable() const
    {
        return Memory::Get().ReadMemory<uintptr_t>(m_pHandle).value();
    }

    uml::Vector3 BaseEntity::GetVelocity() const
    {
        return Memory::Get().ReadMemory<uml::Vector3>(m_pHandle+OFFSET_ABS_VELOCITY).value();
    }

    uint32_t BaseEntity::GetFlags() const
    {
        return Memory::Get().ReadMemory<int>(m_pHandle+0xc8).value();;
    }

    uml::Vector3 BaseEntity::GetBreathAngle() const
    {
        return Memory::Get().ReadMemory<uml::Vector3>(m_pHandle+OFFSET_BREATH_ANGLES).value();
    }

    int BaseEntity::GetMaxShieldValue() const
    {
        return Memory::Get().ReadMemory<int>(m_pHandle+OFFSET_MAXSHIELD).value();
    }
    uml::color::Color BaseEntity::GetHealthColor() const
    {
        using Color = uml::color::Color;

        return Color::Red().Blend(Color::Green(), static_cast<float>(GetHealth()) / 100.f);
    }

    uml::color::Color BaseEntity::GetShieldColor() const
    {
        const auto shieldVal = GetShieldValue();
        const auto barVal = (shieldVal == 0) ? 0 : (shieldVal % 25 == 0) ? 25 : shieldVal % 25;
        const float ratio = (float) barVal / (float )25;

        using Color = uml::color::Color;
        const auto common = Color::FromRGBA(168, 168, 168, 255);
        const auto rare = Color::FromRGBA(81, 168, 214, 255);
        const auto epic = Color::FromRGBA(178, 55, 200, 255);
        const auto mythic = Color::FromRGBA(255, 78, 29, 255);

        if (shieldVal <= 25)
            return  GetHealthColor().Blend(Color::FromRGBA(255, 255, 255, 255), ratio);

        if (shieldVal <= 50)
            return  Color::FromRGBA(255, 255, 255, 255).Blend(common, ratio);

        if (shieldVal <= 75)
            return common.Blend(rare, ratio);

        if (shieldVal <= 100)
            return rare.Blend(epic, ratio);

        if (shieldVal <= 125)
            return epic.Blend(mythic, ratio);

        return GetHealthColor();
    }
}