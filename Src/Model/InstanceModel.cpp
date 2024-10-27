#include "InstanceModel.hpp"

Shader* InstanceModel::instanceModelShaderProgram = NULL;

InstanceModel::InstanceModel()
{
    if (instanceModelShaderProgram == NULL)
    {
        instanceModelShaderProgram = new Shader("InstanceVertexShader", "InstanceFragmentShader");
        bindShader(instanceModelShaderProgram);
        bindShaderToUBO(Constants::CameraMatricies);
    }

    bindShader(instanceModelShaderProgram);

    instanceCount = 0;
    models = NULL;
}

InstanceModel::~InstanceModel()
{
    if(models != NULL)
    {
        for(int i = 0; i < instanceCount; i++) delete models[i];

        delete[] models;
    }
}

void InstanceModel::createInstanceModel(const char* path, int count)
{
    loadModel(path);

    instanceCount = count;
    models = new BaseObject*[instanceCount];
    for(int i = 0; i < instanceCount; i++) models[i] = new BaseObject();
}


// Set the model matrices
void InstanceModel::setInstanceModelToVBO()
{
    glm::mat4* modelMatrices = new glm::mat4[instanceCount];
    for (int i = 0; i < instanceCount; i++)
        modelMatrices[i] = models[i]->getModelMatrix();

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, instanceCount * sizeof(glm::mat4), &modelMatrices[0] , GL_STATIC_DRAW);

    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i].getObject().use();

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);

        glBindVertexArray(0);
    }
}

void InstanceModel::draw()
{
    shaderProgram->use();
    shaderProgram->setInt("diffuseMap", 0);

    for (unsigned int j = 0; j < meshes.size(); j++) meshes[j].drawInstanced(instanceCount);
}

void InstanceModel::drawWithoutInstance()
{
    glm::mat4 model;

    shaderProgram->use();
    shaderProgram->setInt("diffuseMap", 0);

    for (int i = 0; i < instanceCount; i++)
    {
        model = models[i]->getModelMatrix();

        shaderProgram->setMat4("model", model);
        for (unsigned int j = 0; j < meshes.size(); j++) meshes[j].draw();
    }
}

BaseObject* InstanceModel::operator[](int index)
{
    if (index < 0 || index >= instanceCount) return NULL;
    return models[index];
}

int InstanceModel::getInstanceCount()
{
    return instanceCount;
}
