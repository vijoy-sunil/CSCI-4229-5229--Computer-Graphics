
#include "CSCIx229.h"

extern int ntex, mode, t_mode;
double rep;
extern float shiny;
extern int emission;

/*
 *  Draw vertex in polar coordinates
 */
void Vertex(double th,double ph, double rgb)
{
   //glColor3f(Cos(th)*Cos(th) , Sin(ph)*Sin(ph) , Sin(th)*Sin(th));
   glColor3f(rgb, rgb, rgb);
   glVertex3d(Sin(th)*Cos(ph) , Sin(ph) , Cos(th)*Cos(ph));
   glNormal3d(Sin(th)*Cos(ph) , Sin(ph) , Cos(th)*Cos(ph));
}

/*
 *  Draw a sphere (version 2)
 *     at (x,y,z)
 *     radius (r)
 */
void sphere(double x,double y,double z,double r, double rgb, unsigned int texture)
{
   const int d=5;
   int th,ph;

   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0}; 
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);  
   
   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  Enable textures
   //  Select texture if textures are on
   if (ntex<0)
      glDisable(GL_TEXTURE_2D);
   else
   {
      glEnable(GL_TEXTURE_2D);
   }

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,t_mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture);
   //  Latitude bands
   for (ph=-90;ph<90;ph+=d)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=d)
      {
         glTexCoord2f(0.0, 0.0);
         Vertex(th,ph, rgb);

	 glTexCoord2f(0.0, rep);
         Vertex(th,ph+d, rgb);
      }
      glEnd();
   }

   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

/*
 *  Draw a cube
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th, double r, double g, double b,
		 unsigned int texture, int top, int bottom, int front, int back, int left, int right)
{
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0}; 
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission); 
   //  Save transformation
   glPushMatrix();

   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);

   //  Enable textures
   //  Select texture if textures are on
   if (ntex<0)
      glDisable(GL_TEXTURE_2D);
   else
   {
      glEnable(GL_TEXTURE_2D);
   }

   glColor3f(r,g,b);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,t_mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture);
   //  Front
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, 1);

   if(front == 1){
      glTexCoord2f(0.0, 0.0); glVertex3f(-1,-1, 1);
      glTexCoord2f(rep, 0.0); glVertex3f(+1,-1, 1);
      glTexCoord2f(rep, rep); glVertex3f(+1,+1, 1);
      glTexCoord2f(0.0, rep); glVertex3f(-1,+1, 1);      
   }
   else{
      glVertex3f(-1,-1, 1);
      glVertex3f(+1,-1, 1);
      glVertex3f(+1,+1, 1);
      glVertex3f(-1,+1, 1);
   }
   glEnd();

   //  Back
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0,-1);
   if(back == 1){
      glTexCoord2f(0.0, 0.0); glVertex3f(+1,-1,-1);
      glTexCoord2f(rep, 0.0); glVertex3f(-1,-1,-1);
      glTexCoord2f(rep, rep); glVertex3f(-1,+1,-1);
      glTexCoord2f(0.0, rep); glVertex3f(+1,+1,-1);
   }

   else{
      glVertex3f(+1,-1,-1);
      glVertex3f(-1,-1,-1);
      glVertex3f(-1,+1,-1);
      glVertex3f(+1,+1,-1);
   }
   glEnd();

   //  Right
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture);
   glBegin(GL_QUADS);
   glNormal3f(+1, 0, 0);

   if(right == 1){
      glTexCoord2f(0.0, 0.0); glVertex3f(+1,-1,+1);
      glTexCoord2f(rep, 0.0); glVertex3f(+1,-1,-1);
      glTexCoord2f(rep, rep); glVertex3f(+1,+1,-1);
      glTexCoord2f(0.0, rep); glVertex3f(+1,+1,+1);
   }
   else{
      glVertex3f(+1,-1,+1);
      glVertex3f(+1,-1,-1);
      glVertex3f(+1,+1,-1);
      glVertex3f(+1,+1,+1);
   }
   glEnd();

   //  Left
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture);
   glBegin(GL_QUADS);
   glNormal3f(-1, 0, 0);

   if(left == 1){
      glTexCoord2f(0.0, 0.0); glVertex3f(-1,-1,-1);
      glTexCoord2f(rep, 0.0); glVertex3f(-1,-1,+1);
      glTexCoord2f(rep, rep); glVertex3f(-1,+1,+1);
      glTexCoord2f(0.0, rep); glVertex3f(-1,+1,-1);
   }
   else{
      glVertex3f(-1,-1,-1);
      glVertex3f(-1,-1,+1);
      glVertex3f(-1,+1,+1);
      glVertex3f(-1,+1,-1);
   }
   glEnd();

   //  Top
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture);
   glBegin(GL_QUADS);
   glNormal3f( 0,+1, 0);

   if(top == 1){
   glTexCoord2f(0.0, 0.0); glVertex3f(-1,+1,+1);
   glTexCoord2f(rep, 0.0); glVertex3f(+1,+1,+1);
   glTexCoord2f(rep, rep); glVertex3f(+1,+1,-1);
   glTexCoord2f(0.0, rep); glVertex3f(-1,+1,-1);
   }

   else{
      glVertex3f(-1,+1,+1);
      glVertex3f(+1,+1,+1);
      glVertex3f(+1,+1,-1);
      glVertex3f(-1,+1,-1);
   }
   glEnd();

   //  Bottom
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture);
   glBegin(GL_QUADS);
   glNormal3f( 0,-1, 0);

   if(bottom == 1){
      glTexCoord2f(0.0, 0.0); glVertex3f(-1,-1,-1);
      glTexCoord2f(rep, 0.0); glVertex3f(+1,-1,-1);
      glTexCoord2f(rep, rep); glVertex3f(+1,-1,+1);
      glTexCoord2f(0.0, rep); glVertex3f(-1,-1,+1);
   }

   else{
      glVertex3f(-1,-1,-1);
      glVertex3f(+1,-1,-1);
      glVertex3f(+1,-1,+1);
      glVertex3f(-1,-1,+1);
   }
   glEnd();

   //  Undo transformations and textures
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

void draw_cylinder(float radius,float height,
                   float R, float G,float B, unsigned int texture)
{
    float x              = 0.0;
    float y              = 0.0;
    float angle          = 0.0;
    float angle_stepsize = 0.1;

    //  Enable textures
    //  Select texture if textures are on
    if (ntex<0)
       glDisable(GL_TEXTURE_2D);
    else
    {
       glEnable(GL_TEXTURE_2D);
    }

    /** Draw the tube */
    glColor3ub(R-40,G-40,B-40);

    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,t_mode?GL_REPLACE:GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture);
    if (ntex) glBindTexture(GL_TEXTURE_2D,texture);
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;

    while( angle < 2*PI ) {
       x = radius * cos(angle);
       y = radius * sin(angle);
       const float tc = ( angle / (float)( 2 * PI ) );
       glTexCoord2f(tc, 1.0); glVertex3f(x, y , height);
       glTexCoord2f(tc, 0.0); glVertex3f(x, y , 0.0);
       angle = angle + angle_stepsize;
    }
    glTexCoord2f(0.0, 1.0); 
    glVertex3f(radius, 0.0, height);
    glTexCoord2f(0.0, 0.0); 
    glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on top of cylinder */
    glColor3ub(R,G,B);
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5,0.5); glVertex3f(0,0,height);
    for (int k=0;k<=360;k+=10)
    {
       glTexCoord2f(rep/2*Cos(k)+0.5,rep/2*Sin(k)+0.5);
       glVertex3f(Cos(k),Sin(k), height);
    }
    glDisable(GL_TEXTURE_2D);
    glEnd();

}

void draw_cone(double height, double radius, double r, double g, double b, unsigned int texture)
{
   int k = 0;
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0}; 
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission); 

    //sides
    //  Enable textures
    //  Select texture if textures are on
    if (ntex<0)
       glDisable(GL_TEXTURE_2D);
    else
    {
       glEnable(GL_TEXTURE_2D);
    }

    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,t_mode?GL_REPLACE:GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture);
    if (ntex) glBindTexture(GL_TEXTURE_2D,texture);

    glColor3f(r,g,b);
    glBegin(GL_TRIANGLE_FAN);

    glTexCoord2f(0.5, 0.5); glVertex3f(0,0,height);
    for (k=0;k<=360;k+=5){  

      glNormal3f(Cos(k),Sin(k), 0);   
      glTexCoord2f(rep/2*Cos(k)+0.5,rep/2*Sin(k)+0.5);
      glVertex2f(Cos(k),Sin(k));
    }
    glDisable(GL_TEXTURE_2D);
    glEnd();
}
