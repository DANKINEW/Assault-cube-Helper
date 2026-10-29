
#include "pch.h"
#include "proc.h"

int main()
{ 
    MessageBox(0, L"Virus launched", L"SUCCESS", MB_ICONERROR | MB_OK | MB_DEFBUTTON1);

    DWORD pid = GetProcId(L"AssaultCube");

    uintptr_t moduleBase = GetModuleBaseAddress(pid, L"ac_client.exe");

    uintptr_t baseAddress = moduleBase + 0x18AC00;

    std::vector<UINT> offsets = { 0x364, 0x14, 0x0 };
    std::vector<UINT> Health_offsets = { 0xec };

    uintptr_t ResolvedAddr = ResolvePtrChain(baseAddress, offsets);
    uintptr_t ResolvedHealthAddr = ResolvePtrChain(baseAddress, Health_offsets);

    uintptr_t address = ResolvedAddr;
    uintptr_t Health_address = ResolvedHealthAddr;

    UINT addr = Read<UINT>(address);
    uint32_t AmmoAmount;
    std::cout << "How much ammo: ";
    std::cin >> AmmoAmount;
    Write<int>(address, AmmoAmount);

    addr = Read<UINT>(address);

    std::cout << "Changed ammo:" << addr << '\n';

    char answ;
    std::cout << "Toggle infinite health mode or enter value yourself?(press del to close program if in inf health mode) Y/N: ";
    std::cin >> answ;
    if(answ == 'N')
    {
        uint32_t HealthAmount;
        std::cout << "How much Health: ";
        std::cin >> HealthAmount;
        Write<int>(Health_address, HealthAmount);
        UINT HltAm = Read<UINT>(Health_address);
        std::cout << "Changed Health: " << HltAm << '\n';
    }
    if (answ == 'Y') {
        while (!GetAsyncKeyState(VK_DELETE)) {
            Write<int>(Health_address, 9999);
            Sleep(60);
        }
        for (UINT i = 5; i > 0; i--) {
            std::cout << "Cancelled Inf health mode, closing program in " << i << " seconds" << '\n';
            Sleep(1000);
        }
    }
    return 0;

}

