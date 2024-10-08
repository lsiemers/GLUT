#include <windows.h>
#include <GL/glut.h>	
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>

using namespace std;

// *********** Global values ************************************************
/* These values are global because the timing call back functions will only take certain parameters
   hence their needs to be global variables to communicate with these functions */
float theta = 0.0; // global angular value for rotation
float scale1 = 1.0; // global scaling value for triangle
float dx = 7.0, dy = -3.0; // global movement value for dx and dy
int frame = 1;

void RenderScene(void); // this is a function to draw a square in an opened window
void loadicon(float[], float[], float[], float[]); /* loads the triangle icon */
void drawicon(float[], float[], float[], float[]); /* draws the icon */
void settrans(float[][3], float, float, float); /* sets the transformation matrix for desired scale, rotation, new pos */
float xprime(float, float, float[][3]); /* calculates x' from x and transform */
float yprime(float, float, float[][3]); /* calculates y' from y and transform */
void transform(float[], float[], float[], float[], float[][3], float[], float[], float[], float[]); /* performs the transformation on the icon pattern */
void SetupRC(void); // sets up the clear color
void TimerFunction(int); // this call back function is called each 30 ms and changes the location, scale, and rotation

// Main Program
int main(int argc, char** argv)
{
    // set up window title
    char header[] = "Red Triangle by Lukas Siemers";

    glutInit(&argc, argv);
    // Set up the display mode with a single buffer and RGB colors
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    // Initialize window size and position
    glutInitWindowSize(560, 440);
    glutInitWindowPosition(140, 20);
    // Initialize background color in window
    SetupRC();
    // Open and Label Window
    glutCreateWindow(header);
    glutDisplayFunc(RenderScene);
    glutTimerFunc(30, TimerFunction, 1);
    // Now draw the scene
    glutMainLoop();

    return 0;
}

// ************************* RenderScene Function *************************
void RenderScene(void)
{
    float px[3], py[3], plx[2], ply[2]; /* these variables hold the pattern for the triangle icon. */
    float pxp[3], pyp[3], plxp[2], plyp[2], t[3][3]; /* these variables hold the icon after it has been scaled, rotated, and translated. */
    cout << "in renderscene" << endl;
    
    glColor3f(1.0, 1.0, 1.0); // set the current drawing color to white
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // set the viewport to the window dimensions
    glViewport(0, 0, 540, 440);
    // Establish the clipping volume in user units
    glOrtho(-7.0, 7.0, -7.0, 7.0, 1.0, -1.0);
    loadicon(px, py, plx, ply); // load the triangle icon
    settrans(t, scale1, dx, dy); // set the transformation matrix
    transform(pxp, pyp, plxp, plyp, t, px, py, plx, ply); // perform transformations
    // Clear the window with the background color
    glClear(GL_COLOR_BUFFER_BIT);
    // set the current drawing color to white
    glColor3f(1.0, 1.0, 1.0);

    // Draw the triangle
    drawicon(pxp, pyp, plxp, plyp);

    glEnd();
    glutSwapBuffers();

    return;
} // end of RenderScene

// ****************************** Load Icon Function ************************************
void loadicon(float px[], float py[], float plx[], float ply[])
{
    // Triangle vertices
	px[0] = 0.0; py[0] = 1.0; // Top of the triangle
	px[1] = 1.0; py[1] = 0.0; // Bottom right of the triangle
	px[2] = -1.0; py[2] = 0.0; // Bottom left of the triangle

    // Line points
	plx[0] = 0.0; ply[0] = 1.5; // Top of the triangle
	plx[1] = 0.0; ply[1] = -0.5; // Bottom of the triangle

    return;
} // end of load icon

/************************* function drawicon ***************************/
void drawicon(float pxp[], float pyp[], float plxp[], float plyp[])
{
    cout << "in drawicon" << endl;

    // Draw the triangle
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 3; i++)
    {
        glVertex2f(pxp[i], pyp[i]);
    }
    glEnd();

    // Draw the line
    glBegin(GL_LINES);
    glVertex2f(plxp[0], plyp[0]);
    glVertex2f(plxp[1], plyp[1]);
    glEnd();

    // Fill one half of the triangle with a color (e.g., green)
    glColor3f(1.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glBegin(GL_TRIANGLES);
    glVertex2f(pxp[0], pyp[0]);
    glVertex2f((pxp[1] + pxp[2]) / 2.0, (pyp[1] + pyp[2]) / 2.0); // Midpoint of the base
    glVertex2f(pxp[1], pyp[1]);
    glEnd();
} // end of draw icon

/************************** function settrans ***********************/
void settrans(float t[][3], float scale1, float dx, float dy)
{
    cout << "in settrans" << endl;
    int i, j;
    float ts, ct, st;
    double theta1;

    // Setup identity matrix
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
        {
            t[i][j] = 0.0;
            if (i == j) t[i][j] = 1.0;
        }

    // Set rotation parameters
    theta1 = (3.1416 / 180.0) * theta;
    ct = cos(theta1);
    st = sin(theta1);
    t[0][0] = ct;
    t[0][1] = -st;
    t[1][0] = st;
    t[1][1] = ct;

    // Translate the figure
    t[2][0] = dx;
    t[2][1] = dy;

    return;
}

/****************** function xprime ***********************/
float xprime(float x1, float y1, float t[][3])
{
    // this function multiplies the x vector by the transformation matrix
    float xp1;
    xp1 = x1 * t[0][0] + y1 * t[1][0] + t[2][0];
    return xp1;
}

/******************* function yprime ************************/
float yprime(float x1, float y1, float t[][3])
{
    // this function multiplies the y vector by the transformation matrix
    float yp1;
    yp1 = x1 * t[0][1] + y1 * t[1][1] + t[2][1];
    return yp1;
}

/********************* function transform ********************/
void transform(float pxp[], float pyp[], float plxp[], float plyp[],
    float t[][3], float px[], float py[], float plx[], float ply[])
{
    int i;
    cout << "intransform" << endl;

    // Transform the triangle
    for (i = 0; i < 3; i++)
    {
        pxp[i] = xprime(px[i], py[i], t);
        pyp[i] = yprime(px[i], py[i], t);
    }

    // Transform the line
    for (i = 0; i < 2; i++)
    {
        plxp[i] = xprime(plx[i], ply[i], t);
        plyp[i] = yprime(plx[i], ply[i], t);
    }

    return;
}

// **************************** Function SetupRC *************************************
void SetupRC(void)
{
    // this function sets the clear color of an open window and clears the open window
    // Set clear color to blue
    glClearColor(0.0, 0.0, 1.0, 1.0);
    return;
} // end of SetupRC

/******************************** Function Timer ****************************************/
void TimerFunction(int value)
//this call back function is call each 30 ms and changes the location,scale and rotation
// of the square.
{
    static float swc = 0.1, sdx = 0.1, sdy = 0.1;

    switch (frame)
    {
    case 1:		//frame 1 square starts at right and rolls the square to middle
        theta += 5.0;

        dx -= 0.15;
        if (dx <= 0.0) {
            dx = 0.0;
            frame = 2;
        }
        break;

    case 2:// frame 2 the square rises to y=3.0
        dy += 0.2;
        if (dy > 5.0)
        {
            dy = 5.0;
            frame = 3;
        }
        break;
    case 3: // frame 3: square rotates at x = 0.0, y = 3.0
        theta += 5.0; // Adjust rotation speed
        if (theta >= 610.0) // Complete one full rotation (not accurate should be 360 Degree instead of 610 Degrees ?)
        {
            frame = 4;
            
        }
        break;
    case 4:  // frame 4 square moves down to x=0.0, y=-3.0
        dy -= 0.2;
        if (dy <= -3.0)
        {
            dy = -3.0;
            frame = 5;
        }
        break;
    case 5:// frame 5 square rolls off stage to left
        dx -= 0.15;
        theta += 5.0;
        if (dx <= -6.5)dx = -6.5;
        break;
    }
    // Redraw the scene with new coordinates
    glutPostRedisplay();
    glutTimerFunc(33, TimerFunction, 1);
}
