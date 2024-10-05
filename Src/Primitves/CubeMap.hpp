#ifndef __CUBEMA_HPP__
#define __CUBEMA_HPP__

#include "../BaseObject/BaseObject.hpp"
#include "../Object/Object.hpp"
#include "../Shader/Shader.hpp"

#include "../Camera/Camera.hpp"

#ifndef TEXTURE_PATH
    #define TEXTURE_PATH "./Resources/Images/"
#endif

class CubeMap : public BaseObject
{
    public:
        CubeMap();
        ~CubeMap();

        void draw();
        void loadCubeMap(std::vector<std::string> faces);

    private:
        static Object *mainObject;
        static Shader *mainShaderProgram;
        Object *object;
        unsigned int textureID;

        void createCubeMap();
};

#endif
