
#include "CSCIx229.h"

extern double room_w, room_h;
extern double door_w, door_h;

extern double pillar1_w, pillar2_w;
extern double ground_w, ground_h;
extern double rep;
extern int ntex;
extern unsigned int texture[12]; 
extern float shiny;
extern int emission;

void render_room(void)
{
   //glEnable(GL_POLYGON_OFFSET_FILL);
   //glPolygonOffset(1,1);
   double walls_r = 0.90, walls_g = 0.810, walls_b = 0.70;
   double floors_r = 0.60, floors_g = 0.60, floors_b = 0.60;

   //  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   //--------------------------------------------------------------
   // Draw floor
   glColor3f(floors_r,floors_g,floors_b);
   //  Enable textures
   //  Select texture if textures are on
   if (ntex<0)
      glDisable(GL_TEXTURE_2D);
   else
   {
      glEnable(GL_TEXTURE_2D);
   }
   
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[0]);					
   glBegin(GL_QUADS);
   glNormal3f( 0, 1, 0);

   glTexCoord2f(0.0,0.0); 	glVertex3f(-ground_w/2,0.0,room_h);
   glTexCoord2f(rep,0.0); 	glVertex3f(-ground_w/2,0.0,-ground_h);
   glTexCoord2f(rep,rep); 	glVertex3f(ground_w/2,0.0,-ground_h);
   glTexCoord2f(0.0,rep); 	glVertex3f(ground_w/2,0.0,room_h);
   glEnd();
   //glDisable(GL_POLYGON_OFFSET_FILL);
   
   //--------------------------------------------------------------
   // Draw side walls (LEFT)
   glColor3f(walls_r,walls_g,walls_b);
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[2]);					
   glBegin(GL_QUADS);
   glNormal3f( 1, 0, 0);   

   glTexCoord2f(0.0, 0.0);	glVertex3f(-room_w/2,0.0,room_h);
   glTexCoord2f(rep, 0.0);	glVertex3f(-room_w/2,room_w/3.9,room_h);
   glTexCoord2f(rep, rep);	glVertex3f(-room_w/2,room_w/3.9,-room_h);
   glTexCoord2f(0.0, rep);	glVertex3f(-room_w/2,0.0,-room_h);
   glEnd();   

   // Upper strip
   glColor3f(walls_r,walls_g,walls_b);
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[2]);	
   glBegin(GL_QUADS);
   glNormal3f( 1, 0, 0);

   glTexCoord2f(0.0, 0.0);	glVertex3f(-room_w/2,room_w/2,room_h);
   glTexCoord2f(rep, 0.0);	glVertex3f(-room_w/2,room_w/2,-room_h);
   glTexCoord2f(rep, rep);	glVertex3f(-room_w/2,(room_w/2)-0.3,-room_h);
   glTexCoord2f(0.0, rep);	glVertex3f(-room_w/2,(room_w/2)-0.3,room_h);
   glEnd(); 

   // Draw side walls (LEFT OUTER)
   glColor3f(walls_r,walls_g,walls_b);	
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f( 1, 0, 0);

   glTexCoord2f(0.0, 0.0);	glVertex3f(-ground_w/2,0.0,room_h);
   glTexCoord2f(rep, 0.0);	glVertex3f(-ground_w/2,room_w/2,room_h);
   glTexCoord2f(rep, rep);	glVertex3f(-ground_w/2,room_w/2,-ground_h);
   glTexCoord2f(0.0, rep);	glVertex3f(-ground_w/2,0.0,-ground_h);
   glEnd(); 

 
   // Draw side walls (RIGHT)
   glColor3f(walls_r,walls_g,walls_b);
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[2]);	
   glBegin(GL_QUADS);
   glNormal3f( -1, 0, 0);

   glTexCoord2f(0.0, 0.0);	glVertex3f(room_w/2,0.0,room_h);
   glTexCoord2f(rep, 0.0);	glVertex3f(room_w/2,room_w/3.9,room_h);
   glTexCoord2f(rep, rep);	glVertex3f(room_w/2,room_w/3.9,-room_h);
   glTexCoord2f(0.0, rep);	glVertex3f(room_w/2,0.0,-room_h);
   glEnd(); 

   // Upper strip
   glColor3f(walls_r,walls_g,walls_b);	
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f( -1, 0, 0);

   glTexCoord2f(0.0, 0.0);	glVertex3f(room_w/2,room_w/2,room_h);
   glTexCoord2f(rep, 0.0);	glVertex3f(room_w/2,room_w/2,-room_h);
   glTexCoord2f(rep, rep);	glVertex3f(room_w/2,(room_w/2)-0.3,-room_h);
   glTexCoord2f(0.0, rep);	glVertex3f(room_w/2,(room_w/2)-0.3,room_h);
   glEnd(); 

   // Draw side walls (RIGHT OUTER)
   glColor3f(walls_r,walls_g,walls_b);	
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f( -1, 0, 0);

   glTexCoord2f(0.0, 0.0);	glVertex3f(ground_w/2,0.0,room_h);
   glTexCoord2f(rep, 0.0);	glVertex3f(ground_w/2,room_w/2,room_h);
   glTexCoord2f(rep, rep);	glVertex3f(ground_w/2,room_w/2,-ground_h);
   glTexCoord2f(0.0, rep);	glVertex3f(ground_w/2,0.0,-ground_h);
   glEnd();  

   //--------------------------------------------------------------
   // Draw back wall  
   glColor3f(walls_r,walls_g,walls_b);	
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, -1);

   glTexCoord2f(0.0, 0.0);	glVertex3f(-ground_w/2,0.0,room_h);
   glTexCoord2f(rep, 0.0);	glVertex3f(-ground_w/2,room_w/2,room_h);
   glTexCoord2f(rep, rep);	glVertex3f(ground_w/2,room_w/2,room_h);
   glTexCoord2f(0.0, rep);	glVertex3f(ground_w/2,0.0,room_h);
   glEnd();  

   //--------------------------------------------------------------
   // Draw front wall (DOOR)  
   glColor3f(walls_r,walls_g,walls_b);	
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, 1);

   glTexCoord2f(0.0, 0.0);	glVertex3f(-room_w/2,0.0,-room_h);
   glTexCoord2f(rep, 0.0);	glVertex3f(-room_w/2,room_w/2,-room_h);
   glTexCoord2f(rep, rep);	glVertex3f(-door_w/2,room_w/2,-room_h);
   glTexCoord2f(0.0, rep);	glVertex3f(-door_w/2,0.0,-room_h);
   glEnd();

   glColor3f(walls_r,walls_g,walls_b);	
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, 1);

   glTexCoord2f(0.0, 0.0);	glVertex3f(room_w/2,0.0,-room_h);
   glTexCoord2f(rep, 0.0);	glVertex3f(room_w/2,room_w/2,-room_h);
   glTexCoord2f(rep, rep);	glVertex3f(door_w/2,room_w/2,-room_h);
   glTexCoord2f(0.0, rep);	glVertex3f(door_w/2,0.0,-room_h);
   glEnd();

   glColor3f(walls_r,walls_g,walls_b);
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[2]);	
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, 1);

   glTexCoord2f(0.0, 0.0);	glVertex3f(-door_w/2,room_w/2,-room_h);
   glTexCoord2f(rep, 0.0);	glVertex3f(door_w/2,room_w/2,-room_h);
   glTexCoord2f(rep, rep);	glVertex3f(door_w/2,door_h,-room_h);
   glTexCoord2f(0.0, rep);	glVertex3f(-door_w/2,door_h,-room_h);
   glEnd();

   // Draw front wall (LEFT - NO DOOR)  
   glColor3f(walls_r,walls_g,walls_b);
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[2]);	
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, 1);

   glTexCoord2f(0.0, 0.0);	glVertex3f(-ground_w/2,0.0,-ground_h);
   glTexCoord2f(rep, 0.0);	glVertex3f(-ground_w/2,room_w/2,-ground_h);
   glTexCoord2f(rep, rep);	glVertex3f(-room_w/2,room_w/2,-ground_h);
   glTexCoord2f(0.0, rep);	glVertex3f(-room_w/2,0.0,-ground_h);
   glEnd();

   // Draw front wall (LEFT - DOOR)  
   glColor3f(walls_r,walls_g,walls_b);
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[2]);	
   glBegin(GL_QUADS);
   glNormal3f( 1, 0, 0);

   glTexCoord2f(0.0, 0.0);	glVertex3f(-room_w/2,room_w/2,-ground_h);
   glTexCoord2f(rep, 0.0);	glVertex3f(-room_w/2,room_w/2,-room_h);
   glTexCoord2f(rep, rep);	glVertex3f(-room_w/2,door_h,-room_h);
   glTexCoord2f(0.0, rep);	glVertex3f(-room_w/2,door_h,-ground_h);
   glEnd();

   glColor3f(walls_r,walls_g,walls_b);
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[2]);	
   glBegin(GL_QUADS);
   glNormal3f( 1, 0, 0);

   glTexCoord2f(0.0, 0.0);	glVertex3f(-room_w/2,door_h,-ground_h);
   glTexCoord2f(rep, 0.0);	glVertex3f(-room_w/2,door_h,-ground_h + 1.4);
   glTexCoord2f(rep, rep);	glVertex3f(-room_w/2,0.0,-ground_h + 1.4);
   glTexCoord2f(0.0, rep);	glVertex3f(-room_w/2,0.0,-ground_h);
   glEnd();

   // Draw front wall (RIGHT - NO DOOR)  
   glColor3f(walls_r,walls_g,walls_b);
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[2]);	
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, 1);

   glTexCoord2f(0.0, 0.0);	glVertex3f(ground_w/2,0.0,-ground_h);
   glTexCoord2f(rep, 0.0);	glVertex3f(ground_w/2,room_w/2,-ground_h);
   glTexCoord2f(rep, rep);	glVertex3f(room_w/2,room_w/2,-ground_h);
   glTexCoord2f(0.0, rep);	glVertex3f(room_w/2,0.0,-ground_h);
   glEnd();

   // Draw front wall (RIGHT - DOOR)  
   glColor3f(walls_r,walls_g,walls_b);
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[2]);	
   glBegin(GL_QUADS);
   glNormal3f( -1, 0, 0);

   glTexCoord2f(0.0, 0.0);	glVertex3f(room_w/2,room_w/2,-ground_h);
   glTexCoord2f(rep, 0.0);	glVertex3f(room_w/2,room_w/2,-room_h);
   glTexCoord2f(rep, rep);	glVertex3f(room_w/2,door_h,-room_h);
   glTexCoord2f(0.0, rep);	glVertex3f(room_w/2,door_h,-ground_h);
   glEnd();

   glColor3f(walls_r,walls_g,walls_b);
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[2]);	
   glBegin(GL_QUADS);
   glNormal3f( -1, 0, 0);

   glTexCoord2f(0.0, 0.0);	glVertex3f(room_w/2,door_h,-ground_h);
   glTexCoord2f(rep, 0.0);	glVertex3f(room_w/2,door_h,-ground_h + 1.4);
   glTexCoord2f(rep, rep);	glVertex3f(room_w/2,0.0,-ground_h + 1.4);
   glTexCoord2f(0.0, rep);	glVertex3f(room_w/2,0.0,-ground_h);

   glEnd();
   glDisable(GL_TEXTURE_2D);
}




void render_pillars(void)
{
   double pillars_r = 0.90, pillars_g = 0.810, pillars_b = 0.70;
   double pillar_thickness = 0.4;

   //vertical pillars
   // thick pillars - pillar1
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(-room_w/2+pillar_thickness/2,room_w/4,2.5, -pillar_thickness/2,room_w/4,-pillar1_w/2, 0, pillars_r,pillars_g,pillars_b, texture[1], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(room_w/2-pillar_thickness/2,room_w/4,2.5, pillar_thickness/2,room_w/4,pillar1_w/2, 0,pillars_r,pillars_g,pillars_b, texture[1], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(-room_w/2+pillar_thickness/2,room_w/4,-2.5, -pillar_thickness/2,room_w/4,-pillar1_w/2, 0, pillars_r,pillars_g,pillars_b, texture[1], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(room_w/2-pillar_thickness/2,room_w/4,-2.5, pillar_thickness/2,room_w/4,pillar1_w/2, 0, pillars_r,pillars_g,pillars_b, texture[1], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   //thin pillars - pillar2
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(-room_w/2+pillar_thickness/2,room_w/4,room_h-pillar2_w/2, -pillar_thickness/2,room_w/4,-pillar2_w/2, 0,pillars_r,pillars_g,pillars_b, texture[1], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(room_w/2-pillar_thickness/2,room_w/4,room_h-pillar2_w/2, -pillar_thickness/2,room_w/4,-pillar2_w/2, 0, pillars_r,pillars_g,pillars_b, texture[1], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(room_w/2-pillar_thickness/2,room_w/4,-room_h+pillar2_w/2, -pillar_thickness/2,room_w/4,-pillar2_w/2, 0, pillars_r,pillars_g,pillars_b, texture[1], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(-room_w/2+pillar_thickness/2,room_w/4,-room_h+pillar2_w/2, -pillar_thickness/2,room_w/4,-pillar2_w/2, 0, pillars_r,pillars_g,pillars_b, texture[1], 1,1,1,1,1,1); 
   glDisable(GL_POLYGON_OFFSET_FILL);

   //horizontal pillars
   double pillar_thickness1 = 0.2;

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(-room_w/2+pillar_thickness1/2,room_w/10,0.0, pillar_thickness1/2,room_w/10,room_h, 0, 1, 1, 1, texture[0], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(room_w/2-pillar_thickness1/2,room_w/10,0.0, pillar_thickness1/2,room_w/10,room_h, 0, 1, 1, 1, texture[0], 1,1,1,1,1,1);  
   glDisable(GL_POLYGON_OFFSET_FILL); 
}

void render_table(void)
{
   double table_r = 0.420, table_g = 0.420, table_b = 0.420;
   double table_r2 = 0.360, table_g2 = 0.360, table_b2 = 0.360;
   double table_l = 3.0;
   double table_w = 1.5;
   double table_top_thickness = 0.05;

   //table top
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(0,room_w/6,0, table_l/2,table_top_thickness/2, table_w/2, 0, table_r, table_g, table_b, texture[3], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   //table top2
   double table_top_thickness1 = 0.15;
   double table_l1 = table_l - 0.3;
   double table_w1 = table_w - 0.3;

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(0,(room_w/6)-(table_top_thickness/2)-(table_top_thickness1/2),0, table_l1/2, table_top_thickness1/2,table_w1/2, 0, table_r2, table_g2, table_b2, texture[3], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   //table legs
   double legs_l = room_w/6 - (table_top_thickness/2); 
   double legs_w = 0.15;
   double legs_thickness = legs_w;

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(((table_l1/2) + (table_l/2))/2, legs_l/2, ((table_w1/2) + (table_w)/2)/2, legs_thickness/2, legs_l/2, legs_thickness/2, 0, table_r, table_g, table_b, texture[3], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(((table_l1/2) + (table_l/2))/2, legs_l/2, -((table_w1/2) + (table_w)/2)/2, legs_thickness/2, legs_l/2, legs_thickness/2, 0, table_r, table_g, table_b, texture[3], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1); 
   cube(-((table_l1/2) + (table_l/2))/2, legs_l/2, -((table_w1/2) + (table_w)/2)/2, legs_thickness/2, legs_l/2, legs_thickness/2, 0, table_r, table_g, table_b, texture[3], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1); 
   cube(-((table_l1/2) + (table_l/2))/2, legs_l/2, ((table_w1/2) + (table_w)/2)/2, legs_thickness/2, legs_l/2, legs_thickness/2, 0, table_r, table_g, table_b, texture[3], 1,1,1,1,1,1);  
   glDisable(GL_POLYGON_OFFSET_FILL);
}

void render_chair(void)
{

   double chair_r = 0.380, chair_g = 0.380, chair_b = 0.380;
   double legs_thickness = 0.075;
   double legs_width = legs_thickness;
   double legs_height = room_w/9;

   double base_length = 1.0;
   //legs
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(base_length/2,legs_height,-base_length/2, legs_thickness/2, legs_height, legs_thickness/2, 0, chair_r, chair_g, chair_b, texture[4], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(-base_length/2,legs_height,-base_length/2, legs_thickness/2, legs_height, legs_thickness/2, 0, chair_r, chair_g, chair_b, texture[4], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(-base_length/2+(legs_thickness/1.9),legs_height/2,base_length/2-(legs_thickness/1.9), legs_thickness/2, legs_height/2, legs_thickness/2, 0, chair_r, chair_g, chair_b, texture[4], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(base_length/2-(legs_thickness/1.9),legs_height/2,base_length/2-(legs_thickness/1.9), legs_thickness/2, legs_height/2, legs_thickness/2, 0, chair_r, chair_g, chair_b, texture[4], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   //base
   double base_thickness = 1.5*legs_thickness;
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(0,legs_height,0,  base_length/2,base_thickness/2 , base_length/2, 0, chair_r, chair_g, chair_b, texture[5], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   //back support - horizontal
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(0,(2*legs_height)-(legs_width/2),-base_length/2, base_length/2, legs_thickness/2, legs_thickness/2, 0, chair_r, chair_g, chair_b, texture[4], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(0,(1.85*legs_height)-(legs_width/2),-base_length/2, base_length/2, legs_thickness/2, legs_thickness/2, 0, chair_r, chair_g, chair_b, texture[4], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(0,(1.2*legs_height)-(legs_width/2),-base_length/2, base_length/2, legs_thickness/2, legs_thickness/2, 0, chair_r, chair_g, chair_b, texture[4], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   //back support - vertical
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(0,(1.525*legs_height)-(legs_width/2),-base_length/2, legs_thickness/2, 0.65*legs_height/2, legs_thickness/2, 0, chair_r, chair_g, chair_b, texture[4], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);
}


void render_lamp(void)
{
   double cone_r = 0.30, cone_g = 0.30, cone_b = 0.30;
   double cube_h1 = 0.3, cube_w1 = 1.0;
   //base cube
   glPushMatrix();
   cube(0, (cube_h1/2), 0, cube_w1/2, cube_h1/2, cube_w1/2, 0, cone_r, cone_g, cone_b, texture[6], 1,1,1,1,1,1);
   glPopMatrix();

   //cube on top of cube
   double cube_h = 0.3;
   double cube_w = 0.7;
   double cylinder_h = 0.3;
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(0, cylinder_h + (cube_h/2), 0, cube_w/2, cube_h/2, cube_w/2, 0, cone_r, cone_g, cone_b, texture[6], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);  

   //cone on top of cube
   double cone_h = 0.5;
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   glPushMatrix();
   glTranslated(0.0, cylinder_h+cube_h, 0.0);
   glRotated(-90.0,1,0,0);
   glScaled(0.35,0.35,1.0);
   draw_cone(cone_h, 1.0,0.180,0.180,0.180, texture[6]);
   glPopMatrix();
   glDisable(GL_POLYGON_OFFSET_FILL); 


   //sphere on top of cube
   double sphere_r = cube_w/2;
   sphere(0,cylinder_h+cube_h+sphere_r+cone_h-0.1,0, sphere_r, cone_r, texture[9]);

   //rod1
   double rod_w = 0.2;
   double rod_h = 3.0;
   glPushMatrix();
   glTranslated(-rod_h/2, cylinder_h+cube_h+sphere_r+cone_h+0.4, 0.0);
   glRotated(70.0,0,0,1);
   cube(0,0,0,rod_w/2, rod_h/2, rod_w/2, 0, cone_r, cone_g, cone_b, texture[6], 1,1,1,1,1,1);  
   glPopMatrix();


   //sphere connected to rod1
   glPushMatrix();
   glTranslated(-rod_h,2.4, 0);
   sphere(0,0,0, sphere_r, cone_r, texture[9]);
   glPopMatrix();

   //rod2
   glPushMatrix();
   glTranslated(-rod_h/2,1.5+rod_h/2, 0);
   glRotated(-75.0,0,0,1);
   cube(0,0,0,rod_w/2, rod_h/2, rod_w/2, 0, cone_r, cone_g, cone_b, texture[6], 1,1,1,1,1,1); 
   glPopMatrix();

   //sphere connected to rod2
   glPushMatrix();
   glTranslated(0,3.4, 0);
   sphere(0,0,0, sphere_r, cone_r, texture[9]);
   glPopMatrix();

   //rod3
   glPushMatrix();
   glTranslated(rod_h/4, 3.4, 0);
   cube(0,0,0,rod_h/4, rod_w/2, rod_w/2, 0, cone_r, cone_g, cone_b, texture[6], 1,1,1,1,1,1);
   glPopMatrix();

   //sphere
   glPushMatrix();
   glTranslated(rod_h/2,3.4, 0);
   sphere(0,0,0, sphere_r, cone_r, texture[9]);
   glPopMatrix();

   //cone
   double cone_h2 = 1.5;
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   glPushMatrix();
   glTranslated(rod_h/2,2.0, 0);
   glRotated(-90.0,1,0,0);
   glScaled(1.0,1.0,1.0);
   draw_cone(cone_h2, 1.0,0.180,0.180,0.180, texture[7]);
   glPopMatrix();
   glDisable(GL_POLYGON_OFFSET_FILL); 
}

void render_computer(void)
{
   double comp_r = 0.3, comp_g = 0.26, comp_b = 0.26;
   double base_thickness = 0.05, base_l = 1.0, base_w = 0.8;
   //base
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(0,base_thickness/2,0, base_l/2,base_thickness/2, base_w/2, 0, comp_r, comp_g, comp_b, texture[10], 1,0,0,0,0,0);
   glDisable(GL_POLYGON_OFFSET_FILL);

   //top
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   glPushMatrix();
   glTranslated(0.0, 0.33, -0.65);
   glRotated(45.0,1,0,0);
   cube(0,base_thickness/2,0, base_l/2,base_thickness/2, base_w/2, 0, comp_r, comp_g, comp_b, texture[11], 1,0,0,0,0,0);
   glPopMatrix();
  
   
   
   //ports
   cube(-0.5,base_thickness/2,0.10, 0.0,base_thickness/4, 0.05, 0, comp_r+0.4, comp_g+0.4, comp_b+0.4, texture[4], 1,1,1,1,1,1);
   cube(-0.5,base_thickness/2,0.30, 0.0,base_thickness/4, 0.05, 0, comp_r+0.4, comp_g+0.4, comp_b+0.4, texture[4], 1,1,1,1,1,1);
   cube(0.5,base_thickness/2,0.10, 0.0,base_thickness/4, 0.05, 0, comp_r+0.4, comp_g+0.4, comp_b+0.4, texture[4], 1,1,1,1,1,1);
   cube(0.5,base_thickness/2,0.30, 0.0,base_thickness/4, 0.05, 0, comp_r+0.4, comp_g+0.4, comp_b+0.4, texture[4], 1,1,1,1,1,1);
}






























