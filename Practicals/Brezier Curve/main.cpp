//
//  main.cpp
//  Brezier Curve_prac
//
//  Created by Paras Ningune on 07/05/24.
//

#include <iostream>
#include <GLUT/glut.h>
using namespace std;

#define w 500
#define h 500
int clicks = 0;
int points[4][2];
bool is_drawn = false;

void plot_point(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void drawLines(int x0, int y0, int x1, int y1)
{
    glBegin(GL_LINES);
    glVertex2i(x0, y0);
    glVertex2i(x1, y1);
    glEnd();
    glFlush();
}

void drawCurve(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3)
{
    float x01 = (x0+x1)/2;
    float y01 = (y0+y1)/2;
    float x12 = (x1+x2)/2;
    float y12 = (y1+y2)/2;
    float x23 = (x2+x3)/2;
    float y23 = (y2+y3)/2;
    
    float x012 = (x01+x12)/2;
    float y012 = (y01+y12)/2;
    float x123 = (x12+x23)/2;
    float y123 = (y12+y23)/2;
    
    float x0123 = (x012+x123)/2;
    float y0123 = (y012+y123)/2;
    
    if((x1-x0)*(x1-x0) + (y1-y0)*(y1-y0) > 4 || (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) > 4 || (x3-x2)*(x3-x2) + (y3-y2)*(y3-y2) > 4)
    {
        drawCurve(x0, y0, x01, y01, x012, y012, x0123, y0123);
        drawCurve(x0123, y0123, x123, y123, x23, y23, x3, y3);
        is_drawn = true;
    }
    else
    {
        drawLines(x0, y0, x0123, y0123);
        drawLines(x0123, y0123, x3, y3);
    }
}

void display()
{
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, w, 0, h);
}


void myMouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        points[clicks][0] = x;
        points[clicks][1] = h-y;
        clicks++;
        plot_point(x, h-y);
        
        if(clicks == 4)
        {
            drawLines(points[0][0], points[0][1], points[1][0], points[1][1]);
            drawLines(points[1][0], points[1][1], points[2][0], points[2][1]);
            drawLines(points[2][0], points[2][1], points[3][0], points[3][1]);
            
            drawCurve(points[0][0], points[0][1], points[1][0], points[1][1], points[2][0], points[2][1], points[3][0], points[3][1]);
        }
    }
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(w, h);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Brezier Curve");
    
    glutDisplayFunc(display);
    glutMouseFunc(myMouse);
    glutMainLoop();
    
    return 0;
}

