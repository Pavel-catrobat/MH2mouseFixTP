#include <windows.h>
#include <cstdio>

UINT keyBind = 0x5A;

DWORD WINAPI AimThread(LPVOID lpParam) {
    bool isAiming = false;
    
    char iniPath[MAX_PATH];
    GetModuleFileNameA((HMODULE)lpParam, iniPath, MAX_PATH);
    strcpy(strrchr(iniPath, '.'), ".ini");

    keyBind = GetPrivateProfileIntA("Settings", "KeyCode", 0x5A, iniPath);

    while (true) {
        if (GetAsyncKeyState(keyBind) & 0x8000) {
            if (!isAiming) {
                mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
                isAiming = true;
            }
        } else {
            if (isAiming) {
                mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
                isAiming = false;
            }
        }
        Sleep(10);
    }
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        // hModule
        CreateThread(NULL, 0, AimThread, (LPVOID)hModule, 0, NULL);
    }
    return TRUE;
}

