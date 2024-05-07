//
// Created by vlad on 10/29/23.
//

#pragma once
#include "uml/Vector3.h"
#include "uml/matrix.h"
#include <optional>

namespace apex_sdk
{
    const uml::matrix& GetViewProjectionMatrix();
    std::optional<uml::Vector3> WorldToScreen(uml::Vector3 worldPosition, float width, float height);
}