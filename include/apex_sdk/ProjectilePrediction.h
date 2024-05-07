//
// Created by vlad on 11/6/23.
//

#pragma once
#include "uml/ProjectilePredictor.h"
#include "uml/Vector3.h"
#include "apex_sdk/BaseEntity.h"

namespace apex_sdk
{
    class ProjectilePrediction : private uml::prediction::ProjectilePredictor
    {
    public:
        [[nodiscard]]
        static std::optional<uml::Vector3> CalculateViewAngles(const BaseEntity& local,
                                                               const BaseEntity& target);

    };
}