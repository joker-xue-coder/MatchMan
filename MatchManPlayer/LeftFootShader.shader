#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 leftFootTransform0;
uniform mat4 leftFootTransform00;
uniform mat4 matchManTransform;

void main()
{
	if (aPos.y == -0.8)
	{
		gl_Position = matchManTransform * leftFootTransform0 * leftFootTransform00 * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	}
	else
	{
		gl_Position = matchManTransform * leftFootTransform0 * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	}
};

#shader fragment
#version 330 core

out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
};