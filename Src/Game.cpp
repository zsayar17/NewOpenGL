#include "Game.hpp"

Game::Game()
{

}

Game::~Game()
{

}

void Game::setup()
{
    camera.setWorldPosition(glm::vec3(0.0f, 0.0f, 5.0f));

    createCubes();
    createPlane();
    createLights();
    createModel();
    createQuad();
}

void Game::update()
{
}

void Game::draw()
{
    drawPlane();
    //drawCubes();
    //drawLights();
    drawModel();
    drawQuad();
}

void Game::createCubes()
{
    /*glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };*/

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  0.0f, -15.0f),
        glm::vec3(-1.5f, -0.0f, -2.5f),
        glm::vec3(-3.8f, -0.0f, -12.3f),
        glm::vec3( 2.4f, -0.0f, -3.5f),
        glm::vec3(-1.7f,  0.0f, -7.5f),
        glm::vec3( 1.3f, -0.0f, -2.5f),
        glm::vec3( 1.5f,  0.0f, -2.5f),
        glm::vec3( 1.5f,  0.0f, -1.5f),
        glm::vec3(-1.3f,  0.0f, -1.5f)
    };

    b_material.loadTexture("marble.jpg", DIFFUSE_MAP);

    for (int i = 0; i < 10; i++)
    {
        Cube cube;
        //float angle = 20.0f * i;

        cube.bindMaterial(&b_material);
        cube.setWorldPosition(cubePositions[i]);
        //cube.rotateWorld(angle, glm::vec3(1.0f, 0.3f, 0.5f));

        cubes.push_back(cube);
    }
}

void Game::drawCubes()
{
    for (unsigned int i = 0; i < cubes.size(); i++)
        cubes[i].draw();
}

void Game::createLights()
{
    glm::vec3 pointLightPositions[] = {
	    glm::vec3( 0.7f,  0.2f,  5.0f),
	    glm::vec3( 2.3f, -3.3f, -4.0f),
	    glm::vec3(-4.0f,  2.0f, -12.0f),
	    glm::vec3( 0.0f,  0.0f, -3.0f)
    };

    lights = new Light*[6];

    DirectionalLight* directionalLight;

    directionalLight = new DirectionalLight();
    directionalLight->setLightColor(glm::vec3(.0f), AMBIENT);
    directionalLight->setLightColor(glm::vec3(.7f), DIFUSE);
    directionalLight->setLightColor(glm::vec3(1.f), SPECULAR);
    lights[0] = directionalLight;

    for (int i = 1; i < 5; i++)
    {
        PointLight* pointL = new PointLight();

        pointL->setWorldPosition(pointLightPositions[i - 1]);
        pointL->setLightLevel((LightDistanceLevel)(i % 3));

        pointL->setLightColor(glm::vec3(.0f), AMBIENT);
        pointL->setLightColor(glm::vec3(1.f), DIFUSE);
        pointL->setLightColor(glm::vec3(1.f), SPECULAR);

        lights[i] = pointL;
    }
}

void Game::drawLights()
{
    for (int i = 1; i < 5; i++)
        lights[i]->draw();
}

void Game::createModel()
{
    //model.loadModel("yeni5-anim/kilavuz-yeni-robot.obj");
    model.loadModel("backpack/backpack.obj");
    //model.loadModel("Mercedes-Benz_SLS_AMG/Mercedes_AMG_GT3New.obj");

    model.setWorldPosition(glm::vec3(0.0f, 5.0f, 0.0f));
    //model.enableOutline();
}

void Game::drawModel()
{
    model.draw();
}

void Game::drawPlane()
{
    plane.draw();
}

void Game::createPlane()
{
    p_material.loadTexture("metal.png", DIFFUSE_MAP);

    plane.bindMaterial(&p_material);

    plane.scale(glm::vec3(5.0f, 1.f, 5.0f));
}

void Game::createQuad()
{
    std::vector<glm::vec3> positions =
    {
        glm::vec3(-1.5f, 0.0f, -0.48f),
        glm::vec3( 1.5f, 0.0f, 0.51f),
        glm::vec3( 0.0f, 0.0f, 0.7f),
        glm::vec3(-0.3f, 0.0f, -2.3f),
        glm::vec3 (0.5f, 0.0f, -0.6f)
    };

    //q_material.loadTexture("grass.png", DIFFUSE_MAP);
    q_material.loadTexture("transparent_window.png", DIFFUSE_MAP);

    for (size_t i = 0; i < positions.size(); i++)
    {
        Quad quad;

        quad.bindMaterial(&q_material);
        quad.setWorldPosition(positions[i]);

        quads.push_back(quad);
    }
}

void Game::drawQuad()
{
    // Sort the quads based on the distance to the camera to draw the farthest quad first for transparency
    std::multimap<float, int> sortedMap;

    for (unsigned int i = 0; i < quads.size(); i++)
    {
        glm::vec3 position = quads[i].getPosition();
        glm::vec3 cameraPos = camera.getPosition();

        float distance = glm::length(cameraPos - position);

        sortedMap.insert(std::make_pair(distance, i));
    }

    for (std::multimap<float, int>::reverse_iterator it = sortedMap.rbegin(); it != sortedMap.rend(); it++)
        quads[it->second].draw();

    // draw the quads without sorting
    //for (unsigned int i = 0; i < quads.size(); i++) quads[i].draw();
}
