//
//  main.cpp
//  Polygon Clipping_prac
//
//  Created by Paras Ningune on 04/05/24.
//

#include <iostream>
#include <GLUT/glut.h>

#define w 500
#define h 500
#define outcode int

const int RIGHT = 8;
const int TOP = 4;
const int LEFT = 2;
const int BOTTOM = 1;


int xmin = 100, ymin = 100, xmax = 200, ymax = 200; //clipping window
int xvmin = 300, yvmin = 300, xvmax = 400, yvmax = 400; //view port
int n = 0;

GLfloat obj[10][2];
double x_0, y_0, x_1, y_1;


outcode ComputeCode(double x, double y)
{
    outcode code = 0;
    if(y > ymax)
    {
        code |= TOP;
    }
    else if(y < ymin)
    {
        code |= BOTTOM;
    }
    
    if(x > xmax)
    {
        code |= RIGHT;
    }
    else if (x < xmin)
    {
        code |= LEFT;
    }
    
    return code;
}

void Clipping(double x_0, double y_0, double x_1, double y_1)
{
    outcode code1, code2, code;
    bool accept = false, done = false;
    
    code1 = ComputeCode(x_0, y_0);
    code2 = ComputeCode(x_1, y_1);
    
    do
    {
        if(!(code1 | code2))
        {
            accept = true;  //line completely visible
            done = true;
        }
        else if(code1 & code2)
        {
            done = true;    //line completely invisible
        }
        else
        {
            int x, y;
            code = code1 ? code1 : code2;
            
            if(code & TOP)
            {
                x = x_0 + (x_1 - x_0) * (ymax - y_0) / (y_1 - y_0);
                y = ymax;
            }
            else if(code & BOTTOM)
            {
                x = x_0 + (x_1 - x_0) * (ymin - y_0) / (y_1 - y_0);
                y = ymin;
            }
            else if(code & RIGHT)
            {
                y = y_0 + (y_1 - y_0) * (xmax - x_0) / (x_1 - x_0);
                x = xmax;
            }
            else
            {
                y = y_0 + (y_1 - y_0) * (xmin - x_0) / (x_1 - x_0);
                x = xmin;
            }
            if(code == code1)
            {
                x_0 = x;
                y_0 = y;
                code1 = ComputeCode(x_0, y_0);
            }
            else
            {
                x_1 = x;
                y_1 = y;
                code2 = ComputeCode(x_1, y_1);
            }
        }
    }while(!done);
    
    if(accept)
    {
        double sx = (xvmax - xvmin) / (xmax - xmin);
        double sy = (yvmax - yvmin) / (ymax - ymin);
        
        double vx0 = xvmin + (x_0 - xmin) * sx;
        double vy0 = yvmin + (y_0 - ymin) * sy;
        double vx1 = yvmin + (x_1 - ymin) * sx;
        double vy1 = yvmin + (y_1 - ymin) * sy;
        
        glBegin(GL_LINES);
        glVertex2d(vx0, vy0);
        glVertex2d(vx1, vy1);
        glEnd();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    
    glBegin(GL_LINE_LOOP);
    glVertex2d(xmin, ymin);
    glVertex2d(xmax, ymin);
    glVertex2d(xmax, ymax);
    glVertex2d(xmin, ymax);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex2d(xvmin, yvmin);
    glVertex2d(xvmax, yvmin);
    glVertex2d(xvmax, yvmax);
    glVertex2d(xvmin, yvmax);
    glEnd();
    
    glFlush();
}

void myMouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        y = h-y;
        obj[n][0] = x;
        obj[n][1] = y;
        
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        n++;
        glFlush();
    }
    
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        glBegin(GL_LINE_LOOP);
        for(int i=0; i<n; i++)
        {
            glVertex2i(obj[i][0], obj[i][1]);
        }
        glEnd();
        glFlush();
        
        for(int i=0; i<n; i++)
        {
            int j = (i+1) % n;
            
            Clipping(obj[i][0], obj[i][1], obj[j][0], obj[j][1]);
        }
        
        glFlush();
        n = 0;
    }
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(w, h);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Clipping");
    
    
    glutDisplayFunc(display);
    glutMouseFunc(myMouse);
    glutMainLoop();
    
    return 0;
}
