#include <windows.h>
#include <bcrypt.h>
#include <iostream>
#include <ntstatus.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Please, specify secret and text as two arguments" << std::endl;
        return 0;
    }
    PUCHAR secret = reinterpret_cast<PUCHAR>(argv[1]);
    PUCHAR text = reinterpret_cast<PUCHAR>(argv[2]);

    NTSTATUS status;
    // 0x00000001 - cipher operation; 0x00000040 - key derivation operation
    ULONG symmetric_key_operation_filter = 0x00000041;
    // 0x00000010 - signature operation; 0x00000004 - asymmetric encryption; 0x00000008 - secret agreement;
    ULONG asymmetric_key_operation_filter = 0x0000001C;


    // Symmetric keys
    ULONG alg_count = 0;
    BCRYPT_ALGORITHM_IDENTIFIER* alg_id = nullptr;
    BCRYPT_ALG_HANDLE alg_handle = 0;
    BCRYPT_KEY_HANDLE key_handle = 0;
    // Filter algorithms
    status = BCryptEnumAlgorithms(symmetric_key_operation_filter, &alg_count, &alg_id, 0);
    if (status != STATUS_SUCCESS) {
        std::cerr << "Error: " << std::hex << status << std::endl;
        return 1;
    }

    std::cout << "Symmetric algorithm amount: " << alg_count << std::endl;
    // For each algorithm
    for (ULONG i = 0; i < alg_count; i++) {
        std::wcout << alg_id[i].pszName << std::endl;
        // Pick the default provider
        status = BCryptOpenAlgorithmProvider(&alg_handle, alg_id[i].pszName, 0, 0);
        if (status != STATUS_SUCCESS) {
            std::cerr << "Error: " << std::hex << status << std::endl;
            return 1;
        }

        // Create a key
        //status = BCryptGenerateSymmetricKey(alg_handle, &key_handle, PUCHAR pbKeyObject, ULONG cbKeyObject, PUCHAR pbSecret, ULONG cbSecret, 0)
    }
    BCryptFreeBuffer(alg_id);

    return 0;
}
