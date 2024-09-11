#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../Essantials/Stb_Image/stb_image.h"

const char* TextureTypeNames::names[] = {
    "diffuseMap",
    "specularMap",
    "emissionMap",
};

bool Texture::flipVertically = false;
Shader* Texture::lastBindedShader = NULL;

Texture::Texture()
{
    if (!flipVertically) stbi_set_flip_vertically_on_load((flipVertically = true));
}

Texture::~Texture()
{
    /*for (unsigned int i = 0; i < textures.size(); i++)
        glDeleteTextures(1, &textures[i].second);*/
}

TextureStruct* Texture::getLoadedTexture(const char *path)
{
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        if (textures[i].path == std::string(path))
            return &textures[i];
    }
    return NULL;
}

void Texture::addTexture(TextureStruct texture)
{
    textures.push_back(texture);
}

void Texture::loadTexture(const char *path, TextureType textureType, bool usePrefix)
{
    unsigned char   *texture_data = NULL;
    int             texture_width, texture_height, nrChannels;
    unsigned int    texture;
    int             textureTypeIndex;
    const char*     texture_path;
    std::string     texture_path_str;
    GLenum          textureStyle;

    if (usePrefix)
        texture_path = (texture_path_str = std::string(TEXTURE_PATH) + path).c_str();
    else
        texture_path = path;

    texture_data = stbi_load(texture_path, &texture_width, &texture_height, &nrChannels, 0);
    if (!texture_data)
    {
        std::cout << "Failed to Load Texture" << std::endl;
        return;
    }

    if (nrChannels == 1)
        textureStyle = GL_RED;
    else if (nrChannels == 3)
        textureStyle = GL_RGB;
    else if (nrChannels == 4)
        textureStyle = GL_RGBA;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureStyle == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureStyle == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, textureStyle, texture_width, texture_height, 0, textureStyle, GL_UNSIGNED_BYTE, texture_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    textureTypeIndex = findTextureType(textureType);
    if (textureTypeIndex != -1)
    {
        glDeleteTextures(1, &textures[textureTypeIndex].texture);
        textures[textureTypeIndex].texture = texture;
        textures[textureTypeIndex].path = texture_path;
    }
    else textures.push_back({textureType, texture, texture_path});

    stbi_image_free(texture_data);
}

void Texture::activateTextures()
{
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures[i].texture);
    }
}

int Texture::getTextureSize() const{
    return textures.size();
}

int Texture::findTextureType(TextureType textureType) const
{
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        if (textures[i].textureType == textureType)
            return i;
    }
    return -1;
}

void Texture::bindToShader(Shader &shader)
{
    if (lastBindedShader == &shader) return;

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        shader.setInt(std::string(TextureTypeNames::names[textures[i].textureType]), i);
    }
    shader.setFloat("material.shininess", 64.0f);
    lastBindedShader = &shader;
}
