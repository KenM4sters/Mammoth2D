#pragma once
#include <GLFW/glfw3.h>
#include "PlayerController.hpp"
#include "Events/Bus.hpp"

namespace Super 
{
class PlayerController
{
public:
    static constexpr float playerSpeed = 5.0f;

    PlayerController(EventBus& eventBus, Entity& player) : mPlayer{player} 
    {
        eventBus.Subscribe(this, &PlayerController::MovePlayer);
    }
    ~PlayerController() {}

    void MovePlayer(KeyPressEvent* event) 
    {
        switch(event->mKey) 
        {
            case GLFW_KEY_W: JumpPlayer(); break;
            case GLFW_KEY_A: mPlayer.transform.position += glm::vec2(-playerSpeed, 0.0f); break;
            case GLFW_KEY_D: mPlayer.transform.position += glm::vec2(playerSpeed, 0.0f); break;
        }
    }

    void JumpPlayer() 
    {
        mPlayer.motion.acceleration += glm::vec2(0.0f, 10000.0f);
    }

    Entity& mPlayer;
};
}

