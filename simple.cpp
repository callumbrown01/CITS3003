#include "Angel.h"
#include "GL/glut.h"

using namespace std;

const int NumTriangles = 2; //two triangles to be displayed
const int NumVertices = 6; // two triangles with three vertices each

Vec3 points[NumVertices] = {
    vec3(-0.5, -0.5, 0), vec3(0.5, -0.5, 0), vec3(-0.5, 0.5, 0),
    vec3(0.5, 0.5, 0), vec3(-0.5, 0.5, 0), vec3(0.5, -0.5, 0)
};

void init(void)
{
    // create vertex array object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // create and initialise a vertex buffer object
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    // move the six vertices to the vertex buffer object
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    // load shaders and use the resulting program
    GLuint program = InitShader("vertex.glsl", "fragment.glsl");
    glUseProgram(program);

    // initialise the vertex position attribute from the vertex shader program
    GLuint vPos = glGetAttributeLocation(program, "vPosition");
    glEnableVertexAttribArray(vPos);
    glVertexAttribPointer(vPos, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    // give the image a black background
    glClearColor(0,0,0,0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // clears the screen
    glDrawArrays(GL_TRIANGLES, 0, NumVertices); // draw the two triangles in the vertex buffer object
    glFlush(); // queue the process and force the rendering to show
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv); // initialises GLUT
    glutInitDisplayModel(GLUT_RGBA); // sets the display mode
    glutInitWindowSize(256, 256); // width x height in pixels of the new window
    glutCreateWindow("simple"); // new window named 'simple'

    inti(); // call earlier initialisation function
    glutDisplayFunc(display);  // registers the callback function
    glutMainLoop(); // wait for an event to occur
}