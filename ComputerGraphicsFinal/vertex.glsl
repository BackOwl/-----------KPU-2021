#version 330 core

layout (location = 0) in vec3 vPos; //--- ��ġ ����: attribute position 0
layout (location = 1) in vec3 vNormal;

out vec3 outColor; //--- �÷��� fragment shader�� ���
out vec3 lightColor;
out vec3 lightPos;
out vec3 viewPos;
out float ambientlight;
out float Shininess;

out vec3 FragPos; //--- ��ü�� ��ġ���� �����׸�Ʈ ���̴��� ������.
out vec3 Normal; //--- ��ְ��� �����׸�Ʈ ���̴��� ������.

uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;


uniform vec3 objectColor;
uniform vec3 lightColo;
uniform vec3 lightPo;
uniform vec3 viewPo;
uniform float ambientLigh;
uniform float Shinines;

void main()
{
	gl_Position = projectionTransform * viewTransform * modelTransform * vec4(vPos, 1.0);
	FragPos = vec3(modelTransform * vec4(vPos, 1.0)); //--- vertex data�κ��� ������ �÷� �Է��� ourColor�� ����
	Normal = vec3(transpose(inverse(modelTransform)) * vec4(vNormal, 1.0));

	outColor = objectColor;
	lightColor = lightColo;
	lightPos = lightPo;
	viewPos = viewPo;
	ambientlight = ambientLigh;
	Shininess = Shinines;
} 