#ifndef MAMMOTH_2D_RESOURCE_MANAGER_HPP
#define MAMMOTH_2D_RESOURCE_MANAGER_HPP

#include <unordered_map>

namespace mt 
{
class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    /**
     * Creates and stores an Image object from a file path
     * @param key The key that the Image object will be stored as. 
     * @param imagePath Relative or Absolute path to the image/texture.
    */
    void LoadImage(std::string key, std::string imagePath);

    /**
     * Creates and stores a Shader object from paths to a Vertex and Fragment shader
     * @param key The key that the Image object will be stored as. 
     * @param vertexPath Relative or Absolute path to the Vertex shader.
     * @param fragmentPath Relative or Absolute path to the Fragment shader.
    */
    void LoadShader(std::string key, std::string vertexPath, std::string fragmentPath);

    /**
     * Attempts to find the key and delete its corresponding shader object.
     * @param key key associated with the object that you wish to delete (what you loaded the asset under).
     * @return Whether the key was succesfully found or not.
    */
    void UnloadShader(std::string key);

    /**
     * Attempts to find the key and delete its corresponding shader object.
     * @param key key associated with the object that you wish to delete (what you loaded the asset under).
     * @return Whether the key was succesfully found or not.
    */
    void UnloadImage(std::string key);

private:
    std::unordered_map<std::string, std::unique_ptr<std::string>> mShaders{};
    std::unordered_map<std::string, std::unique_ptr<std::string>> mShaders{};
};
}

#endif