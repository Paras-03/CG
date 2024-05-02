//
//  main.cpp
//  Bresenham_circle_prac
//
//  Created by Paras Ningune on 02/05/24.
//

#include <iostream>
#include <GLUT/glut.h>
using namespace std;

#define w 750
#define h 750

const int max_lines = 10;
const int max_points = 20;

int num_lines = 0;
int num_points = 0;
int selected = 1;

int lines[max_lines][2][2];

void init()
{
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-w/2, h/2, -w/2, h/2);
}

void menu(int value)
{
    selected = value;
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
    for(int i=-h; i<h; i++)
    {
        plot_point(i, 0);
        plot_point(0, i);
    }
}

void Circle(int x0, int y0, int x1, int y1)
{
    int H = x0;
    int K = y0;
    
    int r = abs(sqrt(((x1-x0)*(x1-x0)) + ((y1-y0)*(y1-y0))));
    
    int d = 3-(2*r);
    
    int x = 0;
    int y = r;
    
    while(x < y)
    {
        if(d <= 0)
        {
            d = d+4*x+6;
            x+=1;
        }
        else
        {
            d = d+4*(x-y)+10;
            x += 1;
            y -= 1;
        }
        
        plot_point(x+H, y+K);
        plot_point(-x+H, -y+K);
        
        plot_point(y+H, x+K);
        plot_point(-y+H, -x+K);
        
        plot_point(-y+H, x+K);
        plot_point(y+H, -x+K);
        
        plot_point(-x+H, y+K);
        plot_point(x+H, -y+K);
    }
}

void ConcentricCircle(int x0, int y0, int x1, int y1)
{
    int n, r_inc, H, K;
    H = x0;
    K = y0;
    
    int x, y;
    int r = abs(sqrt(((x1-x0)*(x1-x0)) + ((y1-y0)*(y1-y0))));
    
    cout<<"\nEnter no of concentric cirlces to be shown: ";
    cin>>n;
    cout<<endl;
    
    cout<<"\nEnter radius increment: ";
    cin>>r_inc;
    cout<<endl;
    
    int d = 3-(2*r);
    
    for(int i=0; i<n; i++)
    {
        x = 0;
        y = r;
        
        while(x < y)
        {
            if(d <= 0)
            {
                d = d+4*x+6;
                x+=1;
            }
            else
            {
                d = d+4*(x-y)+10;
                x += 1;
                y -= 1;
            }
            
            plot_point(x+H, y+K);
            plot_point(-x+H, -y+K);
            
            plot_point(y+H, x+K);
            plot_point(-y+H, -x+K);
            
            plot_point(-y+H, x+K);
            plot_point(y+H, -x+K);
            
            plot_point(-x+H, y+K);
            plot_point(x+H, -y+K);
        }
        glFlush();
        r = r+r_inc;
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
                switch (selected)
                {
                    case 1:
                        ConcentricCircle(lines[num_lines][0][0], lines[num_lines][0][1], lines[num_lines][1][0], lines[num_lines][1][1]);
                        //Circle(lines[num_lines][0][0], lines[num_lines][0][1], lines[num_lines][1][0], lines[num_lines][1][1]);
                        break;
                        
                    case 2:
                        ConcentricCircle(lines[num_lines][0][0], lines[num_lines][0][1], lines[num_lines][1][0], lines[num_lines][1][1]);
                    default:
                        break;
                }
                num_lines++;
                num_points = 0;
            }
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
    glutCreateWindow("Bresenham Circle");
    
    
    init();
    
    glutDisplayFunc(display);
    glutMouseFunc(myMouse);
    glutMainLoop();
    
    return 0;
}
