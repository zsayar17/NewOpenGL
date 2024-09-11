#ifndef __MATERIAL_HPP__
#define __MATERIAL_HPP__

#include "../Texture/Texture.hpp"

class Material
{
    public:
        Material();
        ~Material();

        void bindToShader(Shader& shader);
        void loadTexture(const char* path, TextureType textureType, bool usePrefix = true);
        void activateTextures();
        int getTextureSize() const;

        TextureStruct* getLoadedTexture(const char* path);
        void addTexture(TextureStruct texture);

    private:
        Texture texture;
};

#endif
