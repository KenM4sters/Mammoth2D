#ifndef MAMMOTH_2D_GL_RESOUCE_HPP
#define MAMMOTH_2D_GL_RESOUCE_HPP


#include <mammoth/mamoth.hpp>
#include "gl_buffer.hpp"

#include <unordered_map>

namespace mt 
{

class GLResource final : public Resource 
{
public:
    explicit GLResource() noexcept 
        : m_name{"default"},
        m_type{ResourceType::Float}, 
        m_buffer{nullptr}
    {}

    virtual void create(const char* name, ResourceType type, const Memory* memory) override;

    virtual void update(const Memory* memory) override;

    virtual void destroy() override;

    [[nodiscard]] const char* getName() const noexcept { return m_name; }
    [[nodiscard]] constexpr ResourceType getResouceType() const noexcept { return m_type; }
    [[nodiscard]] const std::unique_ptr<GLUniformBuffer>& getBuffer() const noexcept { return m_buffer; }

private:
    const char* m_name;
    ResourceType m_type;
    std::unique_ptr<GLUniformBuffer> m_buffer;
};

}


#endif