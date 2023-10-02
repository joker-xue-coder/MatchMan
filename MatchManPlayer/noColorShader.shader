#shader vertex
#version 330 core
uniform mat4 matchManTransform;
layout(location = 0) in vec3 aPos;

void main()
{
	gl_Position = matchManTransform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
};

#shader fragment
#version 330 core

out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
};