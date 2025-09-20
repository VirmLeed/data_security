#include <windows.h>
#include <bcrypt.h>
#include <iostream>
#include <ntstatus.h>

int main() {
  ULONG buffer_size = 0;
  // PCRYPT - pointer to struct
  PCRYPT_PROVIDERS providers = nullptr;
  NTSTATUS status;

  // get provider data size
  status = BCryptEnumRegisteredProviders(&buffer_size, 0);
  if (status != STATUS_SUCCESS) {
      std::cerr << "Error: " << std::hex << status << std::endl;
      return 1;
  }

  // fill provider data
  status = BCryptEnumRegisteredProviders(&buffer_size, &providers);
  if (status != STATUS_SUCCESS) {
      std::cerr << "Error: " << std::hex << status << std::endl;
      return 1;
  }

  ULONG count = providers->cProviders;
  std::cout << "Provider count: " << count << std::endl;
  for (ULONG i = 0; i < count; i++) {
    std::wcout << providers->rgpszProviders[i] << std::endl;
  }

  BCryptFreeBuffer(providers);

  return 0;
}
