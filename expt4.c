#include<stdio.h>
#include<GL/glut.h>

GLfloat vertices[]={-1.0,-1.0,-1.0,
			1.0,-1.0,-1.0,
			1.0,1.0,-1.0,
			-1.0,1.0,-1.0,
			-1.0,-1.0,1.0,
			1.0,-1.0,1.0,
			1.0,1.0,1.0,
			-1.0,1.0,1.0};
GLfloat colors[]={0.0,0.0,0.0,
		  0.0,0.0,1.0,
		  0.0,1.0,0.0,
		  0.0,1.0,1.0,
		  1.0,0.0,0.0,
		  1.0,0.0,1.0,
		  1.0,1.0,0.0,
		  1.0,1.0,1.0};
GLubyte cubeindices[]={0,1,2,3,1,2,6,5,4,5,6,7,0,4,7,3,2,3,7,6,0,1,5,5};
static GLdouble viewer[]={0.0,0.0,5.0};

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewer[0],viewer[1],viewer[2],0.0,0.0,0.0,0.0,1.0,0.0);
	glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,cubeindices);
	glutSwapBuffers();
}

void keys(unsigned char key,int x,int y)
{
	if(key=='x') viewer[0]-=1.0;
	if(key=='X') viewer[0]+=1.0;
	if(key=='y') viewer[1]-=1.0;
	if(key=='Y') viewer[1]+=1.0;
	if(key=='z') viewer[2]-=1.0;
	if(key=='Z') viewer[2]+=1.0;
	glutPostRedisplay();
}

void myreshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<h)
		glFrustum(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w,2.0*(GLfloat)h/(GLfloat)w,2.0,20.0);
	else
		glFrustum(-2.0*(GLfloat)w/(GLfloat)h,2.0*(GLfloat)w/(GLfloat)h,-2.0,2.0,2.0,20.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize(500,500);
	glutCreateWindow("PRESPECTIVE VIEWING");
	glutReshapeFunc(myreshape);
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	glutKeyboardFunc(keys);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,vertices);
	glColorPointer(3,GL_FLOAT,0,colors);
	glutMainLoop();
}
	






