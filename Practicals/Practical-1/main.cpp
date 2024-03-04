//  main.cpp
//  dda
//
//  Created by Paras Ningune on 25/02/24.
//

#include <iostream>
#include <GLUT/glut.h>
using namespace std;

#define h  1000
#define w  1000

void init()
{
    glClearColor(0.0, 0.0, 0.0,0.0);
    gluOrtho2D(-w/2, h/2, -w/2, h/2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void display_point(int x, int y)
{
    glColor3f(1, 1, 0);
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
    glFlush();
}

int sign(float x)
{
    if(x==0)
    {
        return 0;;
    }
    else if (x<0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}


void draw_axis()
{
    for(int i=-h; i<h; i++)
    {
        display_point(i, 0);
        display_point(0, i);
    }
    glFlush();
}

void draw_simple_line()
{
    float x0, y0, x1, y1;
    
    cout<<"Enter coordinates of first point: \n";
    cout<<"X0: ";
    cin>>x0;
    
    cout<<"Y0: ";
    cin>>y0;
    
    cout<<"Enter coordinates of second point: \n";
    cout<<"X1: ";
    cin>>x1;
    
    cout<<"y1: ";
    cin>>y1;
    cout<<endl;
    
    if(x0==x1 && y0==y1)
    {
        cout<<"Both points same!!";
    }
    
    float dx, dy, k;
    
    dx = x1-x0;
    dy = y1-y0;
    
    if(abs(dx) > abs(dy))
    {
        k = dx;
    }
    else
    {
        k = dy;
    }
    
    float DX, DY;
    
    DX = dx/k;
    DY = dy/k;
    
    float x = x0 + 0.5 * sign(DX);
    float y = y0  + 0.5 * sign(DY);

    display_point(x, y);
    for(int i=0; i<=k; i++)
    {
        display_point(x, y);
        
        x += DX;
        y += DY;
    }
    glFlush();
}

void DDA(float x0, float y0, float x1, float y1)
{
    
    if(x0==x1 && y0==y1)
    {
        cout<<"Both points same!!";
    }
    
    float dx, dy, k;
    
    dx = x1-x0;
    dy = y1-y0;
    
    if(abs(dx) > abs(dy))
    {
        k = dx;
    }
    else
    {
        k = dy;
    }
    
    float DX, DY;
    
    DX = dx/k;
    DY = dy/k;
    
    float x = x0 + 0.5 * sign(DX);
    float y = y0  + 0.5 * sign(DY);

    display_point(x, y);
    for(int i=0; i<=k; i++)
    {
        display_point(x, y);
        
        x += DX;
        y += DY;
    }
    glFlush();
}

void draw_solid_line()
{
    float x0, y0, x1, y1;
    
    cout<<"Enter coordinates of first point: \n";
    cout<<"X0: ";
    cin>>x0;
    
    cout<<"Y0: ";
    cin>>y0;
    
    cout<<"Enter coordinates of second point: \n";
    cout<<"X1: ";
    cin>>x1;
    
    cout<<"y1: ";
    cin>>y1;
    cout<<endl;
    
    if(x0==x1 && y0==y1)
    {
        cout<<"Both points same!!";
    }
    
    float dx, dy, k;
    
    dx = x1-x0;
    dy = y1-y0;
    
    if(abs(dx) > abs(dy))
    {
        k = dx;
    }
    else
    {
        k = dy;
    }
    
    float DX, DY;
    
    DX = dx/k;
    DY = dy/k;
    
    float x = x0 + 0.5 * sign(DX);
    float y = y0  + 0.5 * sign(DY);
    
    glLineWidth(50.0);
    display_point(x, y);
    
    for(int i=0; i<=k; i++)
    {
        display_point(x, y);
        
        x += DX;
        y += DY;
    }
    glFlush();
}

void draw_dotted_line()
{
    float x0, y0, x1, y1;
    
    cout<<"Enter coordinates of first point: \n";
    cout<<"X0: ";
    cin>>x0;
    
    cout<<"Y0: ";
    cin>>y0;
    
    cout<<"Enter coordinates of second point: \n";
    cout<<"X1: ";
    cin>>x1;
    
    cout<<"y1: ";
    cin>>y1;
    cout<<endl;
    
    if(x0==x1 && y0==y1)
    {
        cout<<"Both points same!!";
    }
    
    float dx, dy, k;
    
    dx = x1-x0;
    dy = y1-y0;
    
    if(abs(dx) > abs(dy))
    {
        k = dx;
    }
    else
    {
        k = dy;
    }
    
    float DX, DY;
    
    DX = dx/k;
    DY = dy/k;
    
    float x = x0 + 0.5 * sign(DX);
    float y = y0  + 0.5 * sign(DY);
    
    glPointSize(2);
    display_point(x, y);
    
    for(int i=0; i<=k; i++)
    {
        if(i%5 == 0)
        {
            display_point(x, y);
        }
        
        x += DX;
        y += DY;
    }
    glFlush();
}

void Display_Boat()
{
    DDA(-120 , -200 , 120 , -200);
    DDA(-120 , -200 , -200 , 0);
    DDA(-200 , 0 , 200 , 0);
    DDA(120 , -200 , 200 , 0);
    
    DDA(-140 , 0 , 0 , 200);
    DDA(140 , 0 , 0 , 200);

}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    //draw_axis();
    //draw_simple_line();
    //draw_solid_line();
    //draw_dotted_line();
    Display_Boat();
}

int main(int charc, char ** charv)
{
    glutInit(&charc, charv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(400,100);
    glutInitWindowSize(1000,1000);
    glutCreateWindow("Line Drawing");
    
    init();
    glutDisplayFunc(display);
    
    glutMainLoop();
    return 0;
}



