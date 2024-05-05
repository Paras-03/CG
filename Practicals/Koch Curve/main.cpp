//
//  main.cpp
//  Koch Curve
//
//  Created by Paras Ningune on 05/05/24.
//

#include <iostream>
#include <GLUT/glut.h>

using namespace std;

#define w 500
#define h 500

GLfloat oldx = -0.7,  oldy = 0.5;

void drawCurve(GLfloat dir, GLfloat len, int iter)
{
    double dirRad = 0.0174533 * dir;
    float newx = oldx + len * cos(dirRad);
    float newy = oldy + len * sin(dirRad);
    
    glBegin(GL_LINE_LOOP);
    if(iter == 0)
    {
        glVertex2f(newx, newy);
        glVertex2f(oldx, oldy);
        
        oldx = newx;
        oldy = newy;
    }
    else
    {
        iter --;
        drawCurve(dir, len, iter);
        dir += 60;
        drawCurve(dir, len, iter);
        dir -= 120;
        drawCurve(dir, len, iter);
        dir += 60;
        drawCurve(dir, len, iter);
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glColor3f(1, 0, 0);
    
    int n;
    cout<<"\nEnter no of itterations: ";
    cin>>n;
    
    drawCurve(0.0, 0.05, n);
    drawCurve(-120.0, 0.05, n);
    drawCurve(120.0, 0.05, n);
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(w, h);
    glutInitWindowPosition(100, 100);
    
    glutCreateWindow("Koch Curve");
    
    glutDisplayFunc(display);
    
    glutMainLoop();
    
    return 0;
}
