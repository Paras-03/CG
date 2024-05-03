#include <iostream>
#include <GLUT/glut.h>
using namespace std;

#define h  750
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

void draw_axis()
{
    for(int i=-h/2; i<=h; i++)
    {
        plot_point(i, 0);
        plot_point(0, i);
    }
}

void menu(int value)
{
    selected = value;
}

int sign(int x)
{
    if(x<0)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}


void Bresehnam(int x0, int y0, int x1, int y1)
{
    bool swapped = false;
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
        swapped = true;
    }
    
    int err = 2*dy - dx;
    int i=1;
    plot_point(x, y);
    
    while(i<=dx)
    {
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
        
        switch (selected)
        {
            case 1:
                plot_point(x, y);
                break;
                
            case 2:
                if(i%5 == 0)
                {
                    plot_point(x, y);
                }
                break;
                
            case 3:
                if(i%3 != 0)
                {
                    plot_point(x, y);
                }
                break;
                
            case 4:
                glPointSize(3);
                plot_point(x, y);
                glPointSize(1);
        }
    }
    glFlush();
}

void myMouse(int state, int button, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(num_lines < max_lines && num_points < max_points)
        {
            int x_cor = x - w/2;
            int y_cor = h/2 - y;
            lines[num_lines][num_points][0] = x_cor;
            lines[num_lines][num_points][1] = y_cor;
            
            num_points++;

            if(num_points == 2)
            {
                Bresehnam(lines[num_lines][0][0], lines[num_lines][0][1], lines[num_lines][1][0], lines[num_lines][1][1]);
                num_lines++;
                num_points = 0;
            }
            plot_point(x_cor, y_cor);
        }
    }
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
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(w, h);
    glutCreateWindow("Bresehnam");
    
    init();
    
    glutCreateMenu(menu);
    glutAddMenuEntry("Simple", 1);
    glutAddMenuEntry("Dotted", 2);
    glutAddMenuEntry("Dashed", 3);
    glutAddMenuEntry("Solid", 4);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    glutDisplayFunc(display);
    glutMouseFunc(myMouse);
    
    glutMainLoop();
    
    return 0;
}
