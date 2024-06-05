#ifndef MAMMOTH_2D_GAME_HPP
#define MAMMOTH_2D_GAME_HPP


namespace mt 
{
class Engine;

class IGame 
{
public:
    IGame(Engine& engine) : m2d{engine}, mRes{engine.GetResourceManager()} 
    {
        Load();
    }

    virtual void Load() = 0;
    
    virtual void Run(std::chrono::duration<double>& ts) = 0;

    virtual void Quit() = 0;

    virtual void PreRender() {};

    virtual void PostRender() {};

protected:
    Engine& m2d;
    ResourceManager& mRes;
};
}

#endif