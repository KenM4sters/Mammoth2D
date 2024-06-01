#include <unordered_map>
#include "Graphics/Pipelines/Shader.hpp"
#include "Graphics/Images/Image.hpp"

namespace Super 
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
    void LoadShader(std::string& key, std::string& imagePath);

    /**
     * Creates and stores a Shader object from paths to a Vertex and Fragment shader
     * @param key The key that the Image object will be stored as. 
     * @param vertexPath Relative or Absolute path to the Vertex shader.
     * @param fragmentPath Relative or Absolute path to the Fragment shader.
    */
    void LoadImage(std::string& key, std::string& vertexPath, std::string& fragmentPath);

    /**
     * Attempts to find the key and delete its corresponding shader object.
     * @param key key associated with the object that you wish to delete (what you loaded the asset under).
     * @return Whether the key was succesfully found or not.
    */
    bool UnloadShader(std::string& key);

    /**
     * Attempts to find the key and delete its corresponding shader object.
     * @param key key associated with the object that you wish to delete (what you loaded the asset under).
     * @return Whether the key was succesfully found or not.
    */
    bool UnloadImage(std::string& key);

private:
    std::unordered_map<std::string, std::unique_ptr<Shader>> mShaders{};
    std::unordered_map<std::string, std::unique_ptr<Image>> mShaders{};
};
}