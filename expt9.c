#include<stdlib.h>
#include<stdio.h>
#include<GL/glut.h>

float x1,x2,x3,x4,Y1,y2,y3,y4;

void edge_detect(float x1,float Y1,float x2,float y2,int* le,int* re)
{
	float x,temp;
	int y;
	if((y2-Y1)<0)
	{
		temp=Y1; Y1=y2; y2=temp;
		temp=x1; x1=x2; x2=temp;
	}
	for(y=Y1;y<y2;y++)
	{
		x=x1+((y-Y1)*(x2-x1)/(y2-Y1));
		if(x<le[y])
			le[y]=x;
		if(x>re[y])
			re[y]=x;
	}
}

void scanfillarea(float x1,float Y1,float x2,float y2,float x3,float y3,float x4,float y4)
{
	int le[500],re[500];
	int i,y;
	for(i=0;i<500;i++)
	{
		le[i]=500;
		re[i]=0;
	}
	edge_detect(x1,Y1,x2,y2,le,re);
	edge_detect(x2,y2,x3,y3,le,re);
	edge_detect(x3,y3,x4,y4,le,re);
	edge_detect(x4,y4,x1,Y1,le,re);
	
	for(y=0;y<500;y++)
	{
		if(le[y]<=re[y])
		{
			for(i=le[y];i<=re[y];i++)
			{
				glColor3f(1.0,0.0,0.0);
				glBegin(GL_POINTS);
					glVertex2i(i,y);
				glEnd();
			}
		}
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(x1,Y1);
		glVertex2f(x2,y2);
		glVertex2f(x3,y3);
		glVertex2f(x4,y4);
	glEnd();
	scanfillarea(x1,Y1,x2,y2,x3,y3,x4,y4);
	glFlush();
}

void myInit()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,499.0,0.0,499.0);
}

int main(int argc,char** argv)
{
	printf("enter four vertices of polygon: ");
	scanf("%f%f%f%f%f%f%f%f",&x1,&Y1,&x2,&y2,&x3,&y3,&x4,&y4);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("scan line area fill algorithm");
	glutDisplayFunc(display);
	myInit();
	glutMainLoop();
}
	
	
