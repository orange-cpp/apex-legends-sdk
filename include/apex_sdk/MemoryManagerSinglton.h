//
// Created by vlad on 10/29/23.
//

#pragma once

#include <memory_manager/MemoryManager.h>

namespace apex_sdk
{
    class Memory : public memory_manager::MemoryManager
    {
    public:
        [[nodiscard]] static Memory& Get();

        Memory(const Memory& val) = delete;
        Memory(const Memory&& val) = delete;

        Memory& operator=(const Memory& val) = delete;
        Memory& operator=(const Memory&& val) = delete;
    private:
        explicit Memory(const std::string &procName);
    };
}