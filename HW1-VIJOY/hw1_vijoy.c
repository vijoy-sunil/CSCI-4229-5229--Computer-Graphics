/*
 *  Three dimensional OpenGL visualization of the Lorenz Attractor
 *
 *  Key bindings:
 *  s      decrement 's' parameter
 *  S      increment 's' parameter
 *  b      decrement 'b' parameter
 *  B      increment 'b' parameter
 *  r	   decrement 'r' parameter
 *  R      increment 'r' parameter
 *  +	   zoom in
 *  -      zoom out
 *  p/P    reset parameters to default
 *  arrows Change view angle
 *  0      Reset view angle
 *  ESC    Exit
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//  Lorenz Parameters
double s  = 10;
double b  = 2.6666;
double r  = 28;
double dt = 0.001;
double steps = 50000;    // Integrate 50,000 steps (50 time units with dt = 0.001)
double w = 0.03;
//  Globals
int th=0;       // Azimuth of view angle
int ph=0;       // Elevation of view angle
double dim=2;   // Dimension of orthogonal box
int mode = 0;	// Parameter to tune
char* text[] = {"","s-","s+","b-","b+", "r-", "r+", "zoom"};  // mode display text


/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 */
#define LEN 8192  // Maximum length of text string
void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   //  Turn the parameters into a character string
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Display the characters one at a time at the current raster position
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

/*
 *  Display the scene
 */
void display()
{
   //  Clear the image
   glClear(GL_COLOR_BUFFER_BIT);
   //  Reset previous transforms
   glLoadIdentity();
   //  Set view angle
   glRotated(ph,1,0,0);
   glRotated(th,0,1,0);

   //Coordinates  
   double x = 1;
   double y = 1;
   double z = 1;

   double dx, dy, dz;
   glBegin(GL_LINE_STRIP);
   for(int i = 0; i < steps; i++)
   {
	dx = s*(y-x);
	dy = x*(r-z)-y;
	dz = x*y - b*z;

	x += dt*dx;
	y += dt*dy;
	z += dt*dz;

        glColor3f(x*w, y*w, z*w);
        glVertex3d(x*w,y*w,z*w);														
   }
 
   glEnd();

   //  Draw axes in white
   glColor3f(1,1,1);
   glBegin(GL_LINES);
   glVertex3d(0,0,0);
   glVertex3d(1,0,0);

   glVertex3d(0,0,0);
   glVertex3d(-1,0,0);

   glVertex3d(0,0,0);
   glVertex3d(0,1,0);

   glVertex3d(0,0,0);
   glVertex3d(0,-1,0);

   glVertex3d(0,0,0);
   glVertex3d(0,0,1);

   glVertex3d(0,0,0);
   glVertex3d(0,0,-1);
   glEnd();

   //  Label axes
   glRasterPos3d(1,0,0);
   Print("X");
   glRasterPos3d(0,1,0);
   Print("Y");
   glRasterPos3d(0,0,1);
   Print("Z");

   glRasterPos3d(-1,0,0);
   Print("-X");
   glRasterPos3d(0,-1,0);
   Print("-Y");
   glRasterPos3d(0,0,-1);
   Print("-Z");

   //  Display parameters
   glWindowPos2i(5,25);
   Print("View Angle=%d,%d  Mode: %s",th,ph,text[mode]);
   glWindowPos2i(5,5);
   Print("Parameters: s=%f, b=%f, r=%f", s,b,r);	
   //  Flush and swap
   glFlush();
   glutSwapBuffers();
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
   else if (ch == '0'){
      th = ph = 0;
      w = 0.03;
   }

   //  Tune parameters
   else if (ch == 's'){
	s -= 1;
	mode = 1;
   }
   else if (ch == 'S'){
	s += 1;
	mode = 2;
   }
   else if (ch == 'b'){
	b -= 1;
	mode = 3;
   }
   else if (ch == 'B'){
	b += 1;
	mode = 4;
   }
   else if (ch == 'r'){
	r -= 1;
	mode = 5;
   }
   else if (ch == 'R'){
	r += 1;
	mode = 6;
   }
   else if (ch == '+'){
        w += 0.01;
        mode = 7;
   }
   else if (ch == '-'){
        w -= 0.01;
        mode = 7;
   }  
 



   // Reset parameters
   else if (ch == 'p' || ch == 'P')
   {
      s = 10;
      b = 2.6666;
      r = 28;
      mode = 0;
   }
  
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase azimuth by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease azimuth by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   double w2h = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Orthogonal projection box adjusted for the
   //  aspect ratio of the window
   glOrtho(-dim*w2h,+dim*w2h, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}


/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
  //  Initialize GLUT and process user parameters
   glutInit(&argc,argv);
   //  Request double buffered, true color window 
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   //  Request 500 x 500 pixel window
   glutInitWindowSize(500,500);
   //  Create the window
   glutCreateWindow("HW1 - Vijoy Sunil Kumar");
   //  Tell GLUT to call "display" when the scene should be drawn
   glutDisplayFunc(display);
  //  Tell GLUT to call "reshape" when the window is resized
   glutReshapeFunc(reshape);
   //  Tell GLUT to call "special" when an arrow key is pressed
   glutSpecialFunc(special);
   //  Tell GLUT to call "key" when a key is pressed
   glutKeyboardFunc(key);
   //  Pass control to GLUT so it can interact with the user
   glutMainLoop();
   //  Return code
   return 0;
}
