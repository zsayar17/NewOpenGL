#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <iostream>
#include <vector>

#include "./Camera/Camera.hpp"
#include "./Material/Material.hpp"
#include "./Primitves/Cube.hpp"
#include "./Primitves/Plane.hpp"
#include "./Utils/Utils.hpp"
#include "./Light/DirectionalLight.hpp"
#include "./Light/PointLight.hpp"
#include "./Light/SpotLight.hpp"
#include "./Model/Model.hpp"
#include "./Primitves/Quad.hpp"

class Game
{
    public:
        Game();
        ~Game();

        void setup();
        void update();
        void draw();

    private:
        std::vector<Cube> cubes;
        std::vector<Quad> quads;

        Plane plane;
        Material b_material;
        Material p_material;
        Material q_material;
        Light** lights;

        Camera camera;

        Model model;

        void createCubes();
        void createLights();
        void createPlane();
        void createModel();
        void createQuad();

        void drawCubes();
        void drawLights();
        void drawModel();
        void drawPlane();
        void drawQuad();
};

#endif
