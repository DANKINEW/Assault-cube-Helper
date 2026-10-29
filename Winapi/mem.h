#pragma once
#include "pch.h"
namespace mem {
	void PatchEx(BYTE* dst, BYTE* src, uint64_t size, HANDLE hProc);
	void NopEx(BYTE* dst, uint64_t size, HANDLE hProc);
}