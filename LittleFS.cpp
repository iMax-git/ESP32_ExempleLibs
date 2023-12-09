/**
 * LittleFS example
 * Ajouter dans le fichier platformio.ini :
 *  board_build.filesystem = littlefs
 * lib_deps =
 *      LittleFS
*/

#include <Arduino.h>

#include <LittleFS.h>

void listDir(fs::FS &fs, const char * dirname, uint8_t levels);
void readFile(fs::FS &fs, const char * path);
void writeFile(fs::FS &fs, const char * path, const char * message);
void appendFile(fs::FS &fs, const char * path, const char * message);


void listDir(fs::FS &fs, const char * dirname, uint8_t levels) {
    Serial.printf("Listing directory: %s\r\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("- failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println(" - not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.path(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}


void readFile(fs::FS &fs, const char * path) {
    Serial.printf("Reading file: %s\r\n", path);

    File file = fs.open(path);
    if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return;
    }

    Serial.println("- read from file:");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}

void writeFile(fs::FS &fs, const char * path, const char * message) {
    Serial.printf("Writing file: %s\r\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("- failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("- file written");
    } else {
        Serial.println("- write failed");
    }
    file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message) {
    Serial.printf("Appending to file: %s\r\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("- failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("- message appended");
    } else {
        Serial.println("- append failed");
    }
    file.close();
}



void setup()
{
    Serial.begin(9600);




    if(!LittleFS.begin()) {
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }

    Serial.println("\nListing du système de fichier");
    listDir(LittleFS, "/", 3);

    if (LittleFS.exists("/mesures.csv")) {
        Serial.println("\nLecture du fichier mesures.csv");
        readFile(LittleFS, "/mesures.csv");
    }
    else {
        Serial.println("\nLe fichier mesures.csv n'existe pas encore, il sera créé");
    }

    String new_line = "Line !\n";

    Serial.printf("\n\nécriture des nouvelles mesures dans le fichier (%s)\n", new_line.c_str());
    appendFile(LittleFS, "/mesures.csv", new_line.c_str());

}


void loop()
{
}
