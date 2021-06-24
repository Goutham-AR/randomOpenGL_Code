#ifndef G_INPUT_HANDLER_H
#define G_INPUT_HANDLER_H

#include <GLFW/glfw3.h>
#include "shader.hpp"

class Command
{
public:
    virtual ~Command() {}
    virtual void execute() = 0;

};

class SmileyTexChangeInc : public Command
{
public:
    SmileyTexChangeInc() = delete;
    SmileyTexChangeInc(const Shader& program);
    void execute() override;

private:
    Shader m_program;

    float m_rate{ 0.001f };
};

SmileyTexChangeInc::SmileyTexChangeInc(const Shader& program)
    : m_program{ program }
{
}

void SmileyTexChangeInc::execute()
{
    m_program.use();
    auto current_amount = m_program.get_float("i");
    if (current_amount < 1.0f)
    {

        m_program.set_float("i", current_amount + m_rate);
    }
    else
    {
        m_program.set_float("i", 1.0f);
    }

}

class SmileyTexChangeDec : public Command
{
public:
    SmileyTexChangeDec() = delete;
    SmileyTexChangeDec(const Shader& program);
    void execute() override;

private:
    Shader m_program;
    float m_rate{ 0.001f };
};

SmileyTexChangeDec::SmileyTexChangeDec(const Shader& program)
    : m_program{ program }
{
}

void SmileyTexChangeDec::execute()
{
    m_program.use();
    auto current_amount = m_program.get_float("i");
    if (current_amount > 0.0f)
    {
        m_program.set_float("i", current_amount - m_rate);
    }
    else
    {
        m_program.set_float("i", 0.0f);
    }
}

class ExitCommand : public Command
{
public:
    ExitCommand(GLFWwindow* window);
    void execute() override;

private:
    GLFWwindow* m_window{ nullptr };

};

ExitCommand::ExitCommand(GLFWwindow* window)
    : m_window{ window }
{
}
void ExitCommand::execute()
{
    glfwSetWindowShouldClose(m_window, true);
}



class InputHandler
{
public:
    InputHandler(GLFWwindow* window);

    void handle_input();

    void bind_btnup(Command* cmnd)
    {
        m_button_up = cmnd;
    }
    void bind_btndown(Command* cmnd)
    {
        m_button_down = cmnd;
    }

    void bind_escape(Command* cmnd)
    {
        m_escape_btn = cmnd;
    }
private:
    GLFWwindow* m_window{ nullptr };

    Command* m_button_up{ nullptr };
    Command* m_button_down{ nullptr };
    Command* m_escape_btn{ nullptr };
};

InputHandler::InputHandler(GLFWwindow* window)
    : m_window{ window }
{

}

void InputHandler::handle_input()
{
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        m_escape_btn->execute();
    else if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
        m_button_up->execute();
    else if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
        m_button_down->execute();
}






#endif