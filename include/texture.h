#pragma once

#include <GL/glew.h>
#include <memory>
#include <string>

namespace ogl {

namespace impl { class TextureImpl; }

class Texture {
public:
    Texture(const std::string& filename);
    ~Texture();

    void bind(GLenum TextureUnit);
    void unbind(GLenum TextureUnit);

private:
    std::unique_ptr<impl::TextureImpl> mImpl;
};

} // namespace ogl
