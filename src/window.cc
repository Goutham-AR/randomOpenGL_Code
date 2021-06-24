#include "window.hpp"

Window::Window(const WindowProps& wp)
    : m_window{ nullptr }, m_props{ wp }
{
    // glfw init
    if (glfwInit() == GLFW_TRUE)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if defined(__APPLE__)
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    }


    m_window = glfwCreateWindow(
        m_props.m_width, m_props.m_height,
        m_props.m_title.c_str(), nullptr, nullptr);

    if (m_window == nullptr)
    {
        std::cerr << "Failed to create a window" << std::endl;
        glfwTerminate();
        std::exit(1);
    }
    glfwMakeContextCurrent(m_window);
}


GLFWwindow* Window::get_window_ptr() const
{
    return m_window;
}

bool Window::is_closed()
{
    return static_cast<bool>(glfwWindowShouldClose(m_window));
}

void Window::swap_buffer()
{
    glfwSwapBuffers(m_window);
}


Window::~Window()
{
    glfwTerminate();
}