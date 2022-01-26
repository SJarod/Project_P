#include <iostream>
#include <string>
#include "stb_image.h"

#include "resources/texture.hpp"

bool Resources::Texture::loadTexture(const std::string& filename)
{
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(("assets/" + filename).c_str(), &width, &height, &nrChannels, 0);

	glGenTextures(1, &this->data);

	glBindTexture(GL_TEXTURE_2D, this->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "could not load texture file : " << filename << std::endl;
		return false;
	}

	std::cout << "successfully loaded texture file : " << filename << std::endl;
	stbi_image_free(data);
	return true;
}

void Resources::Texture::bindTexture() const
{
	glBindTexture(GL_TEXTURE_2D, data);
}