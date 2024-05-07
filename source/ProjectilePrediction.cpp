//
// Created by vlad on 11/6/23.
//

#include "apex_sdk/ProjectilePrediction.h"
#include "uml/ProjectilePredictor.h"

std::optional<uml::Vector3>
apex_sdk::ProjectilePrediction::CalculateViewAngles(const apex_sdk::BaseEntity &local,
                                                    const apex_sdk::BaseEntity &target) {


    const auto predEngine = uml::prediction::ProjectilePredictor(750.f, 5, 0.0005f);

    const auto weapon = local.GetActiveWeapon();

    if (!weapon)
        return target.GetBonePosition(5);

    uml::prediction::Target predtarget
    {
        .m_origin = target.GetBonePosition(5),
        .m_vecVelocity = target.GetVelocity(),
        .m_IsAirborne = !(target.GetFlags() &1)
    };
    uml::prediction::Projectile projectile
    {
        .m_origin = local.GetCameraPosition(),
        .m_velocity = weapon->GetBulletSpeed(),
        .m_gravityMultiplier   = weapon->GetBulletGravityMultiplier()
    };

    return predEngine.PredictPointToAim(predtarget, projectile);
}
