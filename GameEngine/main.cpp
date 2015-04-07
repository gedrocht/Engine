#define FREEGLUT_STATIC
 
#include <iostream>
#include <windows.h>  // for MS Windows
#include "Libraries/freeglut/glut.h"  // GLUT, include glu.h and gl.h
#include <Math.h>     // Needed for sin, cos
#include "Libraries/soil/SOIL.h"

using namespace std;

#define PI 3.14159265f

void display();
GLuint LoadTexture( const char * filename );
//void DrawTexture(GLenum Target, GLuint ID, float X1, float Y1, float X2, float Y2);
//void DrawTexture(int x, int y, Image* texture, bool blendFlag);
void DrawTexture(GLuint texture, int x, int y, int width, int height , bool blendFlag);
void specialKeys(int key, int x, int y);
void keyboard(unsigned char key, int x, int y);
void Timer(int value);
void reshape(GLsizei width, GLsizei height);
void initGL();
void drawSprite(GLint left, GLint right, GLint bottom, GLint top, GLuint texture);

char title[] = "Full-Screen & Windowed Mode";  // Windowed mode's title

int windowWidth  = 640;     // Windowed mode's width
int windowHeight = 480;     // Windowed mode's height
int windowPosX   = 50;      // Windowed mode's top-left corner x
int windowPosY   = 50;      // Windowed mode's top-left corner y
int refreshMillis = 30;      // Refresh period in milliseconds

GLfloat ballRadius = 0.5f;   // Radius of the bouncing ball
GLfloat ballX = 0.0f;        // Ball's center (x, y) position
GLfloat ballY = 0.0f;
GLfloat xSpeed = 0.02f;      // Ball's speed in x and y directions
GLfloat ySpeed = 0.007f;
GLfloat ballXMax, // Ball's center (x, y) bounds
		ballXMin,
		ballYMax,
		ballYMin; 
 
// Projection clipping area
GLdouble clipAreaXLeft,
		 clipAreaXRight,
		 clipAreaYBottom,
		 clipAreaYTop;

GLuint texture;
 
bool fullScreenMode = false; // Full-screen or windowed mode?

// Main function: GLUT runs as a console application starting at main()
int main(int argc, char** argv) {
	/*
	texture = LoadTexture( "test_inverted.jpg" );
	cout << "text.bmp ID: " << texture << endl;
	glBindTexture(GL_TEXTURE_2D, texture);
	*/




	glutInit(&argc, argv);            // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	glutInitWindowSize(windowWidth, windowHeight);  // Initial window width and height
	glutInitWindowPosition(windowPosX, windowPosY); // Initial window top-left corner (x, y)
	glutCreateWindow(title);      // Create window with given title
	glutDisplayFunc(display);     // Register callback handler for window re-paint
	glutReshapeFunc(reshape);     // Register callback handler for window re-shape
	glutTimerFunc(0, Timer, 0);   // First timer call immediately
	glutSpecialFunc(specialKeys); // Register callback handler for special-key event
	glutKeyboardFunc(keyboard);   // Register callback handler for special-key event
	//glutFullScreen();             // Put into full screen
	initGL();                     // Our own OpenGL initialization




    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glFrontFace(GL_CW);

    texture = SOIL_load_OGL_texture(
        "test.bmp",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    if( 0 == texture )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result());
    }


	glutMainLoop();               // Enter event-processing loop

	return 0;
}

void drawSprite(GLint left, GLint right, GLint bottom, GLint top, GLuint texture){  
    //Draw clockwise
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    glTexCoord2i(1,1); glVertex2i(right , top);
    glTexCoord2i(1,0); glVertex2i(right , bottom);
    glTexCoord2i(0,0); glVertex2i(left , bottom);
    glTexCoord2i(0,1); glVertex2i(left , top);
    glEnd();
}

// Initialize OpenGL Graphics
void initGL() {
   glClearColor(0.0, 0.0, 0.0, 1.0); // Set background (clear) color to black
}
 
// Callback handler for window re-paint event
void display() {
	glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer
	glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
	glLoadIdentity();              // Reset model-view matrix
 


	//DrawTexture(GL_TEXTURE_2D, texture, 0, 0, 90, 90);
	//DrawTexture(0, 0, texture, false);


	//DrawTexture(texture, 10, 10, 90, 90, false);

    //glClearColor(0.0, 0.0, 0.0, 1.0);
    //glClear(GL_COLOR_BUFFER_BIT);
    //glLoadIdentity();
    
	
	//glOrtho(0.0, 600.0, 0.0, 600.0, -1.0, 1.0); //LRBT near far

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	int windowWidth  = glutGet(GLUT_WINDOW_WIDTH);
	int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
	
	glOrtho(0.0f, windowWidth, windowHeight, 0.0f, 0.0f, 1.0f);
    
	
	//drawSprite(0, 82, 0, 82, texture);
	int x = 0;
	int y = 0;
	int width = 90;
	int height = 90;

	int left = x;
	int right = x + width;
	int top = y;
	int bottom = y + height;

	drawSprite(left, right, bottom, top, texture); //L R B T
    glFlush();


	glTranslatef(ballX, ballY, 0.0f);  // Translate to (xPos, yPos)
	// Use triangular segments to form a circle
	glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.0f, 0.0f, 1.0f);  // Blue
		glVertex2f(0.0f, 0.0f);       // Center of circle
		int numSegments = 100;
		GLfloat angle;
		for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
			angle = i * 2.0f * PI / numSegments;  // 360 deg for all segments
			glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
		}
	glEnd();
 
	glutSwapBuffers();  // Swap front and back buffers (of double buffered mode)
 
	// Animation Control - compute the location for the next refresh
	ballX += xSpeed;
	ballY += ySpeed;
	// Check if the ball exceeds the edges
	if (ballX > ballXMax) {
		ballX = ballXMax;
		xSpeed = -xSpeed;
	} else if (ballX < ballXMin) {
		ballX = ballXMin;
		xSpeed = -xSpeed;
	}
	if (ballY > ballYMax) {
		ballY = ballYMax;
		ySpeed = -ySpeed;
	} else if (ballY < ballYMin) {
		ballY = ballYMin;
		ySpeed = -ySpeed;
	}
}
 
//Call back when the windows is re-sized
void reshape(GLsizei width, GLsizei height) {
	// Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	 
	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);
	 
	// Set the aspect ratio of the clipping area to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset the projection matrix
	if (width >= height) {
		clipAreaXLeft   = -1.0 * aspect;
		clipAreaXRight  = 1.0 * aspect;
		clipAreaYBottom = -1.0;
		clipAreaYTop    = 1.0;
	} else {
		clipAreaXLeft   = -1.0;
		clipAreaXRight  = 1.0;
		clipAreaYBottom = -1.0 / aspect;
		clipAreaYTop    = 1.0 / aspect;
	}
	gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
	ballXMin = clipAreaXLeft + ballRadius;
	ballXMax = clipAreaXRight - ballRadius;
	ballYMin = clipAreaYBottom + ballRadius;
	ballYMax = clipAreaYTop - ballRadius;
}
 
/* Called back when the timer expired */
void Timer(int value) {
	glutPostRedisplay();    // Post a paint request to activate display()
	glutTimerFunc(refreshMillis, Timer, 0); // subsequent timer call at milliseconds
}
 
/* Callback handler for normal-key event */
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 27:     // ESC key
			exit(0);
			break;
	}
}
 
// Callback handler for special-key event
void specialKeys(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_F1:    // F1: Toggle between full-screen and windowed mode
			fullScreenMode = !fullScreenMode;         // Toggle state
			if (fullScreenMode) {                     // Full-screen mode
				windowPosX   = glutGet(GLUT_WINDOW_X); // Save parameters for restoring later
				windowPosY   = glutGet(GLUT_WINDOW_Y);
				windowWidth  = glutGet(GLUT_WINDOW_WIDTH);
				windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
				glutFullScreen();                      // Switch into full screen
			} else {                                         // Windowed mode
				glutReshapeWindow(windowWidth, windowHeight); // Switch into windowed mode
				glutPositionWindow(windowPosX, windowPosX);   // Position top-left corner
			}
			break;
		case GLUT_KEY_RIGHT:    // Right: increase x speed
			xSpeed *= 1.05f; break;
		case GLUT_KEY_LEFT:     // Left: decrease x speed
			xSpeed *= 0.95f; break;
		case GLUT_KEY_UP:       // Up: increase y speed
			ySpeed *= 1.05f; break;
		case GLUT_KEY_DOWN:     // Down: decrease y speed
			ySpeed *= 0.95f; break;
		case GLUT_KEY_PAGE_UP:  // Page-Up: increase ball's radius
			ballRadius *= 1.05f;
			ballXMin = clipAreaXLeft + ballRadius;
			ballXMax = clipAreaXRight - ballRadius;
			ballYMin = clipAreaYBottom + ballRadius;
			ballYMax = clipAreaYTop - ballRadius;
			break;
		case GLUT_KEY_PAGE_DOWN: // Page-Down: decrease ball's radius
			ballRadius *= 0.95f;
			ballXMin = clipAreaXLeft + ballRadius;
			ballXMax = clipAreaXRight - ballRadius;
			ballYMin = clipAreaYBottom + ballRadius;
			ballYMax = clipAreaYTop - ballRadius;
			break;
	}
}
 
GLuint LoadTexture( const char * filename ) {
	GLuint texture;
	int width, height;
	
	unsigned char * data;
	
	FILE * file;
	
	file = fopen( filename, "rb" );
	
	if ( file == NULL ) return 0;
	width = 1024;
	height = 512;
	data = (unsigned char *)malloc( width * height * 3 );
	//int size = fseek(file,);
	fread( data, width * height * 3, 1, file );
	fclose( file );

	for(int i = 0; i < width * height ; ++i){
		int index = i*3;
		unsigned char B,R;
		B = data[index];
		R = data[index+2];
		
		data[index] = R;
		data[index+2] = B;
	}
	
	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
	free( data );

	return texture;
}

//void DrawTexture(int x, int y, Image* texture, bool blendFlag) {
void DrawTexture(GLuint texture, int x, int y, int width, int height , bool blendFlag) {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT), -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();


	glLoadIdentity();
	glDisable(GL_LIGHTING);


	glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);


	// Draw a textured quad
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(x, y, 0);
	glTexCoord2f(0, 1); glVertex3f(x, y+height, 0);
	glTexCoord2f(1, 1); glVertex3f(x+width, y+height, 0);
	glTexCoord2f(1, 0); glVertex3f(x+width, y, 0);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);

	/*
	//Bind Texture
	glBindTexture(GL_TEXTURE_2D, texture);

	if (blendFlag)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	GLfloat Vertices[] = {(float)x, (float)y, 0,
						(float)x + width, (float)y, 0,
						(float)x + (float)width, (float)y + (float)height, 0,
						(float)x, (float)y + (float)height, 0};
	GLfloat TexCoord[] = {0, 0,
		1, 0,
		1, 1,
		0, 1,
	};
	GLubyte indices[] = {0,1,2, // first triangle (bottom left - top left - top right)
						 0,2,3}; // second triangle (bottom left - top right - bottom right)

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, Vertices);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, TexCoord);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	if (blendFlag) glDisable(GL_BLEND);
	*/
}
/*
void DrawTexture(GLenum Target, GLuint ID, float X1, float Y1, float X2, float Y2) {
    GLfloat ViewPort[4];
    glGetFloatv(GL_VIEWPORT, ViewPort);

    glEnable(Target);
    glBindTexture(Target, ID);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2f(X1, Y1);

        glTexCoord2f(0, Target == GL_TEXTURE_2D ? 1 : ViewPort[3]);
        glVertex2f(X1, Y2);

        glTexCoord2f(Target == GL_TEXTURE_2D ? 1 : ViewPort[2], Target == GL_TEXTURE_2D ? 1 : ViewPort[3]);
        glVertex2f(X2, Y2);

        glTexCoord2f(Target == GL_TEXTURE_2D ? 1 : ViewPort[2], 0);
        glVertex2f(X2, Y1);
    glEnd();
    glDisable(Target);
}
*/