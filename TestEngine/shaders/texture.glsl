#type vertex

#version 330 core

layout(location = 0) in vec3 _position;
layout(location = 1) in vec2 _textcoord;

uniform mat4 viewProjection;
uniform mat4 transform;

out vec2 textcoord;
			
void main()
{
	textcoord = _textcoord;
	gl_Position = viewProjection * transform * vec4(_position, 1.0);

}

#type pixel
#version 330 core

layout(location = 0) out vec4 color;

in vec2 textcoord;
uniform sampler2D sampler;

void main() {
	//color = vec4(textcoord, 0, 1.0);
	color = texture(sampler, textcoord);
}
