#pragma once
#include <filesystem>
#include <string>

namespace Jackster {
    bool setFilePath(const std::filesystem::path& path);
    bool fileExists(const std::filesystem::path& path);
    bool getFileSize(const std::filesystem::path& path, size_t& fSize);
    bool readFile(const std::filesystem::path& path, std::string& buffer);
    std::string getFilePath();
}