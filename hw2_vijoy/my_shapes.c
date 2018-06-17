
#include "CSCIx229.h"
/*
 *  Draw vertex in polar coordinates
 */
void Vertex(double th,double ph, double rgb)
{
   //glColor3f(Cos(th)*Cos(th) , Sin(ph)*Sin(ph) , Sin(th)*Sin(th));
   glColor3f(rgb, rgb, rgb);
   glVertex3d(Sin(th)*Cos(ph) , Sin(ph) , Cos(th)*Cos(ph));
}

/*
 *  Draw a sphere (version 2)
 *     at (x,y,z)
 *     radius (r)
 */
void sphere(double x,double y,double z,double r, double rgb)
{
   const int d=5;
   int th,ph;
   
   
   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glScaled(r,r,r);

   //  Latitude bands
   for (ph=-90;ph<90;ph+=d)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=d)
      {
         Vertex(th,ph, rgb);
         Vertex(th,ph+d, rgb);
      }
      glEnd();
   }

   //  Undo transformations
   glPopMatrix();
}

/*
 *  Draw a cube
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th, double r, double g, double b)
{
   //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  Cube
   glBegin(GL_QUADS);
   //  Front
   glColor3f(r, g, b);
   glVertex3f(-1,-1, 1);
   glVertex3f(+1,-1, 1);
   glVertex3f(+1,+1, 1);
   glVertex3f(-1,+1, 1);
   //  Back
   glVertex3f(+1,-1,-1);
   glVertex3f(-1,-1,-1);
   glVertex3f(-1,+1,-1);
   glVertex3f(+1,+1,-1);
   //  Right
   glVertex3f(+1,-1,+1);
   glVertex3f(+1,-1,-1);
   glVertex3f(+1,+1,-1);
   glVertex3f(+1,+1,+1);
   //  Left
   glVertex3f(-1,-1,-1);
   glVertex3f(-1,-1,+1);
   glVertex3f(-1,+1,+1);
   glVertex3f(-1,+1,-1);
   //  Top
   glVertex3f(-1,+1,+1);
   glVertex3f(+1,+1,+1);
   glVertex3f(+1,+1,-1);
   glVertex3f(-1,+1,-1);
   //  Bottom
   glVertex3f(-1,-1,-1);
   glVertex3f(+1,-1,-1);
   glVertex3f(+1,-1,+1);
   glVertex3f(-1,-1,+1);
   //  End
   glEnd();
   //  Undo transofrmations
   glPopMatrix();
}

void draw_cylinder(float radius,float height,
                   float R, float G,float B)
{
    float x              = 0.0;
    float y              = 0.0;
    float angle          = 0.0;
    float angle_stepsize = 0.1;

    /** Draw the tube */
    glColor3ub(R-40,G-40,B-40);
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;

    while( angle < 2*PI ) {
       x = radius * cos(angle);
       y = radius * sin(angle);
       glVertex3f(x, y , height);
       glVertex3f(x, y , 0.0);
       angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on top of cylinder */
    glColor3ub(R,G,B);
    glBegin(GL_POLYGON);
    angle = 0.0;
    while( angle < 2*PI ) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y , height);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glEnd();

}

void draw_cone(double height, double radius)
{
   int k = 0;
    /* sides */
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_TRIANGLES);
    for (k=0;k<=360;k+=5){
      
      glVertex3f(0,0,height);
      glVertex3f(Cos(k),Sin(k),0);
      glVertex3f(Cos(k+5),Sin(k+5),0);
    }
    glEnd();

    /* bottom circle */ 
    /* rotate back */
    glRotated(90,1,0,0);
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_TRIANGLES);
    for (k=0;k<=360;k+=5) {
      glVertex3f(0,0,0);
      glVertex3f(Cos(k),0,Sin(k));
      glVertex3f(Cos(k+5),0,Sin(k+5));
    }
    glEnd();
}
