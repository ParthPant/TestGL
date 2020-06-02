#shader vertex
#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texCord;

out vec4 vertexColor;
out vec2 v_texCord;

uniform mat4 u_MVP;

void main()
{
   gl_Position = u_MVP * position;
   v_texCord = texCord;
};

#shader fragment
#version 330 core

out vec4 color;
in vec2 v_texCord;

uniform sampler2D u_Texture;
uniform vec4 u_Color;

void main()
{
   vec4 TexColor = texture(u_Texture, v_texCord);
   color = TexColor * u_Color;
};