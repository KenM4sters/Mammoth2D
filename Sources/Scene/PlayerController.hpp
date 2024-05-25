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
            case GLFW_KEY_A: MovePlayerLeft(); break;
            case GLFW_KEY_D: MovePlayerRight(); break;
        }
    }

    void JumpPlayer() 
    {
        mPlayer.body.force += glm::vec2(0.0f, 20.0f);
    }

    void MovePlayerLeft() 
    {
        mPlayer.body.force -= glm::vec2(10.0f, 0.0f);
    }
    
    void MovePlayerRight()
    {
        mPlayer.body.force += glm::vec2(10.0f, 0.0f);
    }


    Entity& mPlayer;
};
}

