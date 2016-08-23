#include<stdlib.h>
#include<GL/glut.h>
 #include<math.h>
#include<GL/GLAux.h>
#include"Vector.h"
#include<stdio.h>;
#include<iostream>
using namespace std;

GLfloat gXAngle, gYAngle, gZAngle;//������Ʈ ���� ���� ����
static GLfloat angle;//���̺� ��Ź�� ȸ����ų�� ���� �� 
int count = 1;
float Delta = 0;

const GLfloat red[]={0.8,0.0,0.0,1.0};
const GLfloat green[]={0.0,1.0,0.0,1.0};
const GLfloat white[]={1.0,1.0,1.0,1.0};
const GLfloat lightPos[]={50,100.0,30.0,1.0};
const GLfloat brass_amb[]={0.33,0.22,0.03,1.0};
const GLfloat brass_diff[]={0.78,0.57,0.11,1.0};
const GLfloat brass_diff2[] = {0.2, 0.8, 1.11 , 1.0};
const GLfloat brass_spec[]={0.99,0.91,0.81,1.0};
const GLfloat brass_shine[]={20.8};
const GLfloat brass_diff8[] = {15.78, 1.0, 1.00 , 1.0}; 
const GLfloat brass_diff3[] = {0.2, 0.4, 0.2 , 1.0}; 
const GLfloat brass_diff4[] = {0.5, 1, 0 , 1.0}; 

const GLfloat brass_diff5[] = {1, 0.5, 0.1 , 1.0}; 

const GLfloat brass_diff6[] = {3, 1.5, 1 , 1.0}; 
const GLfloat brass_diff7[] = {2, 1, 1 , 1.0}; 



 GLfloat MyVertex[][3] = {
 	{ -0.25, -0.25, 0.25 },//v0
 	{ -0.25, 0.25, 0.25 },//v1
 	{ 0.25, 0.25, 0.25 },//v2
 	{ 0.25, -0.25, 0.25 },//v3
 	{ -0.25, -0.25, -0.25 },//v4
 	{ -0.25, 0.25, -0.25 },//v5
 	{ 0.25, 0.25, -0.25 },//v6
 	{ 0.25, -0.25, -0.25 },//v7
 
 };//�ٸ��׸��µ� ��ǥ
GLubyte MyQuadList[] = { 0, 3, 2, 1, 2, 3, 7, 6, 0, 4, 7, 3, 1, 2, 6, 5, 4, 5, 6, 7, 0, 1, 5, 4 };//Ź�ڱ׸��µ� ���̴¸���Ʈ��


GLfloat MyTable[][3] = {

	{ -0.25, 0.25, 0.25 },//v0
	{ 0.25, 0.25, 0.25 },//v1
	{ 0.5, 0.25, 0.0 },//v2
	{ 0.25, 0.25, -0.25 },//v3
	{ -0.25, 0.25, -0.25 },//v4
	{ -0.5, 0.25, 0.0 },//v5
	{ -0.25, -0.25, 0.25 },//6
	{ 0.25, -0.25, 0.25 },//v7
	{ 0.5, -0.25, 0.0 },//v8
	{ 0.25, -0.25, -0.25 },//v9
	{ -0.25, -0.25, -0.25 },//v10
	{ -0.5, -0.25, 0.0 }//v11

};//���̺�׸��µ� ��ǥ 
GLubyte MyTableQuad[] = { 0, 6, 7, 1, 2, 1, 7, 8, 3, 2, 8, 9, 4, 3, 9, 10, 5, 4, 10, 11, 0, 5, 11, 6 };//���� ���� ����
GLuint MyTableQUad2[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };//���� �Ʒ� �� ����
VECTOR normal1[6];//���̺� ���� ���Ͱ� 
VECTOR legNormal[6];//�ٸ����Ͱ� ����


const double ToRadian = 3.141592 / 180.0;//���Ȱ�
float lineData[200][3];//����� ���
float circleData[200][3];//����� ��
GLubyte MyCylinderQuad[]={1,3,2,0,3,5,4,2,5,7,6,4,7,9,8,6,9,11,10,8,11,13,12,10,13,15,14,12,15,17,16,14,17,19,18,16,19,21,20,18,21,23,22,20,23,25,24,22,25,27,26,24,27,29,28,26,29,31,36,28,31,33,32,30,33,35,34,32,35,1,0,34};
VECTOR cylinderNormal[18];
float radius = 0.5;//����� �׸��µ� ������
int k = 0;
int l = 0;



float dishpoints[][2]={{0.3,0.0},{0.2,0.35},{0.5,0.5},{0.6,0.33}};//���ñ׸��µ� �ʱ���ǥ

GLfloat dishData[760][3];//���ð� ��ǥ�ֱ�
float dishNormal2[760][3];//���ð� �����ֱ� 
int c,e,d;

float oneTwo[3], oneThree[3], dishVector[3], dishNormalize[3];//���� ���Ͱ� ���������� 
float dish1[3], dish2[3], dish3[3];

void ver(int x, int y, int z, GLfloat A[3][3])//VECTOR �� ���� �ʰ� �������Ѵ¹� 
{
   dish1[0] = A[x][0]; dish1[1] = A[x][1]; dish1[2] = A[x][2];
   dish2[0] = A[y][0]; dish2[1] = A[y][1]; dish2[2] = A[y][2];
   dish3[0] = A[z][0]; dish3[1] = A[z][1]; dish3[2] = A[z][2];
}
void VectorFromPoints(float dish1[3], float dish2[3], float vectoroneTwo[3])//�����κ��� ���Ͱ��� ���ϱ����� �Լ� 
{
    vectoroneTwo[0] = dish2[0] - dish1[0];
    vectoroneTwo[1] = dish2[1] - dish1[1];
    vectoroneTwo[2] = dish2[2] - dish1[2];
}

void VectorCrossProduct(float v1[3], float v2[3], float v1Crossv2[3])//���ͷκ��� ������ ���ϱ����� �Լ� 
{

   v1Crossv2[0] = v1[1] * v2[2] - v1[2] * v2[1];
   v1Crossv2[1] = v1[2] * v2[0] - v1[0] * v2[2];
   v1Crossv2[2] = v1[0] * v2[1] - v1[1] * v2[0];

}

void VectorNormalize(float vector[3], float normalizedVector[3])//��������ȭ �����ֱ� ���� �۾� 
{
   float temp;

   temp = sqrt((vector[0] * vector[0]) + (vector[1] * vector[1]) + (vector[2] * vector[2]));

   normalizedVector[0] = vector[0]/temp;
   normalizedVector[1] = vector[1]/temp;
   normalizedVector[2] = vector[2]/temp;
}
GLuint dishQuad[760][4];//���� ���帮��Ʈ ���� ���� 


VECTOR normal4;

void makeTable(){//���̺� ������ִ� �Լ� 
  glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, MyVertex);
	//glMatrixMode(GL_MODELVIEW);
 
 	glPushMatrix();//��ٸ� 1
	glScalef(0.3, 1, 0.3);
	glTranslatef(-1.1, -0.23, 2.0);
 	for (int i = 0; i<6; i++){
		glNormal3f(legNormal[i].x,legNormal[i].y,legNormal[i].z);
 		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyQuadList[4 *i]);
	}
 	glPopMatrix();
 
 	glPushMatrix();//��ٸ� 2
 	glScalef(0.3, 1, 0.3);
 	glTranslatef(1.1, -0.23, 2.0);
 	for (int i = 0; i<6; i++){
		glNormal3f(legNormal[i].x,legNormal[i].y,legNormal[i].z);
 		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyQuadList[4 * i]);
	}
 	glPopMatrix();
 
 	glPushMatrix(); //��ٸ�3
 	glScalef(0.3, 1, 0.3);
 	glTranslatef(1.1, -0.23, -2.0);
 	for (int i = 0; i<6; i++){
		glNormal3f(legNormal[i].x,legNormal[i].y,legNormal[i].z);
 		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyQuadList[4 * i]);
	}
 	glPopMatrix();
 
 	glPushMatrix();//��ٸ�4
 	glScalef(0.3, 1, 0.3);
 	glTranslatef(-1.1, -0.23, -2.0);
 	for (int i = 0; i<6; i++){
		glNormal3f(legNormal[i].x,legNormal[i].y,legNormal[i].z);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyQuadList[4 * i]);
	}
 	glPopMatrix();

	glVertexPointer(3, GL_FLOAT, 0, MyTable);

	glPushMatrix();
	glScalef(1.8, 0.2, 3.2);
	glTranslated(0,0.33,0);
	for (int i = 0; i<6; i++){//���ǿ��� �׷��ֱ� 
	glNormal3f(normal1[i].x,normal1[i].y,normal1[i].z);//���ǿ��鿡���� ���� 
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyTableQuad[4 * i]);
	}
	glPopMatrix();

	glPushMatrix();
	glScalef(1.8, 0.2, 3.2);
	glTranslated(0,0.33,0);
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0,1.25,0);//������������ ����
	glColor3f(0.8,0.3,0.8);
	glVertex3f(0,0.25,0);
	for(int i=0;i<5;i+=1){//���Ǳ׷��ֱ�
		glVertex3fv(MyTable[i]);
		glVertex3fv(MyTable[i+1]);
		
	}
	
	glEnd();
	glBegin(GL_TRIANGLE_FAN);{
		glNormal3f(0,1.25,0);//���� ���ǿ����� ���� 
		glVertex3f(0,0.25,0);
		glVertex3fv(MyTable[5]);//���Ǳ׷��ֱ�
		glVertex3fv(MyTable[0]);

	}
	glEnd();
	
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0,-1.25,0);//���� �Ʒ��鿡���� ����
	glVertex3f(0,-0.25,0);
	for(int i=6;i<12;i++){
		
		glVertex3fv(MyTable[i]);//�Ʒ��� ���Ǳ׷��ֱ�
		glVertex3fv(MyTable[i+1]);
		
	}
	glBegin(GL_TRIANGLE_FAN);{
		glVertex3f(0,0.25,0);
		glVertex3fv(MyTable[11]);
		glVertex3fv(MyTable[6]);

	}
	
	glEnd();
	glPopMatrix();

 }
void MyTableNormal(){//���̺� ���������ֱ� 
	int j=0;
	for(int i=6;i<11;i++){
		VECTOR v1(MyTable[i+1],MyTable[i]);
		VECTOR v2(MyTable[i-6],MyTable[i]);
		Cross_Product(v1,v2,normal1[j]);//�����ϱ� 
		j++;
	}
	VECTOR v1(MyTable[6],MyTable[11]);
	VECTOR v2(MyTable[5],MyTable[11]);
	Cross_Product(v1,v2,normal1[j]);

	for(int i=0;i<6;i++)
		normal1[i].normalizer();//��������ȭ ��Ű�� 
		
}
void LegNormal(){//å��ٸ� ���������ֱ� 
	VECTOR v1(MyVertex[3],MyVertex[0]), v2(MyVertex[1],MyVertex[0]);
	Cross_Product(v1,v2,legNormal[0]);

	VECTOR v3(MyVertex[7],MyVertex[3]), v4(MyVertex[2],MyVertex[3]);
	Cross_Product(v3,v4,legNormal[1]);

	VECTOR v5(MyVertex[3],MyVertex[0]), v6(MyVertex[4],MyVertex[0]);
	Cross_Product(v6,v5,legNormal[2]);

	VECTOR v7(MyVertex[2],MyVertex[1]), v8(MyVertex[5],MyVertex[1]);
	Cross_Product(v7,v8,legNormal[3]);

	VECTOR v9(MyVertex[4],MyVertex[7]), v10(MyVertex[6],MyVertex[7]);
	Cross_Product(v9,v10,legNormal[4]);
	VECTOR v11(MyVertex[0],MyVertex[4]), v12(MyVertex[5],MyVertex[4]);
	Cross_Product(v11,v12,legNormal[5]);

	for(int i=0;i<6;i++)
		legNormal[i].normalizer();
}
void cylinder()//����� �׸���
{
	double phi;
	double y;
	
	for (y = 0.5; y >= -0.5; y -= 1.0)//���׸���
	{
		circleData[k][0] = 0.0;
		circleData[k][1] = y;
		circleData[k][2] = 0.0;

		k++;

		for (phi = 0.0; phi <= 360.0; phi += 20.0)
		{
			double phiR = phi * ToRadian;

			double x = radius * cos(phiR);
			double z = radius * sin(phiR);

			circleData[k][0] = x;
			circleData[k][1] = y;
			circleData[k][2] = z;

			k++;
		}
	}

	for (phi = 0.0; phi <= 360.0; phi += 20.0)//����� �׸���
	{
		double phiR = phi * ToRadian;

		double x = radius * cos(phiR);
		double z = radius * sin(phiR);

		lineData[l][0] = x;
		lineData[l][1] = 0.5;
		lineData[l][2] = z;

		l++;

		lineData[l][0] = x;
		lineData[l][1] = -0.5;
		lineData[l][2] = z;

		l++;
	}

	
}
void drawCylinder(){
	 glScalef(0.3,0.3,0.3);
	 glScalef(4.5,0.5,4.5);
	  glTranslatef(0.0,1.3,0.0);
	 glBegin(GL_TRIANGLE_FAN);
     glNormal3f(0,1.5,0);//����� �������� ����
	
	for (int idx = 0; idx < k / 2; idx++)
		
		glVertex3fv(circleData[idx]);
	
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0,-1.5,0);//����� �Ʒ��� ���� ����
	for (int idx = k / 2; idx < k; idx++)
		
		glVertex3fv(circleData[idx]);

	glEnd();
	
	glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, lineData);
for(int i=0;i<18;i++){
		glNormal3f(cylinderNormal[i].x,cylinderNormal[i].y,cylinderNormal[i].z);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyCylinderQuad[4 * i]);
}


	
 }
void CylinderNormal(){//����� ���鿡 ���� ���� ���ϱ� 
	int j=0;
	for(int i=1;i<=33;i+=2){
		VECTOR v1(lineData[i+2],lineData[i]);
		VECTOR v2(lineData[i-1],lineData[i]);
		Cross_Product(v1,v2,cylinderNormal[j]);
		j++;
	}
	VECTOR v1(lineData[1],lineData[35]);
	VECTOR v2(lineData[34],lineData[35]);
	Cross_Product(v1,v2,cylinderNormal[j]);

	for(int i=0;i<j;i++){
		cylinderNormal[i].normalizer();
		
	}
	
}

void dish(){//���ñ׸���
	double  theta;
	 for(float alpha=0.0f;alpha<=1.0f;alpha+=0.05){
		  float px=(1-alpha)*(1-alpha)*(1-alpha)*dishpoints[0][0]+3*(1-alpha)*(1-alpha)*alpha*dishpoints[1][0]+3*(1-alpha)*alpha*alpha*dishpoints[2][0]+alpha*alpha*alpha*dishpoints[3][0];//������ �����
		float py=(1-alpha)*(1-alpha)*(1-alpha)*dishpoints[0][1]+3*(1-alpha)*(1-alpha)*alpha*dishpoints[1][1]+3*(1-alpha)*alpha*alpha*dishpoints[2][1]+alpha*alpha*alpha*dishpoints[3][1];
		float px1=(1-(alpha+0.05))*(1-(alpha+0.05))*(1-(alpha+0.05))*dishpoints[0][0]+3*(1-(alpha+0.05))*(1-(alpha+0.05))*(alpha+0.05)*dishpoints[1][0]+3*(1-(alpha+0.05))*(alpha+0.05)*(alpha+0.05)*dishpoints[2][0]+(alpha+0.05)*(alpha+0.05)*(alpha+0.05)*dishpoints[3][0];//0.05���� ��(���� ��������)
		float py1=(1-(alpha+0.05))*(1-(alpha+0.05))*(1-(alpha+0.05))*dishpoints[0][1]+3*(1-(alpha+0.05))*(1-(alpha+0.05))*(alpha+0.05)*dishpoints[1][1]+3*(1-(alpha+0.05))*(alpha+0.05)*(alpha+0.05)*dishpoints[2][1]+(alpha+0.05)*(alpha+0.05)*(alpha+0.05)*dishpoints[3][1];
		
		for (theta = -180; theta <= 180.0; theta += 20){
			float radian = ToRadian*theta;
			 dishData[e][0] = px*sin(radian);
             dishData[e][1] = py;
             dishData[e][2] = px*cos(radian);
             e++;
            
            
            dishData[e][0] = px1*sin(radian);
            dishData[e][1] = py1;
            dishData[e][2] = px1*cos(radian);
            e++;

		}cout<<e<<endl;
	 }
	 for(int i=0;i<723;i++){//������ ���尪 ����ֱ� 
		 dishQuad[i][0]=i;
		 dishQuad[i][1]=i+1;
		 dishQuad[i][2]=i+38;
		 dishQuad[i][3]=i+39;
		
	 }

}

 int p=0;
 void drawDish(){//���ñ׷��ֱ� 
	glEnableClientState(GL_VERTEX_ARRAY);
	
	 glVertexPointer(3,GL_FLOAT,0,dishData);

	
	
 for (int i = 0; i<721; i++){ 
	  
	glNormal3f(dishNormal2[i][0],dishNormal2[i][1],dishNormal2[i][2]);//���� ���� 
	 glDrawElements(GL_QUAD_STRIP,4,GL_UNSIGNED_INT,&dishQuad[i]);
	}



 glBegin(GL_TRIANGLE_FAN);//���� �ؿ� �ݱ�
 	 glVertex3f(0,0,0);
	 glNormal3f(0,1,0);//���� �ؿ� ���� 
 for(int i=0; i<40; i+=2) {
	 glVertex3fv(dishData[i]);//���ùعٴ� �׷��ֱ� 
 }

 glEnd();
 }

 void DishNormal(){//���� ��������ֱ� 
	
	
	 for (int i = 0; i < 721; i++)
   {
	   
      ver(i, i + 38, i + 1,dishData);
      VectorFromPoints(dish1, dish2, oneTwo);
      VectorFromPoints(dish1, dish3, oneThree);
      VectorCrossProduct(oneTwo, oneThree, dishVector);
      VectorNormalize(dishVector, dishNormalize);
    
      dishNormal2[i][0] = dishNormalize[0];
       dishNormal2[i][1] = dishNormalize[1];
      dishNormal2[i][2] = dishNormalize[2];

      ver(i + 1, i, i + 39,dishData);
      VectorFromPoints(dish1, dish2, oneTwo);
      VectorFromPoints(dish1, dish3, oneThree);
      VectorCrossProduct(oneTwo, oneThree, dishVector);
      VectorNormalize(dishVector, dishNormalize);
    
      dishNormal2[i][0] += dishNormalize[0];
       dishNormal2[i][1] += dishNormalize[1];
       dishNormal2[i][2] += dishNormalize[2];

      ver(i + 38, i + 39, i,dishData);
      VectorFromPoints(dish1, dish2, oneTwo);
      VectorFromPoints(dish1, dish3, oneThree);
      VectorCrossProduct(oneTwo, oneThree, dishVector);
      VectorNormalize(dishVector, dishNormalize);
     
       dishNormal2[i][0] += dishNormalize[0];
      dishNormal2[i][1] += dishNormalize[1];
      dishNormal2[i][2] += dishNormalize[2];

      ver(i + 39, i + 1, i + 38, dishData);
      VectorFromPoints(dish1, dish2, oneTwo);
      VectorFromPoints(dish1, dish3, oneThree);
      VectorCrossProduct(oneTwo, oneThree, dishVector);
      VectorNormalize(dishVector, dishNormalize);
   ;
       dishNormal2[i][0] += dishNormalize[0];
      dishNormal2[i][1] += dishNormalize[1];
      dishNormal2[i][2] += dishNormalize[2];

       dishNormal2[i][0] / 4.0;
       dishNormal2[i][1] / 4.0;
       dishNormal2[i][2] / 4.0;
   

   }
	
   
 }



void DrawfiveDishes(void)//���� �ټ��� �׸��� 
{
	glPushMatrix();
	glScalef(0.3,1.3,0.3);
	glTranslatef(1.0,0.4,0);
      drawDish();
	  glPopMatrix();


  glPushMatrix();
	glScalef(0.3,1.3,0.3);
	glTranslatef(0.2,0.4,-1.0);
      drawDish();
	  glPopMatrix();



	   glPushMatrix();
	glScalef(0.3,1.3,0.3);
	glTranslatef(-0.9,0.4,-0.4);
      drawDish();
	  glPopMatrix();

	 glPushMatrix();
	  glScalef(0.3,1.3,0.3);
	glTranslatef(-0.6,0.4,0.8);
      drawDish();
	  glPopMatrix();

	  glPushMatrix();
	  glScalef(0.25,1.3,0.25);
	glTranslatef(0.6,0.4,1.2);
      drawDish();
	  glPopMatrix();
	
}

void DrawSolid(){// ���ټ��� �׷��ֱ� 
	 glMaterialfv(GL_FRONT,GL_DIFFUSE,brass_diff5);
	glPushMatrix();
	glScalef(0.5,5,0.5);
	glTranslatef(0.6,0.3,0);
	glutSolidSphere(0.2,200,200);
	glPopMatrix();
	 glMaterialfv(GL_FRONT,GL_DIFFUSE,brass_diff4);
	glPushMatrix();
	glScalef(0.5,5,0.5);
	glTranslatef(-0.55,0.3,-0.28);
	glutSolidSphere(0.2,200,200);
	glPopMatrix();
	 glMaterialfv(GL_FRONT,GL_DIFFUSE,brass_diff2);
	glPushMatrix();
	glScalef(0.5,5,0.5);
	glTranslatef(-0.35,0.3,0.5);
	glutSolidSphere(0.2,200,200);
	glPopMatrix();
	 glMaterialfv(GL_FRONT,GL_DIFFUSE,brass_diff5);
	/*glPushMatrix();

	glScalef(0.5,5,0.5);
	glTranslatef(0.32,0.3,0.6);
	glutSolidSphere(0.2,200,200);
	glPopMatrix();*/
	 glMaterialfv(GL_FRONT,GL_DIFFUSE,brass_diff);
	glPushMatrix();
	glScalef(0.5,5,0.5);
	glTranslatef(0.15,0.3,-0.65);
	glutSolidSphere(0.2,200,200);
	glPopMatrix();
	
}



 
void myDisplay(){ 
 glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 glColor3f(1.0,0.0,0.0);
 glLoadIdentity();
 glRotatef(gXAngle, 1.0, 0.0, 0.0);//Ű���� ���������� ������Ʈ ���� �ٲ� 
 glRotatef(gYAngle, 0.0, 1.0, 0.0);
 glRotatef(gZAngle, 0.0, 0.0, 1.0);
 glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
 glMaterialfv(GL_FRONT,GL_DIFFUSE,brass_diff);
 glLightfv(GL_LIGHT7,GL_DIFFUSE,red);
 makeTable();//���̺� ����� 
 glRotatef(angle, 0, angle,0);//����� ȸ���� ���Ѱ� 
 
 drawCylinder();//����� �׷��ֱ� 
  
glMaterialfv(GL_FRONT,GL_DIFFUSE,brass_diff3);//�������� 
 DrawfiveDishes();//���ñ׷��ֱ� 

 DrawSolid();//���� �׷��ֱ� 


 glFlush();
 glutSwapBuffers();
}
void RotationAngle()
{
   angle += Delta;
   if (angle>360)
   {
      angle = 0;
   }
   myDisplay();
}
 void myMouse(int btn, int state, int x, int y)
{
   if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) count = 1;
   if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) count = 2;
   if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) count = 3;

}
  void gSetPos(int dir)//Ű���� ������ ������Ʈ�� �ٲ� 
{
	switch (dir)
	{
	case 1:
		gYAngle += 10.0f;
		break;
	case 2:
		gYAngle -= 10.0f;
		break;
	case 3:
		gXAngle += 10.0f;
		break;
	case 4:
		gXAngle -= 10.0f;
		break;
	case 5:
		gZAngle += 10.0f;
		break;
	case 6:
		gZAngle -= 10.0f;
		break;
	}
}

  void MyKeyboard(unsigned char KeyPressed, int X, int Y)
{
	//q,w,e,a,s,d �� ������ ���̺� ��ü�� ȸ���� �ȴ� 
	//z�� �����ϱ�
	switch (KeyPressed)
	{
	

	case 'W':
	case 'w':
		gSetPos(1);//y++
		break;
	case 'S':
	case 's':
		gSetPos(2);//y--
		break;
	case 'Q':
	case 'q':
		gSetPos(3);//x++
		break;
	case 'A':
	case 'a':
		gSetPos(4);//x--
		break;
	case 'E':
	case 'e':
		gSetPos(5);//z++
		break;
	case 'd':
	case 'D':
		gSetPos(6);//z--
		break;
	
	}
	
	glutPostRedisplay();//�ٽ� �׷��ֱ�
}
void myKeyboard(int key, int x, int y) {//�����ư�� Ŭ���ϸ� ��Ź�� ȸ���Ѵ� 
  switch (key) {
   case GLUT_KEY_LEFT:
      Delta -= 0.01;
      break;
   case GLUT_KEY_RIGHT:
      Delta += 0.02;
      break;
   case GLUT_KEY_UP:
      Delta += 0.02;
      break;
   case GLUT_KEY_DOWN:
      Delta = 0;
      break;
   }
   
}

void myInit(){
 glClearColor(1.0,1.0,1.0,1.0);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 
 gluPerspective(0.0,1.0,1.0,10.0);
 glMatrixMode(GL_MODELVIEW);
 gluLookAt(0.0,0.0,20.0,0.0,0.0,0.0,0.0,1.0,0.0);
 glLightfv(GL_LIGHT0,GL_DIFFUSE,white);
 glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
 glMaterialfv(GL_FRONT,GL_AMBIENT,brass_amb);
 glMaterialfv(GL_FRONT,GL_SPECULAR,brass_spec);
 glMaterialfv(GL_FRONT,GL_SHININESS,brass_shine);
 
 glEnable(GL_LIGHTING);
 glEnable(GL_LIGHT0);

 glShadeModel(GL_SMOOTH);
 glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv){
 
 glutInit(&argc, argv);
 MyTableNormal();//����������ִ� �Լ��� ���� 
 LegNormal();
 cylinder();
 CylinderNormal();
 dish();
 DishNormal();

 glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB | GLUT_DEPTH);
 glutInitWindowSize(500, 500);
 glutInitWindowPosition(100, 100);
  glutCreateWindow("RotateTable");

 myInit();
 glutSpecialFunc(myKeyboard);
glutKeyboardFunc(MyKeyboard);
 glutDisplayFunc(myDisplay);//display callboneThreek function
  glutIdleFunc(RotationAngle);
	  glutMouseFunc(myMouse);
 glutMainLoop();
 return 0;
}