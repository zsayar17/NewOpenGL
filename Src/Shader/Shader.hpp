#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include "../../Essantials/glad/glad.h"

#include <unistd.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


#define shaderPath "./Shaders/"

class Shader
{
    public:
        static unsigned int usingShader;
        unsigned int ID;
        std::map<std::string, int> uniformLocations;

        Shader(const char* vertexPath, const char *fragmentPath);
        ~Shader();

        void use();
        void setBool(const std::string &name, bool value);
        void setInt(const std::string &name , int value);
        void setFloat(const std::string &name, float value);
        void setMat4(const std::string &name, glm::mat4 &value);
        void setVec3(const std::string &name, glm::vec3 &value);
    private:
        Shader();

        std::string loadShader(const char *filename);
        int createShader(const char *code, int type);
        int createProgram(int vertexShader, int fragmentShader);
};

#endif
