//
// Created by vlad on 11/19/23.
//

#pragma once

namespace apex_sdk
{

    class Controller
    {
    public:
        static void SetInForward(int state);
        static int  GetForwardState();
    };

} // apex_sdk
