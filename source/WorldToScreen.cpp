//
// Created by vlad on 10/29/23.
//
#include "apex_sdk/WorldToScreen.h"
#include "apex_sdk/MemoryManagerSinglton.h"
#include "apex_sdk/Offsets.h"

namespace apex_sdk
{

    std::optional<uml::Vector3> WorldToScreen(uml::Vector3 worldPosition, float width, float height)
    {
        auto projected = (GetViewProjectionMatrix() * worldPosition).transpose();

        projected /= projected.at(0, 3);

        const auto out = projected * uml::matrix::to_screen_matrix(width,
                                                                   height);

        if (out.at(0,2) <= 0.f)
            return std::nullopt;
        auto final = uml::Vector3(out.at(0,0),
                                  out.at(0, 1),
                                  out.at(0,2));
        return {final};
    }

    uml::matrix GetViewProjectionMatrix()
    {
        const auto& mm = Memory::Get();

        static const auto base = Memory::Get().GetModuleBaseAddressByName("r5apex.exe").value();

        static const uintptr_t viewRender = mm.ReadMemory<uintptr_t>(base+OFFSET_RENDER).value();
        static const uintptr_t pViewMatrix = mm.ReadMemory<uintptr_t>(viewRender+0x11a350).value();


        const std::vector<uint8_t> raw =  mm.ReadMemory(pViewMatrix, 64);



        return {4,4, (float*)raw.data()};
    }
}