#pragma once
#include <glad/gl.h>
#include "stb_image.h"

class Texture
{
private:
    GLuint textureID;
    int width, height, bitDepth;
    char *fileLocation;
    
public:
    Texture();
    Texture(char* fileLoc);
    void LoadTexture();
    void UseTexture();
    void ClearTexture();
    ~Texture();
};

Texture::Texture()
{
    textureID = 0;
    width = 0;
    height = 0;
    fileLocation = NULL;
}

Texture::Texture(char* fileLoc)
{
    textureID = 0;
    width = 0;
    height = 0;
    fileLocation = fileLoc;
}

void Texture::LoadTexture() 
{
    unsigned char *texData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);
    if (!texData) 
    {
        printf("Failed to find: %s\n", fileLocation);
        return;
    }
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(texData);
}

void Texture::UseTexture() 
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::ClearTexture() 
{
    glDeleteTextures(1, & textureID);
    textureID = 0;
    width = 0;
    height = 0;
    bitDepth = 0;
    fileLocation = NULL;
}

Texture::~Texture()
{
    ClearTexture();
}
