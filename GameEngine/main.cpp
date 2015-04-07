#define FREEGLUT_STATIC
 
#include <iostream>
#include <windows.h>
#include <winuser.h>
#include "Libraries/freeglut/glut.h"
#include <Math.h>
#include "Libraries/soil/SOIL.h"
#include <vector>

#include "Texture.h"
#include "Physical.h"

using namespace std;

#define PI 3.14159265f
#define GRAVITY 0.5;

void display();
void specialKeys(int key, int x, int y);
//void keyboard(unsigned char key, int x, int y);
void Timer(int value);
void reshape(GLsizei width, GLsizei height);
void initGL();
void drawSprite(GLint left, GLint right, GLint bottom, GLint top, GLuint texture);
//void keyboard_up(unsigned char key, int x, int y);
void updateInput();

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

Physical *player;

vector<Physical*> *physicals = new vector<Physical*>();

vector<Texture*> *textures = new vector<Texture*>();
vector<Texture*> *bricks = new vector<Texture*>();

bool left_pressed = true;
bool right_pressed = true;

bool fullScreenMode = false; // Full-screen or windowed mode?

// Main function: GLUT runs as a console application starting at main()
int main(int argc, char** argv) {
	glutInit(&argc, argv);            // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	glutInitWindowSize(windowWidth, windowHeight);  // Initial window width and height
	glutInitWindowPosition(windowPosX, windowPosY); // Initial window top-left corner (x, y)
	glutCreateWindow(title);      // Create window with given title
	glutDisplayFunc(display);     // Register callback handler for window re-paint
	glutReshapeFunc(reshape);     // Register callback handler for window re-shape
	glutTimerFunc(0, Timer, 0);   // First timer call immediately
	//glutSpecialFunc(specialKeys); // Register callback handler for special-key event
	//glutKeyboardFunc(keyboard);   // Register callback handler for special-key event
	//glutKeyboardUpFunc(keyboard_up);
	if( fullScreenMode )
		glutFullScreen();             // Put into full screen
	initGL();                     // Our own OpenGL initialization

	player = new Physical(new Texture("test_inverted.bmp",0,0,90,90));
	physicals->push_back(player);
	textures->push_back(player->texture);
	textures->push_back(new Texture("test.bmp",40,40,90,90));

	Texture *brick;
	for( int i = 0 ; i < 6 ; i++ ){
		brick = new Texture("brick.bmp",i*135-67,300,135,62);
		textures->push_back(brick);
		bricks->push_back(brick);
	}

	glutMainLoop();               // Enter event-processing loop

	return 0;
}

//void drawSprite(GLint left, GLint right, GLint bottom, GLint top, GLuint texture){  
void drawSprite(Texture *texture){  
    //Draw clockwise
    glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, texture->texture);
	
    glBegin(GL_QUADS);
		glTexCoord2i(1,1); glVertex2i(texture->getRight(), texture->getTop());
		glTexCoord2i(1,0); glVertex2i(texture->getRight(), texture->getBottom());
		glTexCoord2i(0,0); glVertex2i(texture->getLeft(), texture->getBottom());
		glTexCoord2i(0,1); glVertex2i(texture->getLeft(), texture->getTop());
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

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	int windowWidth  = glutGet(GLUT_WINDOW_WIDTH);
	int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
	
	glOrtho(0.0f, windowWidth, windowHeight, 0.0f, 0.0f, 1.0f);

	Physical *temp;
	Texture *temp_brick;
	for(vector<Physical*>::iterator it = physicals->begin() ; it != physicals->end(); ++it){
		temp = *it;
		
		for(vector<Texture*>::iterator brick_it = bricks->begin() ; brick_it != bricks->end(); ++brick_it){
			temp_brick = *brick_it;
			if( temp->texture->isColliding(temp_brick) ) {
				temp->Vy = 0;
				temp->texture->setY( temp_brick->getTop() - 1 - temp->texture->getHeight() );
				break;
				//temp->active = false;
			} else if( temp->texture->isOnTopOf(temp_brick) ){
				temp->Vy = 0;
				//temp->active = false;
				break;
			} else {
				temp->Vy += GRAVITY;
			}
		}

		temp->update();
	}

	updateInput();

	for(vector<Texture*>::iterator it = textures->begin() ; it != textures->end(); ++it){
		drawSprite(*it);
	}

    glFlush();

	glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
	glLoadIdentity();              // Reset model-view matrix

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
 
	glutSwapBuffers();  // Swap front and back buffers (of double buffered mode)
}

void updateInput(){
	if (GetAsyncKeyState(VK_LEFT)){
		player->Vx = -3;
	} else if (GetAsyncKeyState(VK_RIGHT)) {
		player->Vx = 3;
	} else {
		player->Vx = 0;
	}
}
 
//Call back when the windows is re-sized
void reshape(GLsizei width, GLsizei height) {
	// Compute aspect ratio of the new window
	//if (height == 0) height = 1;                // To prevent divide by 0
	//GLfloat aspect = (GLfloat)width / (GLfloat)height;
	 
	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);
	 
	// Set the aspect ratio of the clipping area to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset the projection matrix
}
 
// Called back when the timer expires
void Timer(int value) {
	glutPostRedisplay();    // Post a paint request to activate display()
	glutTimerFunc(refreshMillis, Timer, 0); // subsequent timer call at milliseconds
}

/*
void keyboard_up(unsigned char key, int x, int y){
	cout << "UP: " << key << endl;
}

// Callback handler for normal-key event
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
		case GLUT_KEY_RIGHT:
			//texture->setX( texture->getX() + 5 );
			player->Vx = 3;
			break;
		case GLUT_KEY_LEFT:
			//texture->setX( texture->getX() - 5 );
			player->Vx = -3;
			break;
		case GLUT_KEY_UP:
			//texture->setY( texture->getY() - 5 );
			break;
		case GLUT_KEY_DOWN:
			//texture->setY( texture->getY() + 5 );
			break;
		case GLUT_KEY_PAGE_UP:
			break;
		case GLUT_KEY_PAGE_DOWN:
			break;
	}
}
*/