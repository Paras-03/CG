//
//  main.cpp
//  dda_prac
//
//  Created by Paras Ningune on 02/05/24.
//

#include <iostream>
#include <GLUT/glut.h> // Chnage it to #include <gl/glut.h>

using namespace std;
#define h 750
#define w 750

const int max_points = 20;
const int max_lines = 10;

int num_lines = 0;
int num_points = 0;
int selected = 1;
int lines[max_lines][2][2];

void init()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-w/2, h/2, -w/2, h/2);
}

void plot_point(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
    
}

int sign(float x)
{
    if(x>=0)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

void draw_axis()
{
    for(int i=-h/2; i<=h; i++)
    {
        plot_point(i, 0);
        plot_point(0, i);
    }
}

void DDA(int x0, int y0, int x1, int y1)
{
    float dx = x1-x0;
    float dy = y1-y0;
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
    for(int i=0; i<=k; i++)
    {
        x += dx;
        y += dy;
        switch (selected)
        {
            case 1:
                plot_point(x, y);
                break;
            
            case 2:
                if(i%3 == 0)
                {
                    plot_point(x, y);
                }
                break;
                
            case 3:
                if(i%7 != 0)
                {
                    plot_point(x, y);
                }
                break;
                
            case 4:
                glPointSize(3);
                plot_point(x, y);
                break;

        }
    }
}

void myMouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(num_lines < max_lines && num_points < max_points)
        {
            int x_cor = x - w/2;
            int y_cor = h/2 - y;
            
            lines[num_lines][num_points][0] = x_cor;
            lines[num_lines][num_points][1] = y_cor;

            plot_point(x_cor, y_cor);
            num_points++;
            
            if(num_points == 2)
            {
                DDA(lines[num_lines][0][0], lines[num_lines][0][1], lines[num_lines][1][0], lines[num_lines][1][1]);
                num_lines++;
                num_points = 0;
            }
        }
    }
    
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        glutAttachMenu(GLUT_RIGHT_BUTTON);
    }
}

void menu(int value)
{
    selected = value;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    draw_axis();
    glFlush();
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(w, h);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA");
    init();
    
    glutCreateMenu(menu);
    glutAddMenuEntry("Simple", 1);
    glutAddMenuEntry("Dotted", 2);
    glutAddMenuEntry("Dashed", 3);
    glutAddMenuEntry("Solid", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutDisplayFunc(display);
    glutMouseFunc(myMouse);
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
