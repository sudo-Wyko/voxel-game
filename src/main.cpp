#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void processInput(GLFWwindow* window) 
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Voxel Game", NULL, NULL);
    if(window == NULL) 
    {
        std::cout << "Failed to create GLFW window";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        std::cout << "Failed to initialize GLAD";
        return -1;
    }

    glViewport(0, 0, 800, 600);

    // ----------------------------------------------------- //
    const char *vertex_shader_source = "#version 330 core\n"
        "layout(location = 0) in vec3 a_pos;\n"
        "void main()\n"
        "{\n"
        "gl_Position = vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);\n"
        "}\0";

    const char *fragment_shader_source = "#version 330 core\n"
        "out vec4 frag_color;\n"
        "void main()\n"
        "{\n"
        "frag_color= vec4(1.f, .5f, .2f, 1.f);\n"
        "}\0";

    int success;
    char info_log[512];

    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILIATION_FAILED\n" << info_log;
    }

    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILIATION_FAILED\n" << info_log;
    }

    unsigned int shader_program;
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shader_program, 512, NULL, info_log);
        std::cout << "ERROR::SHADERPROGRAM::LINKING_FAILED\n" << info_log;
    }

    float vertices[] = 
        {
            -.5f, -.5f, .0f,
            .5f, -.5f, .0f,
            .0f, .5f, .0f,
        };

    unsigned int vertex_buffer_object;
    glGenBuffers(1, &vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

