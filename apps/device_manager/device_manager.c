#include "device_manager.h"
#include "../../kernel/console.h"
void device_manager_open(void) { console_write("\n[Device Manager]\nProcessors | Display adapters | Network adapters | Audio\nUSB controllers | Storage controllers | Bluetooth\n"); }
