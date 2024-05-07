//
// Created by vlad on 11/6/23.
//

#include "apex_sdk/ProjectilePrediction.h"

std::optional<uml::Vector3>
apex_sdk::ProjectilePrediction::CalculateViewAngles(const apex_sdk::BaseEntity &local,
                                                    const apex_sdk::BaseEntity &target)
{
    using pred = uml::prediction::ProjectilePredictor;

    auto weapon = local.GetActiveWeapon();

    if (!weapon)
        return local.GetCameraPosition().ViewAngleTo(target.GetBonePosition(5));

    return pred::CalculateViewAngles(local.GetCameraPosition(),
                              target.GetBonePosition(5),
                              target.GetVelocity(),
                              750.f,
                              weapon->GetBulletSpeed(),
                              weapon->GetBulletGravity(),
                              !(target.GetFlags() & 1));
}
