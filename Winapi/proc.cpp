#include "proc.h"

HANDLE hProcess = 0;

DWORD GetProcId(const wchar_t* procname) {
	HWND hWnd = FindWindowW(NULL, procname);
	if (!hWnd) return 0;

	DWORD pid = NULL;
	GetWindowThreadProcessId(hWnd, &pid);
	if(pid != NULL)
	{
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	}
	return pid;
}


uintptr_t ResolvePtrChain(uintptr_t baseAddress, std::vector<UINT> offsets) {
    uintptr_t addr = 0;

    ReadProcessMemory(hProcess, (LPCVOID)baseAddress, &addr, sizeof(addr), nullptr);

    for (size_t i = 0; i < offsets.size() - 1; ++i) {
        addr += offsets[i];
        ReadProcessMemory(hProcess, (LPCVOID)addr, &addr, sizeof(addr), nullptr);
    }

    if (!offsets.empty()) {
        addr += offsets.back();
    }

    return addr;
}
