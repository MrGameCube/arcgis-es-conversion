#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <algorithm>
namespace alta4 {
    namespace fs = std::filesystem;

    std::string path;

    std::ofstream outputFile;

    const std::string extension = ".d.ts";

    void handleFile(std::string& filePath) {
        // Ordner Pfad entfernen
        filePath.erase(filePath.begin(),filePath.begin() + std::ssize(path));
        // Dateiendung entfernen
        filePath.erase(filePath.end() - std::ssize(extension), filePath.end());

        //Letzten Abschnitt finden
        int lastSlashIndex = filePath.find_last_of('/');
        //Klassennamen extrahieren
        std::string className = filePath.substr(lastSlashIndex + 1, std::ssize(filePath));

        outputFile << className << "#" << "@arcgis" <<filePath << "\n";
    }

    void iterateDirTree(fs::directory_iterator&& iterator) {
        for(auto& file : iterator) {
            if(file.is_directory()) {
                iterateDirTree(fs::directory_iterator{file.path()});
                continue;
            }
            if(!file.is_regular_file()) {
                continue;
            }
            std::string filePath = file.path();
            if(filePath.ends_with(extension)) {
                handleFile(filePath);
            }

        }
    }


}

/*
 * Die folgenden Imports kommen doppelt vor und sollten aus der Datei je nach Verwendung entfernt werden.
ExpressionInfo
jsonUtils
ColorBackground
ApplicationProperties
InitialViewProperties
clusters
dotDensity
relationship
location
heatmap
predominance
type
size
color
jsonUtils
GamepadSettings
Input
Search

 * */
int main(int argN, char** args) {
    if(argN < 2) {
        return -1;
    }


    alta4::path = args[1];
    alta4::outputFile = std::ofstream{"arcgisExtracted"};
    alta4::iterateDirTree(std::filesystem::directory_iterator{args[1]});
    std::cout << "Jobs done!" << std::endl;
    return 0;
}
