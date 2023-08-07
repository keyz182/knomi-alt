#include "SPIFFS.h"

// Read File from SPIFFS
String readFile(fs::FS &fs, const char *path);

// Write file to SPIFFS
void writeFile(fs::FS &fs, const char *path, const char *message);

void deleteFile(fs::FS &fs, const char *path);