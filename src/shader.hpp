#ifndef G_SHADER_H
#define G_SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdint>


class Shader final
{

    using uint = unsigned int;
public:

    Shader(const std::string& vertex_path, const std::string& fragment_path);
    Shader(const Shader& copy) = default;
    Shader& operator=(const Shader& lhs) = default;
    ~Shader() = default;

    void use();

    // utility uniform function
    void set_bool(const std::string& name, bool value) const;
    void set_int(const std::string& name, int value) const;
    void set_float(const std::string& name, float value) const;

    float get_float(const std::string& name);

private:
    uint m_program_id;


    int get_location(const std::string& name) const;
};






#endif