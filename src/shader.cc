#include "shader.hpp"

Shader::Shader(const std::string& vertex_path, const std::string& fragment_path)
{

    // 1. Read from file
    std::string vertex_code;
    std::string fragment_code;

    std::ifstream v_shader_file;
    std::ifstream f_shader_file;

    v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        v_shader_file.open(vertex_path);
        f_shader_file.open(fragment_path);

        std::stringstream v_stream, f_stream;

        v_stream << v_shader_file.rdbuf();
        f_stream << f_shader_file.rdbuf();

        v_shader_file.close();
        f_shader_file.close();

        vertex_code = v_stream.str();
        fragment_code = f_stream.str();
    }
    catch (const std::ifstream::failure& e)
    {
        std::cerr << "ERROR:SHADER:FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }


    auto v_shader_code = vertex_code.c_str();
    auto f_shader_code = fragment_code.c_str();

    // 2. Compile shaders
    uint vertex, fragment;
    int success_status;
    char info_log[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &v_shader_code, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success_status);
    if (!success_status)
    {
        glGetShaderInfoLog(vertex, 512, nullptr, info_log);
        std::cerr << "ERROR:SHADER:VERTEX:COMPILATION_FAILED\n" << info_log << std::endl;
        std::exit(1);
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &f_shader_code, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success_status);
    if (!success_status)
    {
        glGetShaderInfoLog(fragment, 512, nullptr, info_log);
        std::cerr << "ERROR:SHADER:FRAGMENT:COMPILATION_FAILED\n" << info_log << std::endl;
        std::exit(1);
    }

    // 3. shader program
    m_program_id = glCreateProgram();
    glAttachShader(m_program_id, vertex);
    glAttachShader(m_program_id, fragment);
    glLinkProgram(m_program_id);

    glGetProgramiv(m_program_id, GL_LINK_STATUS, &success_status);
    if (!success_status)
    {
        glGetProgramInfoLog(m_program_id, 512, nullptr, info_log);
        std::cerr << "ERROR:SHADER_PROGRAM:LINKING_FAILED\n" << info_log << std::endl;
        std::exit(1);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

}


void Shader::use()
{
    glUseProgram(m_program_id);
}

void Shader::set_bool(const std::string& name, bool value) const
{
    auto location = get_location(name);
    glUniform1i(location, static_cast<int>(value));
}

void Shader::set_int(const std::string& name, int value) const
{
    auto location = get_location(name);
    glUniform1i(location, static_cast<int>(value));
}

void Shader::set_float(const std::string& name, float value) const
{
    auto location = get_location(name);
    glUniform1f(location, value);
}

float Shader::get_float(const std::string& name)
{
    float value;
    auto loc = get_location(name);
    glGetUniformfv(m_program_id, loc, &value);
    return value;
}


inline int Shader::get_location(const std::string& name) const
{
    return glGetUniformLocation(m_program_id, name.c_str());
}
