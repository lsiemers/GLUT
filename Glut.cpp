#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iostream>

using namespace std;

void RenderScene(void); // Function to draw the scene
void SetupRC(void);     // Function to set the clear color of the window

int main(int argc, char** argv) {
    char header[] = "Graphs of g(x) = Red , h(x) = Green , and f(x) = Blue  |||    from Lukas Siemers";
    // Initialize the GLUT toolkit
    glutInit(&argc, argv);
    // Set up display mode: single buffer and RGB colors
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    // Initialize window size and position
    glutInitWindowSize(1016, 680);
    glutInitWindowPosition(0, 0);
    // Open and label the window
    glutCreateWindow(header);
    // Assign the function to render the scene
    glutDisplayFunc(RenderScene);
    // Set the rendering state
    SetupRC();
    // Start the main OpenGL loop
    glutMainLoop();
    return 0;
}

void SetupRC(void) {    // Set up the rendering state
    // Set the clear color to light purple
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Clear color is black
}

// Render the scene with axes and function graphs
void RenderScene(void) {
    double x, g, h, f, y, xdel = 0.1; // Step size for plotting
	double pi = 3.14159265358979323846; // Value of pi
	glClear(GL_COLOR_BUFFER_BIT); // Clear the window with the current clearing color
	glLoadIdentity(); // Reset the modelview matrix

    // Set the viewport and establish the clipping volume
	glViewport(100, 100, 900, 500); // Set the viewport
	glOrtho(-15.0, 15.0, -30.0, 50.0, 1.0, -1.0);   // Set the clipping volume

    // Draw x-axis and y-axis with tic marks
    glBegin(GL_LINES);
    // x-axis
    glColor3f(1.0, 1.0, 1.0); // Set axis color to white
	glVertex2f(-15.0, 0.0); // Draw x-axis
	glVertex2f(15.0, 0.0); // Draw x-axis
    // Tic marks on x-axis
    for (x = -15.0; x <= 15.0; x += 1.0) {
		glVertex2f(x, 0.0); // Draw tic mark
		glVertex2f(x, 0.5); // Draw tic mark
    }
    // y-axis
	glVertex2f(0.0, -50.0); // Draw y-axis
	glVertex2f(0.0, 50.0); // Draw y-axis
    // Tic marks on y-axis
	for (g = -50.0; g <= 50.0; g += 1.0) { //for position - 10 to position 25
		glVertex2f(-0.15, g); // Draw tic mark
		glVertex2f(0.15, g); // Draw tic mark
    }
    glEnd();

    // Plot the function g(x) = x(x + 5)(x - 4)
    glColor3f(1.0, 0.0, 0.0); // Red color for g(x)
	glBegin(GL_LINE_STRIP); // Draw the function as a line strip
	for (x = -10.0; x <= 10.0; x += xdel) { //for position - 10 to position 10
		g = x * (x + 5) * (x - 4); // Calculate the function value
		glVertex2f(x, g); // Plot the function
    }
    glEnd();

    // Plot the function h(x) = 10 * cos(y) + 3
    glColor3f(0.0, 1.0, 0.0); // Green color for h(x)
	glBegin(GL_LINE_STRIP); // Draw the function as a line strip
	for (y = -16 * pi; y <= 16.0 * pi; y += xdel) { //for position - 16 to position 16
		h = 10 * cos(y) + 3; // Calculate the function value
        glVertex2f(h,y); // Scale x to fit within viewport
    }
    glEnd();

    // Plot the function f(x) = g(x) - h(x)
    glColor3f(0.0, 0.0, 1.0); // Blue color for f(x)
	glBegin(GL_LINE_STRIP); // Draw the function as a line strip
	for (x = -10 ; x <= 10; x += xdel) { //for position - 10 to position 10
        g = x * (x + 5) * (x - 4);  //Graphing each function
		h = 10 * cos(y) + 3;    //Graphing each function
		f = g - h;  //Subtracting the two functions
		glVertex2f(x, f);   //Plotting the function
    }
    glEnd();
    // Flush the rendering pipeline
    glFlush();
}
