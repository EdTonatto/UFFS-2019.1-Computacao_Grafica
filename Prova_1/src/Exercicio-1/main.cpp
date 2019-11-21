/*
 * Autor: Eduardo Tonatto <edtonatto@gmail.com>
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

float g_cen_rot = 0;
float g_ext_rot = 0;
float eye_x= 0, eye_y = 20, eye_z = -30;

class Cube {
public:
	float x, y, z;
	float base, height;

	Cube(float p_x, float p_y, float p_z, float p_base, float p_height) {
		this->x = p_x;
		this->y = p_y;
		this->z = p_z;
		this->base = p_base;
		this->height = p_height;
	}

	void drawCube() {
		//Front face - Red
		glColor3d(1, 0, 0);
		glBegin(GL_QUADS);
			glVertex3f(this->x, this->y, this->z);
			glVertex3f(this->x, this->y - this->height, this->z);
			glVertex3f(this->x + this->base, this->y - this->height, this->z);
			glVertex3f(this->x + this->base, this->y, this->z);
		glEnd();

		//Right face - Green
		glColor3d(0, 1, 0);
		glBegin(GL_QUADS);
			glVertex3f(this->x, this->y, this->z);
			glVertex3f(this->x, this->y - this->height, this->z);
			glVertex3f(this->x, this->y - this->height, this->z + this->base);
			glVertex3f(this->x, this->y, this->z + this->base);
		glEnd();

		//Back face - Blue
		glColor3d(0, 0, 1);
		glBegin(GL_QUADS);
			glVertex3f(this->x, this->y, this->z + this->base);
			glVertex3f(this->x, this->y - this->height, this->z + this->base);
			glVertex3f(this->x + this->base, this->y - this->height, this->z + this->base);
			glVertex3f(this->x + this->base, this->y, this->z + this->base);
		glEnd();

		//Left face - Purple
		glColor3d(0.6, 0.2, 0.6);
		glBegin(GL_QUADS);
			glVertex3f(this->x + this->base, this->y, this->z);
			glVertex3f(this->x + this->base, this->y - this->height, this->z);
			glVertex3f(this->x + this->base, this->y - this->height, this->z + this->base);
			glVertex3f(this->x + this->base, this->y, this->z + this->base);
		glEnd();

		//Top face - Yellow
		glColor3d(1, 1, 0);
		glBegin(GL_QUADS);
			glVertex3f(this->x, this->y, this->z + this->base);
			glVertex3f(this->x, this->y, this->z);
			glVertex3f(this->x + this->base, this->y, this->z);
			glVertex3f(this->x + this->base, this->y, this->z + this->base);
		glEnd();

		//Bottom face - Brown
		glColor3d(0.59, 0.29, 0);
		glBegin(GL_QUADS);
			glVertex3f(this->x, this->y - this->height, this->z + this->base);
			glVertex3f(this->x, this->y - this->height, this->z);
			glVertex3f(this->x + this->base, this->y - this->height, this->z);
			glVertex3f(this->x + this->base, this->y - this->height, this->z + this->base);
		glEnd();
	}

	void cubeRotation(char WhichCube, float x, float y, float z) {
		if(WhichCube == 'C')
			glRotatef(g_cen_rot, x, y, z);
		if(WhichCube == 'E')
			glRotatef(g_ext_rot, x, y, z);
	}
	
	void cubeTranslation(float x, float y, float z) {
		glTranslatef(x, y, z);
	}
};

Cube center_cube(-1.5f, 1.5f, -1.5f, 3.0f, 3.0f);
Cube external_cube(-1.5f, 1.5f, -1.5f, 3.0f, 3.0f);

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
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//renderCoordinateAxis();

	glPushMatrix();
		center_cube.cubeRotation('C', 0.0f, 1.0f, 0.0f);
		center_cube.drawCube();
		glPushMatrix();
			external_cube.cubeRotation('E', 0.0f, 1.0f, 0.0f);
			external_cube.cubeTranslation(-13.5f, 0.0f, 0.0f);
			external_cube.cubeRotation('C', 0.0f, 0.0f, 1.0f);
			external_cube.drawCube();
		glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
}

void update(int value)
{
	if (g_cen_rot >= 0 && g_cen_rot <= 359) {
		g_cen_rot++;
		g_ext_rot -= 2;
	}
	else {
		g_cen_rot = 0;
		g_ext_rot = 0;
	}

	//std::cout << "G_CEN_ROT = " << g_cen_rot << " G_EXT_ROT = " << g_ext_rot << std::endl;
	glutPostRedisplay();

	glutTimerFunc(UPDATE_INTERVAL_MS, update, 0);
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) {
		exit(0);
	}
}

void keyboard_spec(int key, int x, int y) {

}

void mouse(int button, int state, int x, int y)
{
	std::cout << "Mouse pressed: button=" << button << ", state=" << state << ", x=" << x << " y=" << y << std::endl;
}

void initView()
{
	glViewport(0, 0, (GLsizei)WIDTH, (GLsizei)HEIGHT);

	// Adjust the global projection (camera)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 200.0);
	gluLookAt(eye_x, eye_y, eye_z, 0, 0, 0, 0, 1, 0);

	// From now on, every transformation is to be applied on each object, e.g. modelview.
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Prova 1 - Terra Plana - Lua Plana");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard_spec);
	glutMouseFunc(mouse);

	initView();

	glutTimerFunc(UPDATE_INTERVAL_MS, update, 0);

	glutMainLoop();
	return 0;
}