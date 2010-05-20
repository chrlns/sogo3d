#include "gui.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <math.h>

float cameraHeigth = 3;
float camDegree = 0;
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };	
GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };


/* --Copy&Paste. */
void reshape(int w, int h) {
  glViewport(0, 0, w, h);       /* Establish viewing area to cover entire window. */
  glMatrixMode(GL_PROJECTION);  /* Start modifying the projection matrix. */
  glLoadIdentity();             /* Reset project matrix. */
  //float wf = w;
  //float hf = h;
  //gluPerspective(60.0,wf/hf,0.01,1000);
   glOrtho(-1,1,-1,1,0.1,100);
//glRotatef(1, 0, 0, 1);
 glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  glEnable( GL_DEPTH_TEST );
  glEnable(GL_LIGHT1);

}

void keyboardFunc(unsigned char key, int mouseX, int mouseY)
{
  switch(key)
    {
        /* If the user hits escape or Q, then exit */
        /* ESCAPE_KEY = 27 */
        
		case 'w':
		cameraHeigth = cameraHeigth + 0.1;  
	break;
		case 's':
		cameraHeigth = cameraHeigth - 0.1;  
	break;
		case 'a':
		camDegree = camDegree + 0.1;  
	break;
		case 'd':
		camDegree = camDegree - 0.1;  
	break;
		default:
	break;
	}
	glutPostRedisplay();
}

void display(void) {
 glLoadIdentity();
glScalef(0.3, 0.3, 0.3);
   gluLookAt(sin(camDegree) *  4, cos(camDegree) * 4, cameraHeigth, 0, 0, 0, 0, 0, 1);
     glColor3f(0.0f,0.0f,0.0f);
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	 
	 // gluLookAt(sin(camDegree) *  4, cos(camDegree) * 4, cameraHeigth, 0, 0, 0, 0, 0, 1);
	glBegin(GL_QUADS);
		glColor3f(.5f,0.25f,0.0f);	
		//obere fläche	 
		glVertex3f( -2, 2, 1);		 
		glVertex3f( 2, 2, 1);		 
		glVertex3f( 2, -2, 1);		 
		glVertex3f( -2, -2, 1);	
		
		//untere fläche (eigentlich nicht nötig)	 
	    glVertex3f( -2, 2, 1.2);		 
		glVertex3f( 2, 2, 1.2);		 
		glVertex3f( 2, -2, 1.2);		 
		glVertex3f( -2, -2, 1.2);	
		
		glColor3f(.4f,0.2f,0.0f);	
		//seitenränder	 
		glVertex3f( -2, 2, 1);		 
	    glVertex3f( -2, 2, 1.2);		 
		glVertex3f( 2, 2, 1.2);		 
		glVertex3f( 2, 2, 1);		 
		
		glVertex3f( -2, -2, 1);		 
	    glVertex3f( -2, -2, 1.2);		 
		glVertex3f( 2, -2, 1.2);		 
		glVertex3f( 2, -2, 1);		 
		
		glVertex3f( 2, -2, 1);		 
	    glVertex3f( 2, -2, 1.2);		 
		glVertex3f( 2, 2, 1.2);		 
		glVertex3f( 2, 2, 1);		 
		
		glVertex3f( -2, -2, 1);		 
	    glVertex3f( -2, -2, 1.2);		 
		glVertex3f( -2, 2, 1.2);		 
		glVertex3f( -2, 2, 1);		 

		glColor3f(.7f,0.35f,0.0f);	
		//stäbe, 16 an der zahl!
		for (int i=0;i<4;i++) {
			for (int j=0;j<4;j++) {
				float x = -1.5 + i;
				float y = -1.5 + j;
				//printf("Position: %f %f\n", x, y);
				glVertex3f(x + 0.1, y + 0.1, 1.2); 
				glVertex3f(x + 0.1, y + 0.1, 3.5); 
				glVertex3f(x - 0.1, y + 0.1, 3.5); 
				glVertex3f(x - 0.1, y + 0.1, 1.2);
				 
				glVertex3f(x + 0.1, y - 0.1, 1.2); 
				glVertex3f(x + 0.1, y - 0.1, 3.5); 
				glVertex3f(x - 0.1, y - 0.1, 3.5); 
				glVertex3f(x - 0.1, y - 0.1, 1.2);
				 
				glVertex3f(x + 0.1, y + 0.1, 1.2); 
				glVertex3f(x + 0.1, y + 0.1, 3.5); 
				glVertex3f(x + 0.1, y - 0.1, 3.5); 
				glVertex3f(x + 0.1, y - 0.1, 1.2);
				 
				glVertex3f(x - 0.1, y + 0.1, 1.2); 
				glVertex3f(x - 0.1, y + 0.1, 3.5); 
				glVertex3f(x - 0.1, y - 0.1, 3.5); 
				glVertex3f(x - 0.1, y - 0.1, 1.2);
				 
			}		
		}		
		
	glEnd();
	glFlush();
}

void init_gamewindow(int* argc, char **argv) 
{
	glutInit(argc, argv);
    glutInitWindowSize(500,500);    
    glutCreateWindow("S O G O professional");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
   	glutKeyboardFunc(keyboardFunc);
}


