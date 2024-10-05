#include "CubeMap.hpp"

#include "../../Essantials/Stb_Image/stb_image.h"

Object *CubeMap::mainObject = NULL;
Shader *CubeMap::mainShaderProgram = NULL;

CubeMap::CubeMap()
{
    if (!mainObject)
    {
        mainObject = new Object();
        createCubeMap();
    }

    if (!mainShaderProgram)
    {
        mainShaderProgram = new Shader("CubeMapVertex", "CubeMapFragment");
    }


    object = mainObject;
    bindShader(mainShaderProgram);

    shaderProgram->use();
    shaderProgram->setInt("skybox", 0);
}

CubeMap::~CubeMap()
{

}

void CubeMap::draw()
{
    glm::mat4 view;

    shaderProgram->use();
    object->use();

    view = Camera::displayCamera->getViewMatrix(true);

    shaderProgram->setMat4("view", view);

    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    glActiveTexture(GL_TEXTURE0);

    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthFunc(GL_LESS);
}

/*
    the order of faces should be:
    - right
    - left
    - top
    - bottom
    - back
    - front
*/
void CubeMap::loadCubeMap(std::vector<std::string> faces)
{
    int width, height, nrChannels;
    unsigned char* data;
    std::string texture_path;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    stbi_set_flip_vertically_on_load(false);
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        texture_path = TEXTURE_PATH + faces[i];

        data = stbi_load(texture_path.c_str(), &width, &height, &nrChannels, 0);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }
    stbi_set_flip_vertically_on_load(true);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void CubeMap::createCubeMap()
{
    float skyboxVertices[] = {
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
};

    mainObject->bindVBO(sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
    mainObject->bindAttribute(3, 3 * sizeof(float), 0);
}
