/*

	GRAFIIKKAOHJELMOINTI
	Metropolia AMK, 2016

	The following libraries are available in this project:

	OpenGL		(graphics)				https://www.opengl.org/
	GLU			(OpenGL utilities)		https://www.opengl.org/resources/libraries/
	GLEW		(OpenGL extensions)		http://glew.sourceforge.net/
	GLM			(OpenGL mathematics)	http://glm.g-truc.net/0.9.8/index.html
	SDL2		(windowing, event)		https://www.libsdl.org/
	SDL2_image	(image loading)			https://www.libsdl.org/projects/SDL_image/
	SDK2_mixer	(audio mixer)			https://www.libsdl.org/projects/SDL_mixer/
	Bullet		(3D physics)			http://bulletphysics.org/wordpress/
	Box2D		(2D physics)			http://box2d.org/

*/
#define VERTICES 100

#include "esimerkki.h"
#include <math.h>
#include <iostream>
#include <vector>

float radius = 100.0f;
float number = 200.0f;
std::vector<GLfloat> vertices_vector;
float angle = 0.0;
GLuint list;
GLuint cubeVBO;
float data[] =
{
    number, -number, number,
    number, number, number ,
    -number, number, number,
    -number, -number, number,

    number, number, -number,
    number, number, number,
    number, -number, number,
    number, -number, -number,

    -number, number, number,
    number, number, number,
    number, number, -number,
    -number, number, -number,

    -number, -number, number,
    -number, number, number,
    -number, number, -number,
    -number, -number, -number,

    number, -number, number,
    -number, -number, number,
    -number, -number, -number,
    number, -number, -number,

    number, number, -number,
    number, -number, -number,
    -number, -number, -number,
    -number, number, -number
};

void cube();
void cubeNormals();
void t1t2();
void t1t3();
void t1t4();
void t2t1();
void t2t2();
void t2t3();
void t2t4();
void t3t1_init();
void t3t1_display();
void t3t2_init();
void t3t2_display();
void t4t4();
void t4t5();


int main(int argc, char* argv[])
{
	if (!init()) return 1;

	//
	// OpenGL initializations, see esimerkki.h for defines.
	//
	glClearColor(CLEAR_COLOR);
	glColor3f(DRAW_COLOR);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 10, 10000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//
	// Main rendering loop.
	//

    //
	//t1t1
    //
	//std::cout << "VENDOR: " << glGetString(GL_VENDOR) << std::endl
	//		  << "RENDERER: " << glGetString(GL_RENDERER) << std::endl
	//		  << "VERSION: " << glGetString(GL_VERSION) << std::endl
	//		  << "SHADING LANGUAGE VERSION: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	//std::cout << "EXTENSIONS: " << glGetString(GL_EXTENSIONS) << std::endl;

	for (int i = 0; i < VERTICES * 3; ++i)
	{
		float angle = 2.0f * M_PI * float(i) / float(VERTICES);
		float x = radius * cosf(angle);
		float y = radius * sinf(angle);
		vertices_vector.push_back(x);
		vertices_vector.push_back(y);
		vertices_vector.push_back(0.0f);
	}
    t3t1_init();
    t3t2_init();

	SDL_Event event;
	while (1)
	{
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		// ***************************************
		// Your OpenGL rendering code starts here!
		// ***************************************
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0, 0, 2000, 0, 0, 0, 0, 1, 0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_DEPTH_TEST);

		//glBegin(GL_TRIANGLES);
		//glVertex3f(-100, 0, -100);
		//glVertex3f(100, 0, -100);
		//glVertex3f(0, 100, -100);
		//glEnd();

		//t1t2();
		//t1t3();
		//t1t4();
        
        //t2t1();
        //t2t2();
        //t2t3();
        //t2t4();

        //t3t1_display();
        //t3t2_display();

        //t4t4();
        t4t5();

		

		// ***************************************
		// ...and ends here.
		// ***************************************

		SDL_GL_SetSwapInterval(1);
		SDL_GL_SwapWindow(window);
	}
    glDeleteBuffers(1, &cubeVBO);
	if (!fini()) return 1;
	return 0;
}

void t1t2()
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < VERTICES; ++i)
	{
		float angle = 2.0f * M_PI * float(i) / float(VERTICES);
		float x = radius * cosf(angle);
		float y = radius * sinf(angle); 
		glVertex2f(x, y);
	}
	glEnd();
}

void t1t3()
{
	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	for (int i = 0; i < (VERTICES * 3); ++i)
	{
		float angle = 2.0f * M_PI * float(i) / float(VERTICES);
		float x = radius * cosf(angle);
		float y = radius * sinf(angle);
		glVertex2f(x, y);
		glVertex2f(0.0f, 0.0f);
	}
	glEnd();
}

void cube()
{
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(number, -number, number);
    glVertex3f(number, number, number);
    glVertex3f(-number, number, number);
    glVertex3f(-number, -number, number);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(number, number, -number);
    glVertex3f(number, number, number);
    glVertex3f(number, -number, number);
    glVertex3f(number, -number, -number);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-number, number, number);
    glVertex3f(number, number, number);
    glVertex3f(number, number, -number);
    glVertex3f(-number, number, -number);

    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-number, -number, number);
    glVertex3f(-number, number, number);
    glVertex3f(-number, number, -number);
    glVertex3f(-number, -number, -number);

    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(number, -number, number);
    glVertex3f(-number, -number, number);
    glVertex3f(-number, -number, -number);
    glVertex3f(number, -number, -number);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(number, number, -number);
    glVertex3f(number, -number, -number);
    glVertex3f(-number, -number, -number);
    glVertex3f(-number, number, -number);
    glEnd();
}

void t1t4()
{
	glEnableClientState(GL_VERTEX_ARRAY); //Enable the vertex array
	glVertexPointer(3, GL_FLOAT, 0, &vertices_vector[0]); //Tell OpenGL where the vertices are

	glDrawArrays(GL_TRIANGLE_FAN, 0, VERTICES);

	//Finally disable the vertex array
	glDisableClientState(GL_VERTEX_ARRAY);
}

void t2t1()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    cube();
}

void t2t2()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    angle++;
    glRotatef(angle, 0.0, 1.0, 1.0);
    cube();
}
void t2t3()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    angle++;
    glPushMatrix();
    glTranslatef(-400.0, -300.0, -100.0);
    glRotatef(angle, 1.0, 0.0, 0.0);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300.0, 500.0, -100.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300.0, -400.0, -100.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    cube();
    glPopMatrix();
}
void t2t4()
{
    angle++;
    glPushMatrix();
    glTranslatef(-400.0, -300.0, -100.0);
    glRotatef(angle, 1.0, 0.0, 0.0);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300.0, 500.0, -100.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300.0, -400.0, -100.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    cube();
    glPopMatrix();
}

void t3t1_init()
{
    list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    cube();
    glEndList();
    glShadeModel(GL_FLAT);
}
void t3t1_display()
{
    angle++;
    GLuint i;
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
    glTranslatef(-400.0, -300.0, -100.0);
    glRotatef(angle, 1.0, 0.0, 0.0);
    glCallList(list);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300.0, 500.0, -100.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glCallList(list);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300.0, -400.0, -100.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glCallList(list);
    glPopMatrix();
    
    glFlush();
}
void t3t2_init()
{
    glGenBuffers(1, &cubeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
}
void t3t2_display()
{
    angle++;
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glVertexPointer(3, GL_FLOAT, 0, NULL);
    glEnableClientState(GL_VERTEX_ARRAY);
    glPushMatrix();
    glTranslatef(-400.0, -300.0, -100.0);
    glRotatef(angle, 1.0, 0.0, 0.0);
    glDrawArrays(GL_QUADS, 0, sizeof(data) / sizeof(float) / 3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300.0, 500.0, -100.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glDrawArrays(GL_QUADS, 0, sizeof(data) / sizeof(float) / 3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300.0, -400.0, -100.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glDrawArrays(GL_QUADS, 0, sizeof(data) / sizeof(float) / 3);
    glPopMatrix();

    glFlush();
}

void t4t4()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    t2t4();
}

void t4t5()
{
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat mat_diffuse[] = { 1.0, 0.0, 0.0 };
    GLfloat diffuse_light[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    GLfloat light_position[] = { 500.0, 500.0, 1000.0, 0.0 };

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);

    angle++;
    glPushMatrix();
    glTranslatef(-400.0, -300.0, -100.0);
    glRotatef(angle, 1.0, 0.0, 0.0);
    cubeNormals();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300.0, 500.0, -100.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    cubeNormals();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300.0, -400.0, -100.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    cubeNormals();
    glPopMatrix();
}
void cubeNormals()
{
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(number, -number, number);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(number, number, number);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-number, number, number);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-number, -number, number);

    glColor3f(1.0f, 0.0f, 0.0f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(number, number, -number);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(number, number, number);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(number, -number, number);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(number, -number, -number);
    glNormal3f(1.0f, 0.0f, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-number, number, number);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(number, number, number);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(number, number, -number);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-number, number, -number);

    glColor3f(1.0f, 1.0f, 0.0f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-number, -number, number);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-number, number, number);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-number, number, -number);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-number, -number, -number);

    glColor3f(0.0f, 1.0f, 1.0f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(number, -number, number);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-number, -number, number);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-number, -number, -number);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(number, -number, -number);

    glColor3f(1.0f, 1.0f, 1.0f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(number, number, -number);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(number, -number, -number);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-number, -number, -number);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-number, number, -number);
    glEnd();
}