//
// Created by vlad on 10/29/23.
//
#include "apex_sdk/MemoryManagerSinglton.h"

namespace apex_sdk
{
    Memory& Memory::Get()
    {
        static auto obj = Memory("r5apex.exe");
        return obj;
    }

    Memory::Memory(const std::string &procName) : MemoryManager(procName)
    {

    }
}

