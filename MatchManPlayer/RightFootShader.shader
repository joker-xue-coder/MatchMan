#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 rightFootTransform;
uniform mat4 matchManTransform;
uniform int flag;

void main()
{
	if (flag == 0)
	{
		gl_Position = rightFootTransform * matchManTransform *vec4(aPos.x, aPos.y, aPos.z, 1.0);
	}
	else if (flag == 1) 
	{
		if (aPos.y == -0.8)
		{
			gl_Position = rightFootTransform * matchManTransform *vec4(aPos.x, aPos.y, aPos.z, 1.0);
		}
		else
		{
			gl_Position = matchManTransform *vec4(aPos.x, aPos.y, aPos.z, 1.0);
		}
	}
	else if (flag == 2)
	{
		if (aPos.x < 0.2)
		{
			gl_Position = rightFootTransform * matchManTransform *vec4(aPos.x, aPos.y, aPos.z, 1.0);
		}
		else
		{
			gl_Position = matchManTransform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
		}
	}
};

#shader fragment
#version 330 core

out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
};