#ifndef G_WINDOW_H
#define G_WINDOW_H
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <cstdint>

struct WindowProps
{
    std::string m_title;
    std::uint32_t m_width;
    std::uint32_t m_height;

    explicit WindowProps(const std::string& title, std::uint32_t width, std::uint32_t height)
        : m_title{ title }, m_width{ width }, m_height{ height }
    {
    }
};

class Window
{
public:
    explicit Window(const WindowProps& wp = WindowProps("title", 500, 500));

    ~Window();

    bool is_closed();
    void swap_buffer();
    GLFWwindow* get_window_ptr() const;

private:
    GLFWwindow* m_window;
    WindowProps m_props;

};





#endif