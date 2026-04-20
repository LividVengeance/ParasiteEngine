#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Colour;
layout(location = 2) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;

out vec4 v_Colour;
out vec2 v_TexCoord;

void main()
{
	v_TexCoord = a_TexCoord;
	v_Colour = a_Colour;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}


#type pixel
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Colour;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform float u_TilingFactor;
uniform vec4 u_Colour;

void main()
{
	//color = texture(u_Texture, v_TexCoord * u_TilingFactor) * u_Colour;
	color = v_Colour;
}