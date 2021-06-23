#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 acolor;
layout (location = 2) in vec2 atex_coord;

out vec3 color;
out vec2 tex_coord;

void main()
{
   gl_Position = vec4(aPos, 1.0);
   color = acolor;
   tex_coord = atex_coord;
}