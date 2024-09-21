#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include<bits/stdc++.h>
#include "BmpLoader.h"
double Txval=0,Tyval=0,Tzval=0,eyex=2,eyey=2,x,y,eyez=10,centerx=2,centery=0,centerz=0,near_val=6,far_val=50;
double windowHeight=1000, windowWidth=1300;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0,angle_y=0.0,angle_x=0.0,angle_z=0.0,open = 0.0,open_d = 0.0,fr_x = 0.0,fr_y = 0.0,fr_z = 0.0,fr_dx = 0.0,fr_dy = 0.0,fr_dz = 0.0;
GLfloat angleYaw = 90.0, anglePitch = 270.0, angleRoll = 90.0;
double limit,roll_value = .5,upx=0,upy=1,upz=0;
GLboolean bRotate = false, uRotate = false;
int sw=0,rdegree;
float n=0,deg=90,tlz=22,tlx=-1,spx1=-7,spy1=8,spz1=-6,spx2=15,spy2=-7,spz2=-15;
unsigned int numOfTexs = 6;
unsigned int * textures;
unsigned int ID,ID1,ID3;
GLfloat twicepi = 2.0f * 3.1416;
int sptlght,fanon,choice=0;
static GLfloat v[8][3] =
{
    {0,2,0},
    {2,2,0},
    {2,2,2},
    {0,2,2},
    {0,0,2},
    {0,0,0},
    {2,0,0},
    {2,0,2}

};

static GLubyte quadIndices[2][8] =
{
    {0,1,3,2,4,7,5,6},
    {0,3,5,4,2,7,1,6}

};

static GLfloat v_box[8][3] =
{
    {-2.0, 0.0, 0.0},
    {2.0, 0.0, 0.0},
    {-2.0, 0.0, 2.0},
    {2.0, 0.0, 2.0},

    {-2.0, 2.0, 0.0},
    {2.0, 2.0, 0.0},
    {-2.0, 2.0, 2.0},
    {2.0, 2.0, 2.0}
};

static GLubyte quadIndices1[6][4] =
{
    {0,2,3,1},
    {0,2,6,4},
    {2,3,7,6},
    {1,3,7,5},
    {1,5,4,0},
    {6,7,5,4}
};

static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}
void drawBox()
{
  //  glColor3f(1,1,1);
    //GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_QUADS);
    for (GLint i = 0; i <2; i++)
    {
        //glColor3f(colors[4][0],colors[4][1],colors[4][2]);
        getNormal3p(v_box[quadIndices1[i][0]][0], v_box[quadIndices1[i][0]][1], v_box[quadIndices1[i][0]][2],
                    v_box[quadIndices1[i][1]][0], v_box[quadIndices1[i][1]][1], v_box[quadIndices1[i][1]][2],
                    v_box[quadIndices1[i][2]][0], v_box[quadIndices1[i][2]][1], v_box[quadIndices1[i][2]][2]);

        glVertex3fv(&v_box[quadIndices1[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_box[quadIndices1[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_box[quadIndices1[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_box[quadIndices1[i][3]][0]);glTexCoord2f(0,1);
    }
    glEnd();
    //glutSolidSphere (3.0, 20, 16);

}


void drawcube(float val1,float val2, float val3)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { val1,val2,val3,0.3};
    GLfloat mat_diffuse[] = {  val1,val2,val3,1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);


    glBegin(GL_QUAD_STRIP);
    for (GLint i = 0; i <2; i++)
    {

        glVertex3fv(&v[quadIndices[i][0]][0]);
        glVertex3fv(&v[quadIndices[i][1]][0]);
        glVertex3fv(&v[quadIndices[i][2]][0]);
        glVertex3fv(&v[quadIndices[i][3]][0]);
        glVertex3fv(&v[quadIndices[i][4]][0]);

        glVertex3fv(&v[quadIndices[i][5]][0]);
        glVertex3fv(&v[quadIndices[i][6]][0]);
        glVertex3fv(&v[quadIndices[i][7]][0]);
    }
    glEnd();
}
void LoadTexture1(const char*filename)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}
void LoadTexture2(const char*filename)
{
    glGenTextures(2, &ID1);
    glBindTexture(GL_TEXTURE_2D, ID1);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}
void LoadTexture3(const char*filename)
{
    glGenTextures(3, &ID3);
    glBindTexture(GL_TEXTURE_2D, ID1);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

void LoadTexture(const char*filename, unsigned int id)
{

    glBindTexture(GL_TEXTURE_2D, id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}
void sphere(float val1,float val2, float val3)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { val1, val2, val3, 0.3 };
    GLfloat mat_diffuse[] = { val1, val2, val3, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {20};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);

    glutSolidSphere (1.0, 20, 6);
}
void drawcubeT(int choice)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 1,1,1,0.3};
    GLfloat mat_diffuse[] = { 1,1,1,1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {100};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);


    glBegin(GL_QUAD_STRIP);
    if(choice==0)
    {


    for (GLint i = 0; i <2; i++)
    {

        glVertex3fv(&v[quadIndices[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v[quadIndices[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v[quadIndices[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v[quadIndices[i][3]][0]);glTexCoord2f(0,1);
        glVertex3fv(&v[quadIndices[i][4]][0]);glTexCoord2f(1,1);

        glVertex3fv(&v[quadIndices[i][5]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v[quadIndices[i][6]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v[quadIndices[i][7]][0]);glTexCoord2f(0,1);
    }
    glEnd();
    }
    else if(choice==1)
    {

    for (GLint i = 0; i <2; i++)
    {

        glVertex3fv(&v[quadIndices[i][0]][0]);glTexCoord2f(0,1);
        glVertex3fv(&v[quadIndices[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v[quadIndices[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v[quadIndices[i][3]][0]);glTexCoord2f(1,1);

        glVertex3fv(&v[quadIndices[i][4]][0]);glTexCoord2f(0,1);
        glVertex3fv(&v[quadIndices[i][5]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v[quadIndices[i][6]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v[quadIndices[i][7]][0]);glTexCoord2f(1,1);
    }
    glEnd();
    }
}

static GLfloat t[3][3] =
{
    {0,0,0},
    {1,0,0},
    {1,1,0}


};
static GLubyte triangleIndices[1][3] =
{
    {0,1,2}

};



void drawtriangle(float val1,float val2, float val3)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { val1,val2,val3,0.3};
    GLfloat mat_diffuse[] = {  val1,val2,val3,1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);


    glBegin(GL_TRIANGLE_STRIP);
    for (GLint i = 0; i <1; i++)
    {

        glVertex3fv(&v[triangleIndices[i][0]][0]);
        glVertex3fv(&v[triangleIndices[i][1]][0]);
        glVertex3fv(&v[triangleIndices[i][2]][0]);
    }
    glEnd();


}

void triangle()
{
    glPushMatrix();
    glTranslatef(-4,-7.8,-1);
    glScalef(4,0.1,2);
    glRotatef(-90,0,1,0);
    drawtriangle(0.509,0.286,0.043);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4,-8,-1);
    glScalef(4,0.1,2);
    glRotatef(-90,0,1,0);
    drawtriangle(0.509,0.286,0.043);
    glPopMatrix();



}

void glass()
{
    glPushMatrix();
    glTranslatef(0,0,0);
    glScalef(0.05,1,0.05);
    drawcube(0,0,0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,0);
    glScalef(1,0.05,0.05);
    drawcube(0,0,0);
    glPopMatrix();
     glPushMatrix();
    glTranslatef(0,1,0);
    glScalef(1,0.05,0.05);
    drawcube(0,0,0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1,0,0);
    glScalef(0.05,1,0.05);
    drawcube(0,0,0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(2,0,0);
    glScalef(0.05,1,0.05);
    drawcube(0,0,0);
    glPopMatrix();

     glPushMatrix();
    glTranslatef(0,2,0);
    glScalef(1.05,0.05,0.05);
    drawcube(0,0,0);
    glPopMatrix();


}


void bigwindow()
{


     glPushMatrix();
    glTranslatef(0,0,0);

    glass();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2,0,0);

    glass();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(2,2,0);

    glass();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,2,0);
         glass();
    glPopMatrix();

    ///background
     glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,textures[1]);
    glTranslatef(0,0,0);
    glScalef(2,2,0);
    drawcubeT(0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void wall(void)
{

    //seat
    glPushMatrix();
    glTranslatef(12,-8,-13);
    glScalef(3.5,1.5,1.5);
    drawcube(0.458, 0.1, 0.62);
    glPopMatrix();
    //mattress1
    glPushMatrix();
    glTranslatef(12,-5,-13);
    glScalef(1.16,0.2,1.5);
    drawcube(0.4, 0.1, 0.62);
    glPopMatrix();
    //mattress
    glPushMatrix();
    glTranslatef(14.35,-5,-13);
    glScalef(1.16,0.2,1.5);
    drawcube(0.4, 0.1, 0.62);
    glPopMatrix();
    //mattress
    glPushMatrix();
    glTranslatef(16.7,-5,-13);
    glScalef(1.16,0.2,1.5);
    drawcube(0.4, 0.1, 0.62);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9,-8,-12.8);
    glScalef(1.5,6,1.5);
    drawcube(0.5, 0.411, 0.62);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(19,-8,-12.8);
    glScalef(1.5,6,1.5);
    drawcube(0.5, 0.411, 0.62);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(12,2,-13);
    glScalef(3.5,1,1.5);
    drawcube(0.5, 0.411, 0.62);
    glPopMatrix();
    ///glass
    glPushMatrix();
    glRotatef(13,1,0,0);
    glTranslatef(12,-7.3,-11);
    glScalef(1.7,1.7,0.1);
    bigwindow();
    glPopMatrix();


}

void wallleft(void)
{
   glPushMatrix();
    glTranslatef(-10,-2,-8);
    glScalef(0.2,6,10);
    drawcube(0.458, 0.411, 0.62);
    glPopMatrix();
}
void wallright()
{
   glPushMatrix();
    glTranslatef(36,-8,-10);
    glScalef(0.2,6,14);
     drawcube(0.458, 0.411, 0.62);
    glPopMatrix();
}

void part()
{
    glPushMatrix();
    glTranslatef(25,-8,3);
    glScalef(5.5,6,0.2);
     drawcube(0.458, 0.411, 0.62);
    glPopMatrix();
}

void corridor()
{
    //floor
    glPushMatrix();
    glTranslatef(3,-8,-10);
    glScalef(3,0.2,-4.5);
    drawcube(.5,.3,.2);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(3,-8,-10);
    glScalef(0.2,6,-4.5);
    drawcube(0.458, 0.411, 0.62);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(3,-8,-19.3);
    glScalef(3,6,0.2);
    drawcube(0.458, 0.411, 0.62);
    glPopMatrix();
    //rightwallbottom
    glPushMatrix();
    glTranslatef(8.7,-8,-10);
    glScalef(.2,2,-4.5);
    drawcube(0.458, 0.411, 0.62);
    glPopMatrix();
    //windowglass
    glPushMatrix();
    glTranslatef(8.55,-4,-11.5);
    glScalef(.1,3,-2.7);
    drawcube(1,1,1);
    glPopMatrix();
    //window wall right
    glPushMatrix();
    glTranslatef(8.6,-4,-12.25);
    glScalef(.2,4,1.2);
    drawcube(0.458, 0.411, 0.62);
    glPopMatrix();
     //window wall left
    glPushMatrix();
    glTranslatef(8.6,-4,-19);
    glScalef(.2,4,1.2);
    drawcube(0.458, 0.411, 0.62);
    glPopMatrix();
    //bar over window
    glPushMatrix();
    glTranslatef(8.7,2,-18);
    glScalef(.2,1,3);
   drawcube(0.458, 0.411, 0.62);
    glPopMatrix();


}

void wallfront(void)
{
    glPushMatrix();
    glTranslatef(-4,-8,18);
    glScalef(20,6,0.2);
    drawcube(0.458, 0.411, 0.62);
    glPopMatrix();
}

void step()
{
    glPushMatrix();
    glTranslatef(3,-7.8,-13);
    glScalef(9.5,0.3,4.6);
    drawcube(.4,.3,.2);
    glPopMatrix();

}

void bathroom()
{
    //door
    glPushMatrix();
    glTranslatef(3,-8,-10);
    glScalef(0.2,6,4);
    drawcube(0.458, 0.411, 0.62);
    glPopMatrix();
    //backwall
    glPushMatrix();
    glTranslatef(-4,-8,-3);
    glScalef(3.5,6,0.2);
    drawcube(0.458, 0.411, 0.62);
    glPopMatrix();
}
void floortotal()
{
   // glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(16,-8,-10);
    glScalef(10,0.1,15);
   // LoadTexture3("E:\\assginment 1\\F.R.I.E.N.D.S\\floorH.bmp");
    drawcube(0.509,0.286,0.043);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-4,-8.25,-10);
    glScalef(20,0.1,15);
  drawcube(0.509,0.286,0.043);
  //  drawcube(.35,0.219,0.164);
    glPopMatrix();
}
void floorkitchen()
{
    // glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    //glBindTexture(GL_TEXTURE_2D,textures[2]);
    glTranslatef(-10,-8,2);
    glScalef(3,0.1,8);
    drawcube(0.509,0.286,0.043);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-10,-8.25,2);
    glScalef(3,0.1,9);
    drawcube(0.509,0.286,0.043);
    glPopMatrix();
}


void dinning_table()
{
    glPushMatrix();
    glTranslatef(3,-4,6);
    glScalef(3,0.1,3);
    sphere(0.8,.52,.247);
    glPopMatrix();
    //leg
    glPushMatrix();
    glTranslatef(0.2,-8,6);
    glScalef(0.12,2,0.12);
    drawcube(0.8,.52,.247);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.75,-8,6);
    glScalef(0.12,2,0.12);
    drawcube(0.8,.52,.247);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3,-8,8.75);
    glScalef(0.12,2,0.12);
    drawcube(0.8,.52,.247);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3,-8,3.15);
    glScalef(0.12,2,0.12);
    drawcube(0.8,.52,.247);
    glPopMatrix();

}
void chairdisplay()
{

    glPushMatrix();
    glScalef(1,.1,1);
    drawcube(.34,.031,.031);
    glPopMatrix();

    glPushMatrix();
    glScalef(.1,-1,.1);
    drawcube(.34,.031,.031);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.8,0,0);
    glScalef(.1,-1,.1);
    drawcube(.34,.031,.031);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,1.8);
    glScalef(.1,-1,.1);
    drawcube(.34,.031,.031);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.8,0,1.8);
    glScalef(.1,-1,.1);
    drawcube(.34,.031,.031);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,0);
    glScalef(.1,1,.1);
    drawcube(.34,.031,.031);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.7,0,0);
    glScalef(.1,1,.1);
    drawcube(.34,.031,.031);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.1,1.8,0);
    glScalef(.8,-.3,.1);

    drawcube(.34,.031,.031);
    glPopMatrix();
}
void bed()
{
    glPushMatrix();
    glTranslatef(0,0,-6);
    glScalef(4.2,.4,1.5);
    drawcube(.34,.031,.031);
    glPopMatrix();
    //mattress
    glPushMatrix();
    glTranslatef(0,.8,-6);
    glScalef(1.5,.3,1.5);
    drawcube(1,1,1);
    glPopMatrix();
    //duvet
    glPushMatrix();
    glTranslatef(3,.8,-6);
    glScalef(2.7,.3,1.5);
    drawcube(.6,.4,.8);
    glPopMatrix();
    //pillow
    glPushMatrix();
    glTranslatef(0.1,1.3,-5.7);
    glScalef(.5,.2,.6);
    drawcube(.3,.1,.6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.1,1.3,-4.4);
    glScalef(.5,.2,.6);
    drawcube(.3,.1,.6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-.3,-.4,-6);
    glScalef(.1,.2,.1);
    drawcube(.34,.031,.031);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-.3,-.4,-3.2);
    glScalef(.1,.2,.1);
    drawcube(.34,.031,.031);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.4,-.4,-7);
    glScalef(.1,.2,.1);
    drawcube(.34,.031,.031);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.4,-.4,-3.2);
    glScalef(.1,.2,.1);
    drawcube(.34,.031,.031);
    glPopMatrix();

    //headboard
    glPushMatrix();
    glTranslatef(-.4,0,-6);
    glScalef(.2,1.3,1.5);
    drawcube(.3,.4,.2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.4,0,-6);
    glScalef(.2,1,1.5);
    drawcube(.3,.4,.2);
    glPopMatrix();
    //matress
}
void closet()
{
    glPushMatrix();
    glTranslatef(-2,-1,-5);
    glScalef(3.3,4,.5);
    drawcube(.34,.031,.031);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.6,-.85,-3.89);
    glScalef(1.4,3.8,0);
    drawcube(.4,.1,.7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.4,-.85,-3.89);
    glScalef(1.4,3.8,0);
    drawcube(.4,.1,.7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,2.5,-3.89);
    glScalef(.06,.7,0);
    drawcube(.4,.1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.6,2.5,-3.89);
    glScalef(.06,.7,0);
    drawcube(.4,.1,1);
    glPopMatrix();

}
void fixedposition()
{


   glPushMatrix();
    glTranslatef(2,-1.5,8);
    glScalef(0.8,.8,0.6);
    dinning_table();
    glPopMatrix();

     glPushMatrix();
    glTranslatef(6,-5.7,10);
    glScalef(0.8,1,0.6);
    glRotatef(-60,0,1,0);
    chairdisplay();
    glPopMatrix();

     glPushMatrix();
    glTranslatef(7,-5.7,13.5);
    glScalef(0.8,1,0.6);
    glRotatef(-125,0,1,0);
    chairdisplay();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2,-5.7,13.5);
    glScalef(0.8,1,0.6);
    glRotatef(120,0,1,0);
    chairdisplay();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2,-5.7,10);
    glScalef(0.8,1,0.6);
    glRotatef(60,0,1,0);
    chairdisplay();
    glPopMatrix();
}
void sofa()
{
    ///base
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    LoadTexture2("E:\\assginment 1\\F.R.I.E.N.D.S\\sofa.bmp");
    glTranslatef(0,0,-6);
    glScalef(0.5,.5,1.5);
    drawcubeT(0);
   //drawcube(0.584,0.133,0.388);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    ///mat
  glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    LoadTexture2("E:\\assginment 1\\F.R.I.E.N.D.S\\sofa.bmp");
    glTranslatef(0,.8,-6);
    glScalef(0.5,.3,1.5);
     drawcubeT(0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    ///pillowLEFT
    glPushMatrix();
    glTranslatef(.1,1.5,-4.3);
    glScalef(.1,.5,.6);
   // glRotatef(55,1,0,0);
     drawcube(0.945,0.58,0.541);
    glPopMatrix();
    ///pillowRIGHT
     glPushMatrix();
    glTranslatef(.1,1.5,-6);
    glScalef(.1,.5,.6);
   // glRotatef(55,1,0,0);
     drawcube(0.945,0.58,0.541);
    glPopMatrix();


    /*glPushMatrix();
    glTranslatef(-.3,-.4,-6);
    glScalef(.1,.2,.1);
     drawcube(0.945,0.58,0.541);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-.1,-0.4,-3.2);
    glScalef(.1,.2,.1);
     drawcube(0.482,0.141,0.11);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(.8,-.4,-3.2);
    glScalef(.1,.2,.1);
     drawcube(0.482,0.141,0.11);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,-.4,-4);
    glScalef(.1,.1,.1);
     drawcube(0.482,0.141,0.11);
    glPopMatrix();*/

    ///board
  glEnable(GL_TEXTURE_2D);
    glPushMatrix();
     LoadTexture2("E:\\assginment 1\\F.R.I.E.N.D.S\\sofa.bmp");
    glTranslatef(-.4,0,-6);
    glScalef(.2,1.3,1.5);
     drawcubeT(0);
  glPopMatrix();
glDisable(GL_TEXTURE_2D);
glEnable(GL_TEXTURE_2D);
    glPushMatrix();
  LoadTexture2("E:\\assginment 1\\F.R.I.E.N.D.S\\sofa.bmp");
    glTranslatef(1,0,-6);
    glScalef(.05,.5,1.5);
     drawcubeT(0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



}
void sofa_single()
{

    ///base
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,textures[0]);
    glTranslatef(0,0,-6);
    glScalef(0.5,.4,1.5);
   drawcubeT(0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    ///mat
glEnable(GL_TEXTURE_2D);
    glPushMatrix();
 glBindTexture(GL_TEXTURE_2D,textures[0]);
 glTranslatef(0,.8,-6);
    glScalef(0.5,.3,1.5);
    drawcubeT(0);
    glPopMatrix();
glDisable(GL_TEXTURE_2D);
    ///pillowLEFT
    glPushMatrix();
    glTranslatef(.1,2,-5);
    glScalef(.1,.5,.6);
    glRotatef(55,1,0,0);
    drawcubeT(0);
    glPopMatrix();


/*glPushMatrix();
    glTranslatef(-.3,-.4,-6);
    glScalef(.1,.2,.1);
     drawcube(0.945,0.58,0.541);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-.3,-0.4,-3.2);
    glScalef(.1,.2,.1);
    drawcube(0.482,0.141,0.11);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(.8,-.4,-3.2);
    glScalef(.1,.2,.1);
     drawcube(0.482,0.141,0.11);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.8,-.4,-4);
    glScalef(.1,.2,.1);
     drawcube(0.482,0.141,0.11);
    glPopMatrix();*/

    ///board
  glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,textures[0]);
    glTranslatef(-.4,0,-6);
    glScalef(.2,1.3,1.5);
     drawcubeT(0);
  glPopMatrix();
glDisable(GL_TEXTURE_2D);
glEnable(GL_TEXTURE_2D);
    glPushMatrix();
 glBindTexture(GL_TEXTURE_2D,textures[0]);
    glTranslatef(1,0,-6);
    glScalef(.05,.5,1.5);
     drawcubeT(0);
    glPopMatrix();
}
void sofa_double()
{
///sofa
    glPushMatrix();
    glTranslatef(10.1,-7.8,19.8);
    glScalef(2.3,1.9,2.7);
    sofa();
    glPopMatrix();
  ///right
    glPushMatrix();
    glTranslatef(9.2,-7.6,11.75);
    glScalef(1.7,1.5,0.2);
     drawcube(0.8,0.141,0.11);
    glPopMatrix();
   ///left
    glPushMatrix();
    glTranslatef(9.2,-7.6,3.2);
    glScalef(1.7,1.5,0.2);
    drawcube(0.8,0.141,0.11);
    glPopMatrix();
}

void cabinet()
{

   glPushMatrix();
    glTranslatef(0,0,-3);
    glScalef(0.8,1.,2);
    drawcube(0.1, 0.611, 0.62);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,2,-3);
     glScalef(0.8,2.5,0.1);
     drawcube(0.1, 0.611, 0.62);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,6.8,-3);
    glScalef(0.8,0.1,2);
    drawcube(0.1, 0.611, 0.62);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,2,0.8);
    glScalef(0.8,2.5,0.1);
    drawcube(0.1, 0.611, 0.62);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,2,-1.2);
    glScalef(0.8,2.5,0.1);
    drawcube(0.1, 0.611, 0.62);
    glPopMatrix();

    glPushMatrix();
  glTranslatef(0,3.6,-3);
    glScalef(0.8,0.1,2);
     drawcube(0.1, 0.611, 0.62);
    glPopMatrix();

    glPushMatrix();
     glTranslatef(0,5.3,-3);
    glScalef(0.8,0.1,2);
     drawcube(0.1, 0.611, 0.62);
    glPopMatrix();

}
void Fridge()
{
    glPushMatrix();
    glTranslatef(0,0,0);
    glScalef(0.9,1.8,1);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.1,2.1,2);
    glScalef(0.8,0.6,0.05);
    drawcube(1,0.5,0.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.1,0.2,2);
    glScalef(0.8,0.9,0.05);
    drawcube(1,0.5,0.8);
    glPopMatrix();

}

void counter()
{
    glPushMatrix();
    glTranslatef(0,0,-3);
    glScalef(0.8,1.,2);
    glRotatef(-90,0,1,0);
    drawcube(0.1, 0.611, 0.62);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.05,2,-3.05);
    glScalef(0.85,0.1,2.05);
    glRotatef(-90,0,1,0);
    drawcube(0.1, 0.71, 0.62);
    glPopMatrix();
}
void TVRack()
{
    glPushMatrix();
    glTranslatef(0,0,-0.5);
    glScalef(1,1,1);
    drawcube(0.1, 0.611, 0.62);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,3);
    glScalef(1,1,1);
    drawcube(0.1, 0.611, 0.62);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,1.8,1.5);
    glScalef(1,.1,1);
    drawcube(0.1, 0.611, 0.62);
    glPopMatrix();

    glPushMatrix();
   glTranslatef(0,0,1.5);
    glScalef(1,.1,1);
    drawcube(0.1, 0.611, 0.62);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,1,1.5);
    glScalef(1,.1,1);
    drawcube(0.1, 0.611, 0.62);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-.4,0);
    glScalef(.1,.2,.1);
    drawcube(.34,.031,.031);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.7,-.4,0);
    glScalef(.1,.2,.1);
    drawcube(.34,.031,.031);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-.4,4.2);
    glScalef(.1,.2,.1);
    drawcube(.34,.031,.031);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.7,-.4,4.2);
    glScalef(.1,.2,.1);
    drawcube(.34,.031,.031);
    glPopMatrix();
}

void side_table()
{
    glPushMatrix();
    glTranslatef(1.7,-.4,0);
    glScalef(0.5,.7,0.5);
    drawcube(.34,.031,.031);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.75,-.1,0.9);
    glScalef(.45,.2,.1);
    drawcube(.34,.1,.31);

    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.75,0.4,0.9);
    glScalef(.45,.2,.1);
    drawcube(.34,.1,.31);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.7,-.5,.8);
    glScalef(.1,.2,.1);
    drawcube(.34,.031,.031);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.7,-.5,0);
    glScalef(.1,.2,.1);
    drawcube(.34,.031,.031);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5,-.5,.8);
    glScalef(.1,.2,.1);
    drawcube(.34,.031,.031);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5,-.5,0);
    glScalef(.1,.2,.1);
    drawcube(.34,.031,.031);
    glPopMatrix();

}
void sofasingle()
{

    glPushMatrix();
    glRotatef(-90,0,1,0);

    glScalef(1,1,1);
    sofa_single();
    glPopMatrix();

    ///right
    glPushMatrix();
    glTranslatef(6,-7,-8);
    glScalef(1,1.5,0.2);
    drawcube(0.8,0.141,0.11);
    glPopMatrix();
    ///left
    glPushMatrix();
    glTranslatef(6,-7,-4.5);
    glScalef(1,1.5,0.2);
    drawcube(0.8,0.141,0.11);
    glPopMatrix();

}
void sidetable()
{
    glPushMatrix();
    glTranslatef(1.7,-.4,0);
    glScalef(0.5,.7,0.5);
    drawcube(.34,.031,.031);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.7,-.5,.8);
    glScalef(.1,.2,.1);
    drawcube(.34,.031,.031);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.7,-.5,0);
    glScalef(.1,.2,.1);
    drawcube(.34,.031,.031);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5,-.5,.8);
    glScalef(.1,.2,.1);
    drawcube(.34,.031,.031);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5,-.5,0);
    glScalef(.1,.2,.1);
    drawcube(.34,.031,.031);
    glPopMatrix();

}

void rachel_wall()
{
    glPushMatrix();
    glTranslatef(22,-8,10);
    glScalef(0.2,6,4);
     drawcube(0.458, 0.411, 0.62);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(23,-8,4.2);
    glScalef(2,1,0.8);
    glRotatef(-90,0,1,0);
    bed();
    glPopMatrix();

     glPushMatrix();
    glTranslatef(22.5,-7,4);
    glScalef(2,2,2);
  //  glRotatef(-90,0,1,0);
    side_table();
    glPopMatrix();
}

/*void door()
{

     glPushMatrix();


      if(n==1)
    {
       glTranslatef(-1,-1,22);
        deg=90;
    tlz=16.5;
    tlx=0;

      //  glTranslatef(-52,-0.99,-42);
    }
    glScalef(2.7,5,0.1);
    drawcube(0.458,0.3,0.1);
    glPopMatrix();



    glPopMatrix();
}*/
void monica_room()
{
    glPushMatrix();
    glTranslatef(22,-8,-12.2);
    glScalef(0.2,6,3.8);
    drawcube(0.458, 0.411, 0.62);
    glPopMatrix();
   glPushMatrix();
    glTranslatef(25,-8,3);
    glScalef(0.2,6,1);
    drawcube(0.458, 0.411, 0.62);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(22.4,-8,4.6);
    glScalef(1.3,6,.2);
    drawcube(0.458, 0.411, 0.62);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(22,-8,-10);
    glScalef(7,6,0.2);
    drawcube(0.458, 0.411, 0.62);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(22,-8,1);
    glScalef(0.2,6,3.2);
    drawcube(0.458, 0.411, 0.62);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(21,-8,-9.2);
    glScalef(2,1,0.8);
    glRotatef(-90,0,1,0);
    bed();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(27,-8,-9.2);
    glScalef(1.6,1,0.8);
    glRotatef(-90,0,1,0);
    closet();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(21,-6,-8);
    glScalef(2,2,2);
  //  glRotatef(-90,0,1,0);
    side_table();
    glPopMatrix();

       // door();





}

void table(void)
{
    glPushMatrix();
    glScalef(2,.1,1.3);
    drawcube(0.21961,0.11765 ,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,0);
    glScalef(.1,-1,.1);
    drawcube(0.21961,0.11765 ,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.7,0,0);
    glScalef(.1,-1,.1);
    drawcube(0.21961,0.11765 ,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,2.2);
    glScalef(.1,-1,.1);
    drawcube(0.21961,0.11765 ,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.7,0,2.2);
    glScalef(.1,-1,.1);
    drawcube(0.21961,0.11765 ,0);
    glPopMatrix();
}
void coffeetable()
{

    glPushMatrix();
    glTranslatef(1.7,-.4,0);
    glScalef(.7,.6,1);
    table();
    glPopMatrix();
}

void TV()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
   glBindTexture(GL_TEXTURE_2D,textures[4]);
    glTranslatef(1.7,-.6,0);
    glScalef(0.6,0.7,0.7);
    drawcubeT(0);
    glPopMatrix();
     glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(1.7,-1.2,0.1);
    glScalef(0.7,0.1,.5);
    drawcube(.34,.031,.031);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.7,-1.2,0.5);
    glScalef(0.3,0.3,.1);
    drawcube(.34,.031,.031);
    glPopMatrix();

}



void sink()
{
    glPushMatrix();
    glTranslatef(1.7,-.4,0);
    glScalef(0.6,.1,0.6);
    drawcube(0.7607,0.7,0.7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.7,-3,0);
    glScalef(0.6,1.3,0.6);
    drawcube(.4,.1,.71);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.7,-.4,1);
    glScalef(0.6,.4,0.1);
    drawcube(0.7607,0.7606,0.7686);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.7,-.4,0);
    glScalef(0.1,.4,0.6);
    drawcube(0.7607,0.7606,0.7686);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.7,-.4,0);
    glScalef(0.1,.4,0.6);
    drawcube(0.7607,0.7606,0.7686);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.7,-.4,0);
    glScalef(0.6,.4,0.1);
   drawcube(0.7607,0.7606,0.7686);
    glPopMatrix();


}

void block1()
{
    glPushMatrix();
    glTranslatef(0.2,0.2,0);
    glScalef(0.75,.1,0.65);
    drawcube(.4,.1,.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3,-1.8,0);
    glScalef(0.7,1,0.6);
    drawcube(.4,.1,.6);
    glPopMatrix();
}

   void block2()
   {

    glPushMatrix();
    glTranslatef(2.9,0.2,0);
    glScalef(0.75,.1,0.65);
    drawcube(.34,.1,.031);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.9,-1.8,0);
    glScalef(0.7,1,0.6);
    drawcube(.4,.1,.6);
    glPopMatrix();
}

void stove()
{    glPushMatrix();
    glTranslatef(-4.75,-2.75,12.35);
    glScalef(0.4,0.1,0.4);
    drawcube(0.7,0.8,.8);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-5.1,-2.9,12.1);
    glScalef(0.7,0.1,0.7);
    drawcube(0,0,0);
    glPopMatrix();
}

void kitchen()
{
    glPushMatrix();
    glTranslatef(-8,-8,3.5);
    glScalef(1,1.2,1.3);
    glRotatef(180,0,1,0);
    cabinet();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5.4,-8,11.5);
    glScalef(1.4,1.5,1.3);
    glRotatef(90,0,1,0);
    counter();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-8,-2);
    glScalef(1.5,2,1.5);
    Fridge();
    glPopMatrix();

    glPushMatrix();
    glRotatef(45,0,1,0);
    glTranslatef(-7.8,-5.3,-5);
    glScalef(2.3,1.5,1.5);
    block1();
    glPopMatrix();

    glPushMatrix();
    glRotatef(45,0,1,0);
    glTranslatef(-6.7,-4.9,-5.05);
    glScalef(1.6,1,1.7);
    sink();
        glPopMatrix();
    ///pipe

    glPushMatrix();
    glTranslatef(-5,-4.5,0.6);
    glScalef(0.05,.45,0.05);
    drawcube(0,0,0);
    glPopMatrix();
    glPushMatrix();
    glRotatef(45,0,1,0);
    glTranslatef(-4.2,-3.7,-3);
    glScalef(0.3,0.05,0.05);
    drawcube(0,0,0);
    glPopMatrix();


    glPushMatrix();
    //glRotatef(45,0,1,0);
    glTranslatef(-4.7,-5.3,-3.2);
    glScalef(2.6,1.5,2);
    block1();
    glPopMatrix();

    glPushMatrix();

    glTranslatef(-10,-5.3,12);
    glScalef(2,1.5,2.6);
    glRotatef(90,0,1,0);
    block1();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-6,-1.4,2.5);
    glScalef(0.5,1,0.5);
    stove();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6,-1.4,4.2);
    glScalef(0.5,1,0.5);
    stove();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-9.2,-4.5,8);
    glScalef(0.9,0.1,1.7);
    drawcube(0.9,0.9,0.9);
    glPopMatrix();
    glPushMatrix();
    glRotatef(45,0,1,0);
    glTranslatef(-6.2,-3.7,-4);
    glScalef(0.9,1.3,0.1);
    bigwindow();
    glPopMatrix();


}
void drawing_room()
{
    //carpet
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(15.7,-7.7,1.5);
    glScalef(2,0,7.1);
    LoadTexture1("D:\\4.2\\carpet.bmp");
    drawBox();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
   /*glPushMatrix();
    glTranslatef(11,-7.7,1.5);
    glScalef(4.5,0,7);

    drawcube(0.458, 0.411, 0.62);
    glPopMatrix();*/

    //wallleft
    glPushMatrix();
    glTranslatef(-10,-8,3);
    glScalef(0.2,6,7);
    drawcube(0.458, 0.411, 0.62);
    glPopMatrix();
    ///sidetable

    glPushMatrix();

    glTranslatef(8.1,-6,3.3);
    glScalef(1.6,1.4,1.5);
    side_table();
    glPopMatrix();


    glPushMatrix();

    glTranslatef(8.1,-6,15);
    glScalef(1.6,1.4,1.5);

    sidetable();
    glPopMatrix();

    //door


    glPushMatrix();
    glTranslatef(12,-5.2,6);
    glScalef(1.5,1.5,1.5);
    coffeetable();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(20,-7.5,4.5);
    glScalef(1,1.4,1);
    TVRack();
    glPopMatrix();





}

void setCameraEye_Pitch()
{

    centery = 200.0*(cos(anglePitch*3.1416/180.0));

}
void setCameraEye_Yaw()
{

    centerx = 200.0*(cos(angleYaw*3.1416/180.0));
}
void setCameraEye_Roll()
{
    upx = 200.0*(cos(angleRoll*3.1416/180.0));
    upy = 200.0*(sin(angleRoll*3.1416/180.0));
}

void spotlight1(int sptlght)

{
    GLfloat no_lights[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambients[]  = {1.0, 1.0, 1.0,1.0};
    GLfloat light_diffuses[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_speculars[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_positions[] = {spx1,spy1,spz1};
    if(sptlght==0)
    {
    glEnable(GL_LIGHT1);
    glLightfv( GL_LIGHT1, GL_AMBIENT, no_lights);
    glLightfv( GL_LIGHT1, GL_DIFFUSE, no_lights);
    glLightfv( GL_LIGHT1, GL_SPECULAR, no_lights);
    glLightfv( GL_LIGHT1, GL_POSITION, light_positions);
    }
    else if(sptlght==1)
    {
    glEnable(GL_LIGHT1);
    glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambients);
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuses);
    glLightfv( GL_LIGHT1, GL_SPECULAR, light_speculars);
    glLightfv( GL_LIGHT1, GL_POSITION, light_positions);
    }
    else if(sptlght==2)
    {
    glEnable(GL_LIGHT1);
    glLightfv( GL_LIGHT1, GL_AMBIENT, no_lights);
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuses);
    glLightfv( GL_LIGHT1, GL_SPECULAR, light_speculars);
    glLightfv( GL_LIGHT1, GL_POSITION, light_positions);
    }
    else if(sptlght==3)
    {
    glEnable(GL_LIGHT1);
    glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambients);
    glLightfv( GL_LIGHT1, GL_DIFFUSE, no_lights);
    glLightfv( GL_LIGHT1, GL_SPECULAR, light_speculars);
    glLightfv( GL_LIGHT1, GL_POSITION, light_positions);
    }
    else if(sptlght==4)
    {
    glEnable(GL_LIGHT1);
    glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambients);
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuses);
    glLightfv( GL_LIGHT1, GL_SPECULAR,no_lights);
    glLightfv( GL_LIGHT1, GL_POSITION, light_positions);
    }

    GLfloat spt_dir[] = {0,-1,0};
    GLfloat spt_ct[] = {45};
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spt_dir);
    glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, spt_ct);


}
void spotlight2(int sptlght)

{
    GLfloat no_lights[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambients[]  = {1.0, 1.0, 1.0,1.0};
    GLfloat light_diffuses[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_speculars[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_positions[] = {spx2,spy2,spz2};
    if(sptlght==0)
    {
    glEnable(GL_LIGHT1);
    glLightfv( GL_LIGHT1, GL_AMBIENT, no_lights);
    glLightfv( GL_LIGHT1, GL_DIFFUSE, no_lights);
    glLightfv( GL_LIGHT1, GL_SPECULAR, no_lights);
    glLightfv( GL_LIGHT1, GL_POSITION, light_positions);
    }
    else if(sptlght==1)
    {
    glEnable(GL_LIGHT1);
    glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambients);
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuses);
    glLightfv( GL_LIGHT1, GL_SPECULAR, light_speculars);
    glLightfv( GL_LIGHT1, GL_POSITION, light_positions);
    }
    else if(sptlght==2)
    {
    glEnable(GL_LIGHT1);
    glLightfv( GL_LIGHT1, GL_AMBIENT, no_lights);
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuses);
    glLightfv( GL_LIGHT1, GL_SPECULAR, light_speculars);
    glLightfv( GL_LIGHT1, GL_POSITION, light_positions);
    }
    else if(sptlght==3)
    {
    glEnable(GL_LIGHT1);
    glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambients);
    glLightfv( GL_LIGHT1, GL_DIFFUSE, no_lights);
    glLightfv( GL_LIGHT1, GL_SPECULAR, light_speculars);
    glLightfv( GL_LIGHT1, GL_POSITION, light_positions);
    }
    else if(sptlght==4)
    {
    glEnable(GL_LIGHT1);
    glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambients);
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuses);
    glLightfv( GL_LIGHT1, GL_SPECULAR,no_lights);
    glLightfv( GL_LIGHT1, GL_POSITION, light_positions);
    }

    GLfloat spt_dir[] = {0,-1,0};
    GLfloat spt_ct[] = {45};
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spt_dir);
    glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, spt_ct);


}
void light0(int on)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = { 1.0, 0.984, .827, 1.0 };
    GLfloat light_diffuse[]  = { 1.0, 0.984, .827, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { -1, 9.0, 5.0, 1.0 };

    if(on==1)
    {
        glEnable( GL_LIGHT0);
        glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv( GL_LIGHT0, GL_POSITION, light_position);

    }
    else if(on==0)
    {
        glDisable( GL_LIGHT0);
        glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    }
    else if(on==2)
    {
        glEnable( GL_LIGHT0);
        glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);
        glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    }
    else if(on==3)
    {
        glEnable( GL_LIGHT0);
        glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);
        glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    }
    else if(on==4)
    {
        glEnable( GL_LIGHT0);
        glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);
        glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    }
    else if(on==5)
    {
        glEnable( GL_LIGHT0);
        glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);
        glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);
        glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    }
    else if(on==6)
    {
        glEnable( GL_LIGHT0);
        glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);
        glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);
        glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    }
     else if(on==7)
    {
       glEnable( GL_LIGHT0);
        glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);
        glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);
        glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    }

}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
   // glFrustum(-5,5, -5,5, near_val, far_val);
    gluPerspective(60,1,5,100);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyex,eyey,eyez, centerx,centery,centerz, upx,upy,upz);

    glViewport(0, 0, windowWidth, windowHeight);

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    light0(sw);
    spotlight1(sptlght);
    //glRotatef(90,0,0,1);
    glTranslatef(Txval,Tyval,Tzval);
    glRotated(angle_x,1,0,0);
    glRotated(angle_y,0,1,0);
    glRotated(angle_z,0,0,1);


    glPushMatrix();
    glTranslatef(21,-2.5,4.65);
    glScalef(0.1,2,2.8);
    TV();
    glPopMatrix();    //




   floortotal();
    floorkitchen();

    wall();
    wallright();


     // counter();


    step();
      glPushMatrix();
    glTranslatef(0,0,-2);

    drawing_room();
    glPopMatrix();

    bathroom();
    part();
    monica_room();
    corridor();
    rachel_wall();

    sofa_double();
        kitchen();

    glPushMatrix();
    glTranslatef(-8.2,-39.2,4.5);
    glScalef(1.4,4,0.6);
    glRotatef(180,1,0,0);
    glRotatef(90,0,1,0);
    triangle();
    glPopMatrix();

   glPushMatrix();
    glTranslatef(-29.3,0,-28.8);
    glRotatef(-50,0,1,0);
    glScalef(1,1,0.26);
    wallright();
    glPopMatrix();

     glPushMatrix();
     glTranslatef(1,0,-7.8);
    glRotatef(-60,0,1,0);
    ///sofa
    glPushMatrix();
    glTranslatef(6.5,-7,-1.5);
    glScalef(1.3,1.7,1);

    sofa_single();
    glPopMatrix();
    ///right
    glPushMatrix();
    glTranslatef(6,-7,-8);
    glScalef(1,1.5,0.2);
    drawcube(0.8,0.141,0.11);
    glPopMatrix();
    ///left
    glPushMatrix();
    glTranslatef(6,-7,-4.5);
    glScalef(1,1.5,0.2);
    drawcube(0.8,0.141,0.11);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.7,1,-7.5);
    glScalef(1.3,1.1,1.3);
    fixedposition();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(17.55,-5,-6);
    glScalef(1.2,1.5,0.5);
    glRotatef(180,0,1,0);
    table();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 'E':
        n=1;
        break;
    case 'x':
        angle_x+=2;
        if(angle_x>360.0)
            angle_x=0.0;
        glutPostRedisplay();
        break;
    case 'X':
        angle_x-=2;
        if(angle_x<0.0)
            angle_x=360.0;
        glutPostRedisplay();
        break;
    case 'y':
        angle_y+=2;
        if(angle_y>360.0)
            angle_y=360.0;
        glutPostRedisplay();
        break;
    case 'Y':
        angle_y-=2;

        glutPostRedisplay();
        break;
    case 'z':
        angle_z+=2;
        if(angle_z>360.0)
            angle_z=0.0;
        glutPostRedisplay();
        break;
    case 'Z':
        angle_z-=2;
        if(angle_y<0.0)
            angle_y=360.0;
        glutPostRedisplay();
        break;
    case 'o':
        eyez-=2;
        glutPostRedisplay();
        break;

    case 'g':
        centerx-=2;
        centerz-=2;
        glutPostRedisplay();
        break;
    case 'G':
        centerx+=2;
        centerz-=2;
        glutPostRedisplay();
        break;
    case 'n':
        Tzval+=2;
        spz1+=2;
        spz2+=2;

        if(Tzval>40.0)
            Tzval=40.0;
        glutPostRedisplay();
        break;
    case 'f':
        Tzval-=2;
        spz1-=2;spz2-=2;
        if(Tzval<-40.0)
            Tzval=-40.0;
        glutPostRedisplay();
        break;
    case 'r':
        Txval+=2;
        spx1+=2; spx2+=2;
        if(Txval>40.0)
            Txval=40.0;
        glutPostRedisplay();
        break;
    case 'l':
        Txval-=2;
        spx1=-2; spx2=-2;
        if(Txval<-40.0)
            Txval=-40.0;
        glutPostRedisplay();
        break;
    case 'd':
        Tyval+=2;
        spy1+=2;spy2+=2;
        if(Tyval>40.0)
            Tyval=40.0;
        glutPostRedisplay();
        break;
    case 'D':
        Tyval-=2;
        spy1-=2; spy2-=2;
        if(Tyval<-40.0)
            Tyval=-40.0;
        glutPostRedisplay();
        break;
    case '+':
        near_val+=1;
        glutPostRedisplay();
        break;
    case '-':
        near_val-=1;
        glutPostRedisplay();
        break;
    case 'u':
        if(angleYaw==0.0)
            break;
        angleYaw -= roll_value;
        setCameraEye_Yaw();
        glutPostRedisplay();
        break;
    case 'U':
        if(angleYaw==180)
            break;
        angleYaw += roll_value;
        setCameraEye_Yaw();
        glutPostRedisplay();
        break;
    case 'p':
        if(anglePitch==180)
            break;
        anglePitch -= roll_value;
        setCameraEye_Pitch();
        glutPostRedisplay();
        break;
    case 'P':
        if(anglePitch==360)
            break;
        anglePitch += roll_value;
        setCameraEye_Pitch();
        glutPostRedisplay();
        break;
    case 'q':
        angleRoll -= roll_value;
        setCameraEye_Roll();
        glutPostRedisplay();
        break;
    case 'R':
        angleRoll += roll_value;
        setCameraEye_Roll();
        glutPostRedisplay();
        break;
    case 'L':
        sw=1;
        break;
    case 'e':
        sw=0;
        break;
    case 'a'://NO AMBIENT LIGHT
        sw=2;
        break;
    case '7': //NO DIFFUSE
       sw=3;
        break;
    case 's':// NO SPECULAR
        sw=4;
        break;
    case 'A': //NO AMB AND DIFFUSE
        sw=5;
        break;
    case 'Q': // NO DIFFUSE AND SPEC
        sw=6;
        break;
    case 'b': //NO AMB AND SPEC
        sw=7;

    case '_':
        sptlght=1; //spotlight on
        break;
    case 'N':
        sptlght=0;
        break;
    case 'v':
        sptlght=2;
        break;
    case 'V':
        sptlght=3;
        break;
    case 'j':
        sptlght=4;
        break;


    case 27:  // Escape key
        exit(1);
    }
}



void animate()
{
    if(fanon==1)
    {
        rdegree+=1;
        if(rdegree>360)
            rdegree=0.0;
        glutPostRedisplay();

    }
    else if(fanon==0)
    {
        rdegree=0;
        glutPostRedisplay();
    }
    glutPostRedisplay();

}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Traingle-Demo");

     textures = (unsigned int *)malloc(numOfTexs * sizeof(unsigned int));
    glGenTextures(numOfTexs, textures);
    LoadTexture("E:\\assginment 1\\F.R.I.E.N.D.S\\sofa.bmp", textures[0]); /// 1
    LoadTexture("E:\\assginment 1\\F.R.I.E.N.D.S\\glass.bmp", textures[1]); /// 2
    LoadTexture("E:\\assginment 1\\F.R.I.E.N.D.S\\wooden.bmp", textures[2]);
    LoadTexture("E:\\assginment 1\\F.R.I.E.N.D.S\\tv.bmp", textures[4]);
    //LoadTexture("", textures[4]);
   // LoadTexture("", textures[5]);*/

    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
