#pragma once
#include <GLFW/glfw3.h>
#include "PlayerController.hpp"
#include "Events/EventSystem.hpp"

namespace Super 
{
class PlayerController : public EventSystem 
{
public:
    static constexpr float playerSpeed = 5.0f;

    PlayerController(Entity& player) : mPlayer{player} 
    {
        mEventBus->Subscribe(this, &PlayerController::MovePlayer);
    }
    ~PlayerController() {}

    void MovePlayer(KeyPressEvent* event) 
    {
        switch(event->mKey) 
        {
            case GLFW_KEY_W: mPlayer.transform.position += glm::vec2(0.0f, -playerSpeed); break;
            case GLFW_KEY_A: mPlayer.transform.position += glm::vec2(-playerSpeed, 0.0f); break;
            case GLFW_KEY_S: mPlayer.transform.position += glm::vec2(0.0f, playerSpeed); break;
            case GLFW_KEY_D: mPlayer.transform.position += glm::vec2(playerSpeed, 0.0f); break;
        }
    }

    Entity& mPlayer;
};
}

