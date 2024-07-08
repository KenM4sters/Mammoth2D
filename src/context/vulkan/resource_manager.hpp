#ifndef MAMMOTH_2D_RESOURCE_MANAGER_HPP
#define MAMMOTH_2D_RESOURCE_MANAGER_HPP

#include <unordered_map>
#include <string>

namespace mt 
{

/**
 * @brief Holds all the resources that are given by the user (in the derived IGame class 
 * instance) and queried by the engine at some point (mostly by the renderer 
 * during graphics preparation). This class is currently undergoin lots of changes as I decide
 * that different variables should be considered as resources. 
 * At the moment, only shader file paths and image files paths are supported, but I may end
 * up changing this.
*/
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
    std::unordered_map<std::string, std::unique_ptr<std::string>> mImages{};
};
}

#endif