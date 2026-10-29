#pragma once
#include "pch.h"
extern HANDLE hProcess;

DWORD GetProcId(const wchar_t* procname);

template<typename T>
inline T Read(uintptr_t address) {
	T val;
	ReadProcessMemory(hProcess, (LPCVOID)address, &val, sizeof(T), nullptr);
	return val;
}
template<typename T>
inline void Write(uintptr_t address, T value) {
	WriteProcessMemory(hProcess, (LPVOID)address, &value, sizeof(T), nullptr);
}

uintptr_t ResolvePtrChain(uintptr_t base, std::vector<UINT> offsets);

inline uintptr_t GetModuleBaseAddress(DWORD pid, const wchar_t* modName) {
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
    if (hSnap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32W modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32FirstW(hSnap, &modEntry)) {
            do {
                if (!_wcsicmp(modEntry.szModule, modName)) {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32NextW(hSnap, &modEntry));
        }
        CloseHandle(hSnap);
    }
    return modBaseAddr;
}