#include<stdio.h>
#include<stdbool.h>
#include<GL/glut.h>

GLfloat xmin=50,ymin=50,xmax=100,ymax=100;
GLfloat x1,Y1,x2,y2;
int RIGHT=8;
int LEFT=2;
int TOP=4;
int BOTTOM=1;

int computeoutcode(GLfloat x, GLfloat y)
{
	int code=0;
	if(y>ymax)
		code=TOP;
	else if(y<ymin)
		code=BOTTOM;
	
	if(x>xmax)
		code=RIGHT;
	else if(x<xmin)
		code=LEFT;
	return code;
}

void CohenSutherland(GLfloat x1, GLfloat Y1, GLfloat x2, GLfloat y2)
{
	int outcode1,outcode2,outcodeout;
	bool accept=false,done=false;
	outcode1=computeoutcode(x1,Y1);
	outcode2=computeoutcode(x2,y2);
	do
	{
		if((outcode1|outcode2)==0)
		{
			accept=true;
			done=true;
		}
		else if((outcode1&outcode2)!=0)
			done=true;
		else
		{
			GLfloat x,y;
			outcodeout = outcode1?outcode1:outcode2;
			if(outcodeout&TOP)
			{
				x=x1+(x2-x1)*(ymax-Y1)/(y2-Y1);
				y=ymax;
			}
			else if(outcodeout&BOTTOM)
			{
				x=x1+(x2-x1)*(ymin-Y1)/(y2-Y1);
				y=ymin;
			}
			else if(outcodeout&RIGHT)
			{
				y=Y1+(y2-Y1)*(xmax-x1)/(x2-x1);
				x=xmax;
			}
			else
			{
				y=Y1+(y2-Y1)*(xmin-x1)/(x2-x1);
				x=xmin;
			}
			if(outcodeout==outcode1)
			{
				x1=x;
				Y1=y;
				outcode1=computeoutcode(x1,Y1);
			}
			else
			{
				x2=x;
				y2=y;
				outcode2=computeoutcode(x2,y2);
			}
		}
	}while(done!=true);
	
	if(accept)
	{
		glBegin(GL_LINES);
			glVertex2d(x1+200,Y1+200);
			glVertex2d(x2+200,y2+200);
			
		glEnd();
	}
}

void display()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(xmin,ymin);
		glVertex2f(xmax,ymin);
		glVertex2f(xmax,ymax);
		glVertex2f(xmin,ymax);
	glEnd();
	
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
		glVertex2d(x1,Y1);
		glVertex2d(x2,y2);
	glEnd();
	
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(xmin+200,ymin+200);
		glVertex2f(xmax+200,ymin+200);
		glVertex2f(xmax+200,ymax+200);
		glVertex2f(xmin+200,ymax+200);
	glEnd();
	
	CohenSutherland(x1,Y1,x2,y2);
	
	glFlush();
}

void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,499.0,0.0,499.0);
}

int main(int argc,char** argv)
{
	printf("Enter the end points of the line:");
	scanf("%f%f%f%f",&x1,&Y1,&x2,&y2);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Cohen Sutherland line clipping");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}
	
							
		
