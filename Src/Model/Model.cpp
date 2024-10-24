#include "Model.hpp"

Shader *Model::mainModelShaderProgram = NULL;
Shader *Model::outlineModelShaderProgram = NULL;

Model::Model()
{
    if (outlineModelShaderProgram == NULL)
    {
        outlineModelShaderProgram = new Shader("VertexShader", "OutlineFragmentShader");
        bindShaderToUBO(Constants::CameraMatricies);
    }
    isOutline = false;

    if (!mainModelShaderProgram) {
        mainModelShaderProgram = new Shader("VertexShader", "FragmentShader");
        mainModelShaderProgram->createGeometryShader("ModelGeometry");
    }

    bindShader(mainModelShaderProgram);
}

Model::~Model()
{

}

void Model::loadModel(const char* path)
{
    std::vector<Material*> materials;
    Assimp::Importer importer;
    // aiProcess_Triangulate: If the model is not made of triangles, it will be converted to triangles.
    // aiProcess_FlipUVs: If the model has the UVs upside down, it will be flipped.
    // aiProcess_GenNormals : If the model does not have normals, they will be generated.
    // aiProcess_SplitLargeMeshes : If the model has large meshes, they will be split into smaller ones.
    // aiProcess_OptimizeMeshes : If the model has redundant vertices, they will be optimized.
    const aiScene* scene = importer.ReadFile(std::string(MODEL_PATH) + path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_OptimizeMeshes); ;

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    directory = std::string(MODEL_PATH) + path;
    directory = directory.substr(0, directory.find_last_of('/'));

    processNode(scene->mRootNode, scene, materials);
}

void Model::draw()
{
    glm::mat4 model;

    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);
    model = getModelMatrix();

    shaderProgram->use();

    shaderProgram->setMat4("model", model);
    shaderProgram->setInt("diffuseMap", 0);
    shaderProgram->setInt("specularMap", 1);
    shaderProgram->setFloat("material.shininess", 32.0f);
    shaderProgram->setFloat("time", glfwGetTime());

    for (unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].draw();

    Light::setLightsToShader(shaderProgram);
}

void Model::drawOutline(glm::mat4& model, glm::mat4& view)
{
    if (!isOutline) return;

    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);
    glDisable(GL_DEPTH_TEST);
    outlineModelShaderProgram->use();
    model = glm::scale(model, glm::vec3(1.1f, 1.f, 1.1f));
    outlineModelShaderProgram->setMat4("model", model);
    outlineModelShaderProgram->setMat4("view", view);

    for (unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].draw();

    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 0, 0xFF);
    glEnable(GL_DEPTH_TEST);
}

void Model::processNode(aiNode* node, const aiScene* scene, std::vector<Material*>& materials)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene, materials));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, materials);
    }

    //4th child 0 mesh
    //meshes.push_back(processMesh(scene->mMeshes[node->mChildren[4]->mMeshes[0]], scene, materials));
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene, std::vector<Material*>& materials)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Material* material = NULL;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;

        memset(&vertex, 0, sizeof(Vertex));

        processVertices(vertex, mesh->mVertices, i);
        processNormals(vertex, mesh->mNormals, i);
        processTexCoords(vertex, mesh->mTextureCoords[0], i);
        vertices.push_back(vertex);
        /*std::cout << "i: " << i;
        std::cout << " vertex: " << glm::to_string(vertex.Position);
        std::cout << " normal: " << glm::to_string(vertex.Normal);
        std::cout << " texCoord: " << glm::to_string(vertex.TexCoords) << std::endl;*/
    }


    processIndices(indices, mesh);
    processMaterial(mesh, scene, &material, materials);

    return Mesh(vertices, indices, material);
}

void Model::processVertices(Vertex& vertex, aiVector3D* vertices, int index)
{
    glm::vec3 vector;

    vector.x = vertices[index].x;
    vector.y = vertices[index].y;
    vector.z = vertices[index].z;

    vertex.Position = vector;
}

void Model::processNormals(Vertex& vertex, aiVector3D* normals, int index)
{
    glm::vec3 normal;

    if (!normals)
    {
        std::cout << "no normals" << std::endl;
        normal = glm::vec3(0.0f, 0.0f, 0.0f);
        vertex.Normal = normal;
        return;
    }

    //std::cout << normals[index].x << " " << normals[index].y << " " << normals[index].z << std::endl;
    normal.x = normals[index].x;
    normal.y = normals[index].y;
    normal.z = normals[index].z;

    vertex.Normal = normal;
}

void Model::processTexCoords(Vertex& vertex, aiVector3D* texCoords, int index)
{
    glm::vec2 texCoord;

    if (texCoords)
    {
        texCoord.x = texCoords[index].x;
        texCoord.y = texCoords[index].y;
    }
    else {
        std::cout << "no texCoords" << std::endl;
        texCoord = glm::vec2(0.0f, 0.0f);
    }

    vertex.TexCoords = texCoord;
}

void Model::processIndices(std::vector<unsigned int>& indices, aiMesh* mesh)
{
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
}

void Model::processMaterial(aiMesh* mesh, const aiScene* scene, Material** material, std::vector<Material*>& materials)
{
    if (mesh->mMaterialIndex < 0)
    {
        *material = NULL;
        return;
    }

    aiMaterial *mater = scene->mMaterials[mesh->mMaterialIndex];

    *material = new Material();
    loadTexture(mater, material, materials, DIFFUSE_MAP);
    loadTexture(mater, material, materials, SPECULAR_MAP);
}

void Model::loadTexture(aiMaterial* mater, Material** material, std::vector<Material*>& materials, TextureType textureType)
{
    aiTextureType type;
    aiString str;
    std::string path;
    TextureStruct* existingTexture;

    if (textureType == DIFFUSE_MAP)
        type = aiTextureType_DIFFUSE;
    else if (textureType == SPECULAR_MAP)
        type = aiTextureType_SPECULAR;

    for (unsigned int i = 0; i < mater->GetTextureCount(type); i++)
    {
        mater->GetTexture(type, i, &str);
        path = directory + "/" + str.C_Str();

        for (unsigned int j = 0; j < materials.size(); j++)
        {
            existingTexture = materials[j]->getLoadedTexture(path.c_str());
            if (existingTexture != NULL)
            {
                (*material)->addTexture(*existingTexture);
                materials.push_back(*material);
                return;
            }
        }
        (*material)->loadTexture(path.c_str(), textureType, false);
    }

    materials.push_back(*material);
}

void Model::enableOutline()
{
    isOutline = true;
}

void Model::disableOutline()
{
    isOutline = false;
}
