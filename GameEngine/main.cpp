/*
 * GL01Hello.cpp: Test OpenGL/GLUT C/C++ Setup
 * Tested under Eclipse CDT with MinGW/Cygwin and CodeBlocks with MinGW
 * To compile with -lfreeglut -lglu32 -lopengl32
 */
#define FREEGLUT_STATIC

#include <windows.h>  // for MS Windows
#include "Libraries/freeglut/glut.h"  // GLUT, include glu.h and gl.h
 
#include <iostream>
using namespace std;

void display();

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
	cout << "mlem" << endl;

   glutInit(&argc, argv);                 // Initialize GLUT
   glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
   glutInitWindowSize(800, 600);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutDisplayFunc(display); // Register display callback handler for window re-paint
   glutMainLoop();           // Enter the event-processing loop
   return 0;
}

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
 
   // Draw a Red 1x1 Square centered at origin
   glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
      glColor3f(0.1f, 0.1f, 0.88f); // Red
      glVertex2f(-0.5f, -0.5f);    // x, y
      glVertex2f( 0.5f, -0.5f);
      glVertex2f( 0.5f,  0.5f);
      glVertex2f(-0.5f,  0.5f);
   glEnd();
 
   glFlush();  // Render now
}