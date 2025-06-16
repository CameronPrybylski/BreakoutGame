#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "../vendor/stb_image/stb_image.h"
#include "glad/glad.h"


class Texture{

private:

    unsigned int ID;
    const char* filepath;
    unsigned char* localBuffer;
    //BPP = Bits Per Pixel
    int width, height, BPP;

public:

    Texture(const char* filepath);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    int getWidth() const {return width;}
    int getHeight() const {return height;}


};


#endif