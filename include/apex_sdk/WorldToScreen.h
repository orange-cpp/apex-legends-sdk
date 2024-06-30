//
// Created by vlad on 10/29/23.
//

#pragma once
#include "omath/Vector3.h"
#include "omath/matrix.h"
#include <optional>

namespace apex_sdk
{
    const omath::matrix& GetViewProjectionMatrix();
    std::optional<omath::Vector3> WorldToScreen(omath::Vector3 worldPosition, float width, float height);
}