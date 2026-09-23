#include "terminal.h"
#include "../../kernel/console.h"
void terminal_app_open(void) { console_write("\n[Terminal]\nNeoOS shell ready.\n"); }
