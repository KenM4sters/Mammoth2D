#include "api.hpp"
#include "mesh.hpp"


namespace mt 
{
class Factory final 
{
public:
    Factory();
    ~Factory();


    template<typename T, typename... Args>
    [[nodiscard]] T* build(const Args&... args) const noexcept 
    {
        new T(args...);
    } 

private:
    
};
}