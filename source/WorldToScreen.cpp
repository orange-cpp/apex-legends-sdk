//
// Created by vlad on 10/29/23.
//
#include "apex_sdk/WorldToScreen.h"
#include "apex_sdk/MemoryManagerSinglton.h"
#include "apex_sdk/Offsets.h"

namespace apex_sdk
{

    std::optional<omath::Vector3> WorldToScreen(omath::Vector3 worldPosition, float width, float height)
    {
        auto projected = (GetViewProjectionMatrix() * worldPosition).transpose();

        projected /= projected.at(0, 3);

        const auto out = projected * omath::matrix::to_screen_matrix(width,
                                                                   height);

        if (out.at(0,2) <= 0.f)
            return std::nullopt;
        auto final = omath::Vector3(out.at(0,0),
                                  out.at(0, 1),
                                  out.at(0,2));
        return {final};
    }


    const omath::matrix& GetViewProjectionMatrix()
    {
        static const auto& mm = Memory::Get();
        static const auto base = mm.GetModuleBaseAddressByName("r5apex.exe").value();

        static omath::matrix matrix(4,4);

        struct rawMatrix
        {
            float data[16];
        };

        matrix.set_from_raw(mm.ReadMemory<rawMatrix>(base+offset::view_projection_matrix)->data);

        return matrix;
    }
}