#ifndef __INSTANCEMODEL_HPP__
#define __INSTANCEMODEL_HPP__

#include "Model.hpp"

class InstanceModel : public Model
{

    private:
        static Shader* instanceModelShaderProgram;

        BaseObject** models;
        int instanceCount;

    public:
        InstanceModel();
        virtual ~InstanceModel();

        void draw();
        void drawWithoutInstance();

        void createInstanceModel(const char* path, int count);
        void setInstanceModelToVBO();
        BaseObject* operator[](int index);

        int getInstanceCount();
};

#endif
