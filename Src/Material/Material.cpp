#include "material.hpp"

Material::Material()
{

}

Material::~Material()
{

}

void Material::loadTexture(const char* path, TextureType textureType, bool usePrefix)
{
    texture.loadTexture(path, textureType, usePrefix);
}

void Material::activateTextures()
{
    texture.activateTextures();
}

int Material::getTextureSize() const
{
    return texture.getTextureSize();
}

void Material::bindToShader(Shader& shader)
{
    texture.bindToShader(shader);
}

TextureStruct* Material::getLoadedTexture(const char* path)
{
    return texture.getLoadedTexture(path);
}

void Material::addTexture(TextureStruct texture)
{
    this->texture.addTexture(texture);
}
