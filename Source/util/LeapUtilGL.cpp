/******************************************************************************\
* Copyright (C) Leap Motion, Inc. 2011-2013.                                   *
* Leap Motion proprietary and  confidential.  Not for distribution.            *
* Use subject to the terms of the Leap Motion SDK Agreement available at       *
* https://developer.leapmotion.com/sdk_agreement, or another agreement between *
* Leap Motion and you, your company or other organization.                     *
\******************************************************************************/

#include "LeapUtilGL.h"
#include <glm/glm.hpp>

#if !defined(__GLU_H__)
  #if defined(WIN32)
    #include <windows.h>
    #include <GL/glu.h>
  #elif defined(__MACH__)
    #include <OpenGL/glu.h>
  #else
    #include <GL/glu.h>
  #endif
#endif // !__GL_H__

namespace LeapUtilGL {

using namespace Leap;
using namespace LeapUtil;

// create/destroy single global quadric instance for drawing curved surfaces with GLU
class Quadric
{
public:
  Quadric() {}

  ~Quadric()
  {
    if ( s_pQuadric )
    {
      gluDeleteQuadric( s_pQuadric );
      s_pQuadric = NULL;
    }
  }

  operator GLUquadric* ()
  {
    if ( !s_pQuadric )
    {
      s_pQuadric = gluNewQuadric();
    }

    return s_pQuadric;
  }

  static GLUquadric* s_pQuadric;
};

GLUquadric* Quadric::s_pQuadric = NULL;

static Quadric s_quadric;

void drawGrid( ePlane plane, unsigned int horizSubdivs, unsigned int vertSubdivs )
{
    const float fHalfGridSize   = 0.5f;
    const float fHGridStep      = (fHalfGridSize + fHalfGridSize)/static_cast<float>(Max(horizSubdivs, 1u));
    const float fVGridStep      = (fHalfGridSize + fHalfGridSize)/static_cast<float>(Max(vertSubdivs, 1u));
    const float fHEndStep       = fHalfGridSize + fHGridStep;
    const float fVEndStep       = fHalfGridSize + fVGridStep;

    GLAttribScope lightingScope( GL_LIGHTING_BIT );

    glDisable(GL_LIGHTING);

    glBegin( GL_LINES );

    switch ( plane )
    {
      case kPlane_XY:
        for ( float x = -fHalfGridSize; x < fHEndStep; x += fHGridStep )
        {
          glVertex3f( x, -fHalfGridSize, 0 );
          glVertex3f( x, fHalfGridSize, 0 );
        }

        for ( float y = -fHalfGridSize; y < fVEndStep; y += fVGridStep )
        {
          glVertex3f( -fHalfGridSize, y, 0 );
          glVertex3f( fHalfGridSize, y, 0 );
        }
        break;

      case kPlane_YZ:
        for ( float y = -fHalfGridSize; y < fHEndStep; y += fHGridStep )
        {
          glVertex3f( 0, y, -fHalfGridSize );
          glVertex3f( 0, y, fHalfGridSize );
        }

        for ( float z = -fHalfGridSize; z < fVEndStep; z += fVGridStep )
        {
          glVertex3f( 0, -fHalfGridSize, z );
          glVertex3f( 0, fHalfGridSize, z );
        }
        break;

      case kPlane_ZX:
        for ( float z = -fHalfGridSize; z < fHEndStep; z += fHGridStep )
        {
          glVertex3f( -fHalfGridSize, 0, z );
          glVertex3f( fHalfGridSize,  0, z );
        }

        for ( float x = -fHalfGridSize; x < fVEndStep; x += fVGridStep )
        {
          glVertex3f( x, 0, -fHalfGridSize );
          glVertex3f( x,  0, fHalfGridSize );
        }
        break;
    }

    glEnd();
}

void drawSphere( eStyle style, float size )
{
  switch ( style )
  {
   case kStyle_Outline:
    gluQuadricDrawStyle(s_quadric, GLU_SILHOUETTE);
    glPushAttrib( GL_LIGHTING_BIT );
    glDisable(GL_LIGHTING);
    break;

   case kStyle_Solid:
    gluQuadricDrawStyle(s_quadric, GLU_FILL);
    break;
  }

  gluSphere( s_quadric, size*0.05, 32, 32 );

  switch ( style )
  {
   case kStyle_Outline:
    glPopAttrib();
    break;

   case kStyle_Solid:
    break;
  }
}

void drawQuad( eStyle style, ePlane plane, float width, float height )
{
  switch ( style )
  {
   case kStyle_Outline:
    glPushAttrib( GL_LIGHTING_BIT );
    glDisable(GL_LIGHTING);
    break;

   case kStyle_Solid:
    break;
  }

  switch ( plane )
  {
  case kPlane_XY:
    break;
  case kPlane_YZ:
    glPushMatrix();
    glRotatef( 90.0f, 0, 1, 0 );
    break;
  case kPlane_ZX:
    glPushMatrix();
    glRotatef( -90.0f, 1, 0, 0 );
    break;
  }

  //const float kfHalfSize = size/2.f;

  glBegin( style == kStyle_Outline ? GL_LINE_LOOP : GL_TRIANGLES );
  glNormal3f( 0, 0, 1 );
  glTexCoord2f( 0, 0 );
  glVertex3f( -width,  -height, 0 );
  glTexCoord2f( 1, 0 );
  glVertex3f(  width,  -height, 0 );
  glTexCoord2f( 1, 1 );
  glVertex3f(  width,   height, 0 );
  glEnd();

  glBegin( style == kStyle_Outline ? GL_LINE_LOOP : GL_TRIANGLES );
  glTexCoord2f( 1, 1 );
  glVertex3f(  width,   height, 0 );
  glTexCoord2f( 0, 1 );
  glVertex3f( -width,   height, 0 );
  glTexCoord2f( 0, 0 );
  glVertex3f( -width,  -height, 0 );
  glEnd();

  glBegin( style == kStyle_Outline ? GL_LINE_LOOP : GL_TRIANGLES );
  glNormal3f( 0, 0, -1 );
  glTexCoord2f( 0, 0 );
  glVertex3f(  width,  -height, 0 );
  glTexCoord2f( 1, 0 );
  glVertex3f( -width,  -height, 0 );
  glTexCoord2f( 1, 1 );
  glVertex3f( -width,   height, 0 );
  glEnd();

  glBegin( style == kStyle_Outline ? GL_LINE_LOOP : GL_TRIANGLES );
  glTexCoord2f( 1, 1 );
  glVertex3f( -width,   height, 0 );
  glTexCoord2f( 0, 1 );
  glVertex3f(  width,   height, 0 );
  glTexCoord2f( 0, 0 );
  glVertex3f(  width,  -height, 0 );
  glEnd();

  switch ( plane )
  {
  case kPlane_XY:
    break;
  case kPlane_YZ:
  case kPlane_ZX:
    glPopMatrix();
    break;
  }

  switch ( style )
  {
  case kStyle_Outline:
    glPopAttrib();
    break;
  case kStyle_Solid:
    break;
  }
}

void drawFacet( eStyle style, glm::vec3 firstPoint, glm::vec3 secondPoint, glm::vec3 thirdPoint)
{
  switch ( style )
  {
   case kStyle_Outline:
    glPushAttrib( GL_LIGHTING_BIT );
    glDisable(GL_LIGHTING);
    break;

   case kStyle_Solid:
    break;
  }
  glm::vec3 firstVector = secondPoint - firstPoint;
  glm::vec3 secondVector = thirdPoint - firstPoint;
  glm::vec3 normalToFacette = glm::cross(firstVector, secondVector);
  //normalToFacette = glm::normalize(normalToFacette); //the problem when several cubes is here !!!

  glBegin( style == kStyle_Outline ? GL_LINE_LOOP : GL_TRIANGLES );
  glNormal3f( normalToFacette.x, normalToFacette.y, normalToFacette.z );
  glVertex3f(firstPoint.x, firstPoint.y, firstPoint.z);
  glVertex3f(secondPoint.x, secondPoint.y, secondPoint.z);
  glVertex3f(thirdPoint.x, thirdPoint.y, thirdPoint.z);
  glEnd();

  glBegin( style == kStyle_Outline ? GL_LINE_LOOP : GL_TRIANGLES );
  glNormal3f( - normalToFacette.x, - normalToFacette.y, - normalToFacette.z );
  glVertex3f(secondPoint.x, secondPoint.y, secondPoint.z);
  glVertex3f(firstPoint.x, firstPoint.y, firstPoint.z);
  glVertex3f(thirdPoint.x, thirdPoint.y, thirdPoint.z);
  glEnd();

  switch ( style )
  {
  case kStyle_Outline:
    glPopAttrib();
    break;
  case kStyle_Solid:
    break;
  }
}

void drawPolygon( eStyle style, glm::vec3 firstPoint, glm::vec3 secondPoint, glm::vec3 thirdPoint, glm::vec3 forthPoint )
{
  switch ( style )
  {
   case kStyle_Outline:
    glPushAttrib( GL_LIGHTING_BIT );
    glDisable(GL_LIGHTING);
    break;

   case kStyle_Solid:
	   glPushAttrib( GL_LIGHTING_BIT );
    glDisable(GL_LIGHTING);
    break;
  }

  //const float kfHalfSize = size/2.f;

  glBegin( style == kStyle_Outline ? GL_LINE_LOOP : GL_TRIANGLES );
  glNormal3f( 0, 0, 1 );
  glTexCoord2f( 0, 0 );
  glVertex3f( firstPoint.x, firstPoint.y, firstPoint.z );
  glTexCoord2f( 1, 0 );
  glVertex3f(  secondPoint.x, secondPoint.y, secondPoint.z );
  glTexCoord2f( 1, 1 );
  glVertex3f(  thirdPoint.x, thirdPoint.y, thirdPoint.z );
  glEnd();

  glBegin( style == kStyle_Outline ? GL_LINE_LOOP : GL_TRIANGLES );
  glTexCoord2f( 1, 1 );
  glVertex3f(  thirdPoint.x, thirdPoint.y, thirdPoint.z );
  glTexCoord2f( 0, 1 );
  glVertex3f( forthPoint.x, forthPoint.y, forthPoint.z );
  glTexCoord2f( 0, 0 );
  glVertex3f( firstPoint.x, firstPoint.y, firstPoint.z );
  glEnd();

  glBegin( style == kStyle_Outline ? GL_LINE_LOOP : GL_TRIANGLES );
  glNormal3f( 0, 0, -1 );
  glTexCoord2f( 0, 0 );
  glVertex3f(  secondPoint.x, secondPoint.y, secondPoint.z );
  glTexCoord2f( 1, 0 );
  glVertex3f( firstPoint.x, firstPoint.y, firstPoint.z );
  glTexCoord2f( 1, 1 );
  glVertex3f( forthPoint.x, forthPoint.y, forthPoint.z );
  glEnd();

  glBegin( style == kStyle_Outline ? GL_LINE_LOOP : GL_TRIANGLES );
  glTexCoord2f( 1, 1 );
  glVertex3f( forthPoint.x, forthPoint.y, forthPoint.z );
  glTexCoord2f( 0, 1 );
  glVertex3f(  thirdPoint.x, thirdPoint.y, thirdPoint.z );
  glTexCoord2f( 0, 0 );
  glVertex3f(  secondPoint.x, secondPoint.y, secondPoint.z );
  glEnd();

  switch ( style )
  {
  case kStyle_Outline:
    glPopAttrib();
    break;
  case kStyle_Solid:
	  glPopAttrib();
    break;
  }
}


void drawBox( eStyle style, float size )
{
  static const float s_afCorners[8][3] = {
                                            // near face - ccw facing origin from face.
                                            {-size, -size,  size},
                                            { size, -size,  size},
                                            { size,  size,  size},
                                            {-size,  size,  size},

                                            // far face - ccw facing origin from face
                                            { size, -size,  -size},
                                            {-size, -size,  -size},
                                            {-size,  size,  -size},
                                            { size,  size,  -size},

 };

  switch ( style )
  {
   case kStyle_Outline:
    glPushAttrib( GL_LIGHTING_BIT );
    glDisable(GL_LIGHTING);
    break;

   case kStyle_Solid:
    break;
  }

  glBegin( style == kStyle_Solid ? GL_TRIANGLES : GL_LINE_LOOP );

  // near
  glNormal3f( 0, 0, 1 );
  glVertex3fv( s_afCorners[0] );
  glVertex3fv( s_afCorners[1] );
  glVertex3fv( s_afCorners[2] );

  glEnd();
  glBegin( style == kStyle_Solid ? GL_TRIANGLES : GL_LINE_LOOP );

  glVertex3fv( s_afCorners[2] );
  glVertex3fv( s_afCorners[3] );
  glVertex3fv( s_afCorners[0] );

  glEnd();
  glBegin( style == kStyle_Solid ? GL_TRIANGLES : GL_LINE_LOOP );

  // far
  glNormal3f( 0, 0, -1 );
  glVertex3fv( s_afCorners[4] );
  glVertex3fv( s_afCorners[5] );
  glVertex3fv( s_afCorners[6] );

  glEnd();
  glBegin( style == kStyle_Solid ? GL_TRIANGLES : GL_LINE_LOOP );

  glVertex3fv( s_afCorners[6] );
  glVertex3fv( s_afCorners[7] );
  glVertex3fv( s_afCorners[4] );

  glEnd();

  glBegin( style == kStyle_Solid ? GL_TRIANGLES : GL_LINE_LOOP );

  // right
  glNormal3f( 1, 0, 0 );
  glVertex3fv( s_afCorners[1] );
  glVertex3fv( s_afCorners[4] );
  glVertex3fv( s_afCorners[7] );

  glEnd();
  glBegin( style == kStyle_Solid ? GL_TRIANGLES : GL_LINE_LOOP );

  glVertex3fv( s_afCorners[7] );
  glVertex3fv( s_afCorners[2] );
  glVertex3fv( s_afCorners[1] );

  glEnd();
  glBegin( style == kStyle_Solid ? GL_TRIANGLES : GL_LINE_LOOP );

  // left
  glNormal3f( -1, 0, 0 );
  glVertex3fv( s_afCorners[5] );
  glVertex3fv( s_afCorners[0] );
  glVertex3fv( s_afCorners[3] );

  glEnd();
  glBegin( style == kStyle_Solid ? GL_TRIANGLES : GL_LINE_LOOP );

  glVertex3fv( s_afCorners[3] );
  glVertex3fv( s_afCorners[6] );
  glVertex3fv( s_afCorners[5] );

  glEnd();

  glBegin( style == kStyle_Solid ? GL_TRIANGLES : GL_LINE_LOOP );

  // bottom
  glNormal3f( 0, -1, 0 );
  glVertex3fv( s_afCorners[0] );
  glVertex3fv( s_afCorners[5] );
  glVertex3fv( s_afCorners[4] );

  glEnd();
  glBegin( style == kStyle_Solid ? GL_TRIANGLES : GL_LINE_LOOP );

  glVertex3fv( s_afCorners[4] );
  glVertex3fv( s_afCorners[1] );
  glVertex3fv( s_afCorners[0] );

  glEnd();
  glBegin( style == kStyle_Solid ? GL_TRIANGLES : GL_LINE_LOOP );

  // top
  glNormal3f( 0, 1, 0 );
  glVertex3fv( s_afCorners[3] );
  glVertex3fv( s_afCorners[2] );
  glVertex3fv( s_afCorners[7] );

  glEnd();
  glBegin( style == kStyle_Solid ? GL_TRIANGLES : GL_LINE_LOOP );

  glVertex3fv( s_afCorners[7] );
  glVertex3fv( s_afCorners[6] );
  glVertex3fv( s_afCorners[3] );

  glEnd();

  switch ( style )
  {
   case kStyle_Outline:
    glPopAttrib();
    break;

   case kStyle_Solid:
    break;
  }
}

void drawCylinder( eStyle style, eAxis axis )
{
  GLMatrixScope matrixScope;

  switch ( style )
  {
   case kStyle_Outline:
    gluQuadricDrawStyle(s_quadric, GLU_SILHOUETTE);
    glPushAttrib( GL_LIGHTING_BIT );
    glDisable(GL_LIGHTING);
    break;

   case kStyle_Solid:
    gluQuadricDrawStyle(s_quadric, GLU_FILL);
    break;
  }

  switch ( axis )
  {
  case kAxis_X:
    glRotatef( 90.0f, 0, 1, 0 );
    break;
  case kAxis_Y:
    glRotatef( 90.0f, 1, 0, 0 );
    break;
  case kAxis_Z:
    break;
  }

  // draw end caps
  if ( style != kStyle_Outline )
  {
    GLMatrixScope matrixScope;

    glTranslatef( 0, 0, 0.5f );
    drawDisk( style, kPlane_XY );

    glTranslatef( 0, 0, -1.0f );
    drawDisk( style, kPlane_XY );
  }

  glTranslatef( 0, 0, -0.5f );

  gluCylinder( s_quadric, 0.5f, 0.5f, 1.0f, 32, 32 );

  switch ( style )
  {
   case kStyle_Outline:
    glPopAttrib();
    break;

   case kStyle_Solid:
    break;
  }
}

void drawCylinder(eStyle style, float size)
{
  GLMatrixScope matrixScope;

  switch ( style )
  {
   case kStyle_Outline:
    gluQuadricDrawStyle(s_quadric, GLU_SILHOUETTE);
    glPushAttrib( GL_LIGHTING_BIT );
    glDisable(GL_LIGHTING);
    break;

   case kStyle_Solid:
    gluQuadricDrawStyle(s_quadric, GLU_FILL);
    break;
  }

  gluCylinder( s_quadric, 0.001f, 0.001f, size, 32, 32 );

  switch ( style )
  {
   case kStyle_Outline:
    glPopAttrib();
    break;

   case kStyle_Solid:
    break;
  }
}

void drawCylinder(eStyle style, glm::vec3 firstPoint, glm::vec3 secondPoint, float radius)
{
  GLMatrixScope matrixScope;

  switch ( style )
  {
   case kStyle_Outline:
    gluQuadricDrawStyle(s_quadric, GLU_SILHOUETTE);
    glPushAttrib( GL_LIGHTING_BIT );
    glDisable(GL_LIGHTING);
    break;

   case kStyle_Solid:
    gluQuadricDrawStyle(s_quadric, GLU_FILL);
    break;
  }

	float vx = secondPoint.x-firstPoint.x;
	float vy = secondPoint.y-firstPoint.y;
	float vz = secondPoint.z-firstPoint.z;

	//handle the degenerate case of z1 == z2 with an approximation
	if(vz == 0)
		vz = .0001;

	float v = sqrt( vx*vx + vy*vy + vz*vz );
	float ax = 57.2957795*acos( vz/v );
	if ( vz < 0.0 )
		ax = -ax;
	float rx = -vy*vz;
	float ry = vx*vz;
	//draw the cylinder body
	glTranslatef( firstPoint.x, firstPoint.y, firstPoint.z);
	glRotatef(ax, rx, ry, 0.0);
	gluCylinder( s_quadric, radius, radius, glm::length(secondPoint-firstPoint), 32, 32 );

  switch ( style )
  {
   case kStyle_Outline:
    glPopAttrib();
    break;

   case kStyle_Solid:
    break;
  }
}

void drawDisk( eStyle style, ePlane plane )
{
  GLMatrixScope matrixScope;

  switch ( style )
  {
   case kStyle_Outline:
    gluQuadricDrawStyle(s_quadric, GLU_SILHOUETTE);
    glPushAttrib( GL_LIGHTING_BIT );
    glDisable(GL_LIGHTING);
    break;

   case kStyle_Solid:
    gluQuadricDrawStyle(s_quadric, GLU_FILL);
    break;
  }

  switch ( plane )
  {
  case kPlane_XY:
    break;
  case kPlane_YZ:
    glRotatef( 90.0f, 0, 1, 0 );
    break;
  case kPlane_ZX:
    glRotatef( -90.0f, 1, 0, 0 );
    break;
  }

  gluDisk(s_quadric, 0, 0.5f, 32, 1);
  glRotatef( 180.0f, 0, 1, 0 );
  gluDisk(s_quadric, 0, 0.5f, 32, 1);

  switch ( style )
  {
   case kStyle_Outline:
    glPopAttrib();
    break;

   case kStyle_Solid:
    break;
  }
}

void drawAxes()
{
    GLAttribScope attribScope( GL_CURRENT_BIT|GL_LIGHTING_BIT|GL_DEPTH_BUFFER_BIT );

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glColor3f( 1, 0, 0 );
    drawArrow( kAxis_X );

    glColor3f( 0, 1, 0 );
    drawArrow( kAxis_Y );

    glColor3f( 0, 0, 1 );
    drawArrow( kAxis_Z );
}

void drawArrow( eAxis axis )
{
  glBegin( GL_LINES );

  switch ( axis )
  {
  case kAxis_X:
    glVertex3f( 0, 0, 0 );
    glVertex3f( 1, 0, 0 );

    glVertex3f( 1, 0, 0 );
    glVertex3f( 0.8f, 0.2f, 0 );

    glVertex3f( 1, 0, 0 );
    glVertex3f( 0.8f, -0.2f, 0 );
    break;

  case kAxis_Y:
    glVertex3f( 0, 0, 0 );
    glVertex3f( 0, 1, 0 );

    glVertex3f( 0, 1, 0 );
    glVertex3f( 0, 0.8f, 0.2f );

    glVertex3f( 0, 1, 0 );
    glVertex3f( 0, 0.8f, -0.2f );
    break;

  case kAxis_Z:
    glVertex3f( 0, 0, 0 );
    glVertex3f( 0, 0, 1 );

    glVertex3f( 0, 0, 1 );
    glVertex3f( 0.2f, 0, 0.8f );

    glVertex3f( 0, 0, 1 );
    glVertex3f( -0.2f, 0, 0.8f );
    break;
  }

  glEnd();
}


//GLCamera methods

void CameraGL::SetupGLProjection() const
{
  ResetGLProjection();
  gluPerspective( GetVerticalFOVDegrees(), GetAspectRatio(), GetNearClip(), GetFarClip() );
}

void CameraGL::SetupGLView() const
{
  ResetGLView();
  glMultMatrixf( GetView().toArray4x4() );
}

}
