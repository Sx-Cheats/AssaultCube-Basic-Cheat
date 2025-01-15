#pragma once

#pragma comment(lib,"opengl32.lib")

#include<Windows.h>
#include "./glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "./glm/gtx/string_cast.hpp"
#include <gl/GLU.h>
#include <gl/GL.h>
#include "Vector3.h"

namespace rgb
{
	const GLubyte red[3] = { 255, 0, 0 };
	const GLubyte green[3] = { 255, 255, 255 };
	const GLubyte gray[3] = { 55, 55, 55 };
	const GLubyte lightgray[3] = { 192, 192, 192 };
	const GLubyte black[3] = { 0, 0, 0 };
	const GLubyte blue[3] = { 0, 0, 255 };
	const GLubyte lightgreen[3] = { 194, 240, 115 };
}

class OpenGl32ESP_t
{
	float * ModelViewMatrix;
	float * ProjectionMatrix;

	glm::vec4 __ToViewPos(glm::vec4 position)
	{
		glm::vec4 EyeVec4Pos;             
		float* ModelViewMatrix = (float*)0x0057E010;

		EyeVec4Pos.x = position.x * ModelViewMatrix[0] + position.y * ModelViewMatrix[4] + position.z * ModelViewMatrix[8] + (position.w * ModelViewMatrix[12]);
		EyeVec4Pos.y = position.x * ModelViewMatrix[1] + position.y * ModelViewMatrix[5] + position.z * ModelViewMatrix[9] + (position.w * ModelViewMatrix[13]);
		EyeVec4Pos.z = position.x * ModelViewMatrix[2] + position.y * ModelViewMatrix[6] + position.z * ModelViewMatrix[10] + (position.w * ModelViewMatrix[14]);
		EyeVec4Pos.w = position.x * ModelViewMatrix[3] + position.y * ModelViewMatrix[7] + position.z * ModelViewMatrix[11] + (position.w * ModelViewMatrix[15]);
		
		return EyeVec4Pos;
	}

	glm::vec4 __ToProjectionPos(glm::vec4 position)
	{
		glm::vec4 ClipVec4Pos;

		ClipVec4Pos.x = position.x * ProjectionMatrix[0] + position.y * ProjectionMatrix[4] + position.z * ProjectionMatrix[8]  + (position.w * ProjectionMatrix[12]);
		ClipVec4Pos.y = position.x * ProjectionMatrix[1] + position.y * ProjectionMatrix[5] + position.z * ProjectionMatrix[9]  + (position.w * ProjectionMatrix[13]);
		ClipVec4Pos.z = position.x * ProjectionMatrix[2] + position.y * ProjectionMatrix[6] + position.z * ProjectionMatrix[10] + (position.w * ProjectionMatrix[14]);
		ClipVec4Pos.w = position.x * ProjectionMatrix[3] + position.y * ProjectionMatrix[7] + position.z * ProjectionMatrix[11] + (position.w * ProjectionMatrix[15]);
		
		return ClipVec4Pos;
	}

public:

	void SetViewMatrix(DWORD32 Address)
	{
		ModelViewMatrix = (float*)Address;
	}

	void SetProjectionMatrix(DWORD32 Address)
	{
		ProjectionMatrix = (float*)Address;
	}

	vec2 WorldToScreen(vec3 Position)
	{
		glm::vec4 pos2d = __ToProjectionPos(__ToViewPos(glm::vec4(Position.z, Position.x, Position.y + 5, 1)));

		if (pos2d.w < .55f)
			return vec2{ 0,0 };

		vec3 NDC;
		NDC.x = pos2d.x / pos2d.w;
		NDC.y = pos2d.y / pos2d.w;
		NDC.z = pos2d.z / pos2d.w;

		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);

		vec2 screen;

		screen.x = (viewport[2] / 2 * NDC.x) + (NDC.x + viewport[2] / 2);
		screen.y = -(viewport[3] / 2 * NDC.y) + (NDC.y + viewport[3] / 2);

		return screen;
	}

	void Setup()
	{
	
	    glPushAttrib(GL_ALL_ATTRIB_BITS);
		glPushMatrix();
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		glViewport(0, 0, viewport[2], viewport[3]);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();
		glDisable(GL_DEPTH_TEST);

	}

	void RestoreGL()
	{
		glPopMatrix();
		glPopAttrib();
	};

	void DrawSquare(bool filled, vec2 position, float width, float height, float lineWidth, const GLubyte color[3])
	{
	/*	if (filled)
			glBegin(GL_QUADS);
		else if (!filled)
		{
			glBegin(GL_LINE_LOOP);
		}	  */

		glLineWidth(lineWidth);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POLYGON_SMOOTH);
		glEnable(GL_BLEND);
		glDepthMask(false);
		glColor3ub(color[0], color[1], color[2]);
		glEnableClientState(GL_VERTEX_ARRAY);

		GLfloat  line_vertex[] =
		{
			position.x,position.y,0.0f,
			(position.x+width),position.y,0.0f,
			(position.x + width),(position.y+height),0.0f,
			position.x,(position.y + height),0.0f,
		};

		glVertexPointer(3, GL_FLOAT, 0, line_vertex);
		if (filled)
			glDrawArrays(GL_QUADS, 0, 4);
		else if (!filled)
			glDrawArrays(GL_LINE_LOOP, 0, 4);  

		glDisableClientState(GL_VERTEX_ARRAY);
		glLineWidth(1);
		glDisable(GL_LINE_SMOOTH);
		glDisable(GL_POLYGON_SMOOTH);
		glDisable(GL_BLEND);
		glDepthMask(true);

	}

	void DrawLine(vec2 from, vec2 to, float lineWidth, const GLubyte color[3])
	{
		glLineWidth(lineWidth);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_BLEND);
		glDepthMask(false);
		glColor3ub(color[0], color[1], color[2]);
		glEnableClientState(GL_VERTEX_ARRAY);

		GLfloat  line_vertex[] =
		{
			from.x,from.y, 
			to.x,to.y
		};

		glVertexPointer(2, GL_FLOAT, 0, line_vertex);
		glDrawArrays(GL_LINES, 0, 2);


		glDisableClientState(GL_VERTEX_ARRAY);
		glLineWidth(1);
		glDisable(GL_LINE_SMOOTH);
		glDisable(GL_BLEND);
		glDepthMask(true);
	};


} OpenGlESP;