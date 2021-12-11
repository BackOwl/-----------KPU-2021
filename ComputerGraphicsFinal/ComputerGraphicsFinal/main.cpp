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
#include <vector>
#include <crtdbg.h>
//#include <stdio.h>

//////�뷡�Լ� //////
#pragma comment(lib,"winmm")
#include <mmsystem.h> 
#include "Digitalv.h"
MCI_OPEN_PARMS m_mciOpenParms;
MCI_PLAY_PARMS m_mciPlayParms;
DWORD m_dwDeviceID;
MCI_OPEN_PARMS mciOpen;
MCI_PLAY_PARMS mciPlay;
MCI_DGV_SETAUDIO_PARMS SetAudio;
int dwID, gunID, walkID;
//�������� 
DWORD dwVolume = 100;



///////////////////��ɾ� Ȯ�� <https://sysys.tistory.com/30>,playsound ��ɾ� <https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=enter_maintanance&logNo=220950709844>

#include "filetobuf.h"
#include "obj.h"
#include "player.h"
#include "enemy.h"
#include "timer_.h"
#include "bullet.h"
#include "bullets.h"
#include "enemies.h"
#include "particle.h"

#define width 600
#define height 600
#pragma warning(disable:4996)

int gun_num_Triangle;
int sphere_num_Triangle;
float walk_time = 0.45;
GLuint vao[4], vbo[8],background_vao[6], background_vbo[12];

bool make_vertexShader();
bool make_fragmentShaders();
GLuint make_shaderProgram();

GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);

void Timer(int value);
GLuint shaderID;

void Init();
void Delete();
void Update();

void Key_Update();



GLuint vertexShader, fragmentShader;
GLchar* vertexsource, * fragmentsource;


Player* player;
Timer_* timer;

POINT prev_mouse;	// ���콺 ���� ��ǥ ����

std::vector<Bullet> enemy_bullet;	// ���� �Ѿ� ���⼭ ����
std::vector<Bullet> player_bullet;	// player �Ѿ� ���⼭ ����
std::vector<Enemy> enemy;	// ��� �� ���⼭ ����
std::vector<ParticleSystem> particle;

GLfloat cube[36][3] = { //--- ���ؽ� �Ӽ�: ��ǥ��(FragPos), �븻�� (Normal)
	{-0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, -0.5f}, {0.5f, 0.5f, -0.5f},
	{0.5f, 0.5f, -0.5f}, {-0.5f, 0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f },

	-0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f,

	-0.5f, 0.5f, 0.5f, -0.5f, 0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f,

	0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f,

	-0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, -0.5f,

	-0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, -0.5f
};

GLfloat cube_normal[36][3] = { //--- ���ؽ� �Ӽ�: ��ǥ��(FragPos), �븻�� (Normal)
0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,

0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

-1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
-1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,

0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f
};

GLfloat star[10][3] = {
	0.0, -0.5, 0.0,
	0.5, -0.8, 0.0,
	0.3, -0.3, 0.0,
	0.8, 0.1, 0.0,
	0.2, 0.1, 0.0,
	0.0, 0.8, 0.0,
	-0.2, 0.1, 0.0,
	-0.3, -0.3, 0.0,
	-0.5, -0.8, 0.0,
};

GLfloat star_normal[10][3] = {
	0.0, 0.0, -1.0,
	0.0, 0.0, -1.0,
	0.0, 0.0, -1.0,
	0.0, 0.0, -1.0,
	0.0, 0.0, -1.0,
	0.0, 0.0, -1.0,
	0.0, 0.0, -1.0,
	0.0, 0.0, -1.0,
	0.0, 0.0, -1.0,
	0.0, 0.0, -1.0,
};


void Init() {
	player = new Player();
	timer = new Timer_();
	enemy.push_back(Enemy(10.0, 0.0, 5.0));
	enemy.push_back(Enemy(-10.0, 0.0, 10.0));
	enemy.push_back(Enemy(10.0, 0.0, -10.0));
}

void Delete() {
	delete player;
	delete timer;
	enemy_bullet.clear();	// ���� �Ѿ� ���⼭ ����
	player_bullet.clear();	// player �Ѿ� ���⼭ ����
	enemy.clear();	// ��� �� ���⼭ ����
	particle.clear();
}


void update_particle(std::vector<ParticleSystem>* v, float time) {
	int i = 0;
	for (std::vector<ParticleSystem>::iterator it = v->begin(); it != v->end(); it++)
	{
		if ((*v)[i].Update(time)) {
			it = v->erase(it);
			break;
		}
		++i;
	}
}

void draw_particle(std::vector<ParticleSystem>* v, float ch_angle, unsigned int modelLocation, unsigned int colorLocation, int numTriangle) {	//ch_angle, unsigned int modelLocation, unsigned int colorLocation, int numTriangle
	for (int i = 0; i < v->size(); ++i) {
		(*v)[i].Draw(ch_angle, modelLocation, colorLocation, numTriangle);
	}
}

void Update() {
	ShowCursor(FALSE);
	int x = glutGet(GLUT_WINDOW_X);
	int y = glutGet(GLUT_WINDOW_Y);
	int window_width = glutGet(GLUT_WINDOW_WIDTH);
	int window_height = glutGet(GLUT_WINDOW_HEIGHT);
	float pl_x, pl_y, pl_z;
	player->GetPos(&pl_x, &pl_y, &pl_z);
	update_enemy(&enemy, &enemy_bullet, &player_bullet, pl_x, pl_z, timer->SlowDeltaTime());
	Key_Update();
	timer->Update();
	player->Update(&enemy_bullet, x, y, window_width, window_height, timer->SlowDeltaTime());
	update_bullet(&player_bullet, timer->SlowDeltaTime());
	update_bullet(&enemy_bullet, timer->SlowDeltaTime());
	update_particle(&particle, timer->SlowDeltaTime());

	int i = 0;
	for (std::vector<Enemy>::iterator it = enemy.begin(); it != enemy.end(); it++)
	{
		if (enemy[i].collide_bullet(&player_bullet)) {
			float x, y, z;
			enemy[i].GetPos(&x, &y, &z);
			printf("particle");
			particle.push_back(ParticleSystem(x, y, z));
			it = enemy.erase(it);
			break;
		}
		++i;
	}

}

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
	Obj gun_obj = loadObj("Resource\\gun.obj");
	Obj sphere_obj = loadObj("Resource\\sphere.obj");

	gun_num_Triangle = gun_obj.num;
	sphere_num_Triangle = sphere_obj.num;

	glGenVertexArrays(4, vao); //--- VAO �� �����ϰ� �Ҵ��ϱ�
	glGenBuffers(8, vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�

	glBindVertexArray(vao[0]);	// ��obj
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, gun_obj.outvertex.size() * sizeof(glm::vec3), &gun_obj.outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, gun_obj.outnormal.size() * sizeof(glm::vec3), &gun_obj.outnormal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(vao[1]);	// ������ü
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_normal), cube_normal, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(vao[2]);	// ��
	glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
	glBufferData(GL_ARRAY_BUFFER, sphere_obj.outvertex.size() * sizeof(glm::vec3), &sphere_obj.outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);
	glBufferData(GL_ARRAY_BUFFER, sphere_obj.outnormal.size() * sizeof(glm::vec3), &sphere_obj.outnormal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(vao[3]);	// ��
	glBindBuffer(GL_ARRAY_BUFFER, vbo[6]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(star), star, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[7]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(star_normal), star_normal, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	//---------------��� ������-------------------------
	glGenVertexArrays(6, background_vao); //--- VAO �� �����ϰ� �Ҵ��ϱ�
	glGenBuffers(12, background_vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�
	for (int i = 0; i < 6; i ++) {

		glBindVertexArray(background_vao[i]);	// ������ü
		glBindBuffer(GL_ARRAY_BUFFER, background_vbo[2*i+0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, background_vbo[2*i+1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cube_normal), cube_normal, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);
	}


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
	Init();
	//--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ ����
	glutInitWindowSize(width, height); // �������� ũ�� ����
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

	///////������� ��� 
	mciOpen.lpstrElementName = L"Resource/Sound/thema_1.mp3"; // ���� ��� �Է�
	mciOpen.lpstrDeviceType = L"mpegvideo";

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,(DWORD)(LPVOID)&mciOpen);
	dwID = mciOpen.wDeviceID;

	SetAudio.dwCallback = SetAudio.dwOver = 0;
	SetAudio.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	SetAudio.dwValue = dwVolume; //�Ҹ�ũ�� ����
	SetAudio.lpstrAlgorithm = SetAudio.lpstrQuality = NULL;
	mciSendCommandW(dwID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE| MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&SetAudio);

	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT,(DWORD)(LPVOID)&m_mciPlayParms);
	///////������� ��� ��

	//�������

	mciOpen.lpstrElementName = L"Resource/Sound/gun_1.wav"; // ���� ��� �Է�
	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);
	gunID = mciOpen.wDeviceID;

	mciOpen.lpstrElementName = L"Resource/Sound/walk_3.wav"; // ���� ��� �Է�
	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);
	walkID = mciOpen.wDeviceID;
	/////////

	InitShader();
	InitBuffer();
	shaderID = make_shaderProgram(); //--- ���̴� ���α׷� �����
	//glutTimerFunc(TIMEMIN, Timer, 0);

	glutDisplayFunc(drawScene); // ��� �ݹ��Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �ݹ��Լ� ����
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutTimerFunc(10, Timer, 1);
	glutMainLoop(); // �̺�Ʈ ó�� ����

}

GLvoid drawScene() {
	

	GLfloat rColor, gColor, bColor;
	rColor = gColor = bColor = 1.0;

	PlaySound(TEXT("test1.wav"), NULL, SND_ASYNC | SND_ALIAS|SND_LOOP);

	glClearColor(rColor, gColor, bColor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float x, y, z;
	player->GetPos(&x, &y, &z);

	glm::vec3 cameraPos = glm::vec3(x, y, z);
	glm::vec3 cameraDirection = glm::vec3(x, y, z + 1.0); //--- ī�޶� �ٶ󺸴� ����
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);	//glm::cross(cameraDirection, cameraRight);
	glm::mat4 view = glm::mat4(1.0f);

	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(shaderID, "viewTransform"); //--- ���ؽ� ���̴����� viewTransform ������ġ
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	glm::mat4 projection = glm::mat4(1.0f);

	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 110.0f);
	projection = glm::rotate(projection, (GLfloat)glm::radians(player->GetYangle()), glm::vec3(1.0f, 0.0f, 0.0f));
	projection = glm::rotate(projection, (GLfloat)glm::radians(player->GetXangle()), glm::vec3(0.0f, 1.0f, 0.0f));

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
	glUniform1f(ambient, 0.2);

	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);

	glUniform3f(lightPosLocation, 0.0, 0.0, 0.0);

	glm::vec4 Viewl = glm::vec4(0.0, 0.0, 5.0, 0.0);

	Viewl = Viewl * glm::rotate(glm::mat4(1.0f), (GLfloat)glm::radians(float(30.0)), glm::vec3(1.0f, 0.0f, 0.0f));

	glUniform3f(viewPos, Viewl.x, Viewl.y, Viewl.z);

	glBindVertexArray(vao[0]);
	
	glm::mat4 Si = glm::scale(glm::mat4(1.0f), glm::vec3(0.2, 0.2, 0.2));
	//glm::mat4 Light = Tr * Si;
	glUniform3f(colorLocation, 0.0, 0.0, 0.0);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Si));

	glDrawArrays(GL_TRIANGLES, 0, gun_num_Triangle);
	
	player->gun.Draw(modelLocation, colorLocation, gun_num_Triangle);
	glBindVertexArray(vao[1]);
	draw_bullet(&player_bullet, modelLocation, colorLocation, 36);
	draw_bullet(&enemy_bullet, modelLocation, colorLocation, 36);

	glBindVertexArray(vao[2]);
	draw_enemy(&enemy, modelLocation, colorLocation, sphere_num_Triangle);

	glBindVertexArray(vao[3]);
	draw_particle(&particle, player->GetXangle(), modelLocation, colorLocation, 10);

	//----------�� �⺻ 6 //////
	glm::mat4 right =glm::translate(glm::mat4(1.0f), glm::vec3(-50.0, 7.0,0.0));
	glm::mat4 left  = glm::translate(glm::mat4(1.0f), glm::vec3(50.0, 7.0, 0.0));
	glm::mat4 up    = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 10.0, 0.0));
	glm::mat4 front = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 7.0, 50.0));
	glm::mat4 back  = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 7.0, -50.0));
	glm::mat4 down = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, -3.0, -0.0));

	glm::mat4 RLscale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 100.0, 100.0));
	glm::mat4 UDscale = glm::scale(glm::mat4(1.0f), glm::vec3(100.0, 1.0, 100.0));
	glm::mat4 FBscale = glm::scale(glm::mat4(1.0f), glm::vec3(100.0, 100.0, 1.0));

	glm::mat4 END= right * RLscale;
	glUniform3f(colorLocation, 0.0, 1.0, 0.0);
	glBindVertexArray(background_vao[0]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(END));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	END = left * RLscale ;
	glUniform3f(colorLocation, 1.0, 0.0, 0.0);
	glBindVertexArray(background_vao[1]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(END));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	END = up * UDscale;
	glUniform3f(colorLocation, 1.0, 0.0, 1.0);
	glBindVertexArray(background_vao[2]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(END));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	END = down* UDscale;
	glUniform3f(colorLocation, 1.0, 1.0, 0.0);
	glBindVertexArray(background_vao[3]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(END));
	glDrawArrays(GL_TRIANGLES, 0, 36);


	END = front * FBscale ;
	glUniform3f(colorLocation, 0.0, 1.0, 1.0);
	glBindVertexArray(background_vao[4]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(END));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	END = back * FBscale ;
	glUniform3f(colorLocation, 0.0, 0.8, 0.8);
	glBindVertexArray(background_vao[5]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(END));
	glDrawArrays(GL_TRIANGLES, 0, 36);




	glutSwapBuffers();
}

GLvoid Timer(int value) {
	Update();

	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y) {

	switch (key) {		
	case'T':
	case't': // ��ɾ� ���࿩�� �׽�Ʈ�� Ű����
		break;
	case 'q':
	case 'Q':
		Delete();
		glutLeaveMainLoop();
	}
	glutPostRedisplay();
}

void Key_Update() {	
	bool walk = false;
	if (GetAsyncKeyState('W')) {
		player->Move_Front(timer->DeltaTime());
		timer->SetTimerFast();
		walk = true;
	}
	if (GetAsyncKeyState('A')) {
		player->Move_Left(timer->DeltaTime());
		timer->SetTimerFast();
		walk = true;
	}
	if (GetAsyncKeyState('S')) {
		player->Move_Back(timer->DeltaTime());
		timer->SetTimerFast();
		walk = true;
	}
	if (GetAsyncKeyState('D')  ) {
		player->Move_Right(timer->DeltaTime());
		timer->SetTimerFast();
		walk = true;
	}
	if (walk == true){
		walk_time += timer->DeltaTime();
		if (walk_time > 0.5) {
			walk_time = 0.45;
			walk = false;

			mciSendCommand(walkID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)&m_mciPlayParms);
			mciSendCommand(walkID, MCI_PLAY, 0, (DWORD)(LPVOID)&m_mciPlayParms);

		}
		
	}
}


void Mouse(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		if (player->gun.Shot()) {
			float x, y, z;
			player->GetPos(&x, &y, &z);
			player_bullet.push_back(Bullet(x, y, z, player->GetXangle(), player->GetYangle(), true));

			mciSendCommand(gunID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)&m_mciPlayParms);
			mciSendCommand(gunID, MCI_PLAY, 0, (DWORD)(LPVOID)&m_mciPlayParms);
			//particle.push_back(ParticleSystem(0, 0, 0));
		}
		// std::cout << "bullet" << bullet.size() << std::endl;
		// ���ΰ� �� �߻�
	}

	GetCursorPos(&prev_mouse);

	glutPostRedisplay();
}
