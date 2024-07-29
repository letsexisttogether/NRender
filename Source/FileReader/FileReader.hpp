#pragma once

#include <set>
#include <string>

class FileReader
{
public:
    using ExtensionContainer = std::set<std::string>;
    using ReadData = std::string;

public:
    FileReader() = default;
    FileReader(const FileReader&) = default;
    FileReader(FileReader&&) = default;

    FileReader(ExtensionContainer&& allowedExtenstions);

    ~FileReader() = default;

    ReadData Read(const std::string& fileName) 
        const noexcept(false); 

    FileReader& operator = (const FileReader&) = delete;
    FileReader& operator = (FileReader&&) = delete;

    void CheckExistance(const std::string& fileName) 
        const noexcept(false);
    void CheckExtencion(const std::string& fileName) 
        const noexcept(false);

private:
    ExtensionContainer m_AllowedExtencions{};
};
