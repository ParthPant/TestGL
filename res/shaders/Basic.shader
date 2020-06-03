#shader vertex
#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texCord;

out vec4 vertexColor;
out vec2 v_texCord;

void main()
{
   gl_Position = position;
   v_texCord = texCord;
};

#shader fragment
#version 330 core

out vec4 color;
in vec2 v_texCord;

uniform sampler2D u_Texture;

void main()
{
   vec4 TexColor = texture(u_Texture, v_texCord);
   color = TexColor;
};