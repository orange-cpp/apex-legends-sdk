//
// Created by vlad on 10/29/23.
//

#pragma once

#define OFFSET_ENTITYLIST 0x1DB4118 //cl_entitylist
#define OFFSET_LOCAL_ENT 0x2162818  //LocalPlayer might be moved to AVC_GameMovement


#define OFFSET_TEAM 0x030c //m_iTeamNum
#define OFFSET_HEALTH 0x2FC //m_iHealth
#define OFFSET_SHIELD 0x01a0 //m_shieldHealth
#define OFFSET_MAXSHIELD 0x01a4 //m_shieldHealthMax
#define OFFSET_ABS_VELOCITY 0x0170 //m_vecAbsVelocity
#define OFFSET_VISIBLE_TIME 0x1950 //CPlayer!lastVisibleTime
#define OFFSET_BREATH_ANGLES  OFFSET_VIEWANGLES - 0x10

#define OFFSET_LIFE_STATE 0x0658 //m_lifeState, >0 = dead
#define OFFSET_BLEED_OUT_STATE 0x26a0 //m_bleedoutState, >0 = knocked

#define OFFSET_ORIGIN 0x017c //m_vecAbsOrigin - 3rd offset after the first int and vector
#define OFFSET_BONES 0x0d60 + 0x48 //m_nForceBone + 0x48
#define OFFSET_CAMERAPOS 0x1e90 //CPlayer!camera_origin
#define OFFSET_VIEWANGLES 0x24f4 - 0x14 //m_ammoPoolCapacity - 0x14
#define OFFSET_BREATH_ANGLES  OFFSET_VIEWANGLES - 0x10
#define OFFSET_BREATH_ANGLES OFFSET_VIEWANGLES - 0x10
#define OFFSET_RENDER 0x73cc3e0 //ViewRender displays ESp, heath dist names etc

#define OFFSET_WEAPON 0x18f4 //m_latestPrimaryWeapons
#define OFFSET_BULLET_SPEED (0x1e5c) //CWeaponX!m_flProjectileSpeed maybe its WeaponSettings.projectile_launch_speed now
#define OFFSET_BULLET_SCALE (0x1e64) //CWeaponX!m_flProjectileScale maybe its WeaponSettings.projectile_gravity_scale now

namespace apex_sdk
{
    enum offset : std::ptrdiff_t
    {
        entity_list = 0x1DB4118,
        local_player = 0x2162818,
        view_projection_matrix = 0x2190c60,
    };
}

namespace apex_sdk::signatures
{
    constexpr std::string_view entityList = "48 8D 35 ? ? ? ? 0F 84";
    constexpr std::string_view viewProjectionMatrix = "48 8D 0D ? ? ? ? FF 90 ? ? ? ? 41 8B 04 1F" ; // + 0x10

    constexpr std::string_view m_iTeamNumber = "8B 87 ? ? ? ? 89 87 ? ? ? ? 33 C0 8B 15";
    constexpr std::string_view m_iHealth = "44 8B 83 ? ? ? ? 45 85 C0 44 0F 48 C7 41 8B D0 2B 93 ? ? ? ? 85 D2";
    constexpr std::string_view m_iShield = "39 87 ? ? ? ? 0F 84 ? ? ? ? 48 8B 07 48 8B CF FF 90 ? ? ? ? 44 8B 97";
    constexpr std::string_view m_vecAbsVelocity = "F3 0F 10 9F ? ? ? ? F3 0F 10 97 ? ? ? ? F3 0F 59 DB";
    constexpr std::string_view m_lastVisibleTime = "84 C0 0F 84 ? ? ? ? F3 0F 11 B3 ? ? ? ? E9";
    constexpr std::string_view m_vecOrigin = "F3 0F 7E 97";
    constexpr std::string_view m_boneMatrix = "89 81 ? ? ? ? C3 CC 48 89 6C 24"; // + 0x44
    constexpr std::string_view m_cameraPos = "0F 2E 89 ? ? ? ? 7A 58";
    constexpr std::string_view m_viewAngles = "F2 0F 10 B6 ? ? ? ? F3 41 0F 58 D3";
    constexpr std::string_view m_latestPrimaryWeapons = "";
}