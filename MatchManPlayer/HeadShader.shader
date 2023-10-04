#shader vertex
#version 330 core
uniform mat4 matchManTransform;
uniform mat4 headTransform;
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;


out vec2 TexCoord;

void main()
{
	gl_Position = matchManTransform * headTransform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	TexCoord = aTexCoord;
};

#shader fragment
#version 330 core

out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D ourTexture;

void main()
{
	//FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	FragColor = texture(ourTexture, TexCoord);
};