#define STB_IMAGE_IMPLEMENTATION
#include <windows.h>  // for MS Windows
#include<math.h>
#include <stdlib.h>
#include<stdio.h>
#include<vector>
#include<list>
#include <utility>//for pair
#include<string>
#include<iostream>
#include<fstream>
#include <GL/stb_image.h>
#include <GL/glut.h>  // GLUT, include glu.h and gl.h

using namespace std;
/* Global variables */
#define PI 3.1416
bool inGame = false;
bool gameOver = false;
bool pause = false;
int high_score = 0;
int score = 0;
int life = 10;
int time = 0;
float zoom = 10.0;

unsigned int texture;
int width1, height1, nrChannels;
unsigned char *data1 = NULL;


unsigned char string1[100];
int len = glutBitmapLength(GLUT_BITMAP_8_BY_13, string1);
float test = 0.0;

list<pair<float, float>> coinsCenter;
list<pair<float, float>> trapeCenter;



char title[] = "Crazy plane";
pair<float, float> temp = { 0,-0.9 };


int x = GetSystemMetrics(SM_CXSCREEN);
int y = GetSystemMetrics(SM_CYSCREEN);
GLfloat angleFan = 0.0f;     // Rotational angle for cube [NEW]
int refreshMills = 15;        // refresh interval in milliseconds [NEW]
float planeX = -3.0f;
float planeY = 0.0f;
GLfloat planeSlope = 0.0f;
bool straightPlane = true;
GLint i, j, k;
GLfloat ax = 0, bx = 60, cx = -60, dx = 100, ex = 200, fx = -150;

void circle(GLdouble rad, bool coin)
{
	//number of points
	GLint points = 50;
	GLdouble delTheta = (2.0 * PI) / (GLdouble)points;
	GLdouble theta = 0.0;
	//the z-axis
	GLfloat z;
	if (coin) z = 0.0; //if coin or trape
	else z = -30.0;//if cloud
	glBegin(GL_POLYGON);
	{
		for (i = 0; i <= 50; i++, theta += delTheta)
		{
			glVertex3f(rad * cos(theta), rad * sin(theta), z);
		}
	}
	glEnd();
}
void coin_model() {
	glColor3f(1.0f, 0.84f, 0.0f);
	circle(1, 1);
}
void trape_model() {
	glColor3f(1.0f, 0.0f, 0.0f);
	circle(1.2, 1);
}
void trape() {
	for (auto it = trapeCenter.begin(); it != trapeCenter.end(); it++) {
		glLoadIdentity();
		glTranslatef(it->first, it->second, -20.0);
		trape_model();
	}
}
void generateTrape() {
	float x = 70;
	float y = rand() % 20 - 14.5;
	trapeCenter.push_back({ x,y });
}
void coin() {
	for (auto it = coinsCenter.begin(); it != coinsCenter.end(); it++) {
		glLoadIdentity();
		glTranslatef(it->first, it->second, -20.0);
		coin_model();
	}
}
void generateCoins() {
	float x = 70;
	float y = rand() % 24 - 14;
	coinsCenter.push_back({ x,y });
}
void cloud_model_one() {

	glColor3f(1, 1, 1);

	///Top_Left

	glPushMatrix();
	glTranslatef(0, 5, 0);
	circle(5, 0);
	glPopMatrix();

	///Top

	glPushMatrix();
	glTranslatef(5, 8.75, 0);
	circle(5.5, 0);
	glPopMatrix();

	///Right

	glPushMatrix();
	glTranslatef(10, 5, 0);
	circle(5.5, 0);
	glPopMatrix();


	///middle_Fill
	glPushMatrix();
	glTranslatef(9, 5, 0);
	circle(5.5, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8, 5, 0);
	circle(5.5, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7, 4, 0);
	circle(3.5, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6, 4, 0);
	circle(3.5, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, 4, 0);
	circle(3.5, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4, 4, 0);
	circle(3.5, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3, 4, 0);
	circle(3.5, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2, 4, 0);
	circle(3.5, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1, 4, 0);
	circle(3.5, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 4, 0);
	circle(3.5, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1, 4, 0);
	circle(3.5, 0);
	glPopMatrix();

}

void cloud_model_Two() {
	glColor3f(1, 1, 1);

	///Left_Part
	glPushMatrix();
	glTranslatef(12, 0, 0);
	circle(3.5, 0);
	glPopMatrix();

	///Top

	glPushMatrix();
	glTranslatef(15, 1.5, 0);
	circle(5, 0);
	glPopMatrix();

	///Right_Part
	glPushMatrix();
	glTranslatef(18.5, 0.5, 0);
	circle(3.5, 0);
	glPopMatrix();

	///Bottom_Part
	glPushMatrix();
	glTranslatef(15, 0.5, 0);
	circle(3.5, 0);
	glPopMatrix();



}

void cloud_model_Three() {
	glColor3f(1, 1, 1);

	///Left_Part
	glPushMatrix();
	glTranslatef(0, 0, 0);
	circle(5, 0);
	glPopMatrix();

	///Top_Left

	glPushMatrix();
	glTranslatef(6.5, 3.5, 0);
	circle(5, 0);
	glPopMatrix();

	///Top
	glPushMatrix();
	glTranslatef(13, 7, 0);
	circle(5.5, 0);
	glPopMatrix();

	///Top_Right
	glPushMatrix();
	glTranslatef(18.5, 3.5, 0);
	circle(5, 0);
	glPopMatrix();

	///Right_Part
	glPushMatrix();
	glTranslatef(25, 0, 0);
	circle(5, 0);
	glPopMatrix();

	///Bottom_Right
	glPushMatrix();
	glTranslatef(18.5, -3.5, 0);
	circle(6.5, 0);
	glPopMatrix();

	///Bottom_Left
	glPushMatrix();
	glTranslatef(6.5, -3.5, 0);
	circle(6.5, 0);
	glPopMatrix();

	///Bottom
	glPushMatrix();
	glTranslatef(13, -3.5, 0);
	circle(6.5, 0);
	glPopMatrix();




	///****Fill End****

}

void cloud_one() {
	glPushMatrix();
	glTranslatef(ax, 0, -70.0);
	cloud_model_one();
	glPopMatrix();
}


void cloud_two() {
	glPushMatrix();
	glTranslatef(bx, 20, -70.0);
	cloud_model_one();
	glPopMatrix();

}


void cloud_three() {
	glPushMatrix();
	glTranslatef(cx, -20, -70.0);
	cloud_model_Two();
	glPopMatrix();

}

void cloud_four() {
	glPushMatrix();
	glTranslatef(dx, 10, -70.0);
	cloud_model_Two();
	glPopMatrix();

}

void cloud_five() {

	glPushMatrix();
	glTranslatef(ex, -10, -70.0);
	cloud_model_Three();
	glPopMatrix();
}
void cloud_six() {

	glPushMatrix();
	glTranslatef(fx, 20, -70.0);
	cloud_model_Three();
	glPopMatrix();
}



void keySpecialdown(int key, int x, int y) {
	if (inGame && !gameOver && !pause) {
		if (key == GLUT_KEY_UP) {
			if (planeY < 15) {
				planeY += .25;
				if (planeSlope < 20.0)
					planeSlope += 5.0;
				straightPlane = true;
			}

		}
		else if (key == GLUT_KEY_DOWN) {
			if (planeY > -15) {
				planeY -= .25;
				if (planeSlope > -20.0)
					planeSlope -= 5.0;
				straightPlane = true;
			}

		}
	}
}
void keySpecialup(int key, int x, int y) {
	if (inGame && !gameOver && !pause) {
		if (key == GLUT_KEY_UP || key == GLUT_KEY_DOWN) {
			if (planeSlope != 0.0)
				straightPlane = false;
			else
				straightPlane = true;
		}
	}


}

/* Initialize OpenGL Graphics */
void initGL() {
	glClearColor(0.84, 0.90, 0.99, 1.0); // Set background color to black and opaque
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
}

void check(unsigned char *data) {
	if (data)
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}
void load(int imgnum) {
	if (imgnum == 1) {

		data1 = stbi_load("container.jpg", &width1, &height1, &nrChannels, 0);
		check(data1);
	}
}




/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
	glLoadIdentity();                 // Reset the model-view matrix
	if (inGame) {
		if (score > high_score) {
			high_score = score;
		}
		if (gameOver) {
			ofstream writeFile;
			writeFile.open("score.txt");
			writeFile << high_score;
			writeFile.close();
			string s = "Game Over.........!";
			for (int i = 0; i < s.size(); i++)
				string1[i] = s[i];
			glLoadIdentity();
			glTranslatef(0, 0, -20.0f);  // Move right and into the screen
			glRasterPos3f(-5.0f, 0.0f, 0.0f);
			glColor3f(0.0, 0.0, 0.0);
			for (i = 0; i < s.size(); i++) {
				glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string1[i]);
			}
			s = "To Retry game press left click";
			for (int i = 0; i < s.size(); i++)
				string1[i] = s[i];
			glTranslatef(0.0, -2, -20.0f);  // Move right and into the screen
			glRasterPos3f(-15.0f, 0.0f, 0.0f);
			glColor3f(0.0, 0.0, 0.0);
			for (i = 0; i < s.size(); i++) {
				glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string1[i]);
			}
		}
		else {
			if (pause) {
				string s = "Pause.........!";
				for (int i = 0; i < s.size(); i++)
					string1[i] = s[i];
				glLoadIdentity();
				glTranslatef(0, 0, -20.0f);  // Move right and into the screen
				glRasterPos3f(-5.0f, 0.0f, 0.0f);
				glColor3f(0.0, 0.0, 0.0);
				for (i = 0; i < s.size(); i++) {
					glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string1[i]);
				}
				s = "To Resume game press left click";
				for (int i = 0; i < s.size(); i++)
					string1[i] = s[i];
				glTranslatef(0.0, -2, -20.0f);  // Move right and into the screen
				glRasterPos3f(-15.0f, 0.0f, 0.0f);
				glColor3f(0.0, 0.0, 0.0);
				for (i = 0; i < s.size(); i++) {
					glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string1[i]);
				}
			}
			else {
				gluLookAt(
					0, 0, zoom,
					0, 0, 0,
					0, 1, 0
				);
				if (!straightPlane) {
					if (planeSlope > 0) planeSlope -= 2.5;
					else if (planeSlope < 0) planeSlope += 2.5;
					else if (planeSlope == 0) straightPlane = true;
				}
				cloud_three();
				cloud_four();

				cloud_one();




				cloud_two();
				cloud_five();
				cloud_six();

				coin();
				trape();


				glLoadIdentity();                 // Reset the model-view matrix
				glTranslatef(-3.0f, planeY, -20.0f);  // Move right and into the screen
				glRotatef(planeSlope, 0.0f, 0.0f, 1.0f);  // Rotate about (1,1,1)-axis [NEW]

				glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
				   // Top face (y = 1.0f)
				   // Define vertices in counter-clockwise (CCW) order with normal pointing out
				glColor3f(0.98f, 0.97f, 0.96f);     // off white

				glVertex3f(1.0f, 1.0f, -1.0f);
				glVertex3f(0.0f, 1.0f, -1.0f);
				glVertex3f(0.0f, 1.0f, 1.0f);
				glVertex3f(1.0f, 1.0f, 1.0f);

				// Bottom face (y = -1.0f)
				glVertex3f(1.0f, -1.0f, 1.0f);
				glVertex3f(0.0f, -1.0f, 1.0f);
				glVertex3f(0.0f, -1.0f, -1.0f);
				glVertex3f(1.0f, -1.0f, -1.0f);

				// Front face  (z = 1.0f)
				glVertex3f(1.0f, 1.0f, 1.0f);
				glVertex3f(0.0f, 1.0f, 1.0f);
				glVertex3f(0.0f, -1.0f, 1.0f);
				glVertex3f(1.0f, -1.0f, 1.0f);

				// Back face (z = -1.0f)
				glVertex3f(1.0f, -1.0f, -1.0f);
				glVertex3f(0.0f, -1.0f, -1.0f);
				glVertex3f(0.0f, 1.0f, -1.0f);
				glVertex3f(1.0f, 1.0f, -1.0f);

				// Left face (x = -1.0f)
				glVertex3f(0.0f, 1.0f, 1.0f);
				glVertex3f(0.0f, 1.0f, -1.0f);
				glVertex3f(0.0f, -1.0f, -1.0f);
				glVertex3f(0.0f, -1.0f, 1.0f);

				// Right face (x = 1.0f)
				glColor3f(0.88f, 0.87f, 0.82f);     // gray
				glVertex3f(1.0f, 1.0f, -1.0f);
				glVertex3f(1.0f, 1.0f, 1.0f);
				glVertex3f(1.0f, -1.0f, 1.0f);
				glVertex3f(1.0f, -1.0f, -1.0f);

				//second cube//
				//top face
				glColor3f(0.0f, 0.54f, 0.54f);     // blue
				glVertex3f(0.0f, 1.0f, -1.0f);
				glVertex3f(-2.0f, 1.0f, -1.0f);
				glVertex3f(-2.0f, 1.0f, 1.0f);
				glVertex3f(0.0f, 1.0f, 1.0f);

				//bottom face
				glVertex3f(0.0f, -1.0f, -1.0f);
				glVertex3f(-2.0f, -1.0f, -1.0f);
				glVertex3f(-2.0f, -1.0f, 1.0f);
				glVertex3f(0.0f, -1.0f, 1.0f);

				// Back face (z = -1.0f)
				glVertex3f(0.0f, -1.0f, -1.0f);
				glVertex3f(-2.0f, -1.0f, -1.0f);
				glVertex3f(-2.0f, 1.0f, -1.0f);
				glVertex3f(0.0f, 1.0f, -1.0f);

				// Front face  (z = 1.0f)
				glVertex3f(0.0f, 1.0f, 1.0f);
				glVertex3f(-2.0f, 1.0f, 1.0f);
				glVertex3f(-2.0f, -1.0f, 1.0f);
				glVertex3f(0.0f, -1.0f, 1.0f);

				// Left face 
				glVertex3f(-2.0f, 1.0f, 1.0f);
				glVertex3f(-2.0f, 1.0f, -1.0f);
				glVertex3f(-2.0f, -1.0f, -1.0f);
				glVertex3f(-2.0f, -1.0f, 1.0f);

				//tail object
				//top face
				glVertex3f(-2.0f, 1.0f, -1.0f);
				glVertex3f(-4.0f, 1.0f, -0.5f);
				glVertex3f(-4.0f, 1.0f, 0.5f);
				glVertex3f(-2.0f, 1.0f, 1.0f);

				//bottom face
				glVertex3f(-2.0f, 0.0f, -1.0f);
				glVertex3f(-4.0f, 0.5f, -0.5f);
				glVertex3f(-4.0f, 0.5f, 0.5f);
				glVertex3f(-2.0f, 0.0f, 1.0f);

				//back face
				glVertex3f(-2.0f, 0.0f, -1.0f);
				glVertex3f(-4.0f, 0.5f, -0.5f);
				glVertex3f(-4.0f, 1.0f, -0.5f);
				glVertex3f(-2.0f, 1.0f, -1.0f);

				//front face
				glVertex3f(-2.0f, 0.0f, 1.0f);
				glVertex3f(-4.0f, 0.5f, 0.5f);
				glVertex3f(-4.0f, 1.0f, 0.5f);
				glVertex3f(-2.0f, 1.0f, 1.0f);

				//last cube in tail
				//top face
				glVertex3f(-4.0f, 1.5f, -0.5f);
				glVertex3f(-4.5f, 1.5f, -0.5f);
				glVertex3f(-4.5f, 1.5f, 0.5f);
				glVertex3f(-4.0f, 1.5f, 0.5f);

				//bottom face
				glVertex3f(-4.0f, 0.5f, -0.5f);
				glVertex3f(-4.5f, 0.5f, -0.5f);
				glVertex3f(-4.5f, 0.5f, 0.5f);
				glVertex3f(-4.0f, 0.5f, 0.5f);

				//back face
				glVertex3f(-4.0f, 0.5f, -0.5f);
				glVertex3f(-4.5f, 0.5f, -0.5f);
				glVertex3f(-4.5f, 1.5f, -0.5f);
				glVertex3f(-4.0f, 1.5f, -0.5f);

				//front face
				glVertex3f(-4.0f, 0.5f, 0.5f);
				glVertex3f(-4.5f, 0.5f, 0.5f);
				glVertex3f(-4.5f, 1.5f, 0.5f);
				glVertex3f(-4.0f, 1.5f, 0.5f);

				//right face
				glVertex3f(-4.0f, 1.5f, -0.5f);
				glVertex3f(-4.0f, 0.5f, -0.5f);
				glVertex3f(-4.0f, 0.5f, 0.5f);
				glVertex3f(-4.0f, 1.5f, 0.5f);

				//left face
				glVertex3f(-4.5f, 1.5f, -0.5f);
				glVertex3f(-4.5f, 0.5f, -0.5f);
				glVertex3f(-4.5f, 0.5f, 0.5f);
				glVertex3f(-4.5f, 1.5f, 0.5f);

				//left wing
				//top face
				glVertex3f(-1.5f, 1.0f, -1.0f);
				glVertex3f(-1.5f, 1.0f, -3.0f);
				glVertex3f(-3.0f, 1.0f, -3.0f);
				glVertex3f(-3.0f, 1.0f, -1.0f);

				//bottom face
				glVertex3f(-1.5f, 0.8f, -1.0f);
				glVertex3f(-1.5f, 0.8f, -3.0f);
				glVertex3f(-3.0f, 0.8f, -3.0f);
				glVertex3f(-3.0f, 0.8f, -1.0f);

				//front face
				glVertex3f(-1.5f, 1.0f, -3.0f);
				glVertex3f(-1.5f, 0.8f, -3.0f);
				glVertex3f(-3.0f, 0.8f, -3.0f);
				glVertex3f(-3.0f, 1.0f, -3.0f);

				//right face
				glVertex3f(-1.5f, 1.0f, -1.0f);
				glVertex3f(-1.5f, 0.8f, -1.0f);
				glVertex3f(-1.5f, 0.8f, -3.0f);
				glVertex3f(-1.5f, 1.0f, -3.0f);

				//left face
				glVertex3f(-3.0f, 1.0f, -1.0f);
				glVertex3f(-3.0f, 0.8f, -1.0f);
				glVertex3f(-3.0f, 0.8f, -3.0f);
				glVertex3f(-3.0f, 1.0f, -3.0f);

				//right wing
				//top face
				glVertex3f(-1.5f, 1.0f, 1.0f);
				glVertex3f(-1.5f, 1.0f, 3.0f);
				glVertex3f(-3.0f, 1.0f, 3.0f);
				glVertex3f(-3.0f, 1.0f, 1.0f);

				//bottom face
				glVertex3f(-1.5f, 0.8f, 1.0f);
				glVertex3f(-1.5f, 0.8f, 3.0f);
				glVertex3f(-3.0f, 0.8f, 3.0f);
				glVertex3f(-3.0f, 0.8f, 1.0f);

				//front face
				glVertex3f(-1.5f, 1.0f, 3.0f);
				glVertex3f(-1.5f, 0.8f, 3.0f);
				glVertex3f(-3.0f, 0.8f, 3.0f);
				glVertex3f(-3.0f, 1.0f, 3.0f);

				//right face
				glVertex3f(-1.5f, 1.0f, 1.0f);
				glVertex3f(-1.5f, 0.8f, 1.0f);
				glVertex3f(-1.5f, 0.8f, 3.0f);
				glVertex3f(-1.5f, 1.0f, 3.0f);

				//left face
				glVertex3f(-3.0f, 1.0f, 1.0f);
				glVertex3f(-3.0f, 0.8f, 1.0f);
				glVertex3f(-3.0f, 0.8f, 3.0f);
				glVertex3f(-3.0f, 1.0f, 3.0f);



				//

				glEnd();  // End of drawing color-cube
				glRotatef(angleFan, 1.0f, 0.0f, 0.0f);




				glBegin(GL_QUADS);

				//fan object
				glColor3f(test, 0.0f, 0.0f);

				//axe
				//x -> 1 x -> 1.4
				//y ->0.1 : -0.1
				//z ->0.1 : -0.1

				//top face
				glVertex3f(1.0f, 0.1f, -0.1f);
				glVertex3f(1.4f, 0.1f, -0.1f);
				glVertex3f(1.4f, 0.1f, 0.1f);
				glVertex3f(1.0f, 0.1f, 0.1f);
				//bottom face
				glVertex3f(1.0f, -0.1f, -0.1f);
				glVertex3f(1.4f, -0.1f, -0.1f);
				glVertex3f(1.4f, -0.1f, 0.1f);
				glVertex3f(1.0f, -0.1f, 0.1f);
				//front face
				glVertex3f(1.0f, 0.1f, 0.1f);
				glVertex3f(1.4f, 0.1f, 0.1f);
				glVertex3f(1.4f, -0.1f, 0.1f);
				glVertex3f(1.0f, -0.1f, 0.1f);
				//back face
				glVertex3f(1.0f, 0.1f, -0.1f);
				glVertex3f(1.4f, 0.1f, -0.1f);
				glVertex3f(1.4f, -0.1f, -0.1f);
				glVertex3f(1.0f, -0.1f, -0.1f);

				//fan
				//top face
				glVertex3f(1.4f, 1.2f, -0.2f);
				glVertex3f(1.5f, 1.2f, -0.2f);
				glVertex3f(1.5f, 1.2f, 0.2f);
				glVertex3f(1.4f, 1.2f, 0.2f);

				//top face
				glVertex3f(1.4f, -1.2f, -0.2f);
				glVertex3f(1.5f, -1.2f, -0.2f);
				glVertex3f(1.5f, -1.2f, 0.2f);
				glVertex3f(1.4f, -1.2f, 0.2f);


				//right face
				glVertex3f(1.5f, 1.2f, -0.2f);
				glVertex3f(1.5f, 1.2f, 0.2f);
				glVertex3f(1.5f, -1.2f, 0.2f);
				glVertex3f(1.5f, -1.2f, -0.2f);

				//left face
				glVertex3f(1.4f, 1.2f, -0.2f);
				glVertex3f(1.4f, 1.2f, 0.2f);
				glVertex3f(1.4f, -1.2f, 0.2f);
				glVertex3f(1.4f, -1.2f, -0.2f);

				//front face
				glVertex3f(1.4f, 1.2f, 0.2f);
				glVertex3f(1.5f, 1.2f, 0.2f);
				glVertex3f(1.5f, -1.2f, 0.2f);
				glVertex3f(1.4f, -1.2f, 0.2f);

				//back face
				glVertex3f(1.4f, 1.2f, -0.2f);
				glVertex3f(1.5f, 1.2f, -0.2f);
				glVertex3f(1.5f, -1.2f, -0.2f);
				glVertex3f(1.4f, -1.2f, -0.2f);
				glEnd();
				glRotatef(90.0, 1.0f, 0.0f, 0.0f);

				glBegin(GL_QUADS);
				//fan object
				glColor3f(0.0f, 0.0f, 0.0f);

				//top face
				glVertex3f(1.4f, 1.2f, -0.2f);
				glVertex3f(1.5f, 1.2f, -0.2f);
				glVertex3f(1.5f, 1.2f, 0.2f);
				glVertex3f(1.4f, 1.2f, 0.2f);

				//top face
				glVertex3f(1.4f, -1.2f, -0.2f);
				glVertex3f(1.5f, -1.2f, -0.2f);
				glVertex3f(1.5f, -1.2f, 0.2f);
				glVertex3f(1.4f, -1.2f, 0.2f);


				//right face
				glVertex3f(1.5f, 1.2f, -0.2f);
				glVertex3f(1.5f, 1.2f, 0.2f);
				glVertex3f(1.5f, -1.2f, 0.2f);
				glVertex3f(1.5f, -1.2f, -0.2f);

				//left face
				glVertex3f(1.4f, 1.2f, -0.2f);
				glVertex3f(1.4f, 1.2f, 0.2f);
				glVertex3f(1.4f, -1.2f, 0.2f);
				glVertex3f(1.4f, -1.2f, -0.2f);

				//front face
				glVertex3f(1.4f, 1.2f, 0.2f);
				glVertex3f(1.5f, 1.2f, 0.2f);
				glVertex3f(1.5f, -1.2f, 0.2f);
				glVertex3f(1.4f, -1.2f, 0.2f);

				//back face
				glVertex3f(1.4f, 1.2f, -0.2f);
				glVertex3f(1.5f, 1.2f, -0.2f);
				glVertex3f(1.5f, -1.2f, -0.2f);
				glVertex3f(1.4f, -1.2f, -0.2f);
				glEnd();
				string s = "Score: " + to_string(score);
				for (int i = 0; i < s.size(); i++)
					string1[i] = s[i];
				glLoadIdentity();
				glTranslatef(0.0, 0.0, -20.0f);  // Move right and into the screen
				glRasterPos3f(25.0f, 15.0f, 1.0f);
				glColor3f(0.0, 0.0, 0.0);
				for (i = 0; i < s.size(); i++) {
					glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string1[i]);
				}
				s = "High score: " + to_string(high_score);
				for (int i = 0; i < s.size(); i++)
					string1[i] = s[i];
				glLoadIdentity();
				glTranslatef(0.0, 0.0, -20.0f);  // Move right and into the screen
				glRasterPos3f(25.0f, 14.0f, 1.0f);
				glColor3f(0.0, 0.0, 0.0);
				for (i = 0; i < s.size(); i++) {
					glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string1[i]);
				}
				s = "life: " + to_string(life) + "/10";
				for (int i = 0; i < s.size(); i++)
					string1[i] = s[i];
				glLoadIdentity();
				glTranslatef(0.0, 0.0, -20.0f);  // Move right and into the screen
				glRasterPos3f(-30.0f, 15.0f, 1.0f);
				glColor3f(0.0, 0.0, 0.0);
				for (i = 0; i < s.size(); i++) {
					glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string1[i]);
				}
				angleFan += 10.0f;
			}
		}

	}
	else {
		string s = "Hello.........!";
		for (int i = 0; i < s.size(); i++)
			string1[i] = s[i];
		glLoadIdentity();
		//load(1);
		glTranslatef(0, 10, -20.0f);
		glColor3f(1, 0, 0);
		glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(-2, 2, 0);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(2, 2, 0);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(2, -2, 0);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(-2, -2, 0);
		glEnd();
		load(0);
		glLoadIdentity();
		glTranslatef(0, 0, -20.0f);  // Move right and into the screen
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos3f(-5.0f, 0.0f, 0.0f);
		for (i = 0; i < s.size(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string1[i]);
		}
		s = "To start game press left click";
		for (int i = 0; i < s.size(); i++)
			string1[i] = s[i];
		glTranslatef(0.0, -2, -20.0f);  // Move right and into the screen
		glRasterPos3f(-15.0f, 0.0f, 0.0f);
		glColor3f(0.0, 0.0, 0.0);
		for (i = 0; i < s.size(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string1[i]);
		}
	}

	glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)

	// Update the rotational angle after each refresh [NEW]
}
void move_right() {

	ax = ax - 0.3;
	bx = bx - 0.3;
	cx = cx - 0.3;
	dx = dx - 0.3;
	ex = ex - 0.3;
	fx = fx - 0.3;

	if (ax < -250) {
		ax = 200;
	}
	if (bx < -250) {
		bx = 200;

	}
	if (cx < -250) {
		cx = 200;

	}
	if (dx < -250) {
		dx = 250;

	}
	if (ex < -250) {
		ex = 200;

	}
	if (fx < -250) {
		fx = 200;

	}


}

/* Called back when timer expired [NEW] */
void timer(int value) {
	if (inGame && !gameOver && !pause) {
		move_right();
		time++;
		if (time % 200 == 0) {
			generateCoins();
		}
		if (time % 250 == 0) {
			generateTrape();
			time = 1;
		}
		if (coinsCenter.size()) {
			for (auto it = coinsCenter.begin(); it != coinsCenter.end(); ++it)
			{
				if (coinsCenter.front().first < -40) {
					life--;
					if (life == 0) gameOver = true;
					coinsCenter.pop_front();
					break;
				}
				else {
					it->first -= 0.2;
				}
				//collision detect coin
				float distance = sqrt((pow((it->first + 1.5), 2) + pow(it->second - planeY, 2)));
				if (distance <= 1.5) {
					score++;
					coinsCenter.erase(it);
					break;
				}

			}
		}
		if (trapeCenter.size()) {
			for (auto it = trapeCenter.begin(); it != trapeCenter.end(); ++it)
			{
				if (trapeCenter.front().first < -40) {
					trapeCenter.pop_front();
					break;
				}
				else {
					it->first -= 0.25;
				}
				float distance = sqrt((pow((it->first + 1.5), 2) + pow(it->second - planeY, 2)));
				if (distance <= 1.75) {
					life--;
					if (life == 0) gameOver = true;
					trapeCenter.erase(it);
					break;
				}

			}
		}

	}

	glutPostRedisplay();      // Post re-paint request to activate display()
	glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset
	// Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(90.0f, aspect, 0.1f, 500.0f);

}

void mouse(int key, int state, int x, int y) {
	if (inGame) {
		if (gameOver) {

			switch (key)
			{
			case GLUT_LEFT_BUTTON:
				if (state == GLUT_DOWN)
				{

					gameOver = false;
					coinsCenter.clear();
					trapeCenter.clear();
					angleFan = 0.0f;
					planeY = 0.0f;
					planeSlope = 0.0f;
					straightPlane = true;
					ax = 0;
					bx = 60;
					cx = -60;
					dx = 100;
					ex = 200;
					fx = -150;
					pause = false;
					score = 0;
					life = 10;
					time = 0;
				}
				break;
			default:
				break;
			}
		}
		else {
			if (pause) {
				switch (key)
				{
				case GLUT_LEFT_BUTTON:
					if (state == GLUT_DOWN)
					{
						pause = false;
					}
					break;
				default:
					break;
				}
			}
			else {
				switch (key)
				{
				case GLUT_RIGHT_BUTTON:
					if (state == GLUT_DOWN)
					{
						pause = true;
					}
					break;
				default:
					break;
				}
			}
		}
	}
	else {
		switch (key)
		{
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN)
			{
				inGame = true;
			}
			break;
		default:
			break;
		}
	}

}
void keyboard(unsigned char key, int x, int y) {
	if (key == 'i' || key == 'I')
	{
		if (zoom > 1)
			zoom -= 3;
	}
	else if (key == 'o' || key == 'O')
		if (zoom < 15)
			zoom += 3;
		else if (key == 27)
			exit(0);
}


/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
	ifstream readFile;
	readFile.open("score.txt");
	if (readFile.is_open()) {
		string s;
		getline(readFile, s);
		readFile.close();
		if (s.size() > 0) {
			int temp = stoi(s);
			if (temp > high_score) high_score = temp;
			else {
				ofstream writeFile;
				writeFile.open("score.txt");
				writeFile << high_score;
				writeFile.close();
			}
		}
		else {
			ofstream writeFile;
			writeFile.open("score.txt");
			writeFile << 0;
			writeFile.close();
		}
	}
	else {
		ofstream writeFile;
		writeFile.open("score.txt");
		writeFile << 0;
		writeFile.close();
	}
	glutInit(&argc, argv);            // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	glutInitWindowSize(x, y);
	glutCreateWindow(title);          // Create window with the given title
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keySpecialdown);
	glutSpecialUpFunc(keySpecialup);
	glutDisplayFunc(display);       // Register callback handler for window re-paint event
	glutReshapeFunc(reshape);       // Register callback handler for window re-size event
	initGL();                       // Our own OpenGL initialization
	glutTimerFunc(0, timer, 0);     // First timer call immediately [NEW]
	glutMouseFunc(mouse);
	high_score++;
	glutMainLoop();                 // Enter the infinite event-processing loop
	return 0;
}

