// GCExp1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <GL\glut.h>
#include <math.h>

//�����
#define PI 3.1416

//�趨���������
#define BODY 1
#define CROWN 2
#define HAT 3
#define FLAG 4

const int N = 40;//���Ƶľ�ϸ�̶�

float tempX, tempY;//��ʱ��������
float tempR;//��ʱ����İ뾶
float translate;//ƽ����

static GLfloat theta = 0;//��ת�ĽǶ�

int SelectPart;//ѡ�еĲ���
int scale = 1;//���z�����ŵĳ̶�

static int VIEWSIZE = 130;//�ü�����ϵ�Ĵ�С

//����Ԫ�ص�λ��
GLuint Body[2] = { 0,0 };
GLuint Crown[2] = { 110,80 };
GLuint Hat[2] = { 110,30 };
GLuint Flag[2] = { 110,-20 };

//��ɫѡ����
//��ɫ����ɫ����ɫ����ɫ����ɫ����ɫ����ɫ����ɫ
static GLfloat ColorChoose[8][3] = {
	{ 0.0, 0.0, 0.0 },{ 1.0, 0.0, 0.0 },{ 0.0, 1.0, 0.0 },{ 0.25, 0.46, 1.0 },
	{ 0.0, 1.0, 1.0 },{ 1.0, 0.0, 1.0 },{ 1.0, 1.0, 0.0 },{ 1.0, 1.0, 1.0 }
};

//�趨�����ֵ���ɫ
static int LINE_COLOR = 0;
static int BODY_COLOR = 3;
static int NECKLACE_COLOR = 1;
static int FACE_COLOR = 7;
static int EYE_OUT_COLOR = 7;
static int EYE_IN_COLOR = 0;
static int NOSE_COLOR = 1;
static int MOUSE_COLOR = 1;
static int FOOT_COLOR = 7;
static int HAND_COLOR = 7;
static int CROWN_COLOR = 6;
static int HAT_COLOR = 1;
static int FLAG_COLOR = 2;

//�Ƿ�ѡ��ͼԪ
BOOL BODY_STATE;
BOOL CROWN_STATE;
BOOL HAT_STATE;
BOOL FLAG_STATE;

//�Ƿ��������
BOOL SCALE_STATE;

//�Ƿ񴩴�
BOOL CROWN_WEARING;
BOOL HAT_WEARING;
BOOL FLAG_WEARING;

//��������
void DrawBody(int x, int y) {

	/*
	glEnable(GL_BLEND);//������ɫ���
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//����Դ��ɫ���������ɫ��RGB����alphaֵ��ˣ�
													  //Ȼ�������������Ŀ����ɫ�ˡ�1��ȥԴ��ɫ��alphaֵ���Ľ��
	*/

	//���÷�����
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);

	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	//��첲
	{
		glLoadIdentity();
		glRotatef(theta, 0.0, 0.0, 1.0);
		glTranslatef(-38.0, 10.0, 0.0);
		glRotatef(45.0, 0.0, 0.0, 1.0);
		glColor3f(ColorChoose[BODY_COLOR][0], ColorChoose[BODY_COLOR][1], ColorChoose[BODY_COLOR][2]);

		glBegin(GL_POLYGON);
		for (int i = 0; i < N; i++) {
			tempX = 20 * cos(2 * PI*i / N);
			tempY = 10 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();

		//���
		glColor3f(ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][1], ColorChoose[LINE_COLOR][2]);
		glLineWidth(1.0);//������ϸ����

		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < N; i++) {
			tempX = 20 * cos(2 * PI*i / N);
			tempY = 10 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();
	}

	//����
	{
		glLoadIdentity();
		glRotatef(theta, 0.0, 0.0, 1.0);
		glTranslatef(-50.0, 0.0, 0.0);
		glColor3f(ColorChoose[HAND_COLOR][0], ColorChoose[HAND_COLOR][1], ColorChoose[HAND_COLOR][2]);

		glBegin(GL_POLYGON);
		for (int i = 0; i < N; i++) {
			tempX = 8 * cos(2 * PI*i / N);
			tempY = 8 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();

		glColor3f(ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][1], ColorChoose[LINE_COLOR][2]);
		glLineWidth(1.0);//������ϸ����

		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < N; i++) {
			tempX = 8 * cos(2 * PI*i / N);
			tempY = 8 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();
	}

	//�Ҹ첲
	{
		glLoadIdentity();
		glRotatef(theta, 0.0, 0.0, 1.0);
		glTranslatef(38.0, 10.0, 0.0);
		glRotatef(-45.0, 0.0, 0.0, 1.0);
		glColor3f(ColorChoose[BODY_COLOR][0], ColorChoose[BODY_COLOR][1], ColorChoose[BODY_COLOR][2]);

		glBegin(GL_POLYGON);
		for (int i = 0; i < N; i++) {
			tempX = 20 * cos(2 * PI*i / N);
			tempY = 10 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();

		glColor3f(ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][1], ColorChoose[LINE_COLOR][2]);

		glLineWidth(1.0);//������ϸ����
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < N; i++) {
			tempX = 20 * cos(2 * PI*i / N);
			tempY = 10 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();
	}

	//����
	{
		glLoadIdentity();
		glRotatef(theta, 0.0, 0.0, 1.0);
		glTranslatef(50.0, 0.0, 0.0);
		glColor3f(ColorChoose[HAND_COLOR][0], ColorChoose[HAND_COLOR][1], ColorChoose[HAND_COLOR][2]);

		glBegin(GL_POLYGON);
		for (int i = 0; i < N; i++) {
			tempX = 8 * cos(2 * PI*i / N);
			tempY = 8 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();

		glColor3f(ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][1], ColorChoose[LINE_COLOR][2]);
		glLineWidth(1.0);//������ϸ����

		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < N; i++) {
			tempX = 8 * cos(2 * PI*i / N);
			tempY = 8 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();
	}

	//����
	{
		glLoadIdentity();
		glRotatef(theta, 0.0, 0.0, 1.0);
		glColor3f(ColorChoose[BODY_COLOR][0], ColorChoose[BODY_COLOR][1], ColorChoose[BODY_COLOR][2]);

		glBegin(GL_POLYGON);
		for (int i = 0; i <= N / 8; i++) {
			tempX = 40 * cos(2 * PI*i / N);
			tempY = 42 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}

		for (int i = 3 * N / 8; i <= 5 * N / 8; i++) {
			tempX = 40 * cos(2 * PI*i / N);
			tempY = 42 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}

		for (int i = 7 * N / 8; i < N; i++) {
			tempX = 40 * cos(2 * PI*i / N);
			tempY = 42 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();

		//���
		glColor3f(ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][0]);
		glLineWidth(1.0);//������ϸ����

		glBegin(GL_LINE_LOOP);
		for (int i = 0; i <= N / 8; i++) {
			tempX = 40 * cos(2 * PI*i / N);
			tempY = 42 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}

		for (int i = 3 * N / 8; i <= 5 * N / 8; i++) {
			tempX = 40 * cos(2 * PI*i / N);
			tempY = 42 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}

		for (int i = 7 * N / 8; i < N; i++) {
			tempX = 40 * cos(2 * PI*i / N);
			tempY = 42 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();
	}

	//��Ȧ
	{
		glLoadIdentity();
		glRotatef(theta, 0.0, 0.0, 1.0);
		glColor3f(ColorChoose[NECKLACE_COLOR][0], ColorChoose[NECKLACE_COLOR][1], ColorChoose[NECKLACE_COLOR][2]);

		glBegin(GL_POLYGON);
		tempX = 40 * cos(2 * PI * 5 / N);
		tempY = 42 * sin(2 * PI * 5 / N);
		glVertex2f(tempX, tempY);
		tempX = 40 * cos(2 * PI * 15 / N);
		//tempY= 40 * sin(2 * PI*15 / N);
		glVertex2f(tempX, tempY);
		tempY = 40 * sin(2 * PI * 15 / N) + 5;
		glVertex2f(tempX, tempY);
		tempX = 40 * cos(2 * PI * 5 / N);
		glVertex2f(tempX, tempY);
		glEnd();

		glColor3f(ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][0]);
		glLineWidth(1.0);//������ϸ����

		glBegin(GL_LINE_LOOP);
		tempX = 40 * cos(2 * PI * 5 / N);
		tempY = 42 * sin(2 * PI * 5 / N);
		glVertex2f(tempX, tempY);
		tempX = 40 * cos(2 * PI * 15 / N);
		//tempY= 40 * sin(2 * PI*15 / N);
		glVertex2f(tempX, tempY);
		tempY = 40 * sin(2 * PI * 15 / N) + 5;
		glVertex2f(tempX, tempY);
		tempX = 40 * cos(2 * PI * 5 / N);
		glVertex2f(tempX, tempY);
		glEnd();
	}

	//ͷ��
	{
		translate = 42 * sin(2 * PI * 5 / N) + 40 * sin(2 * PI * 5 / N) + 4;
		glLoadIdentity();
		glRotatef(theta, 0.0, 0.0, 1.0);
		glTranslatef(0.0, translate, 0.0);
		glColor3f(ColorChoose[BODY_COLOR][0], ColorChoose[BODY_COLOR][1], ColorChoose[BODY_COLOR][2]);

		glBegin(GL_POLYGON);
		for (int i = 0; i <= 5 * N / 8; i++) {
			tempX = 40 * cos(2 * PI*i / N);
			tempY = 40 * sin(2 * PI*i / N) ;
			glVertex2f(tempX, tempY);
		}

		for (int i = 7 * N / 8; i < N; i++) {
			tempX = 40 * cos(2 * PI*i / N) ;
			tempY = 40 * sin(2 * PI*i / N) ;
			glVertex2f(tempX, tempY);
		}
		glEnd();

		glColor3f(ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][0]);
		glLineWidth(1.0);//������ϸ����
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i <= 5 * N / 8; i++) {
			tempX = 40 * cos(2 * PI*i / N);
			tempY = 40 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}

		for (int i = 7 * N / 8; i < N; i++) {
			tempX = 40 * cos(2 * PI*i / N);
			tempY = 40 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();
	}

	//��
	{
		tempR = 40 * cos(2 * PI * 5 / N) / cos(35.0*PI/180.0);//���İ뾶
		translate = 42 * sin(2 * PI * 5 / N) + tempR*sin(35.0*PI / 180.0) + 5;
		glLoadIdentity();
		glRotatef(theta, 0.0, 0.0, 1.0);
		glTranslatef(0.0, translate, 0.0);
		glColor3f(ColorChoose[FACE_COLOR][0], ColorChoose[FACE_COLOR][1], ColorChoose[FACE_COLOR][2]);

		glBegin(GL_POLYGON);
		for (int i = 0; i < 7 * N / 12 + 2; i++) {
			tempX = tempR*cos(2 * PI*i / N);
			tempY = tempR*sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		for (int i = 11 * N / 12; i < N; i++) {
			tempX = tempR*cos(2 * PI*i / N);
			tempY = tempR*sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();
	}

	//����
	{
		tempR = 40 * cos(2 * PI * 5 / N) / cos(35.0*PI / 180.0)-5;//���ӵİ뾶
		translate = 42 * sin(2 * PI * 5 / N) - tempR*sin(35.0*PI / 180.0)-1;
		glLoadIdentity();
		glRotatef(theta, 0.0, 0.0, 1.0);
		glTranslatef(0.0, translate, 0.0);
		glColor3f(ColorChoose[FACE_COLOR][0], ColorChoose[FACE_COLOR][1], ColorChoose[FACE_COLOR][2]);

		glBegin(GL_POLYGON);
		for (int i = 0; i < N / 12 + 2; i++) {
			tempX = tempR*cos(2 * PI*i / N);
			tempY = tempR*sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		for (int i = 5 * N / 12; i < N; i++) {
			tempX = tempR*cos(2 * PI*i / N);
			tempY = tempR*sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();

		//�ڴ�
		tempR = 18;
		glBegin(GL_POLYGON);
		for (int i = N / 2; i <= N; i++) {
			tempX = tempR * cos(2 * PI*i / N);
			tempY = tempR * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();

		glColor3f(ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][0]);
		glLineWidth(1.0);//������ϸ����

		glBegin(GL_LINE_LOOP);
		for (int i = N / 2; i <= N; i++) {
			tempX = tempR * cos(2 * PI*i / N);
			tempY = tempR * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();
	}

	//����
	{
		tempR = 40 * cos(2 * PI * 5 / N) / cos(35.0*PI / 180.0);//���İ뾶
		translate = 42 * sin(2 * PI * 5 / N) + tempR*sin(35.0*PI / 180.0) + 5 + tempR;
		glLoadIdentity();
		glRotatef(theta, 0.0, 0.0, 1.0);
		glTranslatef(-6.0, translate, 0.0);
		glColor3f(ColorChoose[EYE_OUT_COLOR][0], ColorChoose[EYE_OUT_COLOR][1], ColorChoose[EYE_OUT_COLOR][2]);

		glBegin(GL_POLYGON);
		for (int i = 0; i < N; i++) {
			tempX = 6*cos(2 * PI*i / N);
			tempY = 8*sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();

		glColor3f(ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][0]);

		glLineWidth(1.0);//������ϸ����
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < N; i++) {
			tempX = 6*cos(2 * PI*i / N);
			tempY = 8*sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();
	}

	//��������
	{
		tempR = 40 * cos(2 * PI * 5 / N) / cos(35.0*PI / 180.0);//���İ뾶
		translate = 42 * sin(2 * PI * 5 / N) + tempR*sin(35.0*PI / 180.0) + 5 + tempR;
		glLoadIdentity();
		glRotatef(theta, 0.0, 0.0, 1.0);
		glTranslatef(-3.0, translate, 0.0);
		glColor3f(ColorChoose[EYE_IN_COLOR][0], ColorChoose[EYE_IN_COLOR][1], ColorChoose[EYE_IN_COLOR][2]);

		glBegin(GL_POLYGON);
		for (int i = 0; i < N; i++) {
			tempX = 3 * cos(2 * PI*i / N);
			tempY = 3 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();
	}

	//����
	{
		tempR = 40 * cos(2 * PI * 5 / N) / cos(35.0*PI / 180.0);//���İ뾶
		translate = 42 * sin(2 * PI * 5 / N) + tempR*sin(35.0*PI / 180.0) + 5 + tempR;
		glLoadIdentity();
		glRotatef(theta, 0.0, 0.0, 1.0);
		glTranslatef(6.0, translate, 0.0);
		glColor3f(ColorChoose[EYE_OUT_COLOR][0], ColorChoose[EYE_OUT_COLOR][1], ColorChoose[EYE_OUT_COLOR][2]);

		glBegin(GL_POLYGON);
		for (int i = 0; i < N; i++) {
			tempX = 6 * cos(2 * PI*i / N);
			tempY = 8 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();

		glColor3f(ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][0]);

		glLineWidth(1.0);//������ϸ����
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < N; i++) {
			tempX = 6 * cos(2 * PI*i / N);
			tempY = 8 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();
	}

	//��������
	{
		tempR = 40 * cos(2 * PI * 5 / N) / cos(35.0*PI / 180.0);//���İ뾶
		translate = 42 * sin(2 * PI * 5 / N) + tempR*sin(35.0*PI / 180.0) + 5 + tempR;
		glLoadIdentity();
		glRotatef(theta, 0.0, 0.0, 1.0);
		glTranslatef(3.0, translate, 0.0);
		glColor3f(ColorChoose[EYE_IN_COLOR][0], ColorChoose[EYE_IN_COLOR][1], ColorChoose[EYE_IN_COLOR][2]);

		glBegin(GL_POLYGON);
		for (int i = 0; i < N; i++) {
			tempX = 3 * cos(2 * PI*i / N);
			tempY = 3 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();
	}

	//����
	{
		tempR = 40 * cos(2 * PI * 5 / N) / cos(35.0*PI / 180.0);//���İ뾶
		translate = 42 * sin(2 * PI * 5 / N) + tempR*sin(35.0*PI / 180.0) + tempR-5;
		glLoadIdentity();
		glRotatef(theta, 0.0, 0.0, 1.0);
		glTranslatef(0.0, translate, 0.0);
		glColor3f(ColorChoose[NOSE_COLOR][0], ColorChoose[NOSE_COLOR][1], ColorChoose[NOSE_COLOR][2]);

		glBegin(GL_POLYGON);
		for (int i = 0; i < N; i++) {
			tempX = 3 * cos(2 * PI*i / N);
			tempY = 3 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();
	}

	//��
	{
		tempR = 40 * cos(2 * PI * 5 / N) / cos(35.0*PI / 180.0);//���İ뾶
		translate = 42 * sin(2 * PI * 5 / N) + tempR*sin(35.0*PI / 180.0) + tempR - 25;
		glLoadIdentity();
		glRotatef(theta, 0.0, 0.0, 1.0);
		glTranslatef(0.0, translate, 0.0);
		glColor3f(ColorChoose[NOSE_COLOR][0], ColorChoose[NOSE_COLOR][1], ColorChoose[NOSE_COLOR][2]);

		glBegin(GL_POLYGON);
		for (int i = N/2; i <= N; i++) {
			tempX = 20 * cos(2 * PI*i / N);
			tempY = 20 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();

		glColor3f(ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][0]);
		glLineWidth(1.0);//������ϸ����
		glBegin(GL_LINE_LOOP);
		for (int i = N / 2 ; i <= N; i++) {
			tempX = 20 * cos(2 * PI*i / N);
			tempY = 20 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();

		glBegin(GL_LINES);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, 17.0f);
		glEnd();
	}

	//����
	{
		tempR = 40 * cos(2 * PI * 5 / N) / cos(35.0*PI / 180.0);//���İ뾶
		translate = 42 * sin(2 * PI * 5 / N) + tempR*sin(35.0*PI / 180.0) + tempR - 15;
		glLoadIdentity();
		glRotatef(theta, 0.0, 0.0, 1.0);
		glTranslatef(0.0, translate, 0.0);
		glColor3f(ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][1], ColorChoose[LINE_COLOR][2]);

		glBegin(GL_LINES);
		glVertex2f(-25.0f, 0.0f);
		glVertex2f(-5.0f, 0.0f);
		glVertex2f(25.0f, 0.0f);
		glVertex2f(5.0f, 0.0f);
		glVertex2f(-23.0f, 8.0f);
		glVertex2f(-5.0f, 4.0f);
		glVertex2f(23.0f, 8.0f);
		glVertex2f(5.0f, 4.0f);
		glVertex2f(-23.0f, -8.0f);
		glVertex2f(-5.0f, -4.0f);
		glVertex2f(23.0f, -8.0f);
		glVertex2f(5.0f, -4.0f);
		glEnd();
	}

	//���
	{
		tempR = 20 * cos(2 * PI * 5 / N);
		translate = 42 * sin(2 * PI * 5 / N);
		glLoadIdentity();
		glRotatef(theta, 0.0, 0.0, 1.0);
		glTranslatef(-tempR, -translate, 0.0);
		glColor3f(ColorChoose[FOOT_COLOR][0], ColorChoose[FOOT_COLOR][1], ColorChoose[FOOT_COLOR][2]);

		glBegin(GL_POLYGON);
		for (int i = 0; i < N; i++) {
			tempX = tempR * cos(2 * PI*i / N);
			tempY = tempR * 0.5 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();

		glColor3f(ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][0]);
		glLineWidth(1.0);//������ϸ����
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < N; i++) {
			tempX = tempR * cos(2 * PI*i / N);
			tempY = tempR * 0.5 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();
	}

	//�ҽ�
	{
		tempR = 20 * cos(2 * PI * 5 / N);
		translate = 42 * sin(2 * PI * 5 / N);
		glLoadIdentity();
		glRotatef(theta, 0.0, 0.0, 1.0);
		glTranslatef(tempR, -translate, 0.0);

		glColor3f(ColorChoose[FOOT_COLOR][0], ColorChoose[FOOT_COLOR][1], ColorChoose[FOOT_COLOR][2]);
		glBegin(GL_POLYGON);
		for (int i = 0; i < N; i++) {
			tempX = tempR * cos(2 * PI*i / N);
			tempY = tempR * 0.5 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();

		glColor3f(ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][1], ColorChoose[LINE_COLOR][2]);
		glLineWidth(1.0);//������ϸ����
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < N; i++) {
			tempX = tempR * cos(2 * PI*i / N);
			tempY = tempR * 0.5 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();
	}

	
}

//���ƻʹ�
void DrawCrown(int x, int y) {
	glLoadIdentity();
	
	//���Ǵ������ϣ���һ����ת
	if(CROWN_WEARING==TRUE)
		glRotatef(theta, 0.0, 0.0, 1.0);

	//����ѡ�����ŵ�״̬����ͼ���ƶ���ԭ�㣬���ź����ƶ���ԭλ��
	if (SCALE_STATE == TRUE && SelectPart==CROWN) {
		glTranslatef(x, y, 0.0);
		glScalef(scale, scale, 1);
		glTranslatef(-x, -y, 0.0);
	}
	else {
	}
	
	glColor3f(ColorChoose[CROWN_COLOR][0], ColorChoose[CROWN_COLOR][1], ColorChoose[CROWN_COLOR][2]);
	
	//δ�Ӳ㼶�趨
	/*glBegin(GL_POLYGON);
	glVertex2f(-10 + x, y - 9);
	glVertex2f(-13 + x, 6 + y);
	glVertex2f(-5 + x, y );
	glVertex2f(0 + x, 12 + y);
	glVertex2f(5 + x, y );
	glVertex2f(13 + x, 6 + y);
	glVertex2f(10 + x, y - 9);
	glEnd();*/

	//������z������Ϊ1����ʾ�㼶������֮��
	glBegin(GL_POLYGON);
	glVertex3f(-10 + x, y - 9,1.0);
	glVertex3f(-13 + x, 6 + y, 1.0);
	glVertex3f(-5 + x, y, 1.0);
	glVertex3f(0 + x, 12 + y, 1.0);
	glVertex3f(5 + x, y, 1.0);
	glVertex3f(13 + x, 6 + y, 1.0);
	glVertex3f(10 + x, y - 9, 1.0);
	glEnd();
}

//����ñ��
void DrawHat(int x, int y) {
	glLoadIdentity();

	//���Ǵ������ϣ���һ����ת
	if (HAT_WEARING == TRUE)
		glRotatef(theta, 0.0, 0.0, 1.0);

	//����ѡ�����ŵ�״̬����ͼ���ƶ���ԭ�㣬���ź����ƶ���ԭλ��
	if (SCALE_STATE == TRUE && SelectPart == HAT) {
		glTranslatef(x, y, 0.0);
		glScalef(scale, scale, 1);
		glTranslatef(-x, -y, 0.0);
	}
	else {
	}

	glColor3f(ColorChoose[HAT_COLOR][0], ColorChoose[HAT_COLOR][1], ColorChoose[HAT_COLOR][2]);

	//������z������Ϊ1����ʾ�㼶������֮��
	tempR = 18;
	glBegin(GL_POLYGON);
	for (int i = 0; i <= N/2; i++) {
		tempX = tempR * cos(2 * PI*i / N);
		tempY = tempR * sin(2 * PI*i / N);
		glVertex3f(tempX+x, tempY+y,1.5);
	}
	glEnd();

	glColor3f(ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][1], ColorChoose[LINE_COLOR][2]);
	glLineWidth(1.0);//������ϸ����

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= N/2; i++) {
		tempX = tempR * cos(2 * PI*i / N);
		tempY = tempR * sin(2 * PI*i / N);
		glVertex3f(tempX+x, tempY+y,1.5);
	}
	glEnd();

	glColor3f(ColorChoose[HAT_COLOR][0], ColorChoose[HAT_COLOR][1], ColorChoose[HAT_COLOR][2]);

	tempR = 5;
	glBegin(GL_POLYGON);
	for (int i = 0; i <= N; i++) {
		tempX = tempR * cos(2 * PI*i / N);
		tempY = tempR * sin(2 * PI*i / N) + 23;
		glVertex3f(tempX + x, tempY + y, 1.5);
	}
	glEnd();

	glColor3f(ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][1], ColorChoose[LINE_COLOR][2]);
	glLineWidth(1.0);//������ϸ����

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= N; i++) {
		tempX = tempR * cos(2 * PI*i / N);
		tempY = tempR * sin(2 * PI*i / N) + 23;
		glVertex3f(tempX + x, tempY + y, 1.5);
	}
	glEnd();

	glColor3f(ColorChoose[HAT_COLOR][0], ColorChoose[HAT_COLOR][1], ColorChoose[HAT_COLOR][2]);
	glBegin(GL_POLYGON);
	glVertex3f(-18.0 + x, 0.0+ y , 1.5);
	glVertex3f(-18.0 + x, -5.0 + y, 1.5);
	glVertex3f(18.0 + x, -5.0 + y, 1.5);
	glVertex3f(18.0 + x, 0.0 + y, 1.5);
	glEnd();

	glColor3f(ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][1], ColorChoose[LINE_COLOR][2]);
	glLineWidth(1.0);//������ϸ����

	glBegin(GL_LINE_LOOP);
	glVertex3f(-18.0 + x, 0.0 + y, 1.5);
	glVertex3f(-18.0 + x, -5.0 + y, 1.5);
	glVertex3f(18.0 + x, -5.0 + y, 1.5);
	glVertex3f(18.0 + x, 0.0 + y, 1.5);
	glEnd();
}

//��������
void DrawFlag(int x, int y) {
	glLoadIdentity();

	//���Ǵ������ϣ���һ����ת
	if (FLAG_WEARING == TRUE)
		glRotatef(theta, 0.0, 0.0, 1.0);

	//����ѡ�����ŵ�״̬����ͼ���ƶ���ԭ�㣬���ź����ƶ���ԭλ��
	if (SCALE_STATE == TRUE&& SelectPart == FLAG) {
		glTranslatef(x, y, 0.0);
		glScalef(scale, scale, 1);
		glTranslatef(-x, -y, 0.0);
	}
	else {
	}

	glColor3f(ColorChoose[FLAG_COLOR][0], ColorChoose[FLAG_COLOR][1], ColorChoose[FLAG_COLOR][2]);

	glBegin(GL_POLYGON);
	glVertex3f(0.0 + x, 12.0 + y, 2.0);
	glVertex3f(0.0 + x, 24.0 + y, 2.0);
	glVertex3f(15.0 + x, 24.0 + y, 2.0);
	glVertex3f(15.0 + x, 12.0 + y, 2.0);
	glEnd();

	glColor3f(ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][1], ColorChoose[LINE_COLOR][2]);
	glLineWidth(1.0);//������ϸ����

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0 + x, 12.0 + y, 2.0);
	glVertex3f(0.0 + x, 24.0 + y, 2.0);
	glVertex3f(15.0 + x, 24.0 + y, 2.0);
	glVertex3f(15.0 + x, 12.0 + y, 2.0);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(0.0 + x, 0.0 + y, 2.0);
	glVertex3f(0.0 + x, 12.0 + y, 2.0);
	glEnd();

}

//���ƺ���
void myDisplay(void) {
	//glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	//�����ֶ�ջ���г�ʼ��������֤��ջ��������һ��Ԫ��
	glInitNames();
	glPushName(0);

	glLoadName(BODY);
	DrawBody(Body[0], Body[1]);

	//���ƻʹ�
	/*
	glPushMatrix();
	glLoadIdentity();
	glLoadName(CROWN);

	if (CROWN_WEARING == TRUE) {
		//printf("Crown is wearing!\n");
		DrawCrown(0, 108);
	}
	else {
		//printf("Crown is not wearing!\n");
		DrawCrown(Crown[0], Crown[1]);
	}

	glPopMatrix();
	*/

	//����ñ��
	glPushMatrix();
	glLoadIdentity();
	glLoadName(HAT);
	//��������ڴ�����״̬�����ڹ̶�λ�û���
	if (HAT_WEARING == TRUE) {
		//printf("Hat is wearing!\n");
		DrawHat(0, 102);
	}
	//����״̬�������������λ�û���
	else {
		//printf("Hat is not wearing!\n");
		DrawHat(Hat[0], Hat[1]);
	}
	glPopMatrix();

	//��������
	glPushMatrix();
	glLoadIdentity();
	glLoadName(FLAG);
	if (FLAG_WEARING == TRUE) {
		//printf("Flag is wearing!\n");
		DrawFlag(50, 0);
	}
	else {
		//printf("Flag is not wearing!\n");
		DrawFlag(Flag[0], Flag[1]);
	}
	glPopMatrix();
	
	glutSwapBuffers();
}

//������״̬
void ChooseState(GLuint id) {
	switch (id)
	{
	case BODY:
		BODY_STATE = TRUE;
		SelectPart = BODY;
		break;
	case CROWN:
		CROWN_STATE = TRUE;
		SelectPart = CROWN;
		break;
	case HAT:
		HAT_STATE = TRUE;
		SelectPart = HAT;
		break;
	case FLAG:
		FLAG_STATE = TRUE;
		SelectPart = FLAG;
		break;
	case 0:
		BODY_STATE = FALSE;
		CROWN_STATE = FALSE;
		HAT_STATE = FALSE;
		SelectPart = 0;
		break;
	default:
		break;
	}
}

//����ѡ������������ʱ����
#define BUFFER_LENGTH 64//���建������С
void ChooseProcess(int x, int y) {
	GLfloat Times;
	//������������ӿڴ洢
	GLint hits, viewport[4];

	//ѡ�񻺳����ռ�
	static GLuint SelectBuff[BUFFER_LENGTH];

	//����ѡ�񻺳���
	glSelectBuffer(BUFFER_LENGTH, SelectBuff);

	//����ӿ�(0,0,800,600)��ʼ��������ӿڴ�С
	glGetIntegerv(GL_VIEWPORT, viewport);

	/*for (int i = 0; i < 4; i++) {
		printf("%d \n", viewport[i]);
	}*/

	//�л���ͶӰģʽ�����������
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	//�޸���Ⱦģʽ����Ϊѡ��ģʽ
	glRenderMode(GL_SELECT);

	//Χ�������㣨x,y�������µĵ�λ������ü����򣬲��ڴ�ֱ��ˮƽ������չ2������
	glLoadIdentity();
	gluPickMatrix(x, viewport[3] - y, 2, 2, viewport);

	//�����ӿڴ�С������������Ĵ�С
	Times = (float)viewport[2] / (float)viewport[3];
	if (viewport[2] <= viewport[3]) {
		glOrtho(-VIEWSIZE, VIEWSIZE, -VIEWSIZE * Times, VIEWSIZE * Times, -VIEWSIZE, VIEWSIZE);
	}
	else {
		glOrtho(-VIEWSIZE * Times, VIEWSIZE * Times, -VIEWSIZE, VIEWSIZE, -VIEWSIZE, VIEWSIZE);
	}

	//���Ƴ���
	myDisplay();

	//�ռ������¼
	hits = glRenderMode(GL_RENDER);

	//printf("1> Hits is %d\n", hits);

	//�������е�����4��Ϊһ�飬�ֱ��¼��
	//���ֶ�ջ��������
	//���������ڰ��������ж������С������z���꣬��Χ��[0-1]�����ᱻ���䵽�޷�����������󳤶�
	//���ֶ�ջ�ĵײ�
	if (hits > 0) {
		int Choose = SelectBuff[3];
		int depth = SelectBuff[1];
		//printf("2> SelectBuffer[3] is %d\n", Choose);
		//printf("2> SelectBuffer[1] is %d\n", depth);

		//���������е����ݣ�ѡ����Ƚ�С��ͼԪ
		for (int loop = 1; loop < hits; loop++) {
			if (SelectBuff[loop * 4 + 1] < GLuint(depth)) {
				Choose = SelectBuff[loop * 4 + 3];
				depth = SelectBuff[loop * 4 + 1];
			}
			//printf(">3 Choose is %d depth is  %d \n", Choose, depth);
		}
		//printf(">3 Hits is %d Choose is %d \n", hits, Choose);
		ChooseState(GLuint(Choose));//����ѡ���ͼԪ���ı�����״̬
	}

	//�����Ϊ0��˵�����е��ǿհײ��֣���������״̬
	if (hits == 0) {
		ChooseState(0);
	}

	/*printf("\n show buffer\n");
	for (int i = 0; i < BUFFER_LENGTH; i++) {
		printf("SelectBuffer[%d] is %d  ", i, SelectBuff[i]);
		if (i % 5 == 0)
			printf("\n");
	}
	printf("\n");*/

	//�ָ�ͶӰ����
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	//�ָ���ģ����ͼ
	glMatrixMode(GL_MODELVIEW);
}

//���ڴ�С�ı�ʱ���õĺ���
void ChangeSize(int w, int h) {
	GLfloat Times;
	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);
	Times = (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//���ݴ��ڴ�С������������Ĵ�С
	if (w <= h) {
		glOrtho(-VIEWSIZE, VIEWSIZE, -VIEWSIZE / Times, VIEWSIZE / Times, -VIEWSIZE, VIEWSIZE);
	}
	else {
		glOrtho(-VIEWSIZE * Times, VIEWSIZE * Times, -VIEWSIZE, VIEWSIZE, -VIEWSIZE, VIEWSIZE);
	}

	printf("WindowSize changed , now VIEWSIZE is %d \n", VIEWSIZE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
}

//�����Ӧ����
void MouseCallBack(int button, int state, int x, int y) {

	GLint viewport[4];
	GLfloat Times;
	glGetIntegerv(GL_VIEWPORT, viewport);
	Times = (float)viewport[2] / (float)viewport[3];

	//���ʵ��λ��ת��������ϵ����
	int xnow, ynow;

	if (viewport[2] <= viewport[3])
	{
		xnow = -VIEWSIZE + 2 * VIEWSIZE * x / viewport[2];
		ynow = -VIEWSIZE * Times + (viewport[3] - y) * 2 * VIEWSIZE * Times / viewport[3];
	}
	else
	{
		xnow = -VIEWSIZE * Times + 2 * VIEWSIZE * Times*x / viewport[2];
		ynow = -VIEWSIZE + (viewport[3] - y) * 2 * VIEWSIZE / viewport[3];
	}

	//��갴��ʱ����ѡ�ж�����в���
	if (button == GLUT_LEFT_BUTTON&&state == GLUT_DOWN) {
		ChooseProcess(x, y);
		CROWN_WEARING == FALSE;
		HAT_WEARING == FALSE;
		FLAG_WEARING == FALSE;
		//printf("\n mouse is down! \n");
	}
	
	//�ʹ�λ���ж�
	if (button == GLUT_LEFT_BUTTON&&state == GLUT_UP&&CROWN_STATE == TRUE) {
		//printf("Loop1 success!");
		if (xnow > -10 && xnow < 10 && ynow>105 && ynow < 112) {
			CROWN_WEARING = TRUE;
		}
		else {
			CROWN_WEARING = FALSE;
		}
		glutPostRedisplay();
		myDisplay();
	}

	//ñ��λ���ж�
	if (button == GLUT_LEFT_BUTTON&&state == GLUT_UP&&HAT_STATE == TRUE) {
		//printf("Loop1 success!");
		if (xnow > -15 && xnow < 15 && ynow>103 && ynow < 115) {
			HAT_WEARING = TRUE;
		}
		else {
			HAT_WEARING = FALSE;
		}
		glutPostRedisplay();
		myDisplay();
	}

	//����λ���ж�
	if (button == GLUT_LEFT_BUTTON&&state == GLUT_UP&&FLAG_STATE == TRUE) {
		//printf("Loop1 success!");
		if (xnow > 40 && xnow < 60 && ynow>-10 && ynow < 10) {
			FLAG_WEARING = TRUE;
		}
		else {
			FLAG_WEARING = FALSE;
		}
		glutPostRedisplay();
		myDisplay();
	}

	//���̧��ʱ��������״̬��λ
	if (button == GLUT_LEFT_BUTTON&&state == GLUT_UP) {
		printf("Mouse released on ( %d , %d ) \n", xnow, ynow);
		BODY_STATE = FALSE;
		CROWN_STATE = FALSE;
		HAT_STATE = FALSE;
		FLAG_STATE = FALSE;

		//printf("Loop2 success!");
		glutPostRedisplay();
		myDisplay();
	}
}

//����ƶ���Ӧ����
void MouseMoveCallBack(int x, int y) {

	CROWN_WEARING == FALSE;
	HAT_WEARING == FALSE;

	GLint viewport[4];
	GLfloat Times;
	glGetIntegerv(GL_VIEWPORT, viewport);
	Times = (float)viewport[2] / (float)viewport[3];


	//��ȡ��ǰ���λ��
	/*int xnow, ynow;

	if (viewport[2] <= viewport[3])
	{
		xnow = -VIEWSIZE + 2 * VIEWSIZE * x / viewport[2];
		ynow = -VIEWSIZE * Times + (viewport[3] - y) * 2 * VIEWSIZE * Times / viewport[3];
	}
	else
	{
		xnow = -VIEWSIZE * Times + 2 * VIEWSIZE * Times*x / viewport[2];
		ynow = -VIEWSIZE + (viewport[3] - y) * 2 * VIEWSIZE / viewport[3];
	}
	printf("Now Mouse is on ( %d , %d ) \n", xnow, ynow);*/

	//�����ʵ������ת��Ϊ����ϵ����
	//������굱ǰ����λ�ã�������ͼ�ε�ԭ����Ϊ���λ��
	if (CROWN_STATE == TRUE)
	{
		if (viewport[2] <= viewport[3])
		{
			Crown[0] = -VIEWSIZE + 2 * VIEWSIZE * x / viewport[2];
			Crown[1] = -VIEWSIZE * Times + (viewport[3] - y) * 2 * VIEWSIZE * Times / viewport[3];
		}
		else
		{
			Crown[0] = -VIEWSIZE * Times + 2 * VIEWSIZE * Times*x / viewport[2];
			Crown[1] = -VIEWSIZE + (viewport[3] - y) * 2 * VIEWSIZE / viewport[3];
		}

		//printf("Now Mouse is on ( %d , %d ) \n", Crown[0], Crown[1]);

		//�ƶ���ָ��λ�ã��ı�״̬Ϊwearing
		if (Crown[0] > -10 && Crown[0] < 10 && Crown[1]>105 && Crown[1] < 112) {
			CROWN_WEARING = TRUE;
		}
		else {
			CROWN_WEARING = FALSE;
		}

		myDisplay();
	}

	if (HAT_STATE == TRUE)
	{
		if (viewport[2] <= viewport[3])
		{
			Hat[0] = -VIEWSIZE + 2 * VIEWSIZE * x / viewport[2];
			Hat[1] = -VIEWSIZE * Times + (viewport[3] - y) * 2 * VIEWSIZE * Times / viewport[3];
		}
		else
		{
			Hat[0] = -VIEWSIZE * Times + 2 * VIEWSIZE * Times*x / viewport[2];
			Hat[1] = -VIEWSIZE + (viewport[3] - y) * 2 * VIEWSIZE / viewport[3];
		}

		//printf("Now Mouse is on ( %d , %d ) \n", Crown[0], Crown[1]);

		//�ƶ���ָ��λ�ã��ı�״̬Ϊwearing
		if (Hat[0] > -15 && Hat[0] < 15 && Hat[1]>103 && Hat[1] < 115) {
			HAT_WEARING = TRUE;
		}
		else {
			HAT_WEARING = FALSE;
		}

		myDisplay();
	}

	if (FLAG_STATE == TRUE)
	{
		if (viewport[2] <= viewport[3])
		{
			Flag[0] = -VIEWSIZE + 2 * VIEWSIZE * x / viewport[2];
			Flag[1] = -VIEWSIZE * Times + (viewport[3] - y) * 2 * VIEWSIZE * Times / viewport[3];
		}
		else
		{
			Flag[0] = -VIEWSIZE * Times + 2 * VIEWSIZE * Times*x / viewport[2];
			Flag[1] = -VIEWSIZE + (viewport[3] - y) * 2 * VIEWSIZE / viewport[3];
		}

		//printf("Now Mouse is on ( %d , %d ) \n", Crown[0], Crown[1]);

		//�ƶ���ָ��λ�ã��ı�״̬Ϊwearing
		if (Flag[0] > 40 && Flag[0] < 60 && Flag[1]>-10 && Flag[1] < 10) {
			FLAG_WEARING = TRUE;
		}
		else {
			FLAG_WEARING = FALSE;
		}

		myDisplay();
	}
}

//������Ӧ����
void myKeyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'z':
		SCALE_STATE = TRUE;
		scale += 1;
		if (scale == 4)
			scale = 1;
		glutPostRedisplay();
		myDisplay();
		//SCALE_STATE = FALSE;
		break;
	default:
		break;
	}
}

//���̷������Ӧ�����ݰ��µķ�������в���
void mySpecial(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_UP:
		theta = (theta + 10);
		glutPostRedisplay();
		myDisplay();
		break;

	case GLUT_KEY_DOWN:
		theta = (theta - 10);
		glutPostRedisplay();
		myDisplay();
		break;

	default:
		break;
	}
}

//��ʼ��
void MainInit() {
	BODY_STATE = FALSE;
	CROWN_STATE = FALSE;
	HAT_STATE = FALSE;
	FLAG_STATE = FALSE;

	CROWN_WEARING = FALSE;
	HAT_WEARING = FALSE;
	FLAG_WEARING = FALSE;

	/*
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
}

//�˵�
void myMenu(int index) {
	//����ѡ���趨��ǰѡ��ͼԪ����ɫ
	switch (SelectPart)
	{
	case CROWN:
		CROWN_COLOR = index;
		break;
	case HAT:
		HAT_COLOR = index;
		break;
	case FLAG:
		FLAG_COLOR = index;
		break;
	default:
		break;
	}
	//���λ��Ʒ���˸
	glutPostRedisplay();
	myDisplay();
}

//������
int main(int argc,char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(800, 600);
	glutCreateWindow("GCExp1");

	MainInit();

	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(myDisplay);

	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecial);
	glutMouseFunc(MouseCallBack);
	glutMotionFunc(MouseMoveCallBack);

	//�����Ҽ��˵�
	glutCreateMenu(myMenu);
	glutAddMenuEntry("balck", 0);//��һ�������ǲ˵�����ʾ���ı����ڶ��������Ǵ��ݸ�menu������ֵ
	glutAddMenuEntry("red", 1);
	glutAddMenuEntry("green", 2);
	glutAddMenuEntry("blue", 3);
	glutAddMenuEntry("cyan", 4);
	glutAddMenuEntry("purple", 5);
	glutAddMenuEntry("yellow", 6);
	glutAddMenuEntry("white", 7);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();

    return 0;
}