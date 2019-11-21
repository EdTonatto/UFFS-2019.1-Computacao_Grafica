/**
 * This demo shows how to periodically call an update() function to create
 * animations over time. In this case, the animation is to rotate a red square.
 *
 * Author: Fernando Bevilacqua <fernando.bevilacqua@uffs.edu.br>
 * License: MIT
 */

#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>

 // Constants to define the width/height of the window
const int WIDTH = 800;
const int HEIGHT = 800;

// Define how many frames per seconds we want our
// applications to run.
const unsigned int FRAMES_PER_SECOND = 30;
const unsigned int UPDATE_INTERVAL_MS = 1000 / FRAMES_PER_SECOND;

class Cube {
public:
	float x, y, z;
	float base, height;
	float angle_x, angle_y, angle_z;

	Cube(float p_x, float p_y, float p_z, float p_base, float p_height, float p_angle_x, float p_angle_y, float p_angle_z) {
		this->x = p_x;
		this->y = p_y;
		this->z = p_z;
		this->base = p_base;
		this->height = p_height;
		this->angle_x = p_angle_x;
		this->angle_y = p_angle_y;
		this->angle_z = p_angle_z;
	}

	void drawCube() {
		//Front face
		glBegin(GL_LINES);
			//Front-Left Line
			glVertex3f(this->x, this->y, this->z);
			glVertex3f(this->x, this->y - this->height, this->z);

			//Front-Right Line
			glVertex3f(this->x + this->base, this->y, this->z);
			glVertex3f(this->x + this->base, this->y - this->height, this->z);

			//Front-Bottom Line
			glVertex3f(this->x, this->y - this->height, this->z);
			glVertex3f(this->x + this->base, this->y - this->height, this->z);

			//Front-Top Line
			glVertex3f(this->x, this->y, this->z);
			glVertex3f(this->x + this->base, this->y, this->z);
		glEnd();

		//Back face
		glBegin(GL_LINES);
			//Back-Left Line
			glVertex3f(this->x, this->y, this->z + this->base);
			glVertex3f(this->x, this->y - this->height, this->z + this->base);

			//Back-Right Line
			glVertex3f(this->x + this->base, this->y, this->z + this->base);
			glVertex3f(this->x + this->base, this->y - this->height, this->z + this->base);

			//Back-Bottom Line
			glVertex3f(this->x, this->y - this->height, this->z + this->base);
			glVertex3f(this->x + this->base, this->y - this->height, this->z + this->base);

			//Back-Top Line
			glVertex3f(this->x, this->y, this->z + this->base);
			glVertex3f(this->x + this->base, this->y, this->z + this->base);
		glEnd();

		//Sidelines
		glBegin(GL_LINES);
			//Top-Left Sideline
			glVertex3f(this->x, this->y, this->z);
			glVertex3f(this->x, this->y, this->z + this->base);

			//Bottom-Left Sideline
			glVertex3f(this->x, this->y - this->height, this->z);
			glVertex3f(this->x, this->y - this->height, this->z + this->base);

			//Top-Right Sideline
			glVertex3f(this->x + this->base, this->y, this->z);
			glVertex3f(this->x + this->base, this->y, this->z + this->base);

			//Bottom-Right Sideline
			glVertex3f(this->x + this->base, this->y - this->height, this->z);
			glVertex3f(this->x + this->base, this->y - this->height, this->z + this->base);
		glEnd();
	}
};

Cube cube_bottom(-1.0f, 2.0f, -1.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f);
Cube cube_middle(-1.0f, 2.0f, -1.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f);
Cube cube_top(-1.0f, 2.0f, -1.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f);
Cube rect_top(-1.0f, 4.0f, -1.0f, 2.0f, 4.0f, 0.0f, 0.0f, 0.0f);
Cube claw_left(-0.5f, 2.0f, -0.5f, 1.0f, 2.0f, 0.0f, 0.0f, 0.0f);
Cube claw_right(-0.5f, 2.0f, -0.5f, 1.0f, 2.0f, 0.0f, 0.0f, 0.0f);

float moveOnX = 0.0f, zoom = -20.0f;

void renderCoordinateAxis()
{
	// X axis - green color
	glColor3f(1, 0, 1);
	glBegin(GL_LINES);
	// Left side, negative X
	glVertex2f(-150.0, 0.0);
	glVertex2f(0.0, 0.0);

	// Right side, positive X
	glVertex2f(0.0, 0.0);
	glVertex2f(150.0, 0.0);
	glEnd();

	// Y axis - blue color
	glColor3f(1, 0, 1);
	glBegin(GL_LINES);
	// Top side, positive Y
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 150.0);

	// Bottom side, negative Y
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, -150.0);
	glEnd();
}

void display()
{
	// Clear the screen painting it with the white color
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	// Inform we want to make changes to the modelview matrix, starting
	// with no transformation at all.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Move the camera away from the origin along the Z axis by 10 pixels.
	glTranslatef(0, -8.0f, zoom);
	// Render the X and Y axis to guide ourselves.
	renderCoordinateAxis();

	//Move all on X axis
	glTranslatef(moveOnX, 0.0f, 0.0f);

	//Rotate all under Y axis
	glRotatef(cube_bottom.angle_y, 0.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 0.0f);
	cube_bottom.drawCube();
	
	glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, cube_bottom.height, 0.0f);
		glRotatef(cube_middle.angle_z, 0.0f, 0.0f, 1.0f);
		cube_middle.drawCube();

		glPushMatrix();
			glColor3f(0.0f, 1.0f, 0.0f);
			glTranslatef(0.0f, cube_middle.height, 0.0f);
			glRotatef(cube_top.angle_z, 0.0f, 0.0f, 1.0f);
			cube_top.drawCube();

			glPushMatrix();
				glColor3f(0.0f, 0.0f, 1.0f);
				glTranslatef(0.0f, cube_top.height, 0.0f);
				glRotatef(rect_top.angle_z, 0.0f, 0.0f, 1.0f);
				rect_top.drawCube();

				glColor3f(1.0f, 1.0f, 0.0f);
				glPushMatrix();
					glPushMatrix();
						glTranslatef(-1.0f, rect_top.height, 0.0f);
						glRotatef(claw_left.angle_z, 0.0f, 0.0f, 1.0f);
						claw_left.drawCube();
					glPopMatrix();

					glPushMatrix();
						glTranslatef(1.0f, rect_top.height, 0.0f);
						glRotatef(-claw_right.angle_z, 0.0f, 0.0f, 1.0f);
						claw_right.drawCube();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	// Start the rendering on a new frame
	glutSwapBuffers();
}

void update(int value)
{
	// Request a new frame rendering
	glutPostRedisplay();

	// Re-schedule the update() function to be called after a few
	// milliseconds again.
	glutTimerFunc(UPDATE_INTERVAL_MS, update, 0);
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) { // ESC key
		exit(0);
	}
	else if (key == 81) { //Q key - left rotate - red cube
		if(cube_middle.angle_z <= 40)
			cube_middle.angle_z += 1;
	}
	else if (key == 65) { //A key - right rotate - red cube
		if(cube_middle.angle_z >= -40)
			cube_middle.angle_z -= 1;
	} 
	else if (key == 87) { //W key - left rotate - green cube
		if (cube_top.angle_z <= 40)
			cube_top.angle_z += 1;
	}
	else if (key == 83) { //S key - right rotate - green cube
		if (cube_top.angle_z >= -40)
			cube_top.angle_z -= 1;
	}
	else if (key == 69) { //E key - left rotate - blue cube
		if (rect_top.angle_z <= 45)
			rect_top.angle_z += 1;
	}
	else if (key == 68) { //D key - right rotate - blue cube
		if (rect_top.angle_z >= -45)
			rect_top.angle_z -= 1;
	}
	else if (key == 82) { //R key - open claws
		if (claw_left.angle_z <= 30)
			claw_right.angle_z = claw_left.angle_z += 1;
	}
	else if (key == 70) { //F key - close claws
		if (claw_left.angle_z >= -15)
			claw_right.angle_z = claw_left.angle_z -= 1;
	}
	else if (key == 90) {
		moveOnX -= 0.1f;
	}
	else if (key == 88) {
		moveOnX += 0.1f;
	}
}

void keyboard_spec(int key, int x, int y) {
	if (key == GLUT_KEY_RIGHT) {
		cube_bottom.angle_y += 5;
	}
	else if (key == GLUT_KEY_LEFT) {
		cube_bottom.angle_y -= 5;
	}
}

void mouse(int button, int state, int x, int y)
{
	if (button == 4) {
		zoom -= 1;
	}
	else if (button == 3) {
		zoom += 1;
	}
	std::cout << "Mouse pressed: button=" << button << ", state=" << state << ", x=" << x << " y=" << y << std::endl;
}

void initView()
{
	// We want a window to the world that is a rectangle starting at (0,0)
	// and ending at (WIDTH, HEIGHT).
	glViewport(0, 0, (GLsizei)WIDTH, (GLsizei)HEIGHT);

	// Adjust the global projection (camera)
	glMatrixMode(GL_PROJECTION);

	// Reset any existing projection settings and adjust the field-of-view (FOV)
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 200.0);

	// From now on, every transformation is to be applied on each object, e.g. modelview.
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Braço Robótico");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard_spec);
	glutMouseFunc(mouse);

	initView();

	// Schedule the update() function to be called after a few
	// milliseconds (calculated as 1000 milliseconds divided by FPS).
	glutTimerFunc(UPDATE_INTERVAL_MS, update, 0);

	glutMainLoop();
	return 0;
}