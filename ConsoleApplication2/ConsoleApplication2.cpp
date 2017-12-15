/***************************
4100056027  �d���s��2���@�~4/9
***************************/

#include "stdafx.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

const double pi = 3.14159265359;
int control[3] = {0};
GLfloat	rotaZ = 0.0;
GLfloat rotaX = 0.0;
GLfloat rotaY = 0.0;
//�ۼgfunction
//�[�iglTranslatef glRotatef
void glMultiDrawElements(GLenum mode,GLsizei* count,GLenum type,GLvoid** indices,GLsizei primcount){
	for(int i = 0;i<primcount;i++){
		glTranslatef (3.0, 0.0, 0.0);
		glPushMatrix();	
		glRotatef((float)rotaY, 0.0, 1.0, 0.0);
		if(count[i]>0){
			glDrawElements(mode,count[i],type,indices[i]);
		}
		glPopMatrix();
	}
}
void glMultiDrawArrays(	GLenum mode,GLint* first,GLsizei* count,GLsizei drawcount){
	for(int i = 0;i<drawcount;i++){
		glTranslatef (3.0, 0.0, 0.0);
		glPushMatrix();	
		glRotatef((float)rotaY, 0.0, 1.0, 0.0);
		if(count[i]>0){
			glDrawArrays(mode,first[i],count[i]);
		}
		glPopMatrix();
	}
}

#define POINTER 1
#define INTERLEAVED 2

#define DRAWARRAY 1
#define DRAWELEMENTS 2
#define MULTIDRAWARRAY 3
#define MULTIDRAWELEMENTS 4
//��l�@�}�l�e����
int setupMethod = POINTER;
int derefMethod = DRAWARRAY;

//�ŧi
static GLuint indices[7][21];								//ø�sglMultiDrawElements�Ϊ��}�C  �]���PEindices�P�\�Φ��O�����Ʀr�|���P
															//�Ʀr���P�O�]���ھ� TOTALintertwined �ӱƦC �ҥH�W�ߥX��
static GLsizei iCounts[7] = {12,8,18,21,10,10,12};			//�U�ӭ^��r�ҥΪ��I�ƥ�

//															E
static GLuint Eindices[12] = {0,1,2,3,4,5,6,7,8,9,10,11};	//�H�U�O�U�ۦr�����ŧi   ���ǬO  vertice -> color -> intertwined
static GLfloat Evertices[] = {
	-0.7,0.15,												//12
	-0.7,-0.15,
	0.7,0.15,
	1,-0.15,
	0.7,0.7,
	1.0,1.0,
	-0.7,0.7,
	-1.0,1.0,
	-0.7,-0.7,
	-1.0,-1.0,
	1.0,-0.7,
	1.0,-1.0
};
static GLfloat Ecolors[] = {
	1.0,0.0,0.0,
	1.0,0.0,0.0,
	1.0,0.0,0.0,
	1.0,0.0,0.0,
	1.0,0.0,0.0,
	1.0,0.0,0.0,
	1.0,0.0,0.0,
	1.0,0.0,0.0,
	1.0,0.0,0.0,
	1.0,0.0,0.0,
	1.0,0.0,0.0,
	1.0,0.0,0.0,
};
static GLfloat Eintertwined[] ={							//�ϥ� C3F_V3F
	1.0,0.0,0.0,-0.7,0.15,0.0,
	1.0,0.0,0.0,-0.7,-0.15,0.0,
	1.0,0.0,0.0,0.7,0.15,0.0,
	1.0,0.0,0.0,1,-0.15,0.0,
	1.0,0.0,0.0,0.7,0.7,0.0,
	1.0,0.0,0.0,1.0,1.0,0.0,
	1.0,0.0,0.0,-0.7,0.7,0.0,
	1.0,0.0,0.0,-1.0,1.0,0.0,
	1.0,0.0,0.0,-0.7,-0.7,0.0,
	1.0,0.0,0.0,-1.0,-1.0,0.0,
	1.0,0.0,0.0,1.0,-0.7,0.0,
	1.0,0.0,0.0,1.0,-1.0,0.0
};

//															C
static GLuint Cindices[] = {0,1,2,3,4,5,6,7};
static GLfloat Cvertices[] = {
	1.5,1.2,												//8
	1.5,1.5,
	-1.2,1.2,
	-1.5,1.5,
	-1.2,-1.2,
	-1.5,-1.5,
	1.5,-1.2,
	1.5,-1.5
};
static GLfloat Ccolors[] = {
	0.0,1.0,0.0,
	0.0,1.0,0.0,
	0.0,1.0,0.0,
	0.0,1.0,0.0,
	0.0,1.0,0.0,
	0.0,1.0,0.0,
	0.0,1.0,0.0,
	0.0,1.0,0.0
};
static GLfloat Cintertwined[] ={
	0.0,1.0,0.0,1.5,1.2,0.0,
	0.0,1.0,0.0,1.5,1.5,0.0,
	0.0,1.0,0.0,-1.2,1.2,0.0,
	0.0,1.0,0.0,-1.5,1.5,0.0,
	0.0,1.0,0.0,-1.2,-1.2,0.0,
	0.0,1.0,0.0,-1.5,-1.5,0.0,
	0.0,1.0,0.0,1.5,-1.2,0.0,
	0.0,1.0,0.0,1.5,-1.5,0.0
};

//															A
GLuint Aindices[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
static GLfloat Avertices[] = {
	-1.0,1.0,												//18
	-1.0,0.7,
	1.0,1.0,
	0.7,0.7,
	1.0,-1.0,
	0.7,-0.7,
	-1.0,-1.0,
	-0.7,-0.7,
	-1.0,0.4,
	-0.7,0.1,
	1.0,0.4,
	0.7,0.1,
	1.3,-0.2,
	1.0,-0.6,
	1.4,-0.5,
	1.3,-1.0,
	1.6,-0.8,
	1.6,-1.0,

};
static GLfloat Acolors[] = {
	0.0,0.0,1.0,
	0.0,0.0,1.0,
	0.0,0.0,1.0,
	0.0,0.0,1.0,
	0.0,0.0,1.0,
	0.0,0.0,1.0,
	0.0,0.0,1.0,
	0.0,0.0,1.0,
	0.0,0.0,1.0,
	0.0,0.0,1.0,
	0.0,0.0,1.0,
	0.0,0.0,1.0,
	0.0,0.0,1.0,
	0.0,0.0,1.0,
	0.0,0.0,1.0,
	0.0,0.0,1.0,
	0.0,0.0,1.0,
	0.0,0.0,1.0
};
static GLfloat Aintertwined[] ={
	0.0,0.0,1.0,-1.0,1.0,0.0,
	0.0,0.0,1.0,-1.0,0.7,0.0,
	0.0,0.0,1.0,1.0,1.0,0.0,
	0.0,0.0,1.0,0.7,0.7,0.0,
	0.0,0.0,1.0,1.0,-1.0,0.0,
	0.0,0.0,1.0,0.7,-0.7,0.0,
	0.0,0.0,1.0,-1.0,-1.0,0.0,
	0.0,0.0,1.0,-0.7,-0.7,0.0,
	0.0,0.0,1.0,-1.0,0.4,0.0,
	0.0,0.0,1.0,-0.7,0.1,0.0,
	0.0,0.0,1.0,1.0,0.4,0.0,
	0.0,0.0,1.0,0.7,0.1,0.0,
	0.0,0.0,1.0,1.3,-0.2,0.0,
	0.0,0.0,1.0,1.0,-0.6,0.0,
	0.0,0.0,1.0,1.4,-0.5,0.0,
	0.0,0.0,1.0,1.3,-1.0,0.0,
	0.0,0.0,1.0,1.6,-0.8,0.0,
	0.0,0.0,1.0,1.6,-1.0,0.0
};

//															M
GLuint Mindices[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
static GLfloat Mvertices[] = {
	-1.0,-1.0,												//  21
	-0.7,-1.0,
	-1.0,0.5,
	-0.7,0.5,
	-0.75,0.75,
	-0.425,0.7,
	-0.425,1.0,
	-0.1,0.75,
	-0.15,0.5,
	0.15,0.5,
	-0.15,-1.0,
	0.15,-1.0,
	0.0,0.5,
	0.1,0.75,
	0.425,1.0,
	0.425,0.7,
	0.75,0.75,
	0.7,0.5,
	1.0,0.5,
	0.7,-1.0,
	1.0,-1.0
};
static GLfloat Mcolors[] = {
	1.0,1.0,1.0,
	1.0,1.0,1.0,
	1.0,1.0,1.0,
	1.0,1.0,1.0,
	1.0,1.0,1.0,
	1.0,1.0,1.0,
	1.0,1.0,1.0,
	1.0,1.0,1.0,
	1.0,1.0,1.0,
	1.0,1.0,1.0,
	1.0,1.0,1.0,
	1.0,1.0,1.0,
	1.0,1.0,1.0,
	1.0,1.0,1.0,
	1.0,1.0,1.0,
	1.0,1.0,1.0,
	1.0,1.0,1.0,
	1.0,1.0,1.0,
	1.0,1.0,1.0,
	1.0,1.0,1.0,
	1.0,1.0,1.0
};
static GLfloat Mintertwined[] ={
	1.0,1.0,1.0,-1.0,-1.0,0.0,
	1.0,1.0,1.0,-0.7,-1.0,0.0,
	1.0,1.0,1.0,-1.0,0.5,0.0,
	1.0,1.0,1.0,-0.7,0.5,0.0,
	1.0,1.0,1.0,-0.75,0.75,0.0,
	1.0,1.0,1.0,-0.425,0.7,0.0,
	1.0,1.0,1.0,-0.425,1.0,0.0,
	1.0,1.0,1.0,-0.1,0.75,0.0,
	1.0,1.0,1.0,-0.15,0.5,0.0,
	1.0,1.0,1.0,0.15,0.5,0.0,
	1.0,1.0,1.0,-0.15,-1.0,0.0,
	1.0,1.0,1.0,0.15,-1.0,0.0,
	1.0,1.0,1.0,0.0,0.5,0.0,
	1.0,1.0,1.0,0.1,0.75,0.0,
	1.0,1.0,1.0,0.425,1.0,0.0,
	1.0,1.0,1.0,0.425,0.7,0.0,
	1.0,1.0,1.0,0.75,0.75,0.0,
	1.0,1.0,1.0,0.7,0.5,0.0,
	1.0,1.0,1.0,1.0,0.5,0.0,
	1.0,1.0,1.0,0.7,-1.0,0.0,
	1.0,1.0,1.0,1.0,-1.0,0.0
};

//															P
GLuint Pindices[] = {0,1,2,3,4,5,6,7,8,9};
static GLfloat Pvertices[] = {
	-1.0,-2.0,												//  10
	-0.7,-2.0,
	-1.0,0.5,
	-0.7,0.2,
	1.0,0.5,
	0.7,0.2,
	1.0,-1.0,
	0.7,-0.7,
	-1.0,-1.0,
	-0.7,-0.7
};
static GLfloat Pcolors[] = {
	1.0,1.0,0.0,
	1.0,1.0,0.0,
	1.0,1.0,0.0,
	1.0,1.0,0.0,
	1.0,1.0,0.0,
	1.0,1.0,0.0,
	1.0,1.0,0.0,
	1.0,1.0,0.0,
	1.0,1.0,0.0,
	1.0,1.0,0.0,
};
static GLfloat Pintertwined[] ={
	1.0,1.0,0.0,-1.0,-2.0,0.0,
	1.0,1.0,0.0,-0.7,-2.0,0.0,
	1.0,1.0,0.0,-1.0,0.5,0.0,
	1.0,1.0,0.0,-0.7,0.2,0.0,
	1.0,1.0,0.0,1.0,0.5,0.0,
	1.0,1.0,0.0,0.7,0.2,0.0,
	1.0,1.0,0.0,1.0,-1.0,0.0,
	1.0,1.0,0.0,0.7,-0.7,0.0,
	1.0,1.0,0.0,-1.0,-1.0,0.0,
	1.0,1.0,0.0,-0.7,-0.7,0.0
};
//															U
GLuint Uindices[] = {0,1,2,3,4,5,6,7,8,9};
static GLfloat Uvertices[] = {
	-1.0,1.0,												//10
	-0.7,1.0,
	-1.0,-0.5,
	-0.7,-0.5,
	0.0,-1.0,
	0.0,-0.7,
	1.0,-0.5,
	0.7,-0.5,
	1.0,1.0,
	0.7,1.0
};
static GLfloat Ucolors[] = {
	1.0,0.5,0.0,
	1.0,0.5,0.0,
	1.0,0.5,0.0,
	1.0,0.5,0.0,
	1.0,0.5,0.0,
	1.0,0.5,0.0,
	1.0,0.5,0.0,
	1.0,0.5,0.0,
	1.0,0.5,0.0,
	1.0,0.5,0.0
};
static GLfloat Uintertwined[] ={
	1.0,0.5,0.0,-1.0,1.0,0.0,
	1.0,0.5,0.0,-0.7,1.0,0.0,
	1.0,0.5,0.0,-1.0,-0.5,0.0,
	1.0,0.5,0.0,-0.7,-0.5,0.0,
	1.0,0.5,0.0,0.0,-1.0,0.0,
	1.0,0.5,0.0,0.0,-0.7,0.0,
	1.0,0.5,0.0,1.0,-0.5,0.0,
	1.0,0.5,0.0,0.7,-0.5,0.0,
	1.0,0.5,0.0,1.0,1.0,0.0,
	1.0,0.5,0.0,0.7,1.0,0.0
};
//															S
GLuint Sindices[] = {0,1,2,3,4,5,6,7,8,9,10,11};
static GLfloat Svertices[] = {
	1.0,0.48,												//12
	0.7,0.335,
	0.0,1.0,
	0.0,0.7,
	-0.7,0.335,
	-0.2,0.335,
	0.2,-0.335,
	0.7,-0.335,
	0.0,-0.7,
	0.0,-1.0,
	-0.7,-0.335,
	-1.0,-0.48
};
static GLfloat Scolors[] = {
	0.5,0.0,0.5,
	0.5,0.0,0.5,
	0.5,0.0,0.5,
	0.5,0.0,0.5,
	0.5,0.0,0.5,
	0.5,0.0,0.5,
	0.5,0.0,0.5,
	0.5,0.0,0.5,
	0.5,0.0,0.5,
	0.5,0.0,0.5,
	0.5,0.0,0.5,
	0.5,0.0,0.5
};
static GLfloat Sintertwined[] ={
	0.5,0.0,0.5,1.0,0.48,0.0,
	0.5,0.0,0.5,0.7,0.335,0.0,
	0.5,0.0,0.5,0.0,1.0,0.0,
	0.5,0.0,0.5,0.0,0.7,0.0,
	0.5,0.0,0.5,-0.7,0.335,0.0,
	0.5,0.0,0.5,-0.2,0.335,0.0,
	0.5,0.0,0.5,0.2,-0.335,0.0,
	0.5,0.0,0.5,0.7,-0.335,0.0,
	0.5,0.0,0.5,0.0,-0.7,0.0,
	0.5,0.0,0.5,0.0,-1.0,0.0,
	0.5,0.0,0.5,-0.7,-0.335,0.0,
	0.5,0.0,0.5,-1.0,-0.48,0.0
};


//�N�����^�媺intertwined��b�@�_
static GLfloat TOTALintertwined[] ={
	////E
	1.0,0.0,0.0,-0.7,0.15,0.0,
	1.0,0.0,0.0,-0.7,-0.15,0.0,
	1.0,0.0,0.0,0.7,0.15,0.0,
	1.0,0.0,0.0,1,-0.15,0.0,
	1.0,0.0,0.0,0.7,0.7,0.0,
	1.0,0.0,0.0,1.0,1.0,0.0,
	1.0,0.0,0.0,-0.7,0.7,0.0,
	1.0,0.0,0.0,-1.0,1.0,0.0,
	1.0,0.0,0.0,-0.7,-0.7,0.0,
	1.0,0.0,0.0,-1.0,-1.0,0.0,
	1.0,0.0,0.0,1.0,-0.7,0.0,
	1.0,0.0,0.0,1.0,-1.0,0.0,
	////C
	0.0,1.0,0.0,1.5,1.2,0.0,
	0.0,1.0,0.0,1.5,1.5,0.0,
	0.0,1.0,0.0,-1.2,1.2,0.0,
	0.0,1.0,0.0,-1.5,1.5,0.0,
	0.0,1.0,0.0,-1.2,-1.2,0.0,
	0.0,1.0,0.0,-1.5,-1.5,0.0,
	0.0,1.0,0.0,1.5,-1.2,0.0,
	0.0,1.0,0.0,1.5,-1.5,0.0,
	////A
	0.0,0.0,1.0,-1.0,1.0,0.0,
	0.0,0.0,1.0,-1.0,0.7,0.0,
	0.0,0.0,1.0,1.0,1.0,0.0,
	0.0,0.0,1.0,0.7,0.7,0.0,
	0.0,0.0,1.0,1.0,-1.0,0.0,
	0.0,0.0,1.0,0.7,-0.7,0.0,
	0.0,0.0,1.0,-1.0,-1.0,0.0,
	0.0,0.0,1.0,-0.7,-0.7,0.0,
	0.0,0.0,1.0,-1.0,0.4,0.0,
	0.0,0.0,1.0,-0.7,0.1,0.0,
	0.0,0.0,1.0,1.0,0.4,0.0,
	0.0,0.0,1.0,0.7,0.1,0.0,
	0.0,0.0,1.0,1.3,-0.2,0.0,
	0.0,0.0,1.0,1.0,-0.6,0.0,
	0.0,0.0,1.0,1.4,-0.5,0.0,
	0.0,0.0,1.0,1.3,-1.0,0.0,
	0.0,0.0,1.0,1.6,-0.8,0.0,
	0.0,0.0,1.0,1.6,-1.0,0.0,
	////M
	1.0,1.0,1.0,-1.0,-1.0,0.0,
	1.0,1.0,1.0,-0.7,-1.0,0.0,
	1.0,1.0,1.0,-1.0,0.5,0.0,
	1.0,1.0,1.0,-0.7,0.5,0.0,
	1.0,1.0,1.0,-0.75,0.75,0.0,
	1.0,1.0,1.0,-0.425,0.7,0.0,
	1.0,1.0,1.0,-0.425,1.0,0.0,
	1.0,1.0,1.0,-0.1,0.75,0.0,
	1.0,1.0,1.0,-0.15,0.5,0.0,
	1.0,1.0,1.0,0.15,0.5,0.0,
	1.0,1.0,1.0,-0.15,-1.0,0.0,
	1.0,1.0,1.0,0.15,-1.0,0.0,
	1.0,1.0,1.0,0.0,0.5,0.0,
	1.0,1.0,1.0,0.1,0.75,0.0,
	1.0,1.0,1.0,0.425,1.0,0.0,
	1.0,1.0,1.0,0.425,0.7,0.0,
	1.0,1.0,1.0,0.75,0.75,0.0,
	1.0,1.0,1.0,0.7,0.5,0.0,
	1.0,1.0,1.0,1.0,0.5,0.0,
	1.0,1.0,1.0,0.7,-1.0,0.0,
	1.0,1.0,1.0,1.0,-1.0,0.0,
	////P
	1.0,1.0,0.0,-1.0,-2.0,0.0,
	1.0,1.0,0.0,-0.7,-2.0,0.0,
	1.0,1.0,0.0,-1.0,0.5,0.0,
	1.0,1.0,0.0,-0.7,0.2,0.0,
	1.0,1.0,0.0,1.0,0.5,0.0,
	1.0,1.0,0.0,0.7,0.2,0.0,
	1.0,1.0,0.0,1.0,-1.0,0.0,
	1.0,1.0,0.0,0.7,-0.7,0.0,
	1.0,1.0,0.0,-1.0,-1.0,0.0,
	1.0,1.0,0.0,-0.7,-0.7,0.0,
	////U
	1.0,0.5,0.0,-1.0,1.0,0.0,
	1.0,0.5,0.0,-0.7,1.0,0.0,
	1.0,0.5,0.0,-1.0,-0.5,0.0,
	1.0,0.5,0.0,-0.7,-0.5,0.0,
	1.0,0.5,0.0,0.0,-1.0,0.0,
	1.0,0.5,0.0,0.0,-0.7,0.0,
	1.0,0.5,0.0,1.0,-0.5,0.0,
	1.0,0.5,0.0,0.7,-0.5,0.0,
	1.0,0.5,0.0,1.0,1.0,0.0,
	1.0,0.5,0.0,0.7,1.0,0.0,
	////S
	0.5,0.0,0.5,1.0,0.48,0.0,
	0.5,0.0,0.5,0.7,0.335,0.0,
	0.5,0.0,0.5,0.0,1.0,0.0,
	0.5,0.0,0.5,0.0,0.7,0.0,
	0.5,0.0,0.5,-0.7,0.335,0.0,
	0.5,0.0,0.5,-0.2,0.335,0.0,
	0.5,0.0,0.5,0.2,-0.335,0.0,
	0.5,0.0,0.5,0.7,-0.335,0.0,
	0.5,0.0,0.5,0.0,-0.7,0.0,
	0.5,0.0,0.5,0.0,-1.0,0.0,
	0.5,0.0,0.5,-0.7,-0.335,0.0,
	0.5,0.0,0.5,-1.0,-0.48,0.0
};

void init(void) 
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);
	glEnableClientState (GL_VERTEX_ARRAY);
	glEnableClientState (GL_COLOR_ARRAY);
}

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef((float)rotaZ, 0.0, 0.0, 1.0);				//��¶�ۥ@�ɥD�b����
	glRotatef((float)rotaX, 1.0, 0.0, 0.0);				//�P�W
	glPushMatrix();
	if (derefMethod == DRAWARRAY){
		glVertexPointer (2, GL_FLOAT, 0, Evertices);	//�]�wvertice����
		glColorPointer (3, GL_FLOAT, 0, Ecolors);		//�]�wcolor����
		glTranslatef (-9.0, 0.0, 0.0);					//���ʦr��
		glPushMatrix();	
		glRotatef((float)rotaY, 0.0, 1.0, 0.0);			//����
		glDrawArrays (GL_TRIANGLE_STRIP, 0, 12);		//ø��
		glPopMatrix();
		//C
		glVertexPointer (2, GL_FLOAT, 0, Cvertices);	//�PE
		glColorPointer (3, GL_FLOAT, 0, Ccolors);
		glTranslatef (3.0, 0.5, 0.0);
		glPushMatrix();
		glRotatef((float)rotaY, 0.0, 1.0, 0.0);
		glDrawArrays (GL_TRIANGLE_STRIP, 0, 8);
		glPopMatrix();
		//A
		glVertexPointer (2, GL_FLOAT, 0, Avertices);	//�PE
		glColorPointer (3, GL_FLOAT, 0, Acolors);
		glTranslatef (3.0, -0.5, 0.0);
		glPushMatrix();
		glRotatef((float)rotaY, 0.0, 1.0, 0.0);
		glDrawArrays (GL_TRIANGLE_STRIP, 0, 18);
		glPopMatrix();
		//M
		glVertexPointer (2, GL_FLOAT, 0, Mvertices);	//�PE
		glColorPointer (3, GL_FLOAT, 0, Mcolors);
		glTranslatef (3.0, 0.0, 0.0);
		glPushMatrix();
		glRotatef((float)rotaY, 0.0, 1.0, 0.0);
		glDrawArrays (GL_TRIANGLE_STRIP, 0, 21);
		glPopMatrix();
		//P
		glVertexPointer (2, GL_FLOAT, 0, Pvertices);	//�PE
		glColorPointer (3, GL_FLOAT, 0, Pcolors);
		glTranslatef (3.0, 0.0, 0.0);
		glPushMatrix();
		glRotatef((float)rotaY, 0.0, 1.0, 0.0);
		glDrawArrays (GL_TRIANGLE_STRIP, 0, 10);
		glPopMatrix();
		//U
		glVertexPointer (2, GL_FLOAT, 0, Uvertices);	//�PE
		glColorPointer (3, GL_FLOAT, 0, Ucolors);
		glTranslatef (3.0, 0.0, 0.0);
		glPushMatrix();
		glRotatef((float)rotaY, 0.0, 1.0, 0.0);
		glDrawArrays (GL_TRIANGLE_STRIP, 0, 10);
		glPopMatrix();
		//S
		glVertexPointer (2, GL_FLOAT, 0, Svertices);	//�PE
		glColorPointer (3, GL_FLOAT, 0, Scolors);
		glTranslatef (3.0, 0.0, 0.0);
		glPushMatrix();
		glRotatef((float)rotaY, 0.0, 1.0, 0.0);
		glDrawArrays (GL_TRIANGLE_STRIP, 0, 12);
		glPopMatrix();

	}else if (derefMethod == DRAWELEMENTS) {
		//E
		glTranslatef (-9.0, 0.0, 0.0);					//���ʦr��
		glPushMatrix();	
		glRotatef((float)rotaY, 0.0, 1.0, 0.0);			//����
		glInterleavedArrays (GL_C3F_V3F, 0, Eintertwined);//�]�w����
		glDrawElements (GL_TRIANGLE_STRIP,12, GL_UNSIGNED_INT, Eindices);//ø��
		glPopMatrix();
		//C
		glTranslatef (3.0, 0.5, 0.0);
		glPushMatrix();
		glRotatef((float)rotaY, 0.0, 1.0, 0.0);
		glInterleavedArrays (GL_C3F_V3F, 0, Cintertwined);
		glDrawElements (GL_TRIANGLE_STRIP,8, GL_UNSIGNED_INT, Cindices);
		glPopMatrix();
		//A
		glTranslatef (3.0, -0.5, 0.0);
		glPushMatrix();
		glRotatef((float)rotaY, 0.0, 1.0, 0.0);
		glInterleavedArrays (GL_C3F_V3F, 0, Aintertwined);
		glDrawElements (GL_TRIANGLE_STRIP,18, GL_UNSIGNED_INT, Aindices);
		glPopMatrix();
		//M
		glTranslatef (3.0, 0.0, 0.0);
		glPushMatrix();
		glRotatef((float)rotaY, 0.0, 1.0, 0.0);
		glInterleavedArrays (GL_C3F_V3F, 0, Mintertwined);
		glDrawElements (GL_TRIANGLE_STRIP,21, GL_UNSIGNED_INT, Mindices);
		glPopMatrix();
		//P
		glTranslatef (3.0, 0.0, 0.0);
		glPushMatrix();
		glRotatef((float)rotaY, 0.0, 1.0, 0.0);
		glInterleavedArrays (GL_C3F_V3F, 0, Pintertwined);
		glDrawElements (GL_TRIANGLE_STRIP,10, GL_UNSIGNED_INT, Pindices);
		glPopMatrix();
		//U
		glTranslatef (3.0, 0.0, 0.0);
		glPushMatrix();
		glRotatef((float)rotaY, 0.0, 1.0, 0.0);
		glInterleavedArrays (GL_C3F_V3F, 0, Uintertwined);
		glDrawElements (GL_TRIANGLE_STRIP,10, GL_UNSIGNED_INT, Uindices);
		glPopMatrix();
		//S
		glTranslatef (3.0, 0.0, 0.0);
		glPushMatrix();
		glRotatef((float)rotaY, 0.0, 1.0, 0.0);
		glInterleavedArrays (GL_C3F_V3F, 0, Sintertwined);
		glDrawElements (GL_TRIANGLE_STRIP, 12, GL_UNSIGNED_INT, Sindices);
		glPopMatrix();

	}else if (derefMethod == MULTIDRAWARRAY) {
		glTranslatef (-12.0, 0.0, 0.0);
		glInterleavedArrays (GL_C3F_V3F, 0, TOTALintertwined);
		GLint index[] = {0,12,20,38,59,69,79,91};
		GLsizei iCounts[]={12,8,18,21,10,10,12};
		glMultiDrawArrays(GL_TRIANGLE_STRIP,index,iCounts,7);
	}else if (derefMethod == MULTIDRAWELEMENTS) {
		//indices����l�Ʀbmain�̭�
		glTranslatef (-12.0, 0.0, 0.0);
		glInterleavedArrays (GL_C3F_V3F, 0, TOTALintertwined);
		static GLvoid * Findices[7] = {indices[0],indices[1],indices[2],indices[3],indices[4],indices[5],indices[6]};
		glMultiDrawElements(GL_TRIANGLE_STRIP,iCounts,GL_UNSIGNED_INT,Findices,7);
	}
	glPopMatrix();
	glutSwapBuffers();
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
    glOrtho(-12.0,12.0,-12.0,12.0,-12.0, 12.0);
}

void mouse (int button,int stat,int x,int y)
{												//����mouse�����O
	if(button == GLUT_RIGHT_BUTTON){			//�k��
		if(stat == GLUT_DOWN){					//click�������
			if(control[2]==0)					//�Y�O��e�S�ʧ@
				control[2] = 1;					//�]control[2]=1 �Ϥ�����
			else control[2] = 0;				//�Y�O���त�A�l������
		}
	}
	if(button == GLUT_MIDDLE_BUTTON){			//����
		if(stat == GLUT_DOWN){					//�P�k��
			if(control[1]==0)
				control[1] = 1;
			else control[1] = 0;
		}
	}
	if(button == GLUT_LEFT_BUTTON){				//����
		if(stat == GLUT_DOWN){					//�P�k��
			if(control[0]==0)
				control[0] = 1;
			else control[0] = 0;
		}
	}
	glutPostRedisplay();						//��s�e��
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
      case 49:
         derefMethod = DRAWARRAY;
		 glutPostRedisplay();
         break;
      case 50:
         derefMethod = DRAWELEMENTS;
		 glutPostRedisplay();
         break;
      case 51:
         derefMethod = MULTIDRAWARRAY;
		 glutPostRedisplay();
         break;
      case 52:
         derefMethod = MULTIDRAWELEMENTS;
		 glutPostRedisplay();
         break;
   }
}
void myIdle(){									//���F���I���ƹ��������۰ʱ���
	if(control[0]==1){							//�̷ӷ�e�ӷƹ��O�_�I���L�P�_�O�_�~�����
		rotaZ += 3.0;					//�Y��0�h����  1�h�~�����
		if(rotaZ>360.0) rotaZ -= 360.0;
	}
	if(control[1]==1){
		rotaY += 6.0;
		if(rotaY>360.0) rotaY -= 360.0;
	}
	if(control[2]==1){
		rotaX += 6.0;
		if(rotaX>360.0) rotaX -= 360.0;
	}
	glutPostRedisplay();
}
int main(int argc, char** argv)
{
	int k = 0;
	for(int i = 0;i<7;i++){
		for(int j = 0;j<iCounts[i];j++){
			indices[i][j] = j+k;
		}
		k+=iCounts[i];
	}

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (480,480); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Second");
	init ();
	glutIdleFunc(myIdle);
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc (keyboard);
	glutMainLoop();
	return 0;
}
