#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <algorithm>
#include <unordered_map>
namespace alta4 {
    namespace fs = std::filesystem;

    std::string searchTerm;

    std::unordered_map<std::string, std::string> importMap;

    void iterateDirTree(fs::directory_iterator&& iterator) {
        for(auto& file : iterator) {
            if(file.is_directory()) {
                iterateDirTree(fs::directory_iterator{file.path()});
                continue;
            }
            if(!file.is_regular_file()) {
                continue;
            }
            std::cout << file.path() << "\n";
            auto fStream = std::ifstream{file.path()};
            std::string line;
            while(std::getline(fStream, line)) {
                if(line.find(searchTerm) != std::string::npos) {
                    std::cout << line << "\n";
                }

            }

        }
    }

    void loadImportMap(char* filePath) {
        importMap = std::unordered_map<std::string, std::string>{};
        auto file = std::ifstream{filePath};
        std::string line;
        while(std::getline(file, line)) {
            int splitPos = line.find('#');
            std::string key = line.substr(0, splitPos);
            std::string import = line.substr(splitPos + 1, std::ssize(line));
            if(importMap.contains(key)) {
                std::cout << key << "\n";
            }
            importMap[key] = import;
        }
    }


}

int main(int argN, char** args) {
    std::cout << "Hello, World!" << std::endl;
    alta4::loadImportMap(args[1]);
    alta4::searchTerm = "EsriLoadModulesProvider";
    alta4::iterateDirTree(std::filesystem::directory_iterator{"test"});

    return 0;
}
