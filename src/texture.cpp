#include "texture.h"

#include "nv_dds.h"
#include <GL/glew.h>
#include <iostream>
#include <sstream>

using namespace std;
using namespace ogl;

class impl::TextureImpl {
public:
    TextureImpl(const string& filename, bool flipImage = false, GLenum target = GL_TEXTURE_2D)
        : mTarget(target)
    {
        mImage.load(filename, flipImage);

        glGenTextures(1, &mTextureID);

        glEnable(mTarget);
        bind();

        const auto numMipMaps = mImage.get_num_mipmaps();
        const auto format = mImage.get_format();

        if (mImage.is_compressed())
        {
            glCompressedTexImage2D(
                        mTarget,
                        0,                                          // level
                        format,
                        mImage.get_width(), mImage.get_height(),
                        0,                                          // border
                        mImage.get_size(),                          // image size
                        mImage                                      // data
                        );

            for (int i = 0; i < mImage.get_num_mipmaps(); ++i)
            {
                glCompressedTexImage2D(
                            mTarget,
                            i + 1,
                            format,
                            mImage.get_mipmap(i).get_width(), mImage.get_mipmap(i).get_height(),
                            0,                                      // border
                            mImage.get_mipmap(i).get_size(),
                            mImage.get_mipmap(i)
                            );
            }
        }

        glTexParameteri(target, GL_TEXTURE_BASE_LEVEL, 0 );
        glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, numMipMaps);

    }

    ~TextureImpl()
    {
        glDeleteTextures(1, &mTextureID);
    }

    void bind()
    {
        glBindTexture(mTarget, mTextureID);
    }

    void unbind()
    {
        glBindTexture(mTarget, 0);
    }

private:
    const GLenum mTarget = GL_TEXTURE_2D;

private:
    nv_dds::CDDSImage mImage;
    GLenum mTextureID;
};

Texture::Texture(const std::string& filename)
    : mImpl{make_unique<impl::TextureImpl>(filename)}
{
}

Texture::~Texture()
{
}

void Texture::bind(GLenum textureUnit)
{
    glActiveTexture(textureUnit);
    mImpl->bind();
}

void Texture::unbind(GLenum textureUnit)
{
    glActiveTexture(textureUnit);
    mImpl->unbind();
}
