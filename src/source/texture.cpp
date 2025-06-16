#include "texture.h"

Texture::Texture(const char *filepath) : ID(0), filepath(filepath), localBuffer(nullptr), width(0), height(0), BPP(0)
{
    stbi_set_flip_vertically_on_load(1);
    //Modiefies the width, height and BPP by passing by reference
    //4 for RGBA Red Green Blue Alpha
    localBuffer = stbi_load(filepath, &width, &height, &BPP, 4);

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    // Set Texture Parameters i for integer
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //S is kinda like X for texures and T is kinda like Y for texures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);

    //Unbind
    glBindTexture(GL_TEXTURE_2D, 0);

    if(localBuffer){
        stbi_image_free(localBuffer);
    }

}

Texture::~Texture()
{
    glDeleteTextures(1, &ID);
}

void Texture::Bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 +  slot);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
