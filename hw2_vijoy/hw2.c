/*
 *  Polygon Offset
 *
 *  Demonstrates the use of polygon offset to overdraw lines and polygons.
 *
 *  Key bindings:
 *  m          Toggle orthogonal/perspective/first person
 *  a          Toggle axes
 *  arrows     Change view angle
 *  PgDn/PgUp  Zoom in and out
 *  0          Reset view angle
 *  ESC        Exit
 */
#include "CSCIx229.h"

int axes=0;       //  Display axes
int mode=0;       //  Projection mode
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
double asp=1;     //  Aspect ratio
double dim=10.0;   //  Size of world

double room_w = 8.0;
double room_h = 6.0;
double door_w = 1.6;
double door_h = 2.5;

double pillar1_w = 1.0;
double pillar2_w = 0.250;

double ground_w = 16.0;
double ground_h = 9.0;

static void render_room(void)
{

   //--------------------------------------------------------------
   // Draw floor
   glColor3f(1,1,0);					//set color
   glBegin(GL_QUADS);
   glVertex3f(-ground_w/2,0.0,room_h);
   glVertex3f(-ground_w/2,0.0,-ground_h);
   glVertex3f(ground_w/2,0.0,-ground_h);
   glVertex3f(ground_w/2,0.0,room_h);
   glEnd();

   //--------------------------------------------------------------
   // Draw side walls (LEFT)
   glColor3f(1,0,0);					//set color
   glBegin(GL_QUADS);
   glVertex3f(-room_w/2,0.0,room_h);
   glVertex3f(-room_w/2,room_w/3.9,room_h);
   glVertex3f(-room_w/2,room_w/3.9,-room_h);
   glVertex3f(-room_w/2,0.0,-room_h);
   glEnd();   

   // Upper strip
   glColor3f(1,0,0);					//set color
   glBegin(GL_QUADS);
   glVertex3f(-room_w/2,room_w/2,room_h);
   glVertex3f(-room_w/2,room_w/2,-room_h);
   glVertex3f(-room_w/2,(room_w/2)-0.3,-room_h);
   glVertex3f(-room_w/2,(room_w/2)-0.3,room_h);
   glEnd(); 

   // Draw side walls (LEFT OUTER)
   glColor3f(1,0,0);					//set color
   glBegin(GL_QUADS);
   glVertex3f(-ground_w/2,0.0,room_h);
   glVertex3f(-ground_w/2,room_w/2,room_h);
   glVertex3f(-ground_w/2,room_w/2,-ground_h);
   glVertex3f(-ground_w/2,0.0,-ground_h);
   glEnd(); 
 
   // Draw side walls (RIGHT)
   glColor3f(1,0,0);					//set color
   glBegin(GL_QUADS);
   glVertex3f(room_w/2,0.0,room_h);
   glVertex3f(room_w/2,room_w/3.9,room_h);
   glVertex3f(room_w/2,room_w/3.9,-room_h);
   glVertex3f(room_w/2,0.0,-room_h);
   glEnd(); 

   // Upper strip
   glColor3f(1,0,0);					//set color
   glBegin(GL_QUADS);
   glVertex3f(room_w/2,room_w/2,room_h);
   glVertex3f(room_w/2,room_w/2,-room_h);
   glVertex3f(room_w/2,(room_w/2)-0.3,-room_h);
   glVertex3f(room_w/2,(room_w/2)-0.3,room_h);
   glEnd(); 

   // Draw side walls (RIGHT OUTER)
   glColor3f(1,0,0);					//set color
   glBegin(GL_QUADS);
   glVertex3f(ground_w/2,0.0,room_h);
   glVertex3f(ground_w/2,room_w/2,room_h);
   glVertex3f(ground_w/2,room_w/2,-ground_h);
   glVertex3f(ground_w/2,0.0,-ground_h);
   glEnd();  

   //--------------------------------------------------------------
   // Draw back wall  
   glColor3f(1,1,1);					//set color
   glBegin(GL_QUADS);
   glVertex3f(-ground_w/2,0.0,room_h);
   glVertex3f(-ground_w/2,room_w/2,room_h);
   glVertex3f(ground_w/2,room_w/2,room_h);
   glVertex3f(ground_w/2,0.0,room_h);
   glEnd();  

   //--------------------------------------------------------------
   // Draw front wall (DOOR)  
   glColor3f(1,1,1);					//set color
   glBegin(GL_QUADS);
   glVertex3f(-room_w/2,0.0,-room_h);
   glVertex3f(-room_w/2,room_w/2,-room_h);
   glVertex3f(-door_w/2,room_w/2,-room_h);
   glVertex3f(-door_w/2,0.0,-room_h);
   glEnd();

   glColor3f(1,1,1);					//set color
   glBegin(GL_QUADS);
   glVertex3f(room_w/2,0.0,-room_h);
   glVertex3f(room_w/2,room_w/2,-room_h);
   glVertex3f(door_w/2,room_w/2,-room_h);
   glVertex3f(door_w/2,0.0,-room_h);
   glEnd();

   glColor3f(1,1,1);					//set color
   glBegin(GL_QUADS);
   glVertex3f(-door_w/2,room_w/2,-room_h);
   glVertex3f(door_w/2,room_w/2,-room_h);
   glVertex3f(door_w/2,door_h,-room_h);
   glVertex3f(-door_w/2,door_h,-room_h);
   glEnd();

   //--------------------------------------------------------------
   // Draw ceiling

   /*
   glColor3f(1,1,1);					//set color
   glBegin(GL_QUADS);
   glVertex3f(-room_w/2,room_w/2,-room_h);
   glVertex3f(room_w/2,room_w/2,-room_h);
   glVertex3f(room_w/2,room_w/2,room_h);
   glVertex3f(-room_w/2,room_w/2,room_h);
   glEnd();
   */

}


/*
 *  Draw a cube
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th, int r, int g, int b)
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

static void render_pillars(void)
{
   double pillar_thickness = 0.4;

   //vertical pillars
   // thick pillars - pillar1
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(-room_w/2+pillar_thickness/2,room_w/4,2.5, -pillar_thickness/2,room_w/4,-pillar1_w/2, 0, 1, 0, 0);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(room_w/2-pillar_thickness/2,room_w/4,2.5, pillar_thickness/2,room_w/4,pillar1_w/2, 0, 1, 0, 0);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(-room_w/2+pillar_thickness/2,room_w/4,-2.5, -pillar_thickness/2,room_w/4,-pillar1_w/2, 0, 1, 0, 0);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(room_w/2-pillar_thickness/2,room_w/4,-2.5, pillar_thickness/2,room_w/4,pillar1_w/2, 0, 1, 0, 0);
   glDisable(GL_POLYGON_OFFSET_FILL);

   //thin pillars - pillar2
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(-room_w/2+pillar_thickness/2,room_w/4,room_h-pillar2_w/2, -pillar_thickness/2,room_w/4,-pillar2_w/2, 0, 1, 0, 0);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(room_w/2-pillar_thickness/2,room_w/4,room_h-pillar2_w/2, -pillar_thickness/2,room_w/4,-pillar2_w/2, 0, 1, 0, 0);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(room_w/2-pillar_thickness/2,room_w/4,-room_h+pillar2_w/2, -pillar_thickness/2,room_w/4,-pillar2_w/2, 0, 1, 0, 0);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(-room_w/2+pillar_thickness/2,room_w/4,-room_h+pillar2_w/2, -pillar_thickness/2,room_w/4,-pillar2_w/2, 0, 1, 0, 0);   
   glDisable(GL_POLYGON_OFFSET_FILL);

   //horizontal pillars
   double pillar_thickness1 = 0.2;

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(-room_w/2+pillar_thickness1/2,room_w/10,0.0, pillar_thickness1/2,room_w/10,room_h, 0, 1, 1, 1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(room_w/2-pillar_thickness1/2,room_w/10,0.0, pillar_thickness1/2,room_w/10,room_h, 0, 1, 1, 1);  
   glDisable(GL_POLYGON_OFFSET_FILL); 
}

static render_table(void)
{
   double table_l = 3.0;
   double table_w = 1.5;
   double table_top_thickness = 0.05;

   //table top
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(0,room_w/6,0, table_l/2,table_top_thickness/2, table_w/2, 0, 0, 1, 0);
   glDisable(GL_POLYGON_OFFSET_FILL);

   //table top2
   double table_top_thickness1 = 0.15;
   double table_l1 = table_l - 0.3;
   double table_w1 = table_w - 0.3;

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(0,(room_w/6)-(table_top_thickness/2)-(table_top_thickness1/2),0, table_l1/2, table_top_thickness1/2,table_w1/2, 0, 0, 0, 1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   //table legs
   double legs_l = room_w/6 - (table_top_thickness/2); 
   double legs_w = 0.15;
   double legs_thickness = legs_w;

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(((table_l1/2) + (table_l/2))/2, legs_l/2, ((table_w1/2) + (table_w)/2)/2, legs_thickness/2, legs_l/2, legs_thickness/2, 0, 1, 0, 0); 
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(((table_l1/2) + (table_l/2))/2, legs_l/2, -((table_w1/2) + (table_w)/2)/2, legs_thickness/2, legs_l/2, legs_thickness/2, 0, 1, 0, 0);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1); 
   cube(-((table_l1/2) + (table_l/2))/2, legs_l/2, -((table_w1/2) + (table_w)/2)/2, legs_thickness/2, legs_l/2, legs_thickness/2, 0, 1, 0, 0);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1); 
   cube(-((table_l1/2) + (table_l/2))/2, legs_l/2, ((table_w1/2) + (table_w)/2)/2, legs_thickness/2, legs_l/2, legs_thickness/2, 0, 1, 0, 0);   
   glDisable(GL_POLYGON_OFFSET_FILL);
}

static render_chair(void)
{
   double legs_thickness = 0.075;
   double legs_width = legs_thickness;
   double legs_height = room_w/9;

   double base_length = 1.0;

   //legs
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(base_length/2,legs_height,-base_length/2, legs_thickness/2, legs_height, legs_thickness/2, 0, 1, 0, 0);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(-base_length/2,legs_height,-base_length/2, legs_thickness/2, legs_height, legs_thickness/2, 0, 1, 0, 0);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(-base_length/2+(legs_thickness/1.9),legs_height/2,base_length/2-(legs_thickness/1.9), legs_thickness/2, legs_height/2, legs_thickness/2, 0, 1, 0, 0);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(base_length/2-(legs_thickness/1.9),legs_height/2,base_length/2-(legs_thickness/1.9), legs_thickness/2, legs_height/2, legs_thickness/2, 0, 1, 0, 0);
   glDisable(GL_POLYGON_OFFSET_FILL);

   //base
   double base_thickness = 1.5*legs_thickness;
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(0,legs_height,0,  base_length/2,base_thickness/2 , base_length/2, 0, 0, 1, 0);
   glDisable(GL_POLYGON_OFFSET_FILL);

   //back support - horizontal
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(0,(2*legs_height)-(legs_width/2),-base_length/2, base_length/2, legs_thickness/2, legs_thickness/2, 0, 1, 0, 0);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(0,(1.85*legs_height)-(legs_width/2),-base_length/2, base_length/2, legs_thickness/2, legs_thickness/2, 0, 1, 0, 0);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(0,(1.2*legs_height)-(legs_width/2),-base_length/2, base_length/2, legs_thickness/2, legs_thickness/2, 0, 1, 0, 0);
   glDisable(GL_POLYGON_OFFSET_FILL);

   //back support - vertical
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(0,(1.525*legs_height)-(legs_width/2),-base_length/2, legs_thickness/2, 0.65*legs_height/2, legs_thickness/2, 0, 1, 0, 0);
   glDisable(GL_POLYGON_OFFSET_FILL);
}

static render_lamp(void)
{

}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   int i,j,k;
   const double len=1.5;  //  Length of axes
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective - set eye position
   if (mode)
   {
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   //  Orthogonal - set world orientation
   else
   {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   }

   //Joker chair
   render_chair();
   glTranslated(0.0, 0.0, 2.0);
   glRotated(-180.0,0,1,0);
   
   // Batman chair
   render_chair();
   glTranslated(0.0, 0.0, 1.0);
   render_table();

   render_room();  
   render_pillars();  


   //  Draw axes
   glColor3f(1,1,1);
   if (axes)
   {
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }
   //  Display parameters
   glWindowPos2i(5,5);
   Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s",th,ph,dim,fov,mode?"Perpective":"Orthogonal:First Person");
   //  Render the scene and make it visible
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_UP)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_DOWN && dim>1)
      dim -= 0.1;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(mode,fov,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
   //  Toggle axes
   else if (ch == 'a' || ch == 'A')
      axes = 1-axes;
   //  Switch display mode
   else if (ch == 'm' || ch == 'M')
      mode = 1-mode;
   //  Change field of view angle
   else if (ch == '-' && ch>1)
      fov--;
   else if (ch == '+' && ch<179)
      fov++;
   //  Reproject
   Project(mode,fov,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Project(mode,fov,asp,dim);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(600,600);
   glutCreateWindow("HW2 - Vijoy Sunil Kumar");
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
