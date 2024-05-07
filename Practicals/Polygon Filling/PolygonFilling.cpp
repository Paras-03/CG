//
//  main.cpp
//  polygon_filling_prac
//
//  Created by Paras Ningune on 02/05/24.
//

#include <iostream>
#include <GLUT/glut.h>

using namespace std;

#define w 640
#define h 480

int flag;
float boundary_color[3] = {0, 0, 0};
float interior_color[3] = {1, 1, 1};
float fill_color[3];

float read_pixel[3];

void set_pixel(int x, int y)
{
    glColor3fv(fill_color);
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
    glFlush();
}

void get_pixel(int x, int y, float* color)
{
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}

int sign(float x)
{
    if(x > 0)
    {
        return 1;
    }
    else if (x < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

void plot_point(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2d(x, y);
    glEnd();
    glFlush();
}

void dda(int x0, int y0, int x1, int y1)
{
    int dx = x1-x0;
    int dy = y1-y0;
    
    int k;
    
    if(dx > dy)
    {
        k = abs(dx);
    }
    else
    {
        k = abs(dy);
    }
    
    dx = dx/k;
    dy = dy/k;
    
    float x = x0 + 0.5 * sign(dx);
    float y = y0 + 0.5 * sign(dy);
    
    plot_point(x, y);
    for(int i=0; i<k; i++)
    {
        x += dx;
        y += dy;
        
        plot_point(x, y);
    }
    glEnd();
    glFlush();
}

void boundary_fill(int x, int y)
{
    get_pixel(x, y, read_pixel);
    
    if(boundary_color[0] != read_pixel[0] && boundary_color[1] != read_pixel[1] && boundary_color[2] != read_pixel[2])
    {
        set_pixel(x, y);
        boundary_fill(x+1, y);
        boundary_fill(x, y+1);
        boundary_fill(x-1, y);
        boundary_fill(x, y-1);
        
        glFlush();
    }
}

void flood_fill(int x, int y)
{
    get_pixel(x, y, read_pixel);
    
    if(read_pixel[0] == interior_color[0] && read_pixel[1] == interior_color[1] && read_pixel[2] == interior_color[2])
    {
        set_pixel(x, y);
        flood_fill(x+1, y);
        flood_fill(x, y+1);
        flood_fill(x-1, y);
        flood_fill(x, y-1);
        
        glFlush();
    }
}

void myMouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        y = h-y;
        
        if(flag == 1)
        {
            boundary_fill(x, y);
        }
        else if(flag == 2)
        {
            flood_fill(x, y);
        }
    }
}

void menu(int value)
{
    if(value == 1)
    {
        flag = 1;
        fill_color[0] = 0;
        fill_color[1] = 1;
        fill_color[2] = 2;
    }
    else
    {
        flag = 2;
        fill_color[0] = 1;
        fill_color[1] = 0.5;
        fill_color[2] = 0.8;
    }
}

void display()
{
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0f,0.0f,0.0f);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    dda(300,200,350,250);
    dda(350,250,400,200);
    dda(400,200,350,150);
    dda(350,150,300,200);
    
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(w, h);
    glutCreateWindow("Polygon filling");
    
    glutCreateMenu(menu);
    glutAddMenuEntry("Boundary Fill", 1);
    glutAddMenuEntry("Flood Fill", 2);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutDisplayFunc(display);
    glutMouseFunc(myMouse);
    
    glutMainLoop();
    
    return 0;
}
