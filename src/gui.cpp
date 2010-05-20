#include "gui.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float cameraHeigth = 3;
float camDegree = 0;
GLfloat LightAmbient[]= { 1, 1, 1, 1.0f }; 
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };	
GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };

GLuint		texture[1];


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
 /* glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
glEnable ( GL_COLOR_MATERIAL );
  glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);	
  glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		
  glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHTING);	
*/
}

void keyboardFunc(unsigned char key, int mouseX, int mouseY)
{
	printf("Key: %c\n", key);
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
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
		//glColor3f(.5f,0.25f,0.0f);	
		glColor3f(1, 1, 1);
		//obere fläche	 
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f( -2, 2, 1);	
		glTexCoord2f(1.0f, 0.0f);	 
		glVertex3f( 2, 2, 1);	
		glTexCoord2f(1.0f, 1.0f);	 
		glVertex3f( 2, -2, 1);	
		glTexCoord2f(0.0f, 1.0f);	 
		glVertex3f( -2, -2, 1);	
	glEnd();
	glDisable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
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

void loadTexture() {
	FILE* file = fopen("bodenplatte.bmp", "r");
	if (file == NULL) {
		printf("Kann textur nicht lesen!!!\n");
		return;
	}
	fseek(file, 54, SEEK_SET);
	void* buffer = malloc(256 * 256 * 3);
	int s = fread(buffer, 1, 256 * 256 * 3, file);
	if (s != (256 * 256 * 3))  {
		printf("zuwenig gelesen!\n");
		fclose(file);
		return;
	}
	printf("%i bytes gelesen\n", s);
	fclose(file);
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
}

void init_gamewindow(int* argc, char **argv) 
{
loadTexture();
//bodenTextur; = auxDIBImageLoad("Bodenplatte.bmp");
	glutInit(argc, argv);
    glutInitWindowSize(500,500);    
    glutCreateWindow("S O G O professional");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
   	glutKeyboardFunc(keyboardFunc);
}


