#ifndef GRAPHICS_SETTINGS_H
#define GRAPHICS_SETTINGS_H

/* Window size*/
#define WINDOW_WIDTH 1920.0f
#define WINDOW_HEIGHT 1080.0f
//#define WINDOW_WIDTH 1366.0f
//#define WINDOW_HEIGHT 768.0f

// Ratio coordinates
#define WCX float(WINDOW_WIDTH/1920.0f)
#define WCY float(WINDOW_HEIGHT/1080.0f)
#define MAX_Z 1000.0f


#define WINDOW_MODE GLFW_FULLSCREEN	// Uncomment for fullscreen
//#define WINDOW_MODE GLFW_WINDOW			// Uncomment for window screen

// Include GL
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//#define HIDE_MOUSE	// Uncomment to hide mouse



/* Defines graphics */
#define OPENGL_MAJOR_VERSION 2
#define OPENGL_MINOR_VERSION 1
#define GLSL_FILE_PATH "res/shader/"
//#define GLSL_FILE_PATH "\shaders/"
#define TEXTURE_FILE_PATH "res/texture/"


/* MATH */

#define M_2PI        6.28318530718							/* pi*2 */


#endif
