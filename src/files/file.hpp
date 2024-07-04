#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

class File 
{
public:

    /**
     * @brief Reads source file and returns its contents as a vector of characters.
     * Throws an exception if the file failed to open (check file path).
     * @param filePath path to the file to read from.
     * @return vector of characters read from the file.
     */
    [[nodiscard]] static std::vector<char> ParseFile(const char* filePath) 
    {
        std::ifstream file{filePath, std::ios::ate | std::ios::binary};

        assert(file.is_open() && "File could not be opened!"); // check for errors - if thrown, double check file path.

        size_t fileSize = static_cast<size_t>(file.tellg());

        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
    }
};