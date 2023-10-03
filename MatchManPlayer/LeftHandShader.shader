#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 leftHandTransform0;
uniform mat4 leftHandTransform00;
uniform mat4 matchManTransform;

void main()
{
	if (aPos.x == -0.4)
	{
		gl_Position = leftHandTransform0 * leftHandTransform00 * matchManTransform *vec4(aPos.x, aPos.y, aPos.z, 1.0);
	}
	else
	{
		gl_Position = leftHandTransform0 * matchManTransform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	}
};

#shader fragment
#version 330 core

out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
};