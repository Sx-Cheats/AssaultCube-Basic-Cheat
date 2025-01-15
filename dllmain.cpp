#include "engine.h"




bool EAimbot;
Hook_t* HookAimBot;

void Entry(HMODULE module)
{
    EAimbot = true;
    FreeConsole();
    AllocConsole();
    NTapi::Init();
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "w", stdin);
    freopen("CONOUT$", "w", stderr);

    StartEngine();
   

    std::cout << "Project Initied !" << std::endl;
    std::cout << " Lib Module : " << NTapi::GetModuleAddress("lib.dll") << std::endl;

    
    system("pause");


    StopEngine();

    fclose(stdout);
    fclose(stdin);
    fclose(stderr); 
    FreeConsole();
    FreeLibraryAndExitThread((HMODULE)NTapi::GetModuleAddress("lib.dll"), 0);
   
    
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)Entry, hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

