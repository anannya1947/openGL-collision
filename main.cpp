#include<GL/gl.h>
#include<GL/glut.h>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<windows.h>

int i,q;
int score = 0;
int screen = 0;
bool collide = false;
char buffer[10];

int ptX = 200, ptY = 70;
int hurdleX[4], hurdleY[4];
int divx = 250, divy = 4, movd;

void drawText(char ch[],int xpos, int ypos)//draw score/message on screen
{
    int numofchar = strlen(ch);
    glLoadIdentity ();
    glRasterPos2f( xpos, ypos);
    for (i = 0; i < numofchar; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[i]);
    }
}


void drawTextNum(char ch[],int numtext,int xpos, int ypos)//counting the score
{
    int len;
    int k;
    k = 0;
    len = numtext - strlen (ch);
    glLoadIdentity ();
    glRasterPos2f( xpos, ypos);//postion pixel and write opwration
    for (i = 0; i <=numtext - 1; i++)
    {
        if ( i < len )
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'0');
        else
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[k]);//adjust current raster position based on width of character
            k++;
        }

    }
}


void hurdlePos()
{
    glClearColor(0,1,0,0);
    for(i = 0; i < 4; i++)
    {
        if(rand() % 2 == 0)
        {
            hurdleX[i] = 400;
        }
        else
        {
            hurdleX[i] = 600;
        }
        hurdleY[i] = 1000 - i * 200;
    }
}


void drawSpace()
{
    glBegin(GL_QUADS);
    glColor3f(0.1,0,0.4);
    glVertex2f(50, 500);
    glVertex2f(50, 0);
    glVertex2f(450, 0);
    glVertex2f(450, 500);
    glEnd();
}

void drawUser()
{
    glPointSize(50.0);

    glBegin(GL_QUADS);
    glColor3f(0.6, 1, 0.1);
    glVertex2f(ptX - 25, ptY + 25);
    glVertex2f(ptX - 18, ptY + 40);
    glVertex2f(ptX + 18, ptY + 40);
    glVertex2f(ptX + 25, ptY + 25);
    glEnd();

}

void drawHurdle()
{

    for(i = 0; i < 4; i++)
    {

        glBegin(GL_TRIANGLES);
        glColor3f(1,0.1,0.1);
        glVertex2f(hurdleX[i], hurdleY[i] + 20);
        glVertex2f(hurdleX[i] - 23, hurdleY[i] - 35);
        glVertex2f(hurdleX[i] + 23, hurdleY[i] - 35);
        glEnd();

        hurdleY[i] = hurdleY[i] - 5;

        if(hurdleY[i] > ptY - 13  && hurdleY[i] < ptY + 15 && hurdleX[i] == ptX)
        {
            collide = true;
        }



        if(hurdleY[i] < -25)
        {
            if(rand() % 2 == 0)
            {
                hurdleX[i] = 200;
            }
            else
            {
                hurdleX[i] = 300;
            }
            hurdleY[i] = 800;
        }
    }
}


void keys(int key, int x, int y)
{
    switch(key)
    {

    case GLUT_KEY_LEFT:
        ptX = 200;
        break;
    case GLUT_KEY_RIGHT:
        ptX = 300;
        break;
    }

    glutPostRedisplay();
}

void init()
{
    glClearColor(0.1,0,0.4,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}


void display()
{
    if(collide != true)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        drawSpace();
        drawUser();
        drawHurdle();
        movd = movd - 16;
        if(movd < - 60)
        {
            movd = 0;
        }

        score = score + 1;

        glColor3f(1,1,1);
        drawText("Score:", 360,455);
        itoa (score, buffer, 10);//integer to char str
        drawTextNum(buffer, 6, 420,455);


        glutSwapBuffers(); //swap front and back buffers
        for(q = 0; q<= 10000000; q++)
        {
            ;
        }
    }
    else
    {
        glColor3f(1,1,1);
        drawText("Game Over", 200,250);
        glutSwapBuffers();
    }
}


int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,500);
    glutCreateWindow("Triangle Breakout");
    hurdlePos();
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(keys);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}
