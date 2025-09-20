#include <windows.h>
#include <wincrypt.h>
#include <iostream>
#include <fstream>
#include <chrono>

#define ENCRYPT_ALGORITHM CALG_RC2
#define ENCRYPT_BLOCK_SIZE 64


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Please, specify text file as argument" << std::endl;
        return 0;
    }
    LPCSTR file = reinterpret_cast<LPCSTR>(argv[1]);
    // Check input file
    std::fstream input_stream(file, std::ios::binary | std::ios::in);
    if (!input_stream.is_open()) {
        std::cerr << "Error opening file: " << file << std::endl;
        return 1;
    }
    const auto fb = input_stream.tellg();
    input_stream.seekg(0, std::ios::end);
    const auto fe = input_stream.tellg();
    const auto filesize = (fe-fb);
    input_stream.seekg(0);

    // Acquire provider
    HCRYPTPROV provider = 0;
    LPSTR container = nullptr;
    LPSTR provider_type = nullptr;
    DWORD provider_flags = CRYPT_VERIFYCONTEXT;
    if (!CryptAcquireContextA(&provider, container, provider_type, PROV_RSA_FULL, provider_flags)) {
        std::cout << "Couldn't acquire provider context" << std::endl;
        return 1;
    }

    // Gen key
    HCRYPTKEY key = 0;
    if (!CryptGenKey(provider, CALG_RC2, 0, &key)) {
        std::cout << "Couldn't generate key" << std::endl;
        return 1;
    }

    // How many bytes to encrypt at a time
    DWORD block_len = 1000 - 1000 % ENCRYPT_BLOCK_SIZE;
    // RSA_FULL wants one extra block (from docs)
    DWORD buf_len = block_len + ENCRYPT_BLOCK_SIZE;
    char* buffer = nullptr;
    // Allocate buffer
    if (!(buffer = (char*)malloc(buf_len))) {
        std::cout << "Couldn't allocate buffer memory" << std::endl;
        return 1;
    }

    bool final = false;
    DWORD block_count = 0;
    auto start = std::chrono::high_resolution_clock::now();
    do {
        // Read part of a file
        input_stream.read(buffer, ENCRYPT_BLOCK_SIZE);
        DWORD bytes_read = input_stream.gcount();

        // Check if it's final
        if (bytes_read < ENCRYPT_BLOCK_SIZE) {
            final = true;
        }

        // encrypt
        if (!CryptEncrypt(key, 0, final, 0, (byte*)buffer, &bytes_read, ENCRYPT_BLOCK_SIZE)) {
            std::cout << "Couldn't encrypt" << std::endl;
            return 1;
        }

        //std::cout << buffer << std::endl;
        block_count++;
    } while (!final);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    if (duration.count()) {
        std::cout << "File size: " << filesize / 1024 << "KB" << std::endl;
        std::cout << "Encryption speed: " << (filesize / duration.count()) / 1024 << "KB/ms" << std::endl;
        std::cout << "Encryption took: " << duration.count() << "ms" << std::endl;
    } else {
        std::cout << "Encryption was too quick" << std::endl;
    }

    input_stream.close();
    CryptDestroyKey(key);
    CryptReleaseContext(provider, 0);
    return 0;
}
