#include "FileReader.hpp"

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <sstream>

FileReader::FileReader(ExtensionContainer&& allowedExtenstions)
    : m_AllowedExtencions{ std::move(allowedExtenstions) }
{}

FileReader::ReadData FileReader::Read(const std::string& fileName) 
    const noexcept(false)
{
    CheckExistance(fileName);
    CheckExtencion(fileName);

    std::ifstream file{ fileName, std::ios::in };

    std::stringstream stream{};

    stream << file.rdbuf();

    return stream.str(); 
}

void FileReader::CheckExistance(const std::string& fileName) 
    const noexcept(false)
{
    if (const std::filesystem::path path{ fileName };
        !std::filesystem::exists(path))
    {
        throw std::runtime_error
        {
            "There was an error finding file named " + path.string()
        };
    }
}

void FileReader::CheckExtencion(const std::string& fileName) 
    const noexcept(false)
{
    const std::filesystem::path path{ fileName };
    const std::string extension{ path.extension().string() };

    if(const auto& iter = m_AllowedExtencions.find(extension);
        !m_AllowedExtencions.empty() && iter == m_AllowedExtencions.end())
    {
        throw std::runtime_error
        { 
            "The file's extenstion is not acceptable" 
        };
    }
}

