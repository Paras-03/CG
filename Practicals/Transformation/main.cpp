//
//  main.cpp
//  Transformation_prac
//
//  Created by Paras Ningune on 03/05/24.
//

#include <iostream>
#include <GLUT/glut.h>

using namespace std;

#define w 750
#define h 750
int selected=0;

int obj[5][3];
int res[5][3];
int n=0;
int tran[3][3];

void init()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-w/2, w/2, -h/2, h/2);
}

void plot(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    
    glFlush();
}

void drawAxis()
{
    for(int i=-h/2; i<h; i++)
    {
        plot(i, 0);
        plot(0, i);
    }
}

void joinPoints(int o[][3])
{
    glBegin(GL_LINE_LOOP);
    for(int i=0; i<n; i++)
    {
        glVertex2f(o[i][0], o[i][1]);
    }
    glEnd();
    glFlush();
}


void multiply(int tran[][3], int obj[][3])
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<3; j++)
        {
            res[i][j] = 0;
            for(int k=0; k<3; k++)
            {
                res[i][j] += obj[i][k] * tran[k][j];
            }
        }
    }
    joinPoints(res);
    joinPoints(obj);
}

void translate(int obj[][3])
{
    int tx, ty, xabt, yabt;
    cout<<"\nEnter x-cor abt with translate: ";
    cin>>xabt;
    cout<<"\nEnter y-cor abt with translate: ";
    cin>>yabt;
    
    cout<<"\nEnter tx: ";
    cin>>tx;
    cout<<"Enter ty: ";
    cin>>ty;
    
    tran[0][0] = 1;
    tran[0][1] = 0;
    tran[0][2] = 0;
    tran[1][0] = 0;
    tran[1][1] = 1;
    tran[1][2] = 0;
    tran[2][0] = tx;
    tran[2][1] = ty;
    tran[2][2] = 1;
    
    multiply(tran, obj);
}

void scale(int obj[][3])
{
    int sx, sy;
    cout<<"\nEnter value of sx: ";
    cin>>sx;
    
    cout<<"\nEnter value of sy: ";
    cin>>sy;
    
    tran[0][0] = sx;
    tran[0][1] = 0;
    tran[0][2] = 0;
    tran[1][0] = 0;
    tran[1][1] = sy;
    tran[1][2] = 0;
    tran[2][0] = 0;
    tran[2][1] = 0;
    tran[2][2] = 1;
    
    multiply(tran, obj);
}


void rotate(int obj[][3])
{
    float angle;
    int cx, cy;
    
    cout<<"\nEnter angle of rotation(degree): ";
    cin>>angle;
    
    angle = (angle * M_PI) / 180;
    
    cout<<"Enter x-cor of center of rotation: ";
    cin>>cx;
    
    cout<<"Enter y-cor of center of rotation: ";
    cin>>cy;
    
    cx = -cx * cos(angle) + cy * sin(angle) + cx;
    cy = -cy * cos(angle) - cx * sin(angle) + cy;
    cout<<cos(angle)<<endl;
    tran[0][0] = cos(angle);
    tran[0][1] = -sin(angle);
    tran[0][2] = 0;
    tran[1][0] = sin(angle);
    tran[1][1] = cos(angle);
    tran[1][2] = 0;
    tran[2][0] = 0;
    tran[2][1] = 0;
    tran[2][2] = 1;
    
    multiply(tran, obj);
}


void reflect(int obj[][3])
{
    int choice;
    cout<<"\nEnter 1 for reflection abt x.\nEnter 2 for reflection abt y.\nEnter 3 for reflection abt origin.\nEnter your choice: ";
    cin>>choice;
    
    switch(choice)
    {
        case 1:
            tran[0][0] = 1;
            tran[0][1] = 0;
            tran[0][2] = 0;
            tran[1][0] = 0;
            tran[1][1] = -1;
            tran[1][2] = 0;
            tran[2][0] = 0;
            tran[2][1] = 0;
            tran[2][2] = 1;
            
            multiply(tran, obj);
            break;
            
        case 2:
            tran[0][0] = -1;
            tran[0][1] = 0;
            tran[0][2] = 0;
            tran[1][0] = 0;
            tran[1][1] = 1;
            tran[1][2] = 0;
            tran[2][0] = 0;
            tran[2][1] = 0;
            tran[2][2] = 1;
            
            multiply(tran, obj);
            break;
            
        case 3:
            tran[0][0] = -1;
            tran[0][1] = 0;
            tran[0][2] = 0;
            tran[1][0] = 0;
            tran[1][1] = -1;
            tran[1][2] = 0;
            tran[2][0] = 0;
            tran[2][1] = 0;
            tran[2][2] = 1;
            
            multiply(tran, obj);
            break;
            
        default:
            cout<<"\nEnter valid choice...";
            break;
    }
}


void menu(int value)
{
    selected = value;
    
    switch (selected)
    {
        case 1:
            scale(obj);
            break;
            
        case 2:
            rotate(obj);
            break;
            
        case 3:
            reflect(obj);
            break;
            
        case 4:
            translate(obj);
    }
}


void display()
{
    drawAxis();
    glFlush();
}

void myMouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        x = x - w/2;
        y = h/2 - y;
        obj[n][0] = x;
        obj[n][1] = y;
        obj[n][2] = 1;
        n++;
        cout<<n<<endl;
        plot(x, y);
        glFlush();
    }
    
    else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        if(n > 1)
        {
            joinPoints(obj);
            glFlush();
        }
    }
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(w, h);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Transformation");
    
    init();
    
    glutCreateMenu(menu);
    glutAddMenuEntry("Scale", 1);
    glutAddMenuEntry("Rotate abt point", 2);
    glutAddMenuEntry("Reflection", 3);
    glutAddMenuEntry("Translate", 4);
    
    glutAttachMenu(GLUT_MIDDLE_BUTTON);
    glutDisplayFunc(display);
    glutMouseFunc(myMouse);
    

    glutMainLoop();
    
    return 0;
}
