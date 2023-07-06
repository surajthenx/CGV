#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#define pi 3.142

float theta=0;
typedef struct w3
{
	GLfloat x,y,z;
}w3;
void bino(GLint n,GLint *c)
{
	GLint k,j;
	for(k=0;k<=n;k++)
	{
		c[k]=1;
		for(j=n;j>=k+1;j--)
		{
			c[k] *= j;
		}
		for(j=n-k;j>=1;j--)
		{
			c[k] /= j;
		}
	}
}

void computeBezPt(GLfloat u,w3 *bezPt,GLint ncp,w3 *cp,GLint *c)
{
	GLint k,n=ncp-1;
	GLfloat bezBlendFcn;
	bezPt->x=bezPt->y=bezPt->z=0.0;
	for(k=0;k<ncp;k++)
	{
		bezBlendFcn = c[k]*pow(u,k)*pow(1-u,n-k);
		bezPt->x+=cp[k].x*bezBlendFcn;
		bezPt->y+=cp[k].y*bezBlendFcn;
		bezPt->z+=cp[k].z*bezBlendFcn;
	}
}

void bezier(w3 *cp,GLint ncp,GLint nbezCurvePts)
{
	w3 bezCurvePt;
	GLfloat u;
	GLint *c,k;
	c=new GLint[ncp];
	bino(ncp-1,c);
	glBegin(GL_LINE_STRIP);
		for(k=0;k<nbezCurvePts;k++)
		{
			u=GLfloat(k)/GLfloat(nbezCurvePts);
			computeBezPt(u,&bezCurvePt,ncp,cp,c);
			glVertex2f(bezCurvePt.x,bezCurvePt.y);
		}
	glEnd();
	delete[] c;
}

void display()
{
	GLint ncp=4,nbezCurvePts=20;
	w3 cp[4]={{20,100,0},{30,110,0},{50,90,0},{60,100,0}};
	cp[1].x += 10*sin(theta*pi/180.0);
	cp[1].y += 5*sin(theta*pi/180.0);
	cp[2].x += 10*sin((theta+30)*pi/180.0);
	cp[2].y -= 10*sin((theta+30)*pi/180.0);
	cp[3].x -= 4*sin((theta)*pi/180.0);
	cp[3].y += sin((theta-30)*pi/180.0);
	theta += 1.0;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
	
	glPushMatrix();
	glLineWidth(5);
	glColor3f(255/255.0,153/255.0,51/255.0);
	for(int i=0;i<8;i++)
	{
		glTranslated(0, -0.8, 0);
		bezier(cp,ncp,nbezCurvePts);
	}
	
	glColor3f(1.0, 1.0, 1.0);
	for(int i=0;i<8;i++)
	{
		glTranslated(0, -0.8, 0);
		bezier(cp,ncp,nbezCurvePts);
	}
	
	glColor3f(19/255.0,136/255.0,8/255.0);
	for(int i=0;i<8;i++)
	{
		glTranslated(0, -0.8, 0);
		bezier(cp,ncp,nbezCurvePts);
	}
	
	glPopMatrix();
	glColor3f(0.7, 0.5, 0.3);
	glLineWidth(5);
	glBegin(GL_LINES);
		glVertex2f(20,100);
		glVertex2f(20,40);
	glEnd();
	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 130, 0, 130);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Bezier curve");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
}
	
		
