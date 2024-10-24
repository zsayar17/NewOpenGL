#include "Quad.hpp"
#include "../Light/Light.hpp"


Object* Quad::mainObject = NULL;
Shader* Quad::mainShaderProgram = NULL;

Quad::Quad()
{
    material = NULL;

    if (!mainObject) {
        mainObject = new Object();
        createQuad();
        bindShaderToUBO(Constants::CameraMatricies);
    }

    if (!mainShaderProgram) {
        mainShaderProgram = new Shader("QuadVertex", "QuadFragment");
    }

    object = mainObject;
    bindShader(mainShaderProgram);
}

Quad::~Quad()
{

}

void Quad::bindObject(Object *object)
{
    this->object = object;
}

void Quad::createQuad()
{
    float vertices[] = {
    // positions         // texture Coords (y ekseninde ters çevrilmiş)
    0.0f,  0.5f,  0.0f,  0.0f,  1.0f,  // Üst sol
    0.0f, -0.5f,  0.0f,  0.0f,  0.0f,  // Alt sol
    1.0f, -0.5f,  0.0f,  1.0f,  0.0f,  // Alt sağ

    0.0f,  0.5f,  0.0f,  0.0f,  1.0f,  // Üst sol
    1.0f, -0.5f,  0.0f,  1.0f,  0.0f,  // Alt sağ
    1.0f,  0.5f,  0.0f,  1.0f,  1.0f   // Üst sağ
    };


    mainObject->bindVBO(sizeof(vertices), vertices, GL_STATIC_DRAW);

    mainObject->bindAttribute(3, 5 * sizeof(float), 0);
    mainObject->bindAttribute(2, 5 * sizeof(float), 3 * sizeof(float));
}

void Quad::bindMaterial(Material *material)
{
    this->material = material;

    shaderProgram->use();
    material->bindToShader(*shaderProgram);
}

void Quad::draw()
{
    int isCullingEnabled = glIsEnabled(GL_CULL_FACE);

    if (isCullingEnabled)
        glDisable(GL_CULL_FACE);
    glm::mat4 model;

    shaderProgram->use();
    object->use();

    if (material != NULL)
        material->activateTextures();

    model = getModelMatrix();

    shaderProgram->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    if (isCullingEnabled)
        glEnable(GL_CULL_FACE);
}
