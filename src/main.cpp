#include <iostream>



#include <glad/glad.h>
#include <GLFW/glfw3.h>





void framebuffer_resize_callback(GLFWwindow* window, int new_width, int new_height);
void process_input(GLFWwindow* window);

int main()
{
    /* ------------------------------ */
    /* GLFW and GLAD Init Part */
    /* --------------------------- */

    /* initializing GLFW */
    if (glfwInit() == GLFW_TRUE)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if defined(__APPLE__)
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    }

    /* creating the window */
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cerr << "Failed to create a window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    /* initializing GLAD */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 600);     // redundant
    /* Registering callbacks for window resizing */
    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

    /* ------------------------------ */
    /* GLFW and GLAD Init Part */
    /* --------------------------- */

    const char* vertex_shader_source =
        "#version 460 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "out vec3 color;\n"
        "uniform float b;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "   color = vec3(gl_Position.xy, b);"
        "}\0";

    const char* fragment_shader_source =
        "#version 460 core\n"
        "in vec3 color;\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(color, 1.0f);\n"
        "}\0";

    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertex_shader);
    int  success;
    char infoLog[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, nullptr, infoLog);
        std::cerr << "ERROR:SHADER:VERTEX:COMPILATION_FAILED\n" << infoLog << std::endl;
        std::exit(1);
    }

    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, nullptr, infoLog);
        std::cerr << "ERROR:SHADER:FRAGMENT:COMPILATION_FAILED\n" << infoLog << std::endl;
        std::exit(1);
    }

    unsigned int shader_program;
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader_program, 512, nullptr, infoLog);
        std::cout << "ERROR:PROGRAM:LINKING_FAILED\n" << infoLog << std::endl;
    }

    glUseProgram(shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,

    };
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
    glEnableVertexAttribArray(0);

    unsigned int VAO2;
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);
    float vertices2[] = {
        0.5f, 0.0f, 0.0f,
        0.9f, 0.9f, 0.0f,
        -0.9f, -0.9f, 0.0f
    };
    unsigned int VBO2;
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
    glEnableVertexAttribArray(0);


    glUseProgram(shader_program);


    int no_of_attr{};
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &no_of_attr);
    std::cout << no_of_attr << std::endl;


    auto b_location = glGetUniformLocation(shader_program, "b");
    glUniform1f(b_location, 0.2f);


    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    int i = 0;

    /* render loop */
    while (!glfwWindowShouldClose(window))
    {
        process_input(window);

        /* rendering commands */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        i % 11 == 0 ? glBindVertexArray(VAO2) : glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
        ++i;
    }

    glfwTerminate();
}

void framebuffer_resize_callback(GLFWwindow* window, int new_width, int new_height)
{
    glViewport(0, 0, new_width, new_height);
}

void process_input(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}