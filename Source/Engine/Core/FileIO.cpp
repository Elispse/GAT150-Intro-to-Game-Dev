#include "FileIO.h"
#include "Logger.h"
#include <fstream>
#include <iostream>

namespace Jackster {

    std::string getFilePath() 
    {
        return std::filesystem::current_path().string();
    }

    std::string getFileName(const std::filesystem::path& path)
    {
        return path.filename().string();
    }

    bool setFilePath(const std::filesystem::path& path)
    {
        std::error_code ec;
        std::filesystem::current_path(path, ec);
        return ec.value() == 0;
    }

    bool fileExists(const std::filesystem::path& path)
    {
        return std::filesystem::exists(path);
    }

    bool getFileSize(const std::filesystem::path& path, size_t& fSize)
    {
        std::error_code ec;
        fSize = std::filesystem::file_size(path, ec);
        return ec.value() == 0;
    }

    bool readFile(const std::filesystem::path& path, std::string& buffer)
    {
        if (!fileExists(path))
        {
            WARNING_LOG("File not Loaded: ")

            return false;
        }

        size_t size;
        if (!getFileSize(path, size)) return false;

        buffer.resize(size);

        std::ifstream stream(path);
        stream.read(buffer.data(), size);
        stream.close();

        return true;
    }
}