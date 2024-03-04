//
//  main.cpp
//  Bresenham line drawing algorithm
//
//  Created by Paras Ningune on 03/03/24.
//

#include <iostream>
#include <string.h>
#include <GLUT/glut.h>
using namespace std;

#define w 750
#define h 750
const int maxPoints = 100;
const int maxLines = 50;
int swapped=0;
int selected;

int numLines = 0;
int numPoints = 0;
int lines[maxLines][2][2];

void init()
{
    glClearColor(0, 0, 0, 0);
    gluOrtho2D(-w/2, w/2, -h/2, h/2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void menu(int index)
{
    selected = index;
    glutSwapBuffers();
    glutPostRedisplay();
}

void display_line_point(int x, int y)
{
    glColor3f(1, 1, 0);
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
}

void display_point(int x, int y)
{
    glColor3f(1, 0, 0);
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
    glFlush();
}

void display_axis_point(float x, float y)
{
    glColor3f(0, 1, 1);
    glBegin(GL_POINTS);
        glVertex2f(x, y);
    glEnd();
}

void draw_axis()
{
    for(int i=-h;i<h;i++)
    {
        display_axis_point(i, 0);
        display_axis_point(0, i);
    }
    glViewport(0, 0, w, h);
    glFlush();
}

int sign(int no)
{
    if(no>0)
    {
        return 1;
    }
    else if (no<0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

void draw_simple_line(int x0, int y0, int x1, int y1)
{
    int x = x0;
    int y = y0;
    int dx = abs(x1-x0);
    int dy = abs(y1-y0);
    int s1 = sign(x1-x0);
    int s2 = sign(y1-y0);
    
    if(dy>dx)
    {
        int temp = dx;
        dx = dy;
        dy = temp;
        swapped = 1;
    }
    else
    {
        swapped = 0;
    }
    
    int err = 2*dy - dx;
    int i=1;
    
    while(i<=dx)
    {
        display_line_point(x, y);
        
        while(err>=0)
        {
            if(swapped == 1)
            {
                x = x+s1;
            }
            else
            {
                y = y+s2;
            }
            
            err = err - 2*dx;
        }
        
        if(swapped == 1)
        {
            y = y+s2;
        }
        else
        {
            x = x+s1;
        }
        err = err+2*dy;
        i++;
    }
    display_line_point(x1, y1);
    glFlush();
}

void draw_dotted_line(int x0, int y0, int x1, int y1)
{
    int x = x0;
    int y = y0;
    int dx = abs(x1-x0);
    int dy = abs(y1-y0);
    int s1 = sign(x1-x0);
    int s2 = sign(y1-y0);
    
    if(dy>dx)
    {
        int temp = dx;
        dx = dy;
        dy = temp;
        swapped = 1;
    }
    else
    {
        swapped = 0;
    }
    
    int err = 2*dy - dx;
    int i=1;
    
    while(i<=dx)
    {
        if(i%4 == 0)
        {
            display_line_point(x, y);
        }
        while(err>=0)
        {
            if(swapped == 1)
            {
                x = x+s1;
            }
            else
            {
                y = y+s2;
            }
            
            err = err - 2*dx;
        }
        
        if(swapped == 1)
        {
            y = y+s2;
        }
        else
        {
            x = x+s1;
        }
        err = err+2*dy;
        
        i++;
    }
    display_line_point(x1, y1);
    glFlush();
}


void draw_solid_line(int x0, int y0, int x1, int y1)
{
    int x = x0;
    int y = y0;
    int dx = abs(x1-x0);
    int dy = abs(y1-y0);
    int s1 = sign(x1-x0);
    int s2 = sign(y1-y0);
    
    if(dy>dx)
    {
        int temp = dx;
        dx = dy;
        dy = temp;
        swapped = 1;
    }
    else
    {
        swapped = 0;
    }
    
    int err = 2*dy - dx;
    int i=1;
    
    while(i<=dx)
    {
        display_line_point(x, y);
        
        while(err>=0)
        {
            if(swapped == 1)
            {
                x = x+s1;
            }
            else
            {
                y = y+s2;
            }
            
            err = err - 2*dx;
        }
        
        if(swapped == 1)
        {
            y = y+s2;
        }
        else
        {
            x = x+s1;
        }
        err = err+2*dy;
        i++;
    }
    display_line_point(x1, y1);
    glFlush();
}

void draw_dashed_line(int x0, int y0, int x1, int y1)
{
    int x = x0;
    int y = y0;
    int dx = abs(x1-x0);
    int dy = abs(y1-y0);
    int s1 = sign(x1-x0);
    int s2 = sign(y1-y0);
    
    if(dy>dx)
    {
        int temp = dx;
        dx = dy;
        dy = temp;
        swapped = 1;
    }
    else
    {
        swapped = 0;
    }
    
    int err = 2*dy - dx;
    int i=1;
    
    while(i<=dx)
    {
        if(i%5 != 0)
        {
            display_line_point(x, y);
        }
        
        while(err>=0)
        {
            if(swapped == 1)
            {
                x = x+s1;
            }
            else
            {
                y = y+s2;
            }
            
            err = err - 2*dx;
        }
        
        if(swapped == 1)
        {
            y = y+s2;
        }
        else
        {
            x = x+s1;
        }
        err = err+2*dy;
        i++;
    }
    display_line_point(x1, y1);
    glFlush();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    draw_axis();
    
    if(selected == 1)
    {
        for (int i = 0; i < numLines; ++i)
        {
            draw_simple_line(lines[i][0][0], lines[i][0][1], lines[i][1][0], lines[i][1][1]);
        }
    }
    else if(selected == 2)
    {
        for (int i = 0; i < numLines; ++i)
        {
            draw_dotted_line(lines[i][0][0], lines[i][0][1], lines[i][1][0], lines[i][1][1]);
        }
    }
    
    else if(selected == 3)
    {
        for (int i = 0; i < numLines; ++i)
        {
            draw_dashed_line(lines[i][0][0], lines[i][0][1], lines[i][1][0], lines[i][1][1]);
        }
    }
    else
    {
        for (int i = 0; i < numLines; ++i)
        {
            draw_solid_line(lines[i][0][0], lines[i][0][1], lines[i][1][0], lines[i][1][1]);
        }
    }
    
}

void myMouse(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN)
    {
        if(button == GLUT_LEFT_BUTTON)
        {
            if (numPoints < maxPoints && numLines < maxLines)
            {
                int x_n = x - w/2;
                int y_n = h/2-y;
                lines[numLines][numPoints][0] = x_n;
                lines[numLines][numPoints][1] = y_n;
                
                numPoints++;
                
                if (numPoints == 2) 
                {
                    numLines++;
                    numPoints = 0;
                }
                display_point(x_n, y_n);
                glutPostRedisplay();
            }
        }
        else if(button == GLUT_RIGHT_BUTTON)
        {
            glutAttachMenu(GLUT_RIGHT_BUTTON);
        }
    }
}

int main(int charc, char ** charv)
{
    glutInit(&charc, charv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(400,100);
    glutInitWindowSize(h, w);
    glutCreateWindow("Bresenham line drawing");
    
    glutCreateMenu(menu);
    glutAddMenuEntry("Simple", 1);
    glutAddMenuEntry("Dotted", 2);
    glutAddMenuEntry("Dashed", 3);
    glutAddMenuEntry("Solid", 4);
    
    init();
    glutDisplayFunc(display);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMouseFunc(myMouse);
    glutMainLoop();
    
    return 0;
}
