//
// Created by vlad on 11/19/23.
//

#include "apex_sdk/Controller.h"
#include "apex_sdk/MemoryManagerSinglton.h"
#include <thread>

namespace apex_sdk
{
    void Controller::SetInForward(int state)
    {
        static const auto base = Memory::Get().GetModuleBaseAddressByName("r5apex.exe").value();
        Memory::Get().WriteMemory(base+0x07383d38, state);
    }

    int Controller::GetForwardState()
    {
        static const auto base = Memory::Get().GetModuleBaseAddressByName("r5apex.exe").value();
        return Memory::Get().ReadMemory<int>(base+0x07383d38).value();
    }
} // apex_sdk