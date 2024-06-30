//
// Created by vlad on 11/6/23.
//

#pragma once
#include "omath/Vector3.h"
#include "apex_sdk/BaseEntity.h"

namespace apex_sdk
{
    class ProjectilePrediction
    {
    public:
        [[nodiscard]]
        static std::optional<omath::Vector3> CalculateViewAngles(const BaseEntity& local,
                                                               const BaseEntity& target);

    };
}