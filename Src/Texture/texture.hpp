#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include "../../Essantials/glad/glad.h"

#include "../Shader/Shader.hpp"

#define TEXTURE_PATH "./Resources/Images/"

enum TextureType
{
    DIFFUSE_MAP,
    SPECULAR_MAP,
    EMISSION_MAP,
};

struct TextureTypeNames
{
    static const char* names[];
};

struct TextureStruct
{
    TextureType textureType;

    unsigned int texture;
    std::string path;
    int useCount;
};

class Texture
{
    private:
        static bool flipVertically;
        static Shader* lastBindedShader;

        std::vector<TextureStruct> textures;

        int findTextureType(TextureType textureType) const;

    public:
        Texture();
        ~Texture();

        void loadTexture(const char* path, TextureType textureType, bool usePrefix = true);
        void activateTextures();
        int getTextureSize() const;

        TextureStruct* getLoadedTexture(const char* path);
        void addTexture(TextureStruct texture);

        void bindToShader(Shader& shader);
};

#endif
