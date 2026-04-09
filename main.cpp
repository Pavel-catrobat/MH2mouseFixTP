#include <windows.h>

// function
DWORD WINAPI AimThread(LPVOID lpParam) {
    bool isAiming = false;

    while (true) {
        // button
        if (GetAsyncKeyState(0x58) & 0x8000) {
            if (!isAiming) {
                // button true
                mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
                isAiming = true;
            }
        } else {
            if (isAiming) {
                // button false
                mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
                isAiming = false;
            }
        }
        Sleep(10); // sleep
    }
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        // start
        CreateThread(NULL, 0, AimThread, NULL, 0, NULL);
    }
    return TRUE;
}
