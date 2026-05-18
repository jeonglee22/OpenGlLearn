#include "Game.h"
#include "Shader.h"
#include "Texture.h"
#include "VAO.h"
#include "Model.h"
#include "filesystem.h"

#include "stb_image.h"

void Game::ProcessInput()
{
    auto window = WindowManager::GetInstance().GetWindow();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void Game::Init()
{
    WindowManager::GetInstance().Init();
    ShaderManager::GetInstance().Init();
    SceneManager::GetInstance().Init();
}

void Game::Do()
{
    // float vertices[] = {
    // // positions          // colors           // texture coords
    //  0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
    //  0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    // -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    // -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    // };  

    // float verticesTex[] = {
    //     -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    //     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    //     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    //     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    //     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    //     -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    //     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    //     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    //     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    //     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    //     -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    //     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    //     -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    //     -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    //     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    //     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    //     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    //     -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    //     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    //     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    //     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    //     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    //     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    //     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    //     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    //     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    //     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    //     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    //     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    //     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    //     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    //     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    //     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    //     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    //     -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    //     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    // };

    float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    // positions all containers
    // glm::vec3 cubePositions[] = {
    //     glm::vec3( 0.0f,  0.0f,  0.0f),
    //     glm::vec3( 2.0f,  5.0f, -15.0f),
    //     glm::vec3(-1.5f, -2.2f, -2.5f),
    //     glm::vec3(-3.8f, -2.0f, -12.3f),
    //     glm::vec3( 2.4f, -0.4f, -3.5f),
    //     glm::vec3(-1.7f,  3.0f, -7.5f),
    //     glm::vec3( 1.3f, -2.0f, -2.5f),
    //     glm::vec3( 1.5f,  2.0f, -2.5f),
    //     glm::vec3( 1.5f,  0.2f, -1.5f),
    //     glm::vec3(-1.3f,  1.0f, -1.5f)
    // };
    // // positions of the point lights
    // glm::vec3 pointLightPositions[] = {
    //     glm::vec3( 0.7f,  0.2f,  2.0f),
    //     glm::vec3( 2.3f, -3.3f, -4.0f),
    //     glm::vec3(-4.0f,  2.0f, -12.0f),
    //     glm::vec3( 0.0f,  0.0f, -3.0f)
    // };

    // unsigned int indices[] = {  
    //     0, 1, 3, // first triangle
    //     1, 2, 3  // second triangle
    // };

    // glm::mat4 view;
    // view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), 
    //         glm::vec3(0.0f, 0.0f, 0.0f), 
    //         glm::vec3(0.0f, 1.0f, 0.0f));
    
    // Texture texture1("Assets/Images/container.jpg", TextureDataType::INT);
    // Texture texture2("Assets/Images/awesomeface.png", TextureDataType::INT);
    // Texture texture3("Assets/Images/container2.png", TextureDataType::INT);
    // Texture containerSpecular("Assets/Images/container2_specular.png", TextureDataType::INT);
    // Texture containerColorSpecular("Assets/Images/lighting_maps_specular_color.png", TextureDataType::INT);
    // Texture containerColorSpecular2("Assets/Images/container2_specular_color.png", TextureDataType::INT);
    // Texture containerEmission("Assets/Images/matrix.jpg", TextureDataType::INT);

    // VAO vao;
    // VBO ebo(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices));
    // VBO vbo(GL_ARRAY_BUFFER, verticesTex, sizeof(verticesTex));

    // vao.Bind();
    // vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    // vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    // ebo.Bind();
    // vao.UnBind();

    // VAO cubeVAO;
    VBO cubeVBO(GL_ARRAY_BUFFER, vertices, sizeof(vertices));

    // cubeVAO.Bind();
    // cubeVAO.LinkAttrib(cubeVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    // cubeVAO.LinkAttrib(cubeVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // cubeVAO.LinkAttrib(cubeVBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // cubeVAO.UnBind();

    VAO lightVAO;

    lightVAO.Bind();
    lightVAO.LinkAttrib(cubeVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    lightVAO.UnBind();

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // Shader* ourShader = ShaderManager::GetInstance().Get("Base");
    // ourShader->use();
    // ourShader->setInt("texture1", 0);
    // ourShader->setInt("texture2", 1);

    stbi_set_flip_vertically_on_load(true);

    Shader* cubeShader = ShaderManager::GetInstance().Get("Cube");
    Shader* lightShader = ShaderManager::GetInstance().Get("Light");   
    Shader* modelShader = ShaderManager::GetInstance().Get("Model");
    
    Model ourModel(FileSystem::getPath("Assets/Models/backpack/backpack.obj").c_str());

    glm::vec3 lightPos(1.2f, 1.f, 2.f);

    auto window = WindowManager::GetInstance().GetWindow();

    // camera
    camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    lastX = WindowManager::GetInstance().GetWindowWidth() / 2.0f;
    lastY = WindowManager::GetInstance().GetWindowHeight() / 2.0f;
    firstMouse = true;

    // 렌더 루프
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        ProcessInput();

        SceneManager::GetInstance().Update(deltaTime);


        SceneManager::GetInstance().Render(window);

        // mat4 trans = mat4(1.0f);
        // // trans = rotate(trans, (float)glfwGetTime(), vec3(0.0, 0.0, 1.0));
        // trans = translate(trans, vec3(0.5f, -0.5f, 0.f));
        // trans = rotate(trans, (float)glfwGetTime(), vec3(0.0, 0.0, 1.0));

        // glm::mat4 model = glm::mat4(1.0f);
        // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));  

        // glm::mat4 view = glm::mat4(1.0f);
        // // note that we're translating the scene in the reverse direction of where we want to move
        // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        // const float radius = 10.0f;
        // float camX = sin(glfwGetTime()) * radius;
        // float camZ = cos(glfwGetTime()) * radius;
        // glm::mat4 view;
        // view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));  

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);

        // int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        // int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        // ourShader->setMat4("projection", projection);

        // float timeValue = glfwGetTime();
        // float greenValue = sin(timeValue) / 2.0f + 0.5f;
        // int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // glActiveTexture(GL_TEXTURE0);
        // texture1.Bind();
        // glActiveTexture(GL_TEXTURE1);
        // texture2.Bind();

        // float magnitude = glm::vec2(lightPos.x, lightPos.y).length();
        // float xPos = magnitude * cos(currentAngle + currentFrame);
        // float yPos = magnitude * sin(currentAngle + currentFrame);
        // lightPos = glm::vec3(xPos, yPos, lightPos.z);

        glm::mat4 view = camera.GetViewMatrix();
        // ourShader->setMat4("view", view);

        // glm::vec3 lightColor;
        // lightColor.x = sin(glfwGetTime() * 2.0f);
        // lightColor.y = sin(glfwGetTime() * 0.7f);
        // lightColor.z = sin(glfwGetTime() * 1.3f);
        
        // glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); 
        // glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); 
        
        //glm::mat4 model = glm::mat4(1.0f);
        // cubeShader->use();
        // // cubeShader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        // cubeShader->setVec3("viewPos", camera.Position);
        // cubeShader->setVec3("light.direction", -0.2f, -1.0f, -0.3f); 
        // cubeShader->setVec3("light.direction", camera.Front); 
        // cubeShader->setVec3("light.ambient", 0.1f, 0.1f, 0.1f);
        // cubeShader->setVec3("light.diffuse", 0.8f, 0.8f, 0.8f);
        // cubeShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        // // cubeShader->setVec3("light.position", glm::vec3(view * glm::vec4(lightPos.x, lightPos.y, lightPos.z, 1.0f)));
        // cubeShader->setVec3("light.position", camera.Position);
        // cubeShader->setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
        // cubeShader->setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
        // cubeShader->setFloat("light.constant",  1.0f);
        // cubeShader->setFloat("light.linear",    0.09f);
        // cubeShader->setFloat("light.quadratic", 0.032f);
        // directional light
        // cubeShader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        // cubeShader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        // cubeShader->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        // cubeShader->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        // point light 1
        // cubeShader->setVec3("pointLights.position", lightPos);
        // cubeShader->setVec3("pointLights.ambient", 0.05f, 0.05f, 0.05f);
        // cubeShader->setVec3("pointLights.diffuse", 0.8f, 0.8f, 0.8f);
        // cubeShader->setVec3("pointLights.specular", 1.0f, 1.0f, 1.0f);
        // cubeShader->setFloat("pointLights.constant", 1.0f);
        // cubeShader->setFloat("pointLights.linear", 0.09f);
        // cubeShader->setFloat("pointLights.quadratic", 0.032f);
        // // point light 2
        // cubeShader->setVec3("pointLights[1].position", pointLightPositions[1]);
        // cubeShader->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        // cubeShader->setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        // cubeShader->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        // cubeShader->setFloat("pointLights[1].constant", 1.0f);
        // cubeShader->setFloat("pointLights[1].linear", 0.09f);
        // cubeShader->setFloat("pointLights[1].quadratic", 0.032f);
        // // point light 3
        // cubeShader->setVec3("pointLights[2].position", pointLightPositions[2]);
        // cubeShader->setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        // cubeShader->setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        // cubeShader->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        // cubeShader->setFloat("pointLights[2].constant", 1.0f);
        // cubeShader->setFloat("pointLights[2].linear", 0.09f);
        // cubeShader->setFloat("pointLights[2].quadratic", 0.032f);
        // // point light 4
        // cubeShader->setVec3("pointLights[3].position", pointLightPositions[3]);
        // cubeShader->setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        // cubeShader->setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        // cubeShader->setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        // cubeShader->setFloat("pointLights[3].constant", 1.0f);
        // cubeShader->setFloat("pointLights[3].linear", 0.09f);
        // cubeShader->setFloat("pointLights[3].quadratic", 0.032f);
        // // spotLight
        // cubeShader->setVec3("spotLight.position", camera.Position);
        // cubeShader->setVec3("spotLight.direction", camera.Front);
        // cubeShader->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        // cubeShader->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        // cubeShader->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        // cubeShader->setFloat("spotLight.constant", 1.0f);
        // cubeShader->setFloat("spotLight.linear", 0.09f);
        // cubeShader->setFloat("spotLight.quadratic", 0.032f);
        // cubeShader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        // cubeShader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));     

        // cubeShader->setInt("material.diffuse", 0);
        // glActiveTexture(GL_TEXTURE0);
        // texture3.Bind();
        // cubeShader->setInt("material.specular", 1);
        // glActiveTexture(GL_TEXTURE1);
        // containerSpecular.Bind();
        // cubeShader->setInt("material.emission", 2);
        // glActiveTexture(GL_TEXTURE2);
        // containerEmission.Bind();
        // cubeShader->setFloat("material.shininess", 32.0f);
        // // cubeShader->setVec3("lightPos", lightPos);

        // cubeShader->setMat4("projection", projection);
        // cubeShader->setMat4("view", view);

        // cubeVAO.Bind();
        // for(unsigned int i = 0; i < 10; i++)
        // {
        //     glm::mat4 model = glm::mat4(1.0f);
        //     model = glm::translate(model, cubePositions[i]);
        //     float angle = 20.0f * i;
        //     model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        //     cubeShader->setMat4("model", model);

        //     glDrawArrays(GL_TRIANGLES, 0, 36);
        // }

        // cubeShader->setMat4("model", model);

        // render the cube
        //cubeVAO.Bind();
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        // cubeVAO.UnBind();

        // vao.Bind();
        // for(unsigned int i = 0; i < 10; i++)
        // {
        //     glm::mat4 model = glm::mat4(1.0f);
        //     model = glm::translate(model, cubePositions[i]);
        //     float angle = 20.0f * i; 
        //     // if (i % 3 == 0)
        //     //     angle = glfwGetTime() * 30.f;
        //     model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        //     ourShader->setMat4("model", model);

        //     glDrawArrays(GL_TRIANGLES, 0, 36);
        // }

        // glBindVertexArray(VAO1);
        // glDrawArrays(GL_TRIANGLES, 0, 36);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        modelShader->use();
        modelShader->setMat4("projection", projection);
        modelShader->setMat4("view",view);

        cubeShader->setVec3("viewPos", camera.Position);
        modelShader->setVec3("pointLight.position", lightPos);
        modelShader->setVec3("pointLight.ambient", 0.05f, 0.05f, 0.05f);
        modelShader->setVec3("pointLight.diffuse", 0.8f, 0.8f, 0.8f);
        modelShader->setVec3("pointLight.specular", 1.0f, 1.0f, 1.0f);
        modelShader->setFloat("pointLight.constant", 1.0f);
        modelShader->setFloat("pointLight.linear", 0.09f);
        modelShader->setFloat("pointLight.quadratic", 0.032f);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, currentFrame, glm::vec3(0.0f,1.0f,0.0f));
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        modelShader->setMat4("model", model);
        ourModel.Draw(*modelShader);

        lightShader->use();
        glm::mat4 lightModel = glm::mat4(1.f);
        lightModel = glm::translate(lightModel, lightPos);
        lightModel = glm::scale(lightModel, glm::vec3(0.2f));
        
        lightShader->setMat4("model", lightModel);
        lightShader->setMat4("projection", projection);
        lightShader->setMat4("view", view);

        // lightVAO.Bind();
        // for (unsigned int i = 0; i < 4; i++)
        // {
        //     model = glm::mat4(1.0f);
        //     model = glm::translate(model, pointLightPositions[i]);
        //     model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            // lightShader->setMat4("model", model);
        //     glDrawArrays(GL_TRIANGLES, 0, 36);
        // }
        // lightShader->setVec3("LightColor", lightColor);
        lightVAO.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        lightVAO.UnBind();


        // trans = mat4(1.0f);
        // // trans = rotate(trans, (float)glfwGetTime(), vec3(0.0, 0.0, 1.0));
        // trans = translate(trans, vec3(-0.5f, 0.5f, 0.f));
        // vec3 id = vec3(1.0f);
        // trans = scale(trans, (float) sin(glfwGetTime()) * id);

        // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        // glBindVertexArray(VAO1);
        // // glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0);

        // glUseProgram(shaderProgram2);
        // glBindVertexArray(VAO2);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Game::Release()
{
    ShaderManager::GetInstance().Release();
    SceneManager::GetInstance().Release();

    glfwTerminate();
}

void Game::MouseCallback(double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void Game::ScrollCallback(double xOffset, double yOffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yOffset));
}
