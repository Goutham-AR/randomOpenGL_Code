#version 460 core

in vec3 color;
in vec2 tex_coord;

uniform sampler2D our_texture1;
uniform sampler2D our_texture2;
uniform float i;

out vec4 FragColor;

void main()
{   
    vec2 new_tex_coord = vec2(-tex_coord.x, tex_coord.y);
    FragColor = mix(texture(our_texture1, tex_coord), texture(our_texture2, new_tex_coord), i);
}