#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>
#include <iostream>
#include "src/Shader.h"
#include "src/Camera.hpp"
#include "stb_image/stb_image.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#define SCR_WIDTH 1000
#define SCR_HEIGHT 800
#define MAPSIZE_X 10
#define MAPSIZE_Y 10
#define MAPSIZE_Z 10
#define GLSL_VERSION "#version 330"

// set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // Cube
        /* Top position */  /* Color for each angle */ /* Texture coordinated */ /* Normals*/
        -0.5f, -0.5f, 0.5f,        1.0f, 0.0f, 0.0f,        0.0f, 0.0f,         0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.5f,        0.0f, 1.0f, 0.0f,        1.0f, 0.0f,         0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, 0.5f,        0.0f, 0.0f, 1.0f,        1.0f, 1.0f,         0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, 0.5f,        0.0f, 0.0f, 1.0f,        1.0f, 1.0f,         0.0f, 0.0f, 1.0f, 
        -0.5f,  0.5f, 0.5f,        1.0f, 0.0f, 1.0f,        0.0f, 1.0f,         0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,        1.0f, 0.0f, 0.0f,        0.0f, 0.0f,         0.0f, 0.0f, 1.0f,
       /* Bottom position */  /* Color for each angle */ /* Texture coordinated */ 
        -0.5f, -0.5f, -0.5f,        1.0f, 0.0f, 0.0f,        0.0f, 0.0f,        0.0f, 0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,        0.0f, 1.0f, 0.0f,        1.0f, 0.0f,        0.0f, 0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,        0.0f, 0.0f, 1.0f,        1.0f, 1.0f,        0.0f, 0.0f, -1.0f, 
         0.5f,  0.5f, -0.5f,        0.0f, 0.0f, 1.0f,        1.0f, 1.0f,        0.0f, 0.0f, -1.0f,    
        -0.5f,  0.5f, -0.5f,        1.0f, 0.0f, 1.0f,        0.0f, 1.0f,        0.0f, 0.0f, -1.0f, 
        -0.5f, -0.5f, -0.5f,        1.0f, 0.0f, 0.0f,        0.0f, 0.0f,        0.0f, 0.0f, -1.0f,
        /* Left position */  /* Color for each angle */ /* Texture coordinated */ 
        -0.5f, -0.5f, -0.5f,        1.0f, 0.0f, 0.0f,        0.0f, 0.0f,        -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,        0.0f, 1.0f, 0.0f,        1.0f, 0.0f,        -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,        0.0f, 0.0f, 1.0f,        1.0f, 1.0f,        -1.0f, 0.0f, 0.0f, 
        -0.5f,  0.5f,  0.5f,        0.0f, 0.0f, 1.0f,        1.0f, 1.0f,        -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,        1.0f, 0.0f, 1.0f,        0.0f, 1.0f,        -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,        1.0f, 0.0f, 0.0f,        0.0f, 0.0f,        -1.0f, 0.0f, 0.0f,
        /* Right position */  /* Color for each angle */ /* Texture coordinated */ 
        0.5f, -0.5f, -0.5f,         1.0f, 0.0f, 0.0f,        0.0f, 0.0f,        1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,         0.0f, 1.0f, 0.0f,        1.0f, 0.0f,        1.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,         0.0f, 0.0f, 1.0f,        1.0f, 1.0f,        1.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,         0.0f, 0.0f, 1.0f,        1.0f, 1.0f,        1.0f, 0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,         1.0f, 0.0f, 1.0f,        0.0f, 1.0f,        1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,         1.0f, 0.0f, 0.0f,        0.0f, 0.0f,        1.0f, 0.0f, 0.0f,
        /* Back position */  /* Color for each angle */ /* Texture coordinated */ 
        -0.5f, 0.5f, -0.5f,         1.0f, 0.0f, 0.0f,        0.0f, 0.0f,        0.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,         0.0f, 1.0f, 0.0f,        1.0f, 0.0f,        0.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,         0.0f, 0.0f, 1.0f,        1.0f, 1.0f,        0.0f, 1.0f, 0.0f, 
        0.5f,  0.5f,  0.5f,         0.0f, 0.0f, 1.0f,        1.0f, 1.0f,        0.0f, 1.0f, 0.0f,  
        -0.5f, 0.5f,  0.5f,         1.0f, 0.0f, 1.0f,        0.0f, 1.0f,        0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f,         1.0f, 0.0f, 0.0f,        0.0f, 0.0f,        0.0f, 1.0f, 0.0f,
        /* Front position */  /* Color for each angle */ /* Texture coordinated */ 
        -0.5f, -0.5f, -0.5f,        1.0f, 0.0f, 0.0f,        0.0f, 0.0f,        0.0f, -1.0f, 0.0f,
        0.5f,  -0.5f, -0.5f,        0.0f, 1.0f, 0.0f,        1.0f, 0.0f,        0.0f, -1.0f, 0.0f,
        0.5f,  -0.5f,  0.5f,        0.0f, 0.0f, 1.0f,        1.0f, 1.0f,        0.0f, -1.0f, 0.0f,
        0.5f,  -0.5f,  0.5f,        0.0f, 0.0f, 1.0f,        1.0f, 1.0f,        0.0f, -1.0f, 0.0f, 
        -0.5f, -0.5f,  0.5f,        1.0f, 0.0f, 1.0f,        0.0f, 1.0f,        0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,        1.0f, 0.0f, 0.0f,        0.0f, 0.0f,        0.0f, -1.0f, 0.0f,
    }; 

/* Functions */
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void userInput(GLFWwindow* window);
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos);
void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset);
unsigned int load_texture(const char* texture_path);

/* Matrices */
glm::mat4 model;
glm::mat4 projection;
glm::mat4 view;

/* Light */
glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 1.5f);

/* Frames */
float deltaTime = 0.0f;
float lastFrame = 0.0f;

/* Camera attributes */
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = float(SCR_WIDTH)/2.0f;
float lastY = float(SCR_HEIGHT)/2.0f;
bool isFirstMouse = true;

int main()
{
    /* Initialize GLFW */
    glfwInit();

    /* Initialize Version 3.3 */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

/* Create a window */
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL 3.3", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    /* The most important part */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_cursor_position);
    glfwSetScrollCallback(window, mouse_scroll_position);
    glfwSetInputMode(window, GLFW_CURSOR ,GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    /* Options */
    glEnable(GL_DEPTH_TEST); 

    /* ImGui */
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup the Platform
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(GLSL_VERSION);

	// Style Setup 
	ImGui::StyleColorsDark();

    /* Cube Buffers */
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
   
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    // Position Attribute, at 5th place '6' because in vertices array a row now consist of 6 floats  */ 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0); //start from '0'
    glEnableVertexAttribArray(0);

    // Color Attribute */ 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float))); // last '3' is the offset from prrrevious line
    glEnableVertexAttribArray(1);

    // Texture Attribute                                               offset, will start after position 6*/                                                      
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float))); // last '3' is the offset from prrrevious line
    glEnableVertexAttribArray(2);

    // Normals Attribute 
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

    /* Light Buffers */
    GLuint lightCubeVBO, lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glGenBuffers(1, &lightCubeVBO);
   
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(lightCubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lightCubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    /* Light Position Attribute */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0); //start from '0'
    glEnableVertexAttribArray(0);

     /* Texture */

     /* Shader */
    Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");
    Shader lightCubeShader("res/Shader/lightCube.vert", "res/Shader/lightCube.frag");
    myShader.use(); 


    // Some window
	// bool ShowDemo = false;
	// bool mySecondWindow = false;

    /* Game Loop */
    while (!glfwWindowShouldClose(window))
    {
        /* Update */
        userInput(window);
        // update color 
        float time = glfwGetTime();
        deltaTime = time - lastFrame;
        lastFrame = time;

        float xValue = std::cos(time) / 2.0f + 0.5f; // 0.0f - 1.0f
		float yValue = std::cos(time) / 2.0f + 0.5f; // 0.0f - 1.0f
		float zValue = std::sin(time) / 2.0f + 0.5f; // 0.0f - 1.0f

        float radius = 2.0f;
        float camX = std::sin(time) * radius;
        float camZ = std::cos(time) * radius;


        // GUI Variables
        static float material_ambient[3] = { 1.0f, 0.5f, 0.31f };
		static float material_diffuse[3] = { 1.0f, 0.5f, 0.31f };
		static float material_specular[3] = { 0.5f, 0.5f, 0.5f };
		static float material_shiness = 64.0f;
		static float light_ambient[3] = { 0.2f ,0.2f, 0.2f };
		static float light_diffuse[3] = { 0.5f ,0.5f, 0.5f };
		static float light_specular[3] = { 1.0f ,1.0f, 1.0f };

        /* render */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* Start new frame for Dear ImGui */
		ImGui_ImplOpenGL3_NewFrame(); // !should be before ImGui_ImplGlfw_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

        // 1st Object
        myShader.use();
        //Light
        myShader.setVec3("light.position", lightPos);
        lightPos = glm::vec3(camX, 0.0f, camZ);
		myShader.setVec3("viewPos", camera.Position);
		myShader.setVec3("light.ambient", light_ambient[0], light_ambient[1], light_ambient[2]);
		myShader.setVec3("light.diffuse", light_diffuse[0], light_diffuse[1], light_diffuse[2]);
		myShader.setVec3("light.specular", light_specular[0], light_specular[1], light_specular[2]);

		// Material
		myShader.setVec3("material.ambient", material_ambient[0], material_ambient[1], material_ambient[2]);
		myShader.setVec3("material.diffuse", material_diffuse[0], material_diffuse[1], material_diffuse[2]);
		myShader.setVec3("material.specular", material_specular[0], material_specular[1], material_specular[2]);
		myShader.setFloat("material.shiness", material_shiness);

        /* Coordinates */
        // Projection
        projection = glm::perspective(glm::radians(camera.Zoom), float(SCR_WIDTH) / float(SCR_HEIGHT), 0.1f, 100.0f);
		myShader.setMat4("projection", projection);

        // View
		view = glm::mat4(1.0f);
		view = camera.GetViewMatrix();
		myShader.setMat4("view", view);

		// Model
        model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-25.0f) * time , glm::vec3(0.7f, 1.0f, 0.0f));
		myShader.setMat4("model", model);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // 2nd Object
        lightCubeShader.use();
        lightCubeShader.setMat4("projection", projection);
		lightCubeShader.setMat4("view", view);
		// Model
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.3f));
		lightCubeShader.setMat4("model", model);
		glBindVertexArray(lightCubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
 
        // Render your GUI
        ImGui::Begin("Light test");
		ImGui::SliderFloat3("Material Ambient", material_ambient, 0.0f, 1.0f);
		ImGui::SliderFloat3("Material Diffuse", material_diffuse, 0.0f, 1.0f);
		ImGui::SliderFloat3("Material Specular", material_specular, 0.0f, 1.0f);
		ImGui::SliderFloat("Material Shiness", &material_shiness, 0.0f, 600);
		ImGui::SliderFloat3("Light Ambient", light_ambient, 0.0f, 1.0f);
		ImGui::SliderFloat3("Light Diffuse", light_diffuse, 0.0f, 1.0f);
		ImGui::SliderFloat3("Light Specular", light_specular, 0.0f, 1.0f);
        ImGui::End();

		// Render to screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//Display
		glfwSwapBuffers(window);
		//Pollevents
		glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glfwDestroyWindow(window);

    /* Clear */
    ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
    glfwTerminate();
    return 0;


}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void userInput(GLFWwindow* window) {

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ) // To exit program
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_TRUE) // Forward
		camera.ProcessKeyboard(FORWARD, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_TRUE) // Backward
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_TRUE) // Right
		camera.ProcessKeyboard(RIGHT, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_TRUE) // Left
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_TRUE) // Up
		camera.ProcessKeyboard(UP, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_TRUE) // Down
		camera.ProcessKeyboard(DOWN, deltaTime);
}

void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos) {
    if(isFirstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        isFirstMouse = false;
    }
    // float xoffset = lastX - xpos;
    // float yoffset = ypos - lastY;
    // lastX = xpos;
    // lastY = ypos;
    float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_TRUE)
        camera.ProcessMouseMovement(xoffset, yoffset);
}

void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}

unsigned int load_texture(const char* texture_path) {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    /* Filters Options*/
    // Note : Don't take care so much about this filters if rn, if you would like you can delete. 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int textureWidth, textureHeight, innerChannels;  /* differenciate between jpg, png */
    unsigned char* data = stbi_load(texture_path, &textureWidth, &textureHeight, &innerChannels, 0);

    if(data){
        /* Note it's a better way to see that what our file is like png, jpg or jpeg */
		GLenum format;
		if (innerChannels == 1)
			format = GL_RED;
		if (innerChannels == 3) // jpg file
			format = GL_RGB;
		if (innerChannels == 4) // png file
			format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, textureWidth, textureHeight, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
    } else {
        std::cout << "Failed to load texture\n";
    }

    stbi_image_free(data);

    return texture;

}

