//
// Created by vlad on 11/6/23.
//

#include "apex_sdk/ProjectilePrediction.h"
#include "omath/prediction/Engine.h"

std::optional<omath::Vector3>
apex_sdk::ProjectilePrediction::CalculateViewAngles(const apex_sdk::BaseEntity &local,
                                                    const apex_sdk::BaseEntity &target) {


    static const auto predEngine = omath::prediction::Engine(750.f, 0.0001f, 10.f, 3.f);

    const auto weapon = local.GetActiveWeapon();

    if (!weapon)
        return std::nullopt;

    omath::prediction::Target predtarget
    {
        .m_origin = target.GetBonePosition(3),
        .m_velocity = target.GetVelocity(),
        .m_isAirborne = target.IsAirborne()
    };
    omath::prediction::Projectile projectile
    {
        .m_origin = local.GetCameraPosition(),
        .m_launchSpeed = weapon->GetBulletSpeed(),
        .m_gravityScale   = weapon->GetBulletGravityMultiplier()
    };

    return predEngine.MaybeCalculateAimPoint(projectile, predtarget);
}
