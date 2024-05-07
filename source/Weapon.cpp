//
// Created by vlad on 10/29/23.
//

#include "apex_sdk/Weapon.h"
#include "apex_sdk/MemoryManagerSinglton.h"
#include "apex_sdk/Offsets.h"
namespace apex_sdk
{

    float Weapon::GetBulletSpeed() const
    {
        return Memory::Get().ReadMemory<float>(m_pHandle+OFFSET_BULLET_SPEED).value();
    }

    float Weapon::GetBulletGravity() const
    {
        return Memory::Get().ReadMemory<float>(m_pHandle+OFFSET_BULLET_SCALE).value() * 750.f;
    }
} // apex_sdk