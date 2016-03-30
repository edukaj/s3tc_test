#include "texture.h"
#include <gli/gli.hpp>
#include <iostream>
#include <sstream>

using namespace std;

Texture::Texture(const std::string& filename)
{
#if 0
	// Original example: can load every dxt format and ktx
	gli::texture Texture = gli::load(filename);
	if(Texture.empty())
	{
		ostringstream os;
		os << "unable to load image " << filename;
		throw runtime_error{os.str()};
	}

	gli::gl GL(gli::gl::PROFILE_GL33);
	gli::gl::format const Format = GL.translate(Texture.format(), Texture.swizzles());
	GLenum Target = GL.translate(Texture.target());

	glGenTextures(1, &mTexture);
	glBindTexture(Target, mTexture);
	glTexParameteri(Target, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(Target, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(Texture.levels() - 1));
	glTexParameteri(Target, GL_TEXTURE_SWIZZLE_R, Format.Swizzles[0]);
	glTexParameteri(Target, GL_TEXTURE_SWIZZLE_G, Format.Swizzles[1]);
	glTexParameteri(Target, GL_TEXTURE_SWIZZLE_B, Format.Swizzles[2]);
	glTexParameteri(Target, GL_TEXTURE_SWIZZLE_A, Format.Swizzles[3]);

	glm::tvec3<GLsizei> const Extent(Texture.extent());
	GLsizei const FaceTotal = static_cast<GLsizei>(Texture.layers() * Texture.faces());

	switch(Texture.target())
	{
	case gli::TARGET_1D:
		glTexStorage1D(
					Target, static_cast<GLint>(Texture.levels()), Format.Internal, Extent.x);
		break;
	case gli::TARGET_1D_ARRAY:
	case gli::TARGET_2D:
	case gli::TARGET_CUBE:
		glTexStorage2D(
					Target, static_cast<GLint>(Texture.levels()), Format.Internal,
					Extent.x, Texture.target() == gli::TARGET_2D ? Extent.y : FaceTotal);
		break;
	case gli::TARGET_2D_ARRAY:
	case gli::TARGET_3D:
	case gli::TARGET_CUBE_ARRAY:
		glTexStorage3D(
					Target, static_cast<GLint>(Texture.levels()), Format.Internal,
					Extent.x, Extent.y,
					Texture.target() == gli::TARGET_3D ? Extent.z : FaceTotal);
		break;
	default:
		assert(0);
		break;
	}

	for(std::size_t Layer = 0; Layer < Texture.layers(); ++Layer)
		for(std::size_t Face = 0; Face < Texture.faces(); ++Face)
			for(std::size_t Level = 0; Level < Texture.levels(); ++Level)
			{
				GLsizei const LayerGL = static_cast<GLsizei>(Layer);
				glm::tvec3<GLsizei> Extent(Texture.extent(Level));
				Target = gli::is_target_cube(Texture.target())
						? static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + Face)
						: Target;

				switch(Texture.target())
				{
				case gli::TARGET_1D:
					if(gli::is_compressed(Texture.format()))
						glCompressedTexSubImage1D(
									Target, static_cast<GLint>(Level), 0, Extent.x,
									Format.Internal, static_cast<GLsizei>(Texture.size(Level)),
									Texture.data(Layer, Face, Level));
					else
						glTexSubImage1D(
									Target, static_cast<GLint>(Level), 0, Extent.x,
									Format.External, Format.Type,
									Texture.data(Layer, Face, Level));
					break;
				case gli::TARGET_1D_ARRAY:
				case gli::TARGET_2D:
				case gli::TARGET_CUBE:
					if(gli::is_compressed(Texture.format()))
						glCompressedTexSubImage2D(
									Target, static_cast<GLint>(Level),
									0, 0,
									Extent.x,
									Texture.target() == gli::TARGET_1D_ARRAY ? LayerGL : Extent.y,
									Format.Internal, static_cast<GLsizei>(Texture.size(Level)),
									Texture.data(Layer, Face, Level));
					else
						glTexSubImage2D(
									Target, static_cast<GLint>(Level),
									0, 0,
									Extent.x,
									Texture.target() == gli::TARGET_1D_ARRAY ? LayerGL : Extent.y,
									Format.External, Format.Type,
									Texture.data(Layer, Face, Level));
					break;
				case gli::TARGET_2D_ARRAY:
				case gli::TARGET_3D:
				case gli::TARGET_CUBE_ARRAY:
					if(gli::is_compressed(Texture.format()))
						glCompressedTexSubImage3D(
									Target, static_cast<GLint>(Level),
									0, 0, 0,
									Extent.x, Extent.y,
									Texture.target() == gli::TARGET_3D ? Extent.z : LayerGL,
									Format.Internal, static_cast<GLsizei>(Texture.size(Level)),
									Texture.data(Layer, Face, Level));
					else
						glTexSubImage3D(
									Target, static_cast<GLint>(Level),
									0, 0, 0,
									Extent.x, Extent.y,
									Texture.target() == gli::TARGET_3D ? Extent.z : LayerGL,
									Format.External, Format.Type,
									Texture.data(Layer, Face, Level));
					break;
				default: assert(0); break;
				}
			}
#else
	// reduced example to load only dxt3 formats

	// Loading texture
	gli::texture Texture = gli::load(filename);
	if(Texture.empty())
	{
		ostringstream os;
		os << "unable to load image " << filename;
		throw runtime_error{os.str()};
	}

	// initializing gli to use OpenGL 3.3
	gli::gl GL(gli::gl::PROFILE_GL33);
	gli::gl::format const Format = GL.translate(Texture.format(), Texture.swizzles());
	GLenum Target = GL.translate(Texture.target());


	if (Target != GL_TEXTURE_2D)
		throw runtime_error{"Texture target must be GL_TEXTURE_2D!"};

	if (Format.Swizzles[0] != GL_RED ||
			Format.Swizzles[1] != GL_GREEN ||
			Format.Swizzles[2] != GL_BLUE ||
			Format.Swizzles[3] != GL_ALPHA)
		throw runtime_error{"Invalid swizzles format texture"};

	glGenTextures(1, &mTexture);
	glBindTexture(GL_TEXTURE_2D, mTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(Texture.levels() - 1));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, Format.Swizzles[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, Format.Swizzles[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, Format.Swizzles[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, Format.Swizzles[3]);

	glm::tvec3<GLsizei> const Extent(Texture.extent());

	switch (Format.Internal) {
	case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, Extent.x, Extent.y);
		glCompressedTexSubImage2D(
					GL_TEXTURE_2D,
					0u,
					0, 0,
					Extent.x,
					Extent.y,
					GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,
					static_cast<GLsizei>(Texture.size()),
					Texture.data()
					);
		break;
	case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, Extent.x, Extent.y);
		glCompressedTexSubImage2D(
					GL_TEXTURE_2D,
					0u,
					0, 0,
					Extent.x,
					Extent.y,
					GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,
					static_cast<GLsizei>(Texture.size()),
					Texture.data()
					);
		break;
	case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, Extent.x, Extent.y);
		glCompressedTexSubImage2D(
					GL_TEXTURE_2D,
					0u,
					0, 0,
					Extent.x,
					Extent.y,
					GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,
					static_cast<GLsizei>(Texture.size()),
					Texture.data()
					);
		break;


	default:
		throw runtime_error{"Unsupported texture format"};
	}


#endif
}

Texture::~Texture()
{
	glDeleteTextures(1, &mTexture);
}

void Texture::enable(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, mTexture);
}
