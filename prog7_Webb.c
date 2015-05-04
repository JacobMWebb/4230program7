/*
 * Copyright (c) 1993-1997, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED 
 * Permission to use, copy, modify, and distribute this software for 
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that 
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission. 
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 * 
 * US Government Users Restricted Rights 
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

/*  bezcurve.c			
 *  This program uses evaluators to draw a Bezier curve.
 */
/*
   Jacob Webb
   Program 7
   CSCE 4230 Computer Graphics
   Dr. Renka

This can be compiled on the CSE machines with the makefile that is on Dr. Renka's page.
	
	TO COMPILE:***
	This can be compiled on a Apple computer with the following pasted into terminal:

	gcc prog7_Webb.c -L/System/Library/Frameworks -framework GLUT -framework OpenGL -w 

	TO USE:***
	x/X rotate x-axis
	y/Y rotate y-axis
	=/+ zoom in and out

*/

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>


GLfloat ctrlpoints[7][3] = 
{
	{0.0, 0.0, 0.0}, {1.0, 1.0, 0.0}, 
	{2.0 ,4.0, 0.0}, {2.5, 6.25, 0.0},
	{3.0, 9.0, 0.0}, {4.0, 16.0, 0},
	{5.0, 18.0, 0.0}
};
int old_x, old_y = 0;
int control_point = 0;
// GLfloat p0[] = {0.0, 0.0, 0.0};
// GLfloat p1[] = {1.0, 1.0, 0.0};
// GLfloat p2[] = {2.0 ,4.0, 0.0};
// GLfloat p3[] = {2.5, 6.25, 0.0};
// GLfloat p4[] = {3.0, 9.0, 0.0};
// GLfloat p5[] = {4.0, 16.0, 0};
// GLfloat p6[] = {5.0, 18.0, 0.0};

int return_coordinates(float x, float y) 
{
	//check where our mouse clicked to know which point to move.
	if(x >= ctrlpoints[0][0]-0.05 && x <= ctrlpoints[0][0]+0.2)//check our xcoords +/- .2
	{
		//printf("%f\n", ctrlpoints[0][0] -.05);
		//now we need to check y coords
		if(y >= ctrlpoints[0][1]-0.2 && y <= ctrlpoints[0][1]+0.2){
			//printf("%f\n", ctrlpoints[0][0]-0.05);
			return 1;
		}

			
	}
	else if(x >= ctrlpoints[1][0] -.05 && x <= ctrlpoints[1][0]+.2)
	{
		//now we need to check y coords
		if(y >= ctrlpoints[1][1]-.2 && y <= ctrlpoints[1][1]+.2)
			return 2;
	}
	else if(x >= ctrlpoints[2][0] -.05 && x <= ctrlpoints[2][0]+.2)
	{
		//now we need to check y coords
		if(y >= ctrlpoints[2][1]-.2 && y <= ctrlpoints[2][1]+.2)
			return 3;
	}
	else if(x >= ctrlpoints[3][0] -.05 && x <= ctrlpoints[3][0]+.2)
	{
		//now we need to check y coords
		if(y >= ctrlpoints[3][1]-.2 && y <= ctrlpoints[3][1]+.2)
			return 4;
	}
	else if(x >= ctrlpoints[4][0] -.05 && x <= ctrlpoints[4][0]+.2)
	{
		//now we need to check y coords
		if(y >= ctrlpoints[4][1]-.2 && y <= ctrlpoints[4][1]+.2)
			return 5;
	}
	else if(x >= ctrlpoints[5][0] -.05 && x <= ctrlpoints[5][0]+.2)
	{
		//now we need to check y coords
		if(y >= ctrlpoints[5][1]-.2 && y <= ctrlpoints[5][1]+.2)
			return 6;
	}
	else if(x >= ctrlpoints[6][0] -.05 && x <= ctrlpoints[6][0]+.2)
	{
		//now we need to check y coords
		if(y >= ctrlpoints[6][1]-.2 && y <= ctrlpoints[6][1]+.2)
			return 7;
	}
	else 
		return -1;
}

void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 7, &ctrlpoints[0][0]);
   glEnable(GL_MAP1_VERTEX_3);
}

void display(void)
{
   int i;

   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1.0, 1.0, 1.0);
   glBegin(GL_LINE_STRIP);
      for (i = 0; i <= 30; i++) 
         glEvalCoord1f((GLfloat) i/30.0);
   glEnd();
   /* The following code displays the control points as dots. */
   glPointSize(5.0);
   glColor3f(1.0, 1.0, 0.0);
   glBegin(GL_POINTS); 
        for(i=0;i<7;i++)
        {
        	glVertex3fv(&ctrlpoints[i][0]);
        }
   glEnd();
   glFlush();

}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   
   glOrtho(-1.0, 7.0, -1, 20, -5.0, 5.0);
   
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

void mouse(int button, int state, int x, int y) {
	 
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
         {
         	glutPostRedisplay();
         	//check if we're on a point
         	float x_to_send = 500-x;
         	x_to_send /= 500;
         	x_to_send *=-8;
         	x_to_send+=7;
         	float y_to_send = 500-y;
         	y_to_send /=500;
         	y_to_send *=21;
         	y_to_send-=1;
         	//printf("x:%f\ny:%f\n",x_to_send, y_to_send);
         	control_point = return_coordinates(x_to_send, y_to_send);
         	//printf("%d\n", control_point);
         	control_point -=1; //because function returns human logical value(1-7) instead of (0-6)
         	//returns control point number value if we are
         	old_x = 500-x; //subtract 500 to reverse coordinate system
         	old_y = 500-y; //0 is now bottom, top is now 500(size of window from main function)

         }
         else if(state == GLUT_UP) 
         {
         	 
         	float new_y= 500-y;//once again, reverse coordinate system
         	float new_x= 500-x;
         	float dist_to_move_x = (new_x - old_x) / 500; //divide by 500 to get % distance moved in window
         	float dist_to_move_y = (new_y - old_y) / 500;
         	
         	if(control_point !=-1) //if we clicked a valid control point
         	{
         		//update point and redraw
         		ctrlpoints[control_point][0] += dist_to_move_x*-8;
         		ctrlpoints[control_point][1] += dist_to_move_y*21;
         		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 7, &ctrlpoints[0][0]);	
         	}
         	         	
         	//p0[0] += dist_to_move_x*-8; //multiply by 8 to scale to object coords(-1 to 7)
         	//p0[1] += dist_to_move_y*21; //multiply by 21 to scale to object coords(-1 to 20)
         	//new point should be exactly where cursor is now.      
         	glutPostRedisplay();

         }
         break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Program 7 Jacob Webb");
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMouseFunc(mouse);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
