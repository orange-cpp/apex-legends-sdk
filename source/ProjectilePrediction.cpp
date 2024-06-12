//
// Created by vlad on 11/6/23.
//

#include "apex_sdk/ProjectilePrediction.h"
#include "uml/prediction/Engine.h"

std::optional<uml::Vector3>
apex_sdk::ProjectilePrediction::CalculateViewAngles(const apex_sdk::BaseEntity &local,
                                                    const apex_sdk::BaseEntity &target) {


    const auto predEngine = uml::prediction::Engine(750.f, 0.00001f, 5.f, 5.f);

    const auto weapon = local.GetActiveWeapon();

    if (!weapon)
        return target.GetBonePosition(5);

    uml::prediction::Target predtarget
    {
        .m_origin = target.GetBonePosition(5),
        .m_velocity = target.GetVelocity(),
        .m_isAirborne = target.IsAirborne()
    };
    uml::prediction::Projectile projectile
    {
        .m_origin = local.GetCameraPosition(),
        .m_launchSpeed = weapon->GetBulletSpeed(),
        .m_gravityScale   = weapon->GetBulletGravityMultiplier()
    };

    return predEngine.MaybeCalculateAimPoint(projectile, predtarget);
}
