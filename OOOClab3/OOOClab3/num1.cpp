#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <vector>

using namespace std;

int main() {
    MEMORYSTATUSEX memoryStatus; // struct which is used to store the memory status information
    memoryStatus.dwLength = sizeof(memoryStatus);

    if (GlobalMemoryStatusEx(&memoryStatus)) {
        // Successfully retrieved memory status information
        // access the information in the MEMORYSTATUSEX structure
        cout << "Total virtual memory: " << memoryStatus.ullTotalVirtual / 1024 / 1024 << " mb" << std::endl;
        cout << "Available virtual memory: " << memoryStatus.ullAvailVirtual / 1024 / 1024 << " mb" << std::endl;
    }

    // The size of memory to allocate in bytes
    const size_t blockSize = 100 * 1024 * 1024; // 100 ла

    std::vector<void*> allocatedMemoryBlocks;

    while (true) {

        void* memBlock = VirtualAlloc(nullptr, blockSize, MEM_COMMIT, PAGE_READWRITE);

        if (memBlock == nullptr) {
            // failed
            break;
        }

        allocatedMemoryBlocks.push_back(memBlock);
        cout << "success\n";
    }

    cout << "Allocated " << allocatedMemoryBlocks.size() * blockSize / (1024 * 1024) << " MB memory in " << allocatedMemoryBlocks.size() << " blocks." << std::endl;

    if (GlobalMemoryStatusEx(&memoryStatus)) {
        cout << "Total virtual memory: " << memoryStatus.ullTotalVirtual / 1024 / 1024 << " mb" << std::endl;
        cout << "Available virtual memory: " << memoryStatus.ullAvailVirtual / 1024 / 1024 << " mb" << std::endl;
    }
    cout << "----------------------------------";
    // delete every 2 block
    for (size_t i = 1; i < allocatedMemoryBlocks.size(); i += 2) {
        VirtualFree(allocatedMemoryBlocks[i], 0, MEM_RELEASE);
    }

    cout << "success release\n";

    if (GlobalMemoryStatusEx(&memoryStatus)) {

        cout << "Total virtual memory: " << memoryStatus.ullTotalVirtual / 1024 / 1024 << " mb" << std::endl;
        cout << "Available virtual memory: " << memoryStatus.ullAvailVirtual / 1024 / 1024 << " mb" << std::endl;
    }

    cout << "----------------------------------";

    // delete every 2 block
    for (size_t i = 0; i < allocatedMemoryBlocks.size(); i += 2) {
        VirtualFree(allocatedMemoryBlocks[i], 0, MEM_RELEASE);
    }

    cout << "success release\n";

    if (GlobalMemoryStatusEx(&memoryStatus)) {

        cout << "Total virtual memory: " << memoryStatus.ullTotalVirtual / 1024 / 1024 << " mb" << std::endl;
        cout << "Available virtual memory: " << memoryStatus.ullAvailVirtual / 1024 / 1024 << " mb" << std::endl;
    }

    cout << "----------------------------------";

    while (true) {

        void* memBlock = VirtualAlloc(nullptr, blockSize, MEM_RESERVE, PAGE_READWRITE);

        if (memBlock == nullptr) {
            // failed
            break;
        }

        allocatedMemoryBlocks.push_back(memBlock);
        cout << "success\n";
    }

    if (GlobalMemoryStatusEx(&memoryStatus)) {

        cout << "Total virtual memory: " << memoryStatus.ullTotalVirtual / 1024 / 1024 << " mb" << std::endl;
        cout << "Available virtual memory: " << memoryStatus.ullAvailVirtual / 1024 / 1024 << " mb" << std::endl;
    }

    cout << "Press any button to leave";

    getchar();

    return 0;

}