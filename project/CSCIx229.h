#ifndef CSCIx229
#define CSCIx229

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))
#define PI 3.1415927

#ifdef __cplusplus
extern "C" {
#endif

void Print(const char* format , ...);
void Fatal(const char* format , ...);
unsigned int LoadTexBMP(const char* file);
void Project(int mode, double fov,double asp,double dim);
void ErrCheck(const char* where);
int  LoadOBJ(const char* file);

void cube(double x,double y,double z,
         double dx,double dy,double dz,
         double th, double r, double g, double b, unsigned int texture,
         int top, int bottom, int front, int back, int left, int right);

void draw_cylinder(float radius,float height,
                   float R, float G,float B, unsigned int texture);

void draw_cone(double height, double radius, double r, double g, double b, unsigned int texture);
void sphere(double x,double y,double z,double r, double rgb, unsigned int texture);
void Vertex(double th,double ph,double rgb);

void render_room(void);
void render_pillars(void);
void render_table(void);
void render_chair(void);
void render_lamp(void);
void render_computer(void);
void render_joker(void);
void render_hand(void);
void render_batman(void);

#ifdef __cplusplus
}
#endif

#endif
