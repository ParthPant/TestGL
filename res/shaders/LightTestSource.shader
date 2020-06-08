#shader vertex
#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 Normal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
	
	gl_Position = u_projection * u_view * u_model * position;
	
};

#shader fragment
#version 330 core

out vec4 color;

void main()
{
	//vec4 TexColor = texture(u_Texture, v_texCord);
	color = vec4(1.0f);
};