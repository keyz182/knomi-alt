#include <FSUtils.hpp>

// Read File from SPIFFS
String readFile(fs::FS &fs, const char *path) {
    Serial.printf("Reading file: %s\r\n", path);

    File file = fs.open(path);
    if (file.isDirectory()) {
        Serial.println("- failed to open directory as file");
        return String();
    }
    if (!file) {
        Serial.println("- failed to open file for reading");
        return String();
    }

    String fileContent;
    while (file.available()) {
        fileContent = file.readStringUntil('\n');
        break;
    }
    return fileContent;
}

// Write file to SPIFFS
void writeFile(fs::FS &fs, const char *path, const char *message) {
    Serial.printf("Writing file: %s\r\n", path);

    File file = fs.open(path, FILE_WRITE);
    if (!file) {
        Serial.println("- failed to open file for writing");
        return;
    }
    if (file.print(message)) {
        Serial.println("- file written");
    } else {
        Serial.println("- write failed");
    }
}

// Write file to SPIFFS
void deleteFile(fs::FS &fs, const char *path) {
    Serial.printf("Writing file: %s\r\n", path);

    fs.remove(path);
}