#include "mem.h"
void mem::PatchEx(BYTE* dst, BYTE* src, uint64_t size, HANDLE hProc) {
	DWORD oldProtect;
	VirtualProtectEx(hProc, dst, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	WriteProcessMemory(hProc, dst, src, size, nullptr);
	VirtualProtectEx(hProc, src, size, oldProtect, &oldProtect);
}
void mem::NopEx(BYTE* dst, uint64_t size, HANDLE hProc) {
	BYTE* nopArray = new BYTE[size];
	memset(dst, 0x90, size);
	PatchEx(dst, nopArray, size, hProc);

	delete[] nopArray;
}