#include <windows.h>
#include <bcrypt.h>
#include <iostream>
#include <ntstatus.h>

bool process_status_error(NTSTATUS status) {
  if (status == STATUS_INVALID_PARAMETER) {
    std::cerr << "Invalid parameter" << std::endl;
    return 1;
  } else if (status == STATUS_BUFFER_TOO_SMALL) {
    std::cerr << "Invalid parameter" << std::endl;
    return 1;
  }
  return 0;
}

int main() {
  ULONG buffer_size = 0;
  // PCRYPT - pointer to struct
  PCRYPT_PROVIDERS providers = nullptr;
  NTSTATUS status;

  // get provider data size
  status = BCryptEnumRegisteredProviders(&buffer_size, 0);
  if (process_status_error(status))
    return 1;

  // fill provider data
  status = BCryptEnumRegisteredProviders(&buffer_size, &providers);
  if (process_status_error(status))
    return 1;

  ULONG count = providers->cProviders;
  std::cout << "Provider count: " << count << std::endl;
  for (ULONG i = 0; i < count; i++) {
    std::wcout << providers->rgpszProviders[i] << std::endl;
  }

  BCryptFreeBuffer(providers);

  return 0;
}
