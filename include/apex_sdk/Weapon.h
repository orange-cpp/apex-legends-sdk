//
// Created by vlad on 10/29/23.
//

#pragma once

#include <cstdint>

namespace apex_sdk
{

    class Weapon
    {
    public:
        explicit Weapon(uintptr_t ptr) {m_pHandle = ptr;}
        [[nodiscard]] float GetBulletSpeed() const;
        [[nodiscard]] float GetBulletGravity() const;

    private:
        uintptr_t m_pHandle = 0;
    };

} // apex_sdk
