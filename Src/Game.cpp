#include "Game.hpp"

Game::Game()
{

}

Game::~Game()
{

}

void Game::setup()
{
    frameBuffer = new FrameBuffer(Window::width, Window::height);

    camera.setWorldPosition(glm::vec3(0.0f, 0.0f, 5.0f));

    createCubes();
    createPlane();
    createLights();
    createModel();
    createQuad();
    createSkyBox();
}

void Game::update()
{
    camera.updateCamera();
}

void Game::draw()
{
    frameBuffer->bind();
    drawPlane();
    drawCubes();
    //drawLights();
    drawModel();
    drawQuad();
    drawSkyBox();
    frameBuffer->unbind();

    frameBuffer->draw();
}

void Game::createCubes()
{
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
    createAstroids();
}

void Game::createAstroids()
{
    model[0].loadModel("Planet/planet.obj");
    model[0].setWorldPosition(glm::vec3(0.0f, 25.0f, 0.0f));
    model[0].scale(glm::vec3(4));

    //instanceModel.createInstanceModel("Astroid/rock.obj", 1000);
    instanceModel.createInstanceModel("Astroid/rock.obj", 100000);


    int amount = instanceModel.getInstanceCount();
    srand(glfwGetTime());
    /*float radius = 50.0;
    float offset = 2.5f;*/

    float radius = 150.0;
    float offset = 25.0f;

    for (int i = 0; i < amount; i++)
    {
        float angle = (float)i / (float)amount * 360.0f;
        float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float x = sin(angle) * radius + displacement;
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float y = displacement * 0.4f;
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float z = cos(angle) * radius + displacement;

        glm::vec3 position = glm::vec3(x, y, z) + model[0].getWorldPosition();
        instanceModel[i]->setWorldPosition(position);

        float scale = (rand() % 20) / 100.0f + 0.05;
        instanceModel[i]->scale(glm::vec3(scale));

        float rotAngle = (rand() % 360);
        instanceModel[i]->rotateWorld(rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
    }

    instanceModel.setInstanceModelToVBO();
}

void Game::drawAstroids()
{
    model[0].draw();

    //instanceModel.drawWithoutInstance();
    instanceModel.draw();
}

void Game::drawModel()
{
    drawAstroids();
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


void Game::createSkyBox()
{
    std::vector<std::string> faces = {
        "/skybox/right.jpg",
        "/skybox/left.jpg",
        "/skybox/top.jpg",
        "/skybox/bottom.jpg",
        "/skybox/front.jpg",
        "/skybox/back.jpg",
    };
    cubeMap.loadCubeMap(faces);
}

void Game::drawSkyBox()
{
    cubeMap.draw();
}

