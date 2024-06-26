//
// Created by vlad on 10/29/23.
//

#pragma once


#include <cstdint>
#include <optional>
#include <uml/Vector3.h>
#include "apex_sdk/Weapon.h"
#include <uml/color.h>



namespace apex_sdk
{
    enum BoneIndex : int
    {
        Head = 8,
        Neck = 7,
        Body = 5,
    };

    class BaseEntity
    {
    public:
        explicit BaseEntity(uintptr_t addr) {m_pHandle = addr;}

        [[nodiscard]] int GetHealth() const;

        [[nodiscard]] int GetShieldValue() const;
        [[nodiscard]] int GetMaxShieldValue() const;
        [[nodiscard]] uintptr_t GetVtable() const;

        [[nodiscard]] std::optional<Weapon> GetActiveWeapon() const;

        [[nodiscard]] uml::Vector3 GetOrigin() const;

        [[nodiscard]] int GetTeamNumber() const;

        [[nodiscard]] float LastVisibleTime() const;

        [[nodiscard]] bool IsAlive() const;

        [[nodiscard]] bool IsAirborne() const;


        [[nodiscard]] bool IsKnockedout() const;
        void SetViewAngles(const uml::Vector3 & other);
        [[nodiscard]] uml::Vector3 GetBonePosition(int iBone) const;
        [[nodiscard]] uml::Vector3 GetCameraPosition() const;
        [[nodiscard]] uml::Vector3 GetViewAngles() const;
        [[nodiscard]] uml::Vector3 GetVelocity() const;
        [[nodiscard]] uml::Vector3 GetBreathAngle() const;
        [[nodiscard]] uml::Vector3 GetAimPunch() const;
        [[nodiscard]] uml::color::Color GetHealthColor() const;
        [[nodiscard]] uml::color::Color GetShieldColor() const;
        [[nodiscard]] uint32_t GetFlags() const;
        bool operator==(const apex_sdk::BaseEntity& other) const {return m_pHandle == other.m_pHandle;}
    private:
        uintptr_t m_pHandle = 0;
    };
}