#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#include <iostream>
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.hpp"
#include "../BaseObject/BaseObject.hpp"
#include "../Material/Material.hpp"
#include "../Light/Light.hpp"
#include "../Shader/Shader.hpp"

#define MODEL_PATH "./Resources/Models/"

class Model : public BaseObject
{
    public:
        Model();
        ~Model();

        void loadModel(const char* path);

        void enableOutline();
        void disableOutline();
        void draw();

    protected:
        std::vector<Mesh> meshes;

    private:
        static Shader *mainModelShaderProgram;
        static Shader *outlineModelShaderProgram;

        std::string directory;
        bool isOutline;

        void processNode(aiNode* node, const aiScene* scene, std::vector<Material*>& materials);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene, std::vector<Material*>& materials);

        void processVertices(Vertex& vertex, aiVector3D* vertices, int index);
        void processNormals(Vertex& vertex, aiVector3D* normals, int index);
        void processTexCoords(Vertex& vertex, aiVector3D* texCoords, int index);

        void processIndices(std::vector<unsigned int>& indices, aiMesh* mesh);
        void processMaterial(aiMesh* mesh, const aiScene* scene, Material** material, std::vector<Material*>& materials);

        void loadTexture(aiMaterial* mater, Material** material, std::vector<Material*>& materials, TextureType textureType);

        void drawOutline(glm::mat4& model, glm::mat4& view);
};

#endif
