//
//  walley_gui.h
//  Walley
//
//  Created by shd101wyy on 12-10-4.
//  Copyright (c) 2012年 shd101wyy. All rights reserved.
//

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

void display(void)
{
    
    glClear (GL_COLOR_BUFFER_BIT);
    glFlush ();
}

void init (void)
{
    /* select clearing color */
    glClearColor (0.0, 0.0, 0.0, 0.0);
    
    /* initialize viewing values */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void drawPoint(void){
    glClear (GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);							// 绘制三角形
    glVertex3f( 0.0f, 0.0f, 0.0f);					// 上顶点
    glVertex3f(0.0f,-1.0f, 0.0f);					// 左下
    glVertex3f( 1.0f,-1.0f, 0.0f);					// 右下
	glEnd();
    glFlush();
}

void init_windows(int argc, char **argv, int width, int height, int x, int y, char *windows_name){
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (width, height);
    glutInitWindowPosition (x, y);
    glutCreateWindow (windows_name);
    //init ();
    glutDisplayFunc(&drawPoint);
    glutWireTeapot(0.5);
    glutMainLoop();
    
}



