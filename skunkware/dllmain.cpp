#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include "cheat/menu/menu.hpp"
#include "cheat/modules/clicker.hpp"
#include "cheat/modules/aimassist.hpp"
#include "cheat/modules/velocity.hpp"

#include "cheat/sdk/minecraft/minecraft.hpp"
#include "cheat/sdk/minecraft/entity/entity.hpp"

#include "cheat/sdk/java.hpp"
#include <thread>
#include <iostream>

void init(HMODULE hmod) {

    //AllocConsole();
    //freopen("CONOUT$", "w", stdout);

    menu::place_hooks();
    java::attach();


    instance = std::make_unique<c_minecraft>(java::env, java::klasses);

    while (true) {

        localPlayer = std::make_unique<c_entity_player>(java::env, instance->getPlayer());
        world = std::make_unique<c_world>(java::env, instance->getWorld());


        if (!menu::injected) {
            break;
        }

        aclicker::run();
        aclicker::run_right();
        aimassist::run();
        velocity::run();

        Sleep(1);
    }

    //HWND console = GetConsoleWindow();

    //FreeConsole();
    //PostMessage(console, WM_CLOSE, 0, 0);
    menu::remove_hooks();
    MH_Uninitialize();

    FreeLibraryAndExitThread(hmod, 0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)init, hModule, NULL, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

