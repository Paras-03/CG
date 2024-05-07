//
//  main.cpp
//  Car Animation
//
//  Created by Paras Ningune on 07/05/24.
//

#include <iostream>
#include <GLUT/glut.h>
#define w 1000
#define h 600
using namespace std;

float angle = 0.0;
float rotation_speed = -2;
float sx = 10;

void circle(float radius, float cx, float cy)
{
    glBegin(GL_POLYGON);
    for(int i=0; i<=360; i++)
    {
        float angle = i * 3.146/180;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f((x+cx), (y+cy));
    }
    glEnd();
    
    //Spokes
    int num_spokes = 6;
    glColor3ub(255, 255, 255);
    for(int i =0; i<num_spokes; ++i)
    {
        float angle_spoke = i * (360 / num_spokes) * 3.14 / 180;
        glBegin(GL_LINES);
        glVertex2f(cx, cy);
        float x = (radius-2) * cos(angle_spoke);
        float y = (radius-2) * sin(angle_spoke);
        glVertex2f(x, y);
        glEnd();
    }
}

void drawHills()
{
    glColor3ub(184, 134, 11);
    glBegin(GL_POLYGON);
    glVertex2d(0, 300);
    glVertex2d(200, 300);
    glVertex2d(100, 450);
    glEnd();
    
    glColor3ub(218, 165, 32);
    glBegin(GL_POLYGON);
    glVertex2d(150, 300);
    glVertex2d(350, 300);
    glVertex2d(250, 450);
    glEnd();
    
    glColor3ub(184, 134, 11);
    glBegin(GL_POLYGON);
    glVertex2d(300, 300);
    glVertex2d(500, 300);
    glVertex2d(400, 450);
    glEnd();
    
    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.9, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 500, 0.0, 500);
}

void display()
{
    
    drawHills();    //Draw hill
    
    // Make lower background green
    glColor3ub(0, 200, 0);
    glBegin(GL_POLYGON);
    glVertex2d(0, 0);
    glVertex2d(500, 0);
    glVertex2d(500, 300);
    glVertex2d(0, 300);
    glEnd();
    
    //Draw road border
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2d(0, 100);
    glVertex2d(500, 100);
    glVertex2d(500, 200);
    glVertex2d(0, 200);
    glEnd();
    
    //Draw road
    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(0, 110);
    glVertex2d(500, 110);
    glVertex2d(500, 190);
    glVertex2d(0, 190);
    glEnd();
    
    glPushMatrix();
    glTranslatef(sx, 0, 0);
    glScalef(1.5, 1.5, 1.0);
    
    //Car
    glColor3ub(255, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(410, 100);
    glVertex2d(490, 100);
    glVertex2d(485, 130);
    glVertex2d(410, 130);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex2d(420, 130);
    glVertex2d(475, 130);
    glVertex2d(465, 160);
    glVertex2d(430, 160);
    glEnd();
    
    glColor3ub(220, 220, 220);
    glBegin(GL_POLYGON);
    glVertex2d(425, 130);
    glVertex2d(445, 130);
    glVertex2d(445, 150);
    glVertex2d(430, 150);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2d(450, 130);
    glVertex2d(470, 130);
    glVertex2d(465, 150);
    glVertex2d(450, 150);
    glEnd();
    
    glPushMatrix();
    glTranslatef(470, 100, 0);
    glRotatef(angle, 0, 0, 1);
    glColor3ub(90, 90, 90);
    circle(14, 0, 0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(430, 100, 0);
    glRotatef(angle, 0, 0, 1);
    glColor3ub(90, 90, 90);
    circle(14, 0, 0);
    glPopMatrix();
    
    glPopMatrix();
    
    glFlush();
    glutSwapBuffers();
}

void timer(int value)
{
    angle += rotation_speed;
    sx += 1;
    
    if(sx > 0)
    {
        sx = -700;
    }
    glutPostRedisplay();
    glutTimerFunc(1, timer, 0);
}

int main(int argc,char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(w, h);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Car Animation");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0,timer, 0);
    glutMainLoop();
    
    return 0;
}
