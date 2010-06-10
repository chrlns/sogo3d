#include "gui.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "BMPLoader.h"
#include "playground.h"
#include "game.h"

extern Playground* currentPlayground;
extern bool enableZBuffer;
extern int horizon;

int windowWidth;
int windowHeigth;
float cameraHeigth = 1.8f;
float camDegree = 0;
float camDistance = 1.8f;
int currentViewMode = 0;
GLfloat LightAmbient[]= { 1, 1, 1, 1.0f }; 
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };	
GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };

GLuint* texture = (GLuint*)malloc(sizeof(GLuint) * 1);
GLUquadricObj *quadric;

// das aktuelle spielfeld wird hier vorläufig erstmal ziemlich ineffizient zwischengespeichert
int markedStab = -1;
int count[17];
int gameField[128];	//stupid but too late and too tired to fix now
int currentColor = 0;


void reshape(int w, int h)
{
  windowWidth = w;
  windowHeigth = h;
  glViewport(0, 0, w, h);       /* Establish viewing area to cover entire window. */
  glMatrixMode(GL_PROJECTION);  /* Start modifying the projection matrix. */
  glLoadIdentity();             /* Reset project matrix. */
  if (currentViewMode == 0) {
  	float wf = w;
  	float hf = h;
  	gluPerspective(60.0,wf/hf,0.01,1000);
  } else {	
  	glOrtho(-1,1,-1,1,0.1,100);
  }
  // 
//glRotatef(1, 0, 0, 1);
 glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

	if(enableZBuffer)
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
	}
  /*
  glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
  glEnable ( GL_COLOR_MATERIAL );
  glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);	
  glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		
  glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHTING);	
*/
}

void createBall(int x, int y, int z, int color)
{
glEnable(GL_TEXTURE_2D);
	//printf("CreateBall %i %i %i %i\n", x, y, z, color);
	float ballSize = 0.3;
	float xp = -1.5 + x;
	float yp = -1.5 + y;

	glPushMatrix();
	glTranslatef (xp, yp, z * ballSize * 2 + 1.2 + ballSize);
	
	glBegin(GL_TRIANGLES);
		glColor3f(color, 1, color);		// warum hat glColor3f an dieser Stelle keine Wirkung, wenn man es nicht in einem glBegin glEnd Block aufruft ???
	glEnd();
glMatrixMode(GL_TEXTURE); 

//glRotatef(0, 90, 0, 1);
glScalef(2, 1, 1);

	gluSphere(quadric,ballSize,32,32);
	//if (color == 1) {
		glEnable(GL_BLEND);	
		glBlendFunc(GL_ONE, GL_ONE);
		gluSphere(quadric,ballSize,32,32);
		glDisable(GL_BLEND);
	//}
	
glLoadIdentity();
glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawPlayground(Playground* pg)
{
	for(int x = 0; x < 4; x++) {
		for(int y = 0; y < 4; y++) {
			for(int z = 0; z < 4; z++) {
				switch(pg->get(x, y, z)) {
					case BLACK:
						createBall(x, y, z, 0);
						break;
					case WHITE:
						createBall(x, y, z, 1);
						break;
					case EMPTY:
						z = 4;
						break;
				}
			}
		}
	}
}

void keyboardFunc(unsigned char key, int mouseX, int mouseY)
{
	//printf("Key: %c\n", key);
  switch(key)
    {
        /* If the user hits escape or Q, then exit */
        /* ESCAPE_KEY = 27 */
        
		case 'w':
		camDistance = camDistance - 0.1;  
	break;
		case 's':
		camDistance = camDistance + 0.1;  
	break;
		case 'a':
		camDegree = camDegree + 0.1;  
	break;
		case 'd':
		camDegree = camDegree - 0.1;  
	break;
		case 'r':
		cameraHeigth = cameraHeigth + 0.1;  
	break;
		case 'f':
		cameraHeigth = cameraHeigth - 0.1;  
	break;
		case 'c':
		if (currentViewMode == 0) 
			currentViewMode = 1;
		else
			currentViewMode = 0;
		reshape(windowWidth, windowHeigth);
	break;
		default:
	break;
	}
	glutPostRedisplay();
}


void displayTargets() {
		//stäbe, 16 an der zahl!
		glEnable(GL_TEXTURE_2D);
		
		
		
		for (int i=0;i<4;i++) {
			for (int j=0;j<4;j++) {
		
			int stabId = i*4+j;
			glLoadName(stabId);	// glLoadName darf nicht innerhalb eines glBegin GlEnd Blocks aufgerufen werden.


			glBegin(GL_QUADS);
				if (stabId == markedStab)
					glColor3f(0.8, 0.5, 0);
				else
					glColor3f(.7f,0.35f,0.0f);	
			glEnd();
				float x = -1.5 + i;
				float y = -1.5 + j;
				glPushMatrix();
			glTranslatef (x, y, 1.2);
		gluCylinder(quadric, 0.1, 0.1, 2.5, 16, 16);
		glTranslatef(0, 0, 2.5);
		gluDisk(quadric, 0, 0.1, 16, 1);
		glPopMatrix();
			/*	
				glBegin(GL_QUADS);
				if (stabId == markedStab)
					glColor3f(0.8, 0.5, 0);
				else
					glColor3f(.7f,0.35f,0.0f);	
				
				//printf("Position: %f %f\n", x, y);
				glTexCoord2f(0.0f, 0.0f);	glVertex3f(x + 0.1, y + 0.1, 1.2); 
				glTexCoord2f(0.0f, 1.0f);	glVertex3f(x + 0.1, y + 0.1, 3.5); 
				glTexCoord2f(0.25f, 1.0f);	glVertex3f(x - 0.1, y + 0.1, 3.5); 
				glTexCoord2f(0.25f, 0.0f);	glVertex3f(x - 0.1, y + 0.1, 1.2);
				 
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
				
			glEnd();
				*/ 
			}		
		}	
		glDisable(GL_TEXTURE_2D);	

}

void display(void) 
{
	glLoadIdentity();
	gluLookAt(sin(camDegree) *  camDistance, cos(camDegree) * camDistance, cameraHeigth, 0, 0, 0.5f, 0, 0, 1);
	glScalef(0.3, 0.3, 0.3);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	 
	 // gluLookAt(sin(camDegree) *  4, cos(camDegree) * 4, cameraHeigth, 0, 0, 0, 0, 0, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);


	glBegin(GL_QUADS);
		//glColor3f(.5f,0.25f,0.0f);	
		glColor3f(1, 1, 1);
		//obere fläche	 
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f( -2, 2, 1.2);	
		glTexCoord2f(1.0f, 0.0f);	 
		glVertex3f( 2, 2, 1.2);	
		glTexCoord2f(1.0f, 1.0f);	 
		glVertex3f( 2, -2, 1.2);	
		glTexCoord2f(0.0f, 1.0f);	 
		glVertex3f( -2, -2, 1.2);	
	glEnd();
	glDisable(GL_TEXTURE_2D);
glColor3f(.5f,0.25f,0.0f);
		glBegin(GL_QUADS);
		//untere fläche (eigentlich nicht nötig)	 
	    glVertex3f( -2, 2, 1);		 
		glVertex3f( 2, 2, 1);		 
		glVertex3f( 2, -2, 1);		 
		glVertex3f( -2, -2, 1);	
		
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

		
	glEnd();
	displayTargets();	

	glLoadName(0);
/*
	for (int i=0;i<4;i++) {
		for (int j=0;j<4;j++) {	
			int stabId = i*4+j+1;
			for (int k=0;k<count[stabId];k++) {
				createBall(i, j, k, gameField[stabId * 4 + k]);
			}
		}	
	}
	* */
	
	// Draw the current Playground
	drawPlayground(currentPlayground);

	glFlush();
	glutSwapBuffers();
}

void loadTexture() 
{	
	BMPClass bmp;
	BMPLoad("bodenplatte.bmp", bmp);
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, texture[0]);


	
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    //glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);


	// Diese beiden Parameter müssen auf jedenfall gesetzt werden, 
	// sonst wird die Textur nicht angezeigt !
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

/*
    glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
*/

	
	glTexImage2D(GL_TEXTURE_2D, 0, 3, bmp.width, bmp.height, 
		0, GL_RGB, GL_UNSIGNED_BYTE, bmp.bytes);

}


void mouseMotion(int x, int y)		// grösstenteils übernommen von http://nehe.gamedev.net/data/lessons/lesson.asp?lesson=32
{
   

	GLuint	buffer[512];										// Set Up A Selection Buffer
	GLint	hits;												// The Number Of Objects That We Selected
		// The Size Of The Viewport. [0] Is <x>, [1] Is <y>, [2] Is <length>, [3] Is <width>
	GLint	viewport[4];

	// This Sets The Array <viewport> To The Size And Location Of The Screen Relative To The Window
	glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer(512, buffer);								// Tell OpenGL To Use Our Array For Selection

	// Puts OpenGL In Selection Mode. Nothing Will Be Drawn.  Object ID's and Extents Are Stored In The Buffer.
	(void) glRenderMode(GL_SELECT);

	glInitNames();												// Initializes The Name Stack
	glPushName(0);												// Push 0 (At Least One Entry) Onto The Stack

	glMatrixMode(GL_PROJECTION);								// Selects The Projection Matrix
	glPushMatrix();												// Push The Projection Matrix
	glLoadIdentity();											// Resets The Matrix

	// This Creates A Matrix That Will Zoom Up To A Small Portion Of The Screen, Where The Mouse Is.
	gluPickMatrix((GLdouble) x, (GLdouble) (viewport[3]-y), 1.0f, 1.0f, viewport);

	// Apply The Perspective Matrix
	gluPerspective(60.0f, (GLfloat) (viewport[2]-viewport[0])/(GLfloat) (viewport[3]-viewport[1]), 0.01f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);									// Select The Modelview Matrix

	displayTargets();												// Render The Targets To The Selection Buffer
	glMatrixMode(GL_PROJECTION);								// Select The Projection Matrix
	glPopMatrix();												// Pop The Projection Matrix
	glMatrixMode(GL_MODELVIEW);									// Select The Modelview Matrix
	hits=glRenderMode(GL_RENDER);								// Switch To Render Mode, Find Out How Many


	
	markedStab = -1;
	if (hits > 0)												// If There Were More Than 0 Hits
	{
		int	choose = buffer[3];									// Make Our Selection The First Object
		int depth = buffer[1];									// Store How Far Away It Is

		for (int loop = 1; loop < hits; loop++)					// Loop Through All The Detected Hits
		{
			// If This Object Is Closer To Us Than The One We Have Selected
			if (buffer[loop*4+1] < GLuint(depth))
			{
				choose = buffer[loop*4+3];						// Select The Closer Object
				depth = buffer[loop*4+1];						// Store How Far Away It Is
			}
		}
		markedStab = choose;
	}
	
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (state != GLUT_DOWN) return;
	if (markedStab == -1) return;	 
	if (count[markedStab] == 4) return;
	printf("Auf Stab %i sind %i Bälle\n", markedStab, count[markedStab]);
	gameField[markedStab * 4 + count[markedStab]] = currentColor;
	count[markedStab]++;
	if (currentColor == 0) 
		currentColor = 1; 
	else 
		currentColor = 0;
	
	y = markedStab % 4;
	x = markedStab / 4;
	dbgmsg("Klick " << markedStab << " " << x << " " << y);
	currentPlayground->move(x, y);
	glutPostRedisplay();
	minimax(currentPlayground, BLACK, horizon);
	printf("Bewertung aktuelles Spielfeld: %i\n", currentPlayground->rating());
	glutPostRedisplay();
}

void init_gamewindow(int* argc, char **argv) 
{
	glutInit(argc, argv);
    glutInitWindowSize(800, 600);   
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH); 
    glutCreateWindow("S O G O professional");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
   	glutKeyboardFunc(keyboardFunc);
   	glutMouseFunc(mouse);  
   	glutPassiveMotionFunc(mouseMotion);
   	glutIdleFunc(display);
   	// Texturen dürfen erst hier geladen werden, da vorher u.U. noch
   	// kein OpenGL Kontext existiert
   	loadTexture();
    quadric=gluNewQuadric(); 
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE);
	for (int i=0;i<16;i++) {
		count[i] = 0;
	}
}
