#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h> 

// Globals.
//static float angle = 0.0; // Rotation.angle of hat.
static int isAnimate = 0; // Animated?
static int animationPeriod = 100; // Time interval between frames.
GLfloat angle, fAspect;
GLfloat y = 8.07,z=-33.21,x=-2,moveZ=-10.5,moveY=-35,moveX = 0,cor1=rand()%2,cor2=rand()%2,cor3=rand()%2;
short int flag = rand()%10;
void drawScene(void)
{
    float t; // Parameter along helix.
    
    glClear (GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    glTranslatef(4.0, 0.0, -19.0);
   	 glColor3f(0.68, 1.0, 0.18);
     glBegin(GL_QUADS);
    	glVertex3f(52.0,5.0,-18.0);
		glVertex3f(-52.0,5.0,-18.0);
		glVertex3f(-9.0,-10.0,13.0);
		glVertex3f(1.0,-10.0,13.0);
  		
	glEnd();
   
    glColor3f(0.86, 0.86, 0.86);
    // table 
    glBegin(GL_QUADS);
    	glVertex3f(4.0,5.0,-18.0);
		glVertex3f(-4.0,5.0,-18.0);
		glVertex3f(-8.0,-10.0,13.0);
		glVertex3f(-2.0,-10.0,13.0);
  		
	glEnd();
   
   glColor3f(1.0,0.65,0.0);
   glBegin(GL_LINES);
   			glVertex3f(0.0,5.0,-18.0);
  			glVertex3f(-5.0,-10.0, 13.0);
	glEnd();
   
   glPushMatrix();								//sol
   		glTranslatef(-8.0, 8.0, -2.0);
   			glColor3f(1.0,0.65,0.0); 
   			glutSolidSphere(2,30,30);
   	
	glPopMatrix();
   	
	   glPushMatrix();
		   glTranslatef(moveX,moveY,moveZ);
   			glColor3f(1.0,1.00,1.0); 
   			glutSolidSphere(2,30,30);
   			
   		glPopMatrix();
   		
   		glPushMatrix();
	   		glTranslatef(x,y,z);
   			glColor3f(cor1,cor2,cor3); 
   			glutSolidSphere(2,30,30);
   		glPopMatrix();
   		
	   glutSwapBuffers();
    
}

// Routine to increase the rotation angle.
void increaseAngle(void)
{
  
  if (flag == 0)
  {
	  	if (moveZ > -33.21)
  		{
	  		moveY += 0.81;
   			moveZ -= 0.43;
    		moveX += 0.1; 
		}
	
   else if (moveZ <= -33.21)
	   {
   			moveY=-35;
   			moveZ=-10.5;
   			moveX=0;
			flag = 1;
		}
	 	
  }
   else if (flag == 1)
  {
  		if (z <= 0)
  		{
	  		x-=0.1;
			y-=0.43;
			z+=0.43;   
		}
	
   	else if (z > 0)
   		{
   			x=-2;
   			y=8.07;
   			z=-33.21;
   			
   			cor1=rand()%2;
			cor2=rand()%2;
			cor3=rand()%2;
			
			flag=0;
		}
  	
  }
	printf("%.2f, %.2f, %.2f\n",moveX,moveY,moveZ);
   
}


// Timer function.
void animate(int value)
{
    if (isAnimate)
    {
        increaseAngle();
        
        glutPostRedisplay();
        glutTimerFunc(animationPeriod, animate, 1);
    }
}

// Initialization routine.
void setup(void)
{
	srand(time(NULL));	
    glClearColor(0.94, 1.0, 1.0, 0.0);
    // Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva
	gluPerspective(angle,fAspect,0.1,500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador e do alvo
	gluLookAt(0,80,200, 0,0,0, 0,1,0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 50.0);
    
    glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 27:
            exit(0);
            break;
        case ' ':
            if (isAnimate) isAnimate = 0;
            else
            {
                isAnimate = 1;
                animate(1);
            }
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
    if (key == GLUT_KEY_DOWN) animationPeriod += 5;
    if( key == GLUT_KEY_UP) if (animationPeriod > 5) animationPeriod -= 5;
    glutPostRedisplay();
}


// Main routine.
int main(int argc, char **argv)
{
    
    glutInit(&argc, argv);
  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100); 
    glutCreateWindow ("Rodovia.cpp"); 
    glutDisplayFunc(drawScene); 
	glutReshapeFunc(resize);  
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);
    
    setup(); 
    
    glutMainLoop(); 
}
