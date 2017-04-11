// GCExp1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <GL\glut.h>
#include <math.h>

//定义π
#define PI 3.1416

//设定各部分序号
#define BODY 1
#define CROWN 2
#define HAT 3
#define FLAG 4

const int N = 40;//绘制的精细程度

float tempX, tempY;//临时保存坐标
float tempR;//临时保存的半径
float translate;//平移量

static GLfloat theta = 0;//旋转的角度

int SelectPart;//选中的部分
int scale = 1;//点击z键缩放的程度

static int VIEWSIZE = 130;//裁剪坐标系的大小

//各个元素的位置
GLuint Body[2] = { 0,0 };
GLuint Crown[2] = { 110,80 };
GLuint Hat[2] = { 110,30 };
GLuint Flag[2] = { 110,-20 };

//颜色选择器
//黑色、红色、绿色、蓝色、青色、紫色、黄色、白色
static GLfloat ColorChoose[8][3] = {
	{ 0.0, 0.0, 0.0 },{ 1.0, 0.0, 0.0 },{ 0.0, 1.0, 0.0 },{ 0.25, 0.46, 1.0 },
	{ 0.0, 1.0, 1.0 },{ 1.0, 0.0, 1.0 },{ 1.0, 1.0, 0.0 },{ 1.0, 1.0, 1.0 }
};

//设定各部分的颜色
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

//是否选中图元
BOOL BODY_STATE;
BOOL CROWN_STATE;
BOOL HAT_STATE;
BOOL FLAG_STATE;

//是否进行缩放
BOOL SCALE_STATE;

//是否穿戴
BOOL CROWN_WEARING;
BOOL HAT_WEARING;
BOOL FLAG_WEARING;

//绘制身体
void DrawBody(int x, int y) {

	/*
	glEnable(GL_BLEND);//启用颜色混合
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//接受源颜色并将这个颜色（RGB）与alpha值相乘，
													  //然后把这个结果加上目标颜色乘“1减去源颜色的alpha值”的结果
	*/

	//启用防走样
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);

	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	//左胳膊
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

		//描边
		glColor3f(ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][1], ColorChoose[LINE_COLOR][2]);
		glLineWidth(1.0);//线条粗细设置

		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < N; i++) {
			tempX = 20 * cos(2 * PI*i / N);
			tempY = 10 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();
	}

	//左手
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
		glLineWidth(1.0);//线条粗细设置

		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < N; i++) {
			tempX = 8 * cos(2 * PI*i / N);
			tempY = 8 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();
	}

	//右胳膊
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

		glLineWidth(1.0);//线条粗细设置
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < N; i++) {
			tempX = 20 * cos(2 * PI*i / N);
			tempY = 10 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();
	}

	//右手
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
		glLineWidth(1.0);//线条粗细设置

		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < N; i++) {
			tempX = 8 * cos(2 * PI*i / N);
			tempY = 8 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();
	}

	//身体
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

		//描边
		glColor3f(ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][0]);
		glLineWidth(1.0);//线条粗细设置

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

	//项圈
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
		glLineWidth(1.0);//线条粗细设置

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

	//头部
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
		glLineWidth(1.0);//线条粗细设置
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

	//脸
	{
		tempR = 40 * cos(2 * PI * 5 / N) / cos(35.0*PI/180.0);//脸的半径
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

	//肚子
	{
		tempR = 40 * cos(2 * PI * 5 / N) / cos(35.0*PI / 180.0)-5;//肚子的半径
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

		//口袋
		tempR = 18;
		glBegin(GL_POLYGON);
		for (int i = N / 2; i <= N; i++) {
			tempX = tempR * cos(2 * PI*i / N);
			tempY = tempR * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();

		glColor3f(ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][0]);
		glLineWidth(1.0);//线条粗细设置

		glBegin(GL_LINE_LOOP);
		for (int i = N / 2; i <= N; i++) {
			tempX = tempR * cos(2 * PI*i / N);
			tempY = tempR * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();
	}

	//左眼
	{
		tempR = 40 * cos(2 * PI * 5 / N) / cos(35.0*PI / 180.0);//脸的半径
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

		glLineWidth(1.0);//线条粗细设置
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < N; i++) {
			tempX = 6*cos(2 * PI*i / N);
			tempY = 8*sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();
	}

	//左眼眼珠
	{
		tempR = 40 * cos(2 * PI * 5 / N) / cos(35.0*PI / 180.0);//脸的半径
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

	//右眼
	{
		tempR = 40 * cos(2 * PI * 5 / N) / cos(35.0*PI / 180.0);//脸的半径
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

		glLineWidth(1.0);//线条粗细设置
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < N; i++) {
			tempX = 6 * cos(2 * PI*i / N);
			tempY = 8 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();
	}

	//右眼眼珠
	{
		tempR = 40 * cos(2 * PI * 5 / N) / cos(35.0*PI / 180.0);//脸的半径
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

	//鼻子
	{
		tempR = 40 * cos(2 * PI * 5 / N) / cos(35.0*PI / 180.0);//脸的半径
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

	//嘴
	{
		tempR = 40 * cos(2 * PI * 5 / N) / cos(35.0*PI / 180.0);//脸的半径
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
		glLineWidth(1.0);//线条粗细设置
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

	//胡须
	{
		tempR = 40 * cos(2 * PI * 5 / N) / cos(35.0*PI / 180.0);//脸的半径
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

	//左脚
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
		glLineWidth(1.0);//线条粗细设置
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < N; i++) {
			tempX = tempR * cos(2 * PI*i / N);
			tempY = tempR * 0.5 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();
	}

	//右脚
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
		glLineWidth(1.0);//线条粗细设置
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < N; i++) {
			tempX = tempR * cos(2 * PI*i / N);
			tempY = tempR * 0.5 * sin(2 * PI*i / N);
			glVertex2f(tempX, tempY);
		}
		glEnd();
	}

	
}

//绘制皇冠
void DrawCrown(int x, int y) {
	glLoadIdentity();
	
	//若是穿在身上，则一起旋转
	if(CROWN_WEARING==TRUE)
		glRotatef(theta, 0.0, 0.0, 1.0);

	//若是选择缩放的状态，将图形移动到原点，缩放后再移动到原位置
	if (SCALE_STATE == TRUE && SelectPart==CROWN) {
		glTranslatef(x, y, 0.0);
		glScalef(scale, scale, 1);
		glTranslatef(-x, -y, 0.0);
	}
	else {
	}
	
	glColor3f(ColorChoose[CROWN_COLOR][0], ColorChoose[CROWN_COLOR][1], ColorChoose[CROWN_COLOR][2]);
	
	//未加层级设定
	/*glBegin(GL_POLYGON);
	glVertex2f(-10 + x, y - 9);
	glVertex2f(-13 + x, 6 + y);
	glVertex2f(-5 + x, y );
	glVertex2f(0 + x, 12 + y);
	glVertex2f(5 + x, y );
	glVertex2f(13 + x, 6 + y);
	glVertex2f(10 + x, y - 9);
	glEnd();*/

	//将物体z坐标置为1，表示层级在身体之上
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

//绘制帽子
void DrawHat(int x, int y) {
	glLoadIdentity();

	//若是穿在身上，则一起旋转
	if (HAT_WEARING == TRUE)
		glRotatef(theta, 0.0, 0.0, 1.0);

	//若是选择缩放的状态，将图形移动到原点，缩放后再移动到原位置
	if (SCALE_STATE == TRUE && SelectPart == HAT) {
		glTranslatef(x, y, 0.0);
		glScalef(scale, scale, 1);
		glTranslatef(-x, -y, 0.0);
	}
	else {
	}

	glColor3f(ColorChoose[HAT_COLOR][0], ColorChoose[HAT_COLOR][1], ColorChoose[HAT_COLOR][2]);

	//将物体z坐标置为1，表示层级在身体之上
	tempR = 18;
	glBegin(GL_POLYGON);
	for (int i = 0; i <= N/2; i++) {
		tempX = tempR * cos(2 * PI*i / N);
		tempY = tempR * sin(2 * PI*i / N);
		glVertex3f(tempX+x, tempY+y,1.5);
	}
	glEnd();

	glColor3f(ColorChoose[LINE_COLOR][0], ColorChoose[LINE_COLOR][1], ColorChoose[LINE_COLOR][2]);
	glLineWidth(1.0);//线条粗细设置

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
	glLineWidth(1.0);//线条粗细设置

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
	glLineWidth(1.0);//线条粗细设置

	glBegin(GL_LINE_LOOP);
	glVertex3f(-18.0 + x, 0.0 + y, 1.5);
	glVertex3f(-18.0 + x, -5.0 + y, 1.5);
	glVertex3f(18.0 + x, -5.0 + y, 1.5);
	glVertex3f(18.0 + x, 0.0 + y, 1.5);
	glEnd();
}

//绘制旗子
void DrawFlag(int x, int y) {
	glLoadIdentity();

	//若是穿在身上，则一起旋转
	if (FLAG_WEARING == TRUE)
		glRotatef(theta, 0.0, 0.0, 1.0);

	//若是选择缩放的状态，将图形移动到原点，缩放后再移动到原位置
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
	glLineWidth(1.0);//线条粗细设置

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

//绘制函数
void myDisplay(void) {
	//glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	//对名字堆栈进行初始化，并保证堆栈中至少有一个元素
	glInitNames();
	glPushName(0);

	glLoadName(BODY);
	DrawBody(Body[0], Body[1]);

	//绘制皇冠
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

	//绘制帽子
	glPushMatrix();
	glLoadIdentity();
	glLoadName(HAT);
	//如果是正在穿戴的状态，则在固定位置绘制
	if (HAT_WEARING == TRUE) {
		//printf("Hat is wearing!\n");
		DrawHat(0, 102);
	}
	//其它状态，则在鼠标所在位置绘制
	else {
		//printf("Hat is not wearing!\n");
		DrawHat(Hat[0], Hat[1]);
	}
	glPopMatrix();

	//绘制旗子
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

//各部分状态
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

//处理选择，鼠标左键单击时触发
#define BUFFER_LENGTH 64//定义缓冲区大小
void ChooseProcess(int x, int y) {
	GLfloat Times;
	//点击计数器和视口存储
	GLint hits, viewport[4];

	//选择缓冲区空间
	static GLuint SelectBuff[BUFFER_LENGTH];

	//设置选择缓冲区
	glSelectBuffer(BUFFER_LENGTH, SelectBuff);

	//获得视口(0,0,800,600)起始点坐标和视口大小
	glGetIntegerv(GL_VIEWPORT, viewport);

	/*for (int i = 0; i < 4; i++) {
		printf("%d \n", viewport[i]);
	}*/

	//切换到投影模式，并保存矩阵
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	//修改渲染模式，改为选择模式
	glRenderMode(GL_SELECT);

	//围绕鼠标光标点（x,y）建立新的单位立方体裁剪区域，并在垂直和水平方向扩展2个像素
	glLoadIdentity();
	gluPickMatrix(x, viewport[3] - y, 2, 2, viewport);

	//根据视口大小调整裁切区域的大小
	Times = (float)viewport[2] / (float)viewport[3];
	if (viewport[2] <= viewport[3]) {
		glOrtho(-VIEWSIZE, VIEWSIZE, -VIEWSIZE * Times, VIEWSIZE * Times, -VIEWSIZE, VIEWSIZE);
	}
	else {
		glOrtho(-VIEWSIZE * Times, VIEWSIZE * Times, -VIEWSIZE, VIEWSIZE, -VIEWSIZE, VIEWSIZE);
	}

	//绘制场景
	myDisplay();

	//收集点击记录
	hits = glRenderMode(GL_RENDER);

	//printf("1> Hits is %d\n", hits);

	//缓存器中的数据4个为一组，分别记录着
	//名字堆栈的数量，
	//可视区域内包含的所有顶点的最小和最大的z坐标，范围是[0-1]，但会被扩充到无符号整数的最大长度
	//名字堆栈的底部
	if (hits > 0) {
		int Choose = SelectBuff[3];
		int depth = SelectBuff[1];
		//printf("2> SelectBuffer[3] is %d\n", Choose);
		//printf("2> SelectBuffer[1] is %d\n", depth);

		//遍历缓存中的数据，选择深度较小的图元
		for (int loop = 1; loop < hits; loop++) {
			if (SelectBuff[loop * 4 + 1] < GLuint(depth)) {
				Choose = SelectBuff[loop * 4 + 3];
				depth = SelectBuff[loop * 4 + 1];
			}
			//printf(">3 Choose is %d depth is  %d \n", Choose, depth);
		}
		//printf(">3 Hits is %d Choose is %d \n", hits, Choose);
		ChooseState(GLuint(Choose));//根据选择的图元，改变它的状态
	}

	//点击数为0，说明击中的是空白部分，重置所有状态
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

	//恢复投影矩阵
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	//恢复到模型视图
	glMatrixMode(GL_MODELVIEW);
}

//窗口大小改变时调用的函数
void ChangeSize(int w, int h) {
	GLfloat Times;
	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);
	Times = (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//根据窗口大小调整裁切区域的大小
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

//鼠标响应函数
void MouseCallBack(int button, int state, int x, int y) {

	GLint viewport[4];
	GLfloat Times;
	glGetIntegerv(GL_VIEWPORT, viewport);
	Times = (float)viewport[2] / (float)viewport[3];

	//鼠标实际位置转换成坐标系坐标
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

	//鼠标按下时，对选中对象进行操作
	if (button == GLUT_LEFT_BUTTON&&state == GLUT_DOWN) {
		ChooseProcess(x, y);
		CROWN_WEARING == FALSE;
		HAT_WEARING == FALSE;
		FLAG_WEARING == FALSE;
		//printf("\n mouse is down! \n");
	}
	
	//皇冠位置判定
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

	//帽子位置判断
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

	//旗子位置判断
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

	//鼠标抬起时，将所有状态复位
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

//鼠标移动响应函数
void MouseMoveCallBack(int x, int y) {

	CROWN_WEARING == FALSE;
	HAT_WEARING == FALSE;

	GLint viewport[4];
	GLfloat Times;
	glGetIntegerv(GL_VIEWPORT, viewport);
	Times = (float)viewport[2] / (float)viewport[3];


	//获取当前鼠标位置
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

	//将鼠标实际坐标转换为坐标系坐标
	//根据鼠标当前所在位置，将绘制图形的原点设为鼠标位置
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

		//移动到指定位置，改变状态为wearing
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

		//移动到指定位置，改变状态为wearing
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

		//移动到指定位置，改变状态为wearing
		if (Flag[0] > 40 && Flag[0] < 60 && Flag[1]>-10 && Flag[1] < 10) {
			FLAG_WEARING = TRUE;
		}
		else {
			FLAG_WEARING = FALSE;
		}

		myDisplay();
	}
}

//键盘响应函数
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

//键盘方向键响应，根据按下的方向键进行操作
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

//初始化
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

//菜单
void myMenu(int index) {
	//根据选项设定当前选中图元的颜色
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
	//二次绘制防闪烁
	glutPostRedisplay();
	myDisplay();
}

//主函数
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

	//创建右键菜单
	glutCreateMenu(myMenu);
	glutAddMenuEntry("balck", 0);//第一个参数是菜单项显示的文本，第二个参数是传递给menu函数的值
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