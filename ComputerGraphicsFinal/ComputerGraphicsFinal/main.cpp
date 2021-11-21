#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")
#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include <random>
#include <malloc.h>
#include <stdio.h>
/////
#pragma comment(lib,"winmm")
#include < mmsystem.h> 
// SND_ASUNC = ����߿��� ���α׷��� ��� ���ư�	
// SND_SYNC = ����� ������ ���α׷��� ���ư�
// SND_FILENAME  = �Ű� ������ �����̸��ϋ� 
// SND_LOOP  = �ݺ����
// SND_PURGE = ������� 
// PlaySound(TEXT(SOUND_FILE_NAME), NULL,SND_ASYNC|SND_ALIAS);
/////

#include "filetobuf.h"
#include "obj.h"
#define weight 600
#define height 600
#pragma warning(disable:4996)

int num_Triangle;
GLuint vao, vbo[2];

bool make_vertexShader();
bool make_fragmentShaders();
GLuint make_shaderProgram();

GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
void Timer(int value);
GLuint shaderID;


GLuint vertexShader, fragmentShader;
GLchar* vertexsource, * fragmentsource;


bool make_fragmentShaders()
{
	fragmentsource = filetobuf((char*)"fragment.glsl"); // �����׼��̴� �о����
	//--- �����׸�Ʈ ���̴� �о� �����ϰ� �������ϱ�
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentsource, 0);
	//--- �����׸�Ʈ ���̴� ������
	glCompileShader(fragmentShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader error\n" << errorLog << std::endl;
		return false;
	}
	return true;
}
bool make_vertexShader()
{
	vertexsource = filetobuf("vertex.glsl");
	//--- ���ؽ� ���̴� ��ü �����
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexsource, 0);
	//--- ���ؽ� ���̴� �������ϱ�
	glCompileShader(vertexShader);
	//--- �������� ����� ���� ���� ���: ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader ������ ����\n" << errorLog << std::endl;
		return false;
	}
	return true;
}
void InitShader()
{
	make_vertexShader(); //--- ���ؽ� ���̴� �����
	make_fragmentShaders(); //--- �����׸�Ʈ ���̴� �����
	//-- shader Program
	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);
	glLinkProgram(shaderID);
	//checkCompileErrors(s_program, "PROGRAM");
	//--- ���̴� �����ϱ�
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//--- Shader Program ����ϱ�
	glUseProgram(shaderID);

}
void InitBuffer()
{
	Obj obj = loadObj("Resource\\gun.obj");

	num_Triangle = obj.num;

	glGenVertexArrays(1, &vao); //--- VAO �� �����ϰ� �Ҵ��ϱ�
	glGenBuffers(2, vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, obj.outvertex.size() * sizeof(glm::vec3), &obj.outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, obj.outnormal.size() * sizeof(glm::vec3), &obj.outnormal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	//glBindVertexArray(VAO[]);
	////--- ��ġ �Ӽ�
	//glBindBuffer(GL_ARRAY_BUFFER, VBO[32]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(�̸�), �̸�, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[]); //����Ű�� ��ȣ �ҷ����� 
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(�̸�), �̸�, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);



	////--- vPos �Ӽ� ������ ���� ����
	//GLint pAttribute = glGetAttribLocation(shaderID, "vPos");
	//glBindBuffer(GL_ARRAY_BUFFER, VBO_position);
	//glVertexAttribPointer(pAttribute, 4, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	//glEnableVertexAttribArray(pAttribute);
	////--- vColor �Ӽ� ������ ���� ����
	//GLint cAttribute = glGetAttribLocation(shaderID, "vColor");
	//glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
	//glVertexAttribPointer(cAttribute, 4, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	//glEnableVertexAttribArray(cAttribute);

}
GLuint make_shaderProgram()
{
	make_vertexShader(); //--- ���ؽ� ���̴� �����
	make_fragmentShaders(); //--- �����׸�Ʈ ���̴� �����
	//-- shader Program
	GLuint s_pro;

	s_pro = glCreateProgram();
	glAttachShader(s_pro, vertexShader);
	glAttachShader(s_pro, fragmentShader);
	glLinkProgram(s_pro);


	GLint result;
	GLchar errorLog[512];

	glGetProgramiv(s_pro, GL_LINK_STATUS, &result); // ---���̴��� �� ����Ǿ����� üũ�ϱ�
	if (!result) {
		glGetProgramInfoLog(s_pro, 512, NULL, errorLog);
		std::cerr << "ERROR: shader program ���� ����\n" << errorLog << std::endl;
		return false;
	}
	//glUseProgram(shaderID); //--- ������� ���̴� ���α׷� ����ϱ�
	//--- ���� ���� ���̴����α׷� ���� �� �ְ�, �� �� �Ѱ��� ���α׷��� ����Ϸ���
	//--- glUseProgram �Լ��� ȣ���Ͽ� ��� �� Ư�� ���α׷��� �����Ѵ�.
	//--- ����ϱ� ������ ȣ���� �� �ִ�.

	glDeleteShader(vertexShader); //--- ���̴� ��ü�� ���̴� ���α׷��� ��ũ��������, ���̴� ��ü ��ü�� ���� ����
	glDeleteShader(fragmentShader);

	glUseProgram(s_pro);
	return s_pro;
}


void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ ����
	glutInitWindowSize(weight, height); // �������� ũ�� ����
	glutCreateWindow("super hot"); // ������ ����(������ �̸� )

	glEnable(GL_DEPTH_TEST);    //--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";


	InitShader();
	InitBuffer();
	shaderID = make_shaderProgram(); //--- ���̴� ���α׷� �����
	//glutTimerFunc(TIMEMIN, Timer, 0);

	glutDisplayFunc(drawScene); // ��� �ݹ��Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �ݹ��Լ� ����
	glutKeyboardFunc(Keyboard);
	glutMainLoop(); // �̺�Ʈ ó�� ����

}

GLvoid drawScene() {
	GLfloat rColor, gColor, bColor;
	rColor = gColor = bColor = 1.0;

	PlaySound(TEXT("test1.wav"), NULL, SND_ASYNC | SND_ALIAS|SND_LOOP);

	glClearColor(rColor, gColor, bColor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::vec3 cameraPos = glm::vec3(5.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- ī�޶� �ٶ󺸴� ����
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);	//glm::cross(cameraDirection, cameraRight);
	glm::mat4 view = glm::mat4(1.0f);

	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	view = glm::rotate(view, (GLfloat)glm::radians(float(30.0)), glm::vec3(1.0f, 0.0f, 0.0f));
	unsigned int viewLocation = glGetUniformLocation(shaderID, "viewTransform"); //--- ���ؽ� ���̴����� viewTransform ������ġ
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	glm::mat4 projection = glm::mat4(1.0f);

	projection = glm::perspective(glm::radians(45.0f), (float)weight / (float)height, 0.1f, 50.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, 0.0)); //--- ������ �ణ �ڷ� �̷���


	unsigned int projectionLocation = glGetUniformLocation(shaderID, "projectionTransform"); //--- ���� ��ȯ �� ����
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	glUseProgram(shaderID);
	unsigned int modelLocation = glGetUniformLocation(shaderID, "modelTransform");
	unsigned int colorLocation = glGetUniformLocation(shaderID, "objectColor");
	int lightPosLocation = glGetUniformLocation(shaderID, "lightPo"); //--- lightPos �� ����: (0.0, 0.0, 5.0);
	int lightColorLocation = glGetUniformLocation(shaderID, "lightColo"); //--- lightColor �� ����: (1.0, 1.0, 1.0) ���
	int ambient = glGetUniformLocation(shaderID, "ambientLigh");
	int shine = glGetUniformLocation(shaderID, "Shinines");
	int viewPos = glGetUniformLocation(shaderID, "viewPo");

	glUniform1f(shine, 128.0);
	glUniform1f(ambient, 1.0);

	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);

	glUniform3f(lightPosLocation, 0.0, 0.0, 0.0);

	glm::vec4 Viewl = glm::vec4(0.0, 0.0, 5.0, 0.0);

	Viewl = Viewl * glm::rotate(glm::mat4(1.0f), (GLfloat)glm::radians(float(30.0)), glm::vec3(1.0f, 0.0f, 0.0f));

	glUniform3f(viewPos, Viewl.x, Viewl.y, Viewl.z);

	glBindVertexArray(vao);

	glm::mat4 Si = glm::scale(glm::mat4(1.0f), glm::vec3(0.2, 0.2, 0.2));
	//glm::mat4 Light = Tr * Si;
	glUniform3f(colorLocation, 0.0, 0.0, 0.0);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Si));

	glDrawArrays(GL_TRIANGLES, 0, num_Triangle);

	glutSwapBuffers();
}

GLvoid Timer(int value) {
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y) {
	int i = 0;
	switch (key) {
	}
}
