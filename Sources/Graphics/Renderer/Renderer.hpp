#ifndef MAMMOTH_2D_RENDERER_HPP
#define MAMMOTH_2D_RENDERER_HPP

#include "Device.hpp"
#include "SwapChain.hpp"
#include "Game.hpp"
#include <glm/glm.hpp>

#include <iostream>

namespace mt 
{
class Renderer 
{
public:
    Renderer(Device& device, Window& window);
    ~Renderer();

    void BeginRenderPass(VkCommandBuffer commandBuffer, std::unique_ptr<SwapChain>& swapChain, bool started, uint32_t currentImageIndex);
    void Render(VkCommandBuffer commandBuffer);
    void EndRenderPass(VkCommandBuffer commandBuffer);

    void DrawTempObj(TempRenderObj& obj);

    /**
     * @brief function to tell the renderer to draw a simple quadrilateral.
     * @param size a 2d vector containing the width and height values of the desired quad.
     * @param position a 2d vector containing the x and y coordinates of the top-left corner of the desired quad.
     * @param color a 3d vector containing the RGB color values of the desired quad.
    */
    void DrawQuad(glm::vec2 size, glm::vec2 position, glm::vec3 color);


private:
    Device& mDevice;
    Window& mWindow;
};
}


#endif