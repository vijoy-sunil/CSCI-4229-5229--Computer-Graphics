/*
 *  Homework #2 - Vijoy Sunil Kumar
 *
 *  3-D Scene Rendering
 *
 *  Key bindings:
 *  0          Reset 
 *  1	       Render room
 *  2          Render tables
 *  3          Render lamps, computers
 *  4          Render chairs
 *  5          Render ALL (default on start up)
 *  6          Render OFF
 *  m          Toggle orthogonal/perspective/first person
 *  a          Toggle axes
 *  arrows     Change view angle (in ortho/perspective)
 *  PgDn/PgUp  Zoom in and out (in ortho/perspective)
 *  a,s,w,d    Move in first person (forward/backward/left/right)
 *  j,k,i,l    Viwe angle in first person (left/down/up/right)
 *  .          View center of scene
 *  ESC        Exit
 *  h,H        Toggle help menu
 */
#include "CSCIx229.h"

int axes=0;       //  Display axes
int help_on = 0;  //  Toggle help menu
int mode=0;       //  Projection mode
int th=180;       //  Azimuth of view angle
int ph=90;        //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
double asp=1;     //  Aspect ratio
double dim=12.5;  //  Size of world

int room_on = 0, table_on = 0, table_objs_on = 0, chair_on = 0, render_all = 1;
int recent_press = 0;

double room_w = 8.0;
double room_h = 6.0;
double door_w = 1.6;
double door_h = 3.5;

double pillar1_w = 1.0;
double pillar2_w = 0.250;

double ground_w = 16.0;
double ground_h = 9.0;

char* mode_desc[] = {"Orthogonal", "Perspective", "First person"};
char* rendered_objs[] = {"all", "room", "tables", "lamps,computers", "chairs", "all ", " "};

//angle of rotation
float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, angle=0.0;
float xrot_d, yrot_d;

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   double table_top_thickness = 0.05, table_l = 3.0;
   const double len=1.5;  //  Length of axes
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective - set eye position
   if (mode == 1)
   {
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   //  Orthogonal - set world orientation
   else if (mode == 0)
   {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   }
   // First person point of view
   // Reference: http://www.swiftless.com/tutorials/opengl/camera.html
   else if (mode == 2)
   {
    glRotatef(xrot,1.0,0.0,0.0);  //rotate our camera on the x-axis (left and right)
    glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
    glTranslated(-xpos,-ypos,-zpos); //translate the screen to the position of our camera
   }
  
   // Render objects
   if(render_all == 1)
   {
      room_on = 1;
      table_on = 1;
      table_objs_on = 1;
      chair_on = 1;
   }
   if(render_all == 0)
   {
      room_on = 0;
      table_on = 0;
      table_objs_on = 0;
      chair_on = 0;
      render_all = 2;
   }

   if(room_on == 1){
      render_room();
      render_pillars();
   }

   if(table_on == 1)
   {
      //Outside tables
      glPushMatrix();
      glTranslated(5.0, 0.0, 2.0);
      glRotated(-90.0,0,1,0);
      glScaled(2.0,1.0,1.0);
      render_table();
      glPopMatrix();  

      glPushMatrix();
      glTranslated(-5.0, 0.0, 2.0);
      glRotated(-90.0,0,1,0);
      glScaled(1.5,1.0,1.0);
      render_table();
      glPopMatrix(); 

      glPushMatrix();
      glTranslated(-5.0, 0.0, -2.5);
      glRotated(-90.0,0,1,0);
      render_table();
      glPopMatrix(); 

      // Inner table at (0,0,0)
      render_table();
   }  

   if(table_objs_on == 1)
   {
       glPushMatrix();
       glTranslated((-table_l/2)+0.20, room_w/6 + table_top_thickness/2, 0);
       glScaled(0.20,0.17,0.20);
       render_lamp();
       glPopMatrix(); 

       glPushMatrix();
       glTranslated(4.8, room_w/6 + table_top_thickness/2, 4.5);
       glRotated(75.0,0,1,0);
       glScaled(0.20,0.17,0.20);
       render_lamp();
       glPopMatrix(); 

       glPushMatrix();
       glTranslated(-4.8, room_w/6 + table_top_thickness/2, 2.5); 
       glRotated(120.0,0,1,0);
       glScaled(0.20,0.17,0.20);
       render_lamp();
       glPopMatrix(); 

       glPushMatrix();
       glTranslated(5.0, room_w/6 + table_top_thickness/2, 0.0); 
       glRotated(80.0,0,1,0);
       glScaled(0.8,0.8,0.8);
       render_computer();
       glPopMatrix();

       glPushMatrix();
       glTranslated(-5.0, room_w/6 + table_top_thickness/2, -2.0); 
       glRotated(-90.0,0,1,0);
       glScaled(0.8,0.8,0.8);
       render_computer();
       glPopMatrix();
   }  
   if(chair_on == 1)
   {
       //Outside chairs
       glPushMatrix();
       glTranslated(6.0, 0.0, 4.0);
       glRotated(-110.0,0,1,0);
       render_chair();
       glPopMatrix();

       glPushMatrix();
       glTranslated(6.0, 0.0, 2.0);
       glRotated(-84.0,0,1,0);
       render_chair();
       glPopMatrix();

       glPushMatrix();
       glTranslated(6.0, 0.0, 0.0);
       glRotated(-65.0,0,1,0);
       render_chair();
       glPopMatrix();

       glPushMatrix();
       glTranslated(-6.0, 0.0, 3.0);
       glRotated(110.0,0,1,0);
       render_chair();
       glPopMatrix();

       glPushMatrix();
       glTranslated(-6.0, 0.0, 1.0);
       glRotated(90.0,0,1,0);
       render_chair();
       glPopMatrix();

       glPushMatrix();
       glTranslated(-6.0, 0.0, -2.0);
       glRotated(100.0,0,1,0);
       render_chair();
       glPopMatrix();

       //Joker chair
       glPushMatrix();
       glTranslated(0.0, 0.0, -1.0);
       render_chair();
       glPopMatrix();
   
       // Batman chair
       glPushMatrix();
       glTranslated(0.0, 0.0, 1.0);
       glRotated(-180.0,0,1,0);
       render_chair();
       glPopMatrix();
   } 

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
   glWindowPos2i(5,25);
   Print("Recently Rendered: %s",rendered_objs[recent_press]);
   if(mode <= 1){
     glWindowPos2i(5,5);
     Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s",th,ph,dim,fov,mode_desc[mode]);
   }
   else{
     glWindowPos2i(5,5);
     if(yrot == 0) yrot_d = 0;
     else yrot_d = yrot;

     if(xrot == 0) xrot_d = 0;
     else xrot_d = -xrot;

     Print("Position=%1.f,%1.f,%1.f, Head angle=%1.f,%1.f, Projection=%s",xpos,ypos,zpos,yrot_d,xrot_d,mode_desc[mode]);
   }

   // Help menu
   if(help_on == 0){
      glWindowPos2i(5,45);
      Print("For help, press [H] or [h]");
   }
   if(help_on == 1)
   {
      glWindowPos2i(5,45);
      Print("Press [H] or [h] to turn OFF help");

      glWindowPos2i(5,65);
      Print("[a]	Toggle axes");  

      glWindowPos2i(5,85);
      Print("[j,k,i,l]	turn left/down/up/right [in first-person]"); 
      glWindowPos2i(5,105);
      Print("[a,s,w,d]	move forward/backward/left/right [in first-person]"); 

      glWindowPos2i(5,125);
      Print("[PgDn/PgUp]	Zoom in and out [in ortho or perspective]"); 
      glWindowPos2i(5,145);
      Print("[arrows]	Change view angle [in ortho or perspective]"); 
      glWindowPos2i(5,165);
      Print("[m]	orthogonal / perspective / first-person");

      glWindowPos2i(5,185);
      Print("[6]	Render NONE"); 
      glWindowPos2i(5,205);
      Print("[5]	Render ALL"); 
      glWindowPos2i(5,225);
      Print("[4]	Render chairs"); 
      glWindowPos2i(5,245);
      Print("[3]	Render lamps,computers"); 
      glWindowPos2i(5,265);
      Print("[2]	Render tables"); 
      glWindowPos2i(5,285);
      Print("[1]	Render room");  
      glWindowPos2i(5,305);
      Print("[0]	Reset all"); 
      glWindowPos2i(5,325);
      Print("[.]	Default view"); 
      glWindowPos2i(5,345);
      Print("[ESC]	Exit");  
   }

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

   //  Reset all view (on startup)
   else if (ch == '0'){
      th = 180;
      ph = 90;
      dim = 12.5;
   }

   // Main view
   else if (ch == '.'){
      dim = 5.2;
      th = 180;
      ph = 15; 

      xrot = 0;
      yrot = 180;
      xpos = 0;
      ypos = 3;
      zpos =-9;  
   }
   else if (ch == 'h' || ch == 'H')
      help_on = !help_on;

   //  Toggle axes
   else if (ch == 'x' || ch == 'X')
      axes = 1-axes;
   //  Switch display mode
   else if (ch == 'm' || ch == 'M'){
      mode = (mode + 1)%3;
   }
    
   //  Change field of view angle
   else if (ch == '-' && ch>1)
      fov--;
   else if (ch == '+' && ch<179)
      fov++;
   else if (ch == '1'){
      room_on = 1;
      recent_press = 1;
   } 
   else if (ch == '2'){
      table_on = 1;
      recent_press = 2;
   } 
   else if (ch == '3'){
      table_objs_on = 1;
      recent_press = 3;
   } 
   else if (ch == '4'){
      chair_on = 1;
      recent_press = 4;
   } 
   else if (ch == '5'){
      render_all = 1;
      recent_press = 5;
   } 
   else if (ch == '6'){
      render_all = 0;
      recent_press = 6;
   } 

   // FP view
   else if (ch =='k' || ch=='K')
   {
      xrot += 1;
      if (xrot >360) xrot -= 360;
   }
   else if (ch =='i' || ch=='I')
   {
      xrot -= 1;
      if (xrot < -360) xrot += 360;
   }
   if (ch =='l' || ch=='L')
   {
      yrot += 1;
      if (yrot >360) yrot -= 360;
   }
   else if (ch =='j' || ch=='J')
   {
      yrot -= 1;
      if (yrot < -360) yrot += 360;
   }

   // FP movement
   else if (ch =='w' || ch =='W')
   {
      float xrotrad, yrotrad;
      yrotrad = (yrot / 180 * 3.141592654f);
      xrotrad = (xrot / 180 * 3.141592654f);
      xpos += (sin(yrotrad)) ;
      zpos -= (cos(yrotrad)) ;
      ypos -= (sin(xrotrad)) ;
   }

   else if (ch =='s' || ch =='S')
   {
      float xrotrad, yrotrad;
      yrotrad = (yrot / 180 * 3.141592654f);
      xrotrad = (xrot / 180 * 3.141592654f);
      xpos -= (sin(yrotrad));
      zpos += (cos(yrotrad)) ;
      ypos += (sin(xrotrad));
   }

   else if (ch =='d' || ch =='D')
   {
      float yrotrad;
      yrotrad = (yrot / 180 * 3.141592654f);
      xpos += (cos(yrotrad)) * 0.2;
      zpos += (sin(yrotrad)) * 0.2;
   }

   else if (ch=='a' || ch =='A')
   {
      float yrotrad;
      yrotrad = (yrot / 180 * 3.141592654f);
      xpos -= (cos(yrotrad)) * 0.2;
      zpos -= (sin(yrotrad)) * 0.2;
   }
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
   glutIdleFunc (display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
