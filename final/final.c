/*
 *  Final Project - Vijoy Sunil Kumar
 *
 *  Full Scene Rendering 
 *
 *  Key bindings:
 *  0          Reset view angle
 *  1	       Render roof
 *  m          Toggle orthogonal/perspective/first person
 *  x          Toggle axes
 *  arrows     Change view angle (in ortho/perspective)
 *  PgDn/PgUp  Zoom in and out (in ortho/perspective)
 *  a,s,w,d    Move in first person (forward/backward/left/right)
 *  j,k,i,l    Turn in first person (left/down/up/right)
 *  .          Go to main door
 *  ESC        Exit
 *  ?          Toggle help menu

 * Texture control
 *-----------------
 * &	       Toggle texture
 *
 * Lighting control
 * ----------------
 * *	       Toggle light
 * y/Y	       Toggle light movement
 * <,>	       left/right light movement
 * [,]	       up/down light movement
 * t/T	       tune ambient level
 * f,F	       tune diffuse level
 * g,G	       tune specular level
 * h,H	       tune emission level
 * r,R	       tune shininess level
 */
#include "CSCIx229.h"

int axes=0;       //  Display axes
int help_on = 0;  //  Toggle help menu
int mode=0;       //  Projection mode
int th=200;       //  Azimuth of view angle
int ph=30;        //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
double asp=1;     //  Aspect ratio
double dim=12.5;  //  Size of world

int move=1;       //  Move light
int light=1;      //  Lighting

// Light values
int side      =   0;  //  Two sided mode
int one       =   1;  // Unit value
int distance  =   4;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =  60;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;  // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   4;  // Elevation of light

// Texture
unsigned int texture[28];  //  Texture names
int ntex=0;    		//  Texture
double rep=1;  		//  Repetition
int t_mode = 0;		// texture mode - replace/modulate

int roof_on = 0;

double room_w = 8.0;
double room_h = 6.0;
double door_w = 1.6;
double door_h = 3.5;

double pillar1_w = 1.0;
double pillar2_w = 0.250;

double ground_w = 16.0;
double ground_h = 9.0;

char* mode_desc[] = {"Orthogonal", "Perspective", "First person"};

//angle of rotation
//initial view
float xpos = 0, ypos = 3, zpos = -10, xrot = 0, yrot = 180;
float xrot_d, yrot_d;

//Collision avoidance
float dist = 2;
const float fp_radius = 1;
float prev_xpos, prev_ypos, prev_zpos;
char event;
char no_fwd = 0, no_back = 0, no_left = 0, no_right = 0;
int state = 3;

void find_state(void)
{
   // inner room
   if (xpos <= 3 && xpos >= -3)
   {
      // can enter state0 only from state 3
      if ((zpos >= -5) && (state == 3) && (xpos >= -0.9 && xpos <= 0.9))
          state = 0;

      // can enter state3 from inner room
      else if ((zpos <= -7) && (zpos >= -10) && (xpos >= -0.9 && xpos <= 0.9))
          state = 3;
   }

   // can enter state1 only from state 3
   else if ((xpos >= 3) && (state == 3) && (zpos <= -7.2 && zpos >= -8.2))
      state = 1;

   // enter state3 from state1
   else if ((xpos < 3) && (state == 1) && (zpos <= -7.2 && zpos >= -8.2))
      state = 3;

   // can enter state2 only from state 3		
   else if ((xpos <= -3) && (state == 3) && (zpos <= -7.2 && zpos >= -8.2))
      state = 2;

   // enter state3 from state2
   else if ((xpos > -3) && (state == 2) && (zpos <= -7.2 && zpos >= -8.2))
      state = 3;
}

void collision (void)
{  
   // inner room
   if (state == 0)
   {
      if (xpos > 3 || xpos < -3)
         dist = 0;
      else if ((zpos < -5) && (xpos <= -0.9 || xpos >= 0.9))
         dist = 0;

      else if (ypos < 1 || ypos >= 3.5) // floor, roof
         dist = 0;

      else if (zpos > 4) // back wall
         dist = 0;

      else
      {
         dist = 2;
         prev_xpos = xpos;
         prev_ypos = ypos;
         prev_zpos = zpos;
      }
   }

   // outside corridor
   if (state == 3)
   {
      if (xpos > 3 || xpos < -3)
           dist = 0;

      else if ((zpos > -7) && (xpos <= -0.9 || xpos >= 0.9))
           dist = 0;
      

      else if (ypos < 1) // floor
         dist = 0;
      else
      {
         dist = 2;
         prev_xpos = xpos;
         prev_ypos = ypos;
         prev_zpos = zpos;
      }

   }

   // left room
   if (state == 1)
   {
      if ((xpos < 5) && (zpos >= -7.2 || zpos <= -8.2)) 
         dist = 0;

      else if (ypos < 1) // floor
         dist = 0;

      else if (zpos > 4) // back wall
         dist = 0;

      else if (zpos < -8.2)  // front wall
         dist = 0;   

      else if (xpos > 7)  // side wall
	  dist = 0;     

      else
      {
         dist = 2;
         prev_xpos = xpos;
         prev_ypos = ypos;
         prev_zpos = zpos;
      }

   }

   // right room
   if (state == 2)
   { 
      if ((xpos > -5)  && (zpos >= -7.2 || zpos <= -8.2))
          dist = 0;

      else if (ypos < 1) // floor
         dist = 0;

      else if (zpos > 4) // back wall
         dist = 0;

      else if (zpos < -8.2)  // front wall
         dist = 0;   

      else if (xpos < -7) // side wall
         dist = 0;

      else
      {
         dist = 2;
         prev_xpos = xpos;
         prev_ypos = ypos;
         prev_zpos = zpos;
      }
   }

   if(dist == 0)
   {
      if (event == 'w' || event == 'W')
         no_fwd = 1;
      else if (event == 'a' || event == 'A')
         no_left = 1;
      else if (event == 's' || event == 'S')
         no_back = 1;
      else if (event == 'd' || event == 'D')
         no_right = 1;
   }
   else
   {
      no_fwd = 0;
      no_back = 0;
      no_right = 0;
      no_left = 0;
   }
}


/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius (r)
 */

void ball(double x,double y,double z,double r)
{
   int th,ph;
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glDisable(GL_TEXTURE_2D);
   glColor3f(1,1,1);
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   for (ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=2*inc)
      {
         Vertex(th,ph,1);
         Vertex(th,ph+inc,1);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   // Collision avoidance 
   collision(); 

   double table_top_thickness = 0.05, table_l = 3.0;
   double floors_r = 0.60, floors_g = 0.60, floors_b = 0.60;
   const double len=10.0;  //  Length of axes
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
       roof_on = 1;
       glRotatef(xrot,1.0,0.0,0.0);  //rotate our camera on the x-axis (left and right)
       glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)

       printf("x %f, y %f, z%f\n", xpos, ypos, zpos);
       // collision avoidance
       if(dist > fp_radius){
          glTranslated(-xpos,-ypos,-zpos); //translate the screen to the position of our camera
          printf("no collision\n");
       }
       else
       {
          glTranslated(-prev_xpos,-prev_ypos,-prev_zpos); 
          printf("collision\n"); 
       }     
   }

   //  Select texture if textures are on
   if (ntex<0)
      glDisable(GL_TEXTURE_2D);
   else
   {
      glEnable(GL_TEXTURE_2D);
      glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , t_mode?GL_REPLACE:GL_MODULATE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   }

   //  Flat or smooth shading
   glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

   //  Light switch
   if (light)
   {
        //  Translate intensity to color vectors
        float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
        float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
        float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
        //  Light position
        float Position[]  = {distance*Cos(zh),ylight,distance*Sin(zh),1.0};
        //  Draw light position as ball (still no lighting here)
        glColor3f(1,1,1);
        ball(Position[0],Position[1],Position[2] , 0.1);
        //  OpenGL should normalize normal vectors
        glEnable(GL_NORMALIZE);
        //  Enable lighting
        glEnable(GL_LIGHTING);
        //  Location of viewer for specular calculations
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
        //  Two sided mode
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,side);
        //  glColor sets ambient and diffuse color materials
        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
        //  Enable light 0
        glEnable(GL_LIGHT0);
        //  Set ambient, diffuse, specular components and position of light 0
        glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
        glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
        glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
        glLightfv(GL_LIGHT0,GL_POSITION,Position);

        
   }
   else
     glDisable(GL_LIGHTING);

  
   if(roof_on == 1)
   {
	glColor3f(floors_r,floors_g,floors_b);
	//  Enable textures
	//  Select texture if textures are on
	if (ntex<0)
	 glDisable(GL_TEXTURE_2D);
	else
	 glEnable(GL_TEXTURE_2D);

	if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0);	glVertex3f(-room_w/2,room_w/2,-room_h);
	glTexCoord2f(rep,0.0);	glVertex3f(room_w/2,room_w/2,-room_h);
	glTexCoord2f(rep,rep);	glVertex3f(room_w/2,room_w/2,room_h);
	glTexCoord2f(0.0,rep);	glVertex3f(-room_w/2,room_w/2,room_h);
	glEnd();
	glDisable(GL_TEXTURE_2D);
   }

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

	glPushMatrix();
	glTranslated((-table_l/2)+0.20, room_w/5 + table_top_thickness/2, 0);
	glScaled(0.20,0.17,0.20);
	render_lamp();
	glPopMatrix(); 

	glPushMatrix();
	glTranslated(4.8, room_w/5 + table_top_thickness/2, 4.5);
	glRotated(75.0,0,1,0);
	glScaled(0.20,0.17,0.20);
	render_lamp();
	glPopMatrix(); 

	glPushMatrix();
	glTranslated(-4.8, room_w/5 + table_top_thickness/2, 2.5); 
	glRotated(120.0,0,1,0);
	glScaled(0.20,0.17,0.20);
	render_lamp();
	glPopMatrix(); 

	glPushMatrix();
	glTranslated(5.0, room_w/5 + table_top_thickness/2, 0.0); 
	glRotated(80.0,0,1,0);
	glScaled(0.8,0.8,0.8);
	render_computer();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-5.0, room_w/5 + table_top_thickness/2, -2.0); 
	glRotated(-90.0,0,1,0);
	glScaled(0.8,0.8,0.8);
	render_computer();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.25, 1.09, 1.15); 
	glRotated(90.0,0,1,0);
	glScaled(0.15,0.15,0.15);
	render_batman();
	glPopMatrix(); 

	glPushMatrix();
	glTranslated(0.25, 1.09, -1.15); 
	glRotated(-90.0,0,1,0);
	glScaled(0.15,0.15,0.15);
	render_joker();
	glPopMatrix(); 
     
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


	render_room();
	render_sign();
	render_clock();
	render_pillars();
	render_windows(); 
	
 
   //  Draw axes - no lighting from here on
   glDisable(GL_LIGHTING);
   //  Switch off textures so it doesn't apply to the rest
   glDisable(GL_TEXTURE_2D);

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
   if(light == 1){
      glWindowPos2i(5,25);
      Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",ambient,diffuse,specular,emission,shiny);
   }
   else{
      glWindowPos2i(5,25);
      Print("Lighting: OFF");
   }

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

     Print("Position=%1.f,%1.f,%1.f, Head angle=%1.f,%1.f, Projection=%s",prev_xpos, prev_ypos, prev_zpos,yrot_d,xrot_d,mode_desc[mode]);
   }

   // Help menu
   if(help_on == 0){
      glWindowPos2i(5,65);
      Print("For help, press [?] state = %d",state);
   }

   //page 1/2 of help
   if(help_on == 1)
   {
      glWindowPos2i(5,65);
      Print("Press [?] for page 2/2");
      glWindowPos2i(5,85);
      Print("[.]	Go to main door"); 
 

      glWindowPos2i(5,105);
      Print("[j,k,i,l]	turn left/down/up/right [in first-person]"); 
      glWindowPos2i(5,125);
      Print("[a,s,w,d]	move forward/backward/left/right [in first-person]"); 

      glWindowPos2i(5,145);
      Print("[PgDn/PgUp]	Zoom in and out [in ortho or perspective]"); 
      glWindowPos2i(5,165);
      Print("[arrows]	Change view angle [in ortho or perspective]"); 
      glWindowPos2i(5,185);
      Print("[m]	orthogonal / perspective / first-person");


      glWindowPos2i(5,205);
      Print("[1]	Render roof");  
      glWindowPos2i(5,225);
      Print("[0]	Reset view angle"); 
      glWindowPos2i(5,245);
      Print("[x]	Toggle axes"); 
      glWindowPos2i(5,265);
      Print("[ESC]	Exit");  
   }
   
   //page 2/2 of help
   if(help_on == 2)
   {
      glWindowPos2i(5,65);
      Print("Press [?] to turn OFF help");
      glWindowPos2i(5,85);
      Print("[y]	Toggle light movement"); 
 

      glWindowPos2i(5,105);
      Print("[<.>]	Move light left/right"); 
      glWindowPos2i(5,125);
      Print("[[,]]	Move light up/down"); 

      glWindowPos2i(5,145);
      Print("[t,T]	Tune ambient level"); 
      glWindowPos2i(5,165);
      Print("[f,F]	Tune diffuse level"); 
      glWindowPos2i(5,185);
      Print("[g,G]	Tune specular level");


      glWindowPos2i(5,205);
      Print("[h,H]	Tune emission level"); 
      glWindowPos2i(5,225);
      Print("[r,R]	Tune shininess level"); 
      glWindowPos2i(5,245);
      Print("[*]	Toggle lights"); 
      glWindowPos2i(5,265);
      Print("[&]	Toggle texture"); 
   }

   //  Render the scene and make it visible
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360.0);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
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
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.1;
   //  Smooth color model
   else if (key == GLUT_KEY_F1)
      smooth = 1-smooth;
   //  Local Viewer
   else if (key == GLUT_KEY_F2)
      local = 1-local;
   else if (key == GLUT_KEY_F3)
      distance = (distance==1) ? 5 : 1;
   //  Toggle ball increment
   else if (key == GLUT_KEY_F8)
      inc = (inc==10)?3:10;
   //  Flip sign
   else if (key == GLUT_KEY_F9)
      one = -one;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(mode,mode?fov:0,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   event = ch;
   //  Exit on ESC
   if (ch == 27)
      exit(0);

   //  Reset all 
   else if (ch == '0'){
      th = 200;
      ph = 30;
      dim = 12.5;

      xrot = 0;
      yrot = 180;
      xpos = 0;
      ypos = 3;
      zpos =-10; 

      state = 3;
      dist = 2;
      prev_xpos = xpos;
      prev_ypos = ypos;
      prev_zpos = zpos;

      emission  =   0;  
      ambient   =  60;  
      diffuse   = 100;  
      specular  =   0;  
      shininess =   0;  
      shiny     =   1;  
      zh        =  90;
      distance  =   4;  
      ylight    =   4;  
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
      zpos =-10; 
   
      dist = 2;
      prev_xpos = xpos;
      prev_ypos = ypos;
      prev_zpos = zpos;
      state = 3; 
   }
   else if (ch == '?')
      help_on = (help_on + 1)%3;

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
      roof_on = !roof_on;
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

      if(no_fwd == 0){
         xpos += (sin(yrotrad)) ;
         zpos -= (cos(yrotrad)) ;
         ypos -= (sin(xrotrad)) ;
      }
      
      find_state();
   }

   else if (ch =='s' || ch =='S')
   {
      float xrotrad, yrotrad;
      yrotrad = (yrot / 180 * 3.141592654f);
      xrotrad = (xrot / 180 * 3.141592654f);

      if(no_back == 0){
         xpos -= (sin(yrotrad));
         zpos += (cos(yrotrad)) ;
         ypos += (sin(xrotrad));
      }

      find_state();
    }

   else if (ch =='d' || ch =='D')
   {
      float yrotrad;
      yrotrad = (yrot / 180 * 3.141592654f);

      if(no_right == 0){
         xpos += (cos(yrotrad)) * 0.2;
         zpos += (sin(yrotrad)) * 0.2;
      }
      find_state();
   }

   else if (ch=='a' || ch =='A')
   {
      float yrotrad;
      yrotrad = (yrot / 180 * 3.141592654f);

      if(no_left == 0){
         xpos -= (cos(yrotrad)) * 0.2;
         zpos -= (sin(yrotrad)) * 0.2;
      }
      find_state();
   }

   else if (ch == '*')
      light = 1-light;
   //  Toggle light movement
   else if (ch == 'y' || ch == 'Y')
      move = 1-move;
   //  Move light
   else if (ch == '<')
      zh += 1;
   else if (ch == '>')
      zh -= 1;
   //  Light elevation
   else if (ch=='[')
      ylight -= 0.1;
   else if (ch==']')
      ylight += 0.1;

   //  Ambient level
   else if (ch=='t' && ambient>0)
      ambient -= 5;
   else if (ch=='T' && ambient<100)
      ambient += 5;
   //  Diffuse level
   else if (ch=='f' && diffuse>0)
      diffuse -= 5;
   else if (ch=='F' && diffuse<100)
      diffuse += 5;
   //  Specular level
   else if (ch=='g' && specular>0)
      specular -= 5;
   else if (ch=='G' && specular<100)
      specular += 5;
   //  Emission level
   else if (ch=='h' && emission>0)
      emission -= 5;
   else if (ch=='H' && emission<100)
      emission += 5;
   //  Shininess level
   else if (ch=='r' && shininess>-1)
      shininess -= 1;
   else if (ch=='R' && shininess<7)
      shininess += 1;
   //  Translate shininess power to value (-1 => 0)
   shiny = shininess<0 ? 0 : pow(2.0,shininess);

   // Toggle texture
   if (ch == '&'){
      if(ntex == 0)
         ntex = -1;
      else
         ntex = 0;
   }
   //  Reproject
   Project(mode,mode?fov:0,asp,dim);
   //  Animate if requested
   glutIdleFunc(move?idle:NULL);
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
   glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_ALPHA);

   glutInitWindowSize(600,600);
   glutCreateWindow("Final - Vijoy Sunil Kumar");
   //  Set callbacks
   glutDisplayFunc(display);
   glutIdleFunc(idle);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   //  Load textures
   texture[0] = LoadTexBMP("./textures/floor.bmp");
   texture[1] = LoadTexBMP("./textures/pillar.bmp");
   texture[2] = LoadTexBMP("./textures/wall.bmp");
   texture[3] = LoadTexBMP("./textures/table.bmp");
   texture[4] = LoadTexBMP("./textures/chair.bmp");
   texture[5] = LoadTexBMP("./textures/chair_top.bmp");

   texture[6] = LoadTexBMP("./textures/lamp.bmp");
   texture[7] = LoadTexBMP("./textures/lamp_top.bmp");
   texture[8] = LoadTexBMP("./textures/lamp_base2.bmp");
   texture[9] = LoadTexBMP("./textures/lamp_sphere.bmp");

   texture[10] = LoadTexBMP("./textures/laptop_base.bmp");
   texture[11] = LoadTexBMP("./textures/laptop_top.bmp");

   texture[12] = LoadTexBMP("./textures/warning.bmp");
   texture[13] = LoadTexBMP("./textures/clock.bmp");
   texture[14] = LoadTexBMP("./textures/exit.bmp");

   texture[15] = LoadTexBMP("./textures/batface.bmp");
   texture[16] = LoadTexBMP("./textures/jokerface.bmp");
   texture[17] = LoadTexBMP("./textures/batbody.bmp");
   texture[18] = LoadTexBMP("./textures/jokerbody.bmp");

   texture[19] = LoadTexBMP("./textures/batshoulder.bmp");
   texture[20] = LoadTexBMP("./textures/jokerhand.bmp");

   texture[21] = LoadTexBMP("./textures/batneck.bmp");
   texture[22] = LoadTexBMP("./textures/jokerneck.bmp");

   texture[23] = LoadTexBMP("./textures/jokerbottom.bmp");
   texture[24] = LoadTexBMP("./textures/batbottom1.bmp");
   texture[25] = LoadTexBMP("./textures/batbottom2.bmp");
   texture[26] = LoadTexBMP("./textures/jokergloves.bmp");
   texture[27] = LoadTexBMP("./textures/jokershoes.bmp");

   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
