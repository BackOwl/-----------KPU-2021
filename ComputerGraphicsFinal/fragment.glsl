#version 330 core

in vec3 FragPos; //--- ��ְ��� ����ϱ� ���� ��ü�� ��ġ���� ���ؽ� ���̴����� �޾ƿ´�.
in vec3 Normal;
out vec4 FragColor;

in vec3 outColor;
in vec3 lightColor;
in vec3 lightPos;
in vec3 viewPos;
in float ambientlight;
in float Shininess;

void main()
{

	float ambientLight = ambientlight; //--- �ֺ� ���� ����
	vec3 ambient = ambientLight * lightColor; //--- �ֺ� ���� ��
	if (Shininess != 0.0) {
		vec3 normalVector = normalize (Normal);
		vec3 lightDir = normalize (lightPos - FragPos); //--- ǥ��� ������ ��ġ�� ������ ������ �����Ѵ�.
		float diffuseLight = max (dot (normalVector, lightDir), 0.0); //--- N�� L�� ���� ������ ���� ����: ���� ����
		vec3 diffuse = diffuseLight * lightColor; //--- ��� �ݻ� ����: ����ݻ簪 * �������
		float shininess;
		shininess = Shininess;
		vec3 viewDir = normalize (viewPos - FragPos); //--- �������� ����
		vec3 reflectDir = reflect (-lightDir, normalVector); //--- �ݻ� ����: reflect �Լ� - �Ի� ������ �ݻ� ���� ���
		float specularLight = max (dot (viewDir, reflectDir), 0.0); //--- V�� R�� ���������� ���� ����: ���� ����
		specularLight = pow(specularLight, shininess); //--- shininess ���� ���־� ���̶���Ʈ�� ������ش�.
		vec3 specular = specularLight * lightColor; //--- �ſ� �ݻ� ����: �ſ�ݻ簪 * �������
		vec3 result;
		result = (ambient + diffuse + specular) * outColor; //--- ���� ���� ������ �ȼ� ����: (�ֺ�+����ݻ�+�ſ�ݻ�����)*��ü ����
		//result = (ambient + specular) * outColor;
		FragColor = vec4 (result, 1.0); // --- �ȼ� ���� ���
	}
	else{
		vec3 result = ambient * outColor;
		FragColor = vec4 (result, 1.0); // --- �ȼ� ���� ���
	}
	
}
