#include "Texture.h"

Texture::Texture(const std::string& fileName) :
	fileName(fileName)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int w, h, c;
	unsigned char* data = stbi_load(fileName.c_str(), &w, &h, &c, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		std::cout << "OK: Successfully generated texture: " << fileName << std::endl;
	} else {
		std::cout << "ERROR: Error loading texture data: " << fileName << std::endl;
	}
	
	stbi_image_free(data);
}

Texture::~Texture() {
	glDeleteTextures(1, &textureID);
	std::cout << "OK: Texture deleted!" << std::endl;
}

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, textureID);
}
