#include <windows.h>
#include <wincrypt.h>
#include <iostream>
#include <ntstatus.h>

int main() {
    DWORD index = 0;
    DWORD provider_type = 0;
    DWORD provider_name_size = 0;
    LPSTR provider_name = nullptr;

    while (CryptEnumProviders(index, 0, 0, &provider_type, 0, &provider_name_size)) {
        if (!(provider_name = (LPSTR)malloc(provider_name_size))) {
            std::cerr << "Couldn't allocate provider name buffer" << std::endl;
            exit(1);
        }

        if (!CryptEnumProviders(index++, 0, 0, &provider_type, provider_name, &provider_name_size)) {
            std::cerr << "Couldn't fetch provider name" << std::endl;
            exit(1);
        }

        std::cout << provider_name << std::endl;

        free(provider_name);
    }

    std::cout << "Provider amount: " << index;

  return 0;
}
