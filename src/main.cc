#include <iostream>



#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>

#include "window.hpp"
#include "shader.hpp"
#include "input_handler.hpp"




void framebuffer_resize_callback(GLFWwindow* window, int new_width, int new_height);

int main()
{
	WindowProps window_properties{ "Opengl", 800, 600 };

	Window window{ window_properties };




	/* initializing GLAD */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);     // redundant
	/* Registering callbacks for window resizing */
	glfwSetFramebufferSizeCallback(window.get_window_ptr(), framebuffer_resize_callback);



	Shader program{ "res/shaders/vertex.glsl", "res/shaders/fragment.glsl" };

	program.use();
	// program.set_float("h_offset", 0.3f);

	InputHandler ih{ window.get_window_ptr() };

	SmileyTexChangeDec a{ program };
	SmileyTexChangeInc b{ program };
	ExitCommand cmnd{ window.get_window_ptr() };

	ih.bind_btndown(&b);
	ih.bind_btnup(&a);
	ih.bind_escape(&cmnd);

	unsigned int texture[2];
	glGenTextures(2, texture);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int tex_width, tex_height, nr_channels;
	unsigned char* data = stbi_load("res/textures/container.jpg", &tex_width, &tex_height, &nr_channels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
	else
	{
		std::cerr << "Failed to load texture" << std::endl;
	}


	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("res/textures/awesomeface.png", &tex_width, &tex_height, &nr_channels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
	else
	{
		std::cerr << "Failed to load texture" << std::endl;
	}


	float vertices[] = {
		// positions            // colors               // tex coords
		0.5f, 0.5f, 0.0f,      1.0f, 0.0f, 0.0f,       1.0f, 1.0f,       // top right
		0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,       1.0f, 0.0f,       // bottom right
		-0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,       0.0f, 0.0f,      // bottom left
		-0.5f, 0.5f, 0.0f,     1.0f, 1.0f, 0.0f,       0.0f, 1.0f        //top left
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};


	unsigned int VAO, EBO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	program.use();
	program.set_int("our_texture1", 0);
	program.set_int("our_texture2", 1);

	program.set_float("i", 0.2f);

	/* render loop */
	while (!window.is_closed())
	{
		ih.handle_input();

		/* rendering commands */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		program.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		window.swap_buffer();
		glfwPollEvents();
	}

}

void framebuffer_resize_callback(GLFWwindow* window, int new_width, int new_height)
{
	glViewport(0, 0, new_width, new_height);
}

