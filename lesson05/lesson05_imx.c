#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>
#include <math.h>

#include "GLES2/gl2.h"
#include "GLES2/gl2ext.h"
#include "EGL/egl.h"


#define TRUE 1
#define FALSE !TRUE
EGLDisplay		eglDisplay;
EGLSurface		eglSurface;
EGLContext		eglContext;
NativeDisplayType 	display;
NativeWindowType 	window;

int	     currentFrame = 0;

GLuint       g_hShaderProgram      = 0;
GLuint       g_hModelViewMatrixLoc = 0;
GLuint       g_hProjMatrixLoc      = 0;
GLuint       g_hVertexLoc          = 0;
GLuint       g_hColorLoc           = 1;


//--------------------------------------------------------------------------------------
// Name: g_strVertexShader / g_strFragmentShader
// Desc: The vertex and fragment shader programs
//--------------------------------------------------------------------------------------
const char* g_strVertexShader = 
    "uniform   mat4 g_matModelView;				\n"
    "uniform   mat4 g_matProj;					\n"
    "								\n"
    "attribute vec4 g_vPosition;				\n"
    "attribute vec3 g_vColor;					\n"
    "								\n"
    "varying   vec3 g_vVSColor;					\n"
    "								\n"
    "void main()						\n"
    "{								\n"
    "    vec4 vPositionES = g_matModelView * g_vPosition;	\n"
    "    gl_Position  = g_matProj * vPositionES;		\n"
    "    g_vVSColor = g_vColor;					\n"
    "}								\n";


const char* g_strFragmentShader = 
    "#ifdef GL_FRAGMENT_PRECISION_HIGH				\n"
    "   precision highp float;					\n"
    "#else							\n"
    "   precision mediump float;				\n"
    "#endif							\n"
    "								\n"
    "varying   vec3      g_vVSColor;				\n"
    "								\n"
    "void main()						\n"
    "{								\n"
    "    gl_FragColor = vec4( g_vVSColor, 1.0 );		\n"
    "}								\n";

    // Define vertice for a 4-sided pyramid
    float VertexPositions[] =
    {
    /* Top Of Triangle (Front) */
    0.0f, 1.0f, 0.0f,
    /* Left Of Triangle (Front) */
    -1.0f, -1.0f, 1.0f,
    /* Right Of Triangle (Front) */
    1.0f, -1.0f,1.0f,
    /* Top Of Triangle (Right) */
    0.0f, 1.0f,0.0f,
    /* Left Of Triangle (Right) */
    1.0f,-1.0f,1.0f,
    /* Right Of Triangle (Right) */
    1.0f,-1.0f,-1.0f,
    /* Top Of Triangle (Back) */
    0.0f,1.0f,0.0f,
    /* Left Of Triangle (Back) */
    1.0f,-1.0f,-1.0f,
    /* Right Of Triangle (Back) */
    -1.0f,-1.0f,-1.0f,
    /* Top Of Triangle (Left) */
    0.0f,1.0f,0.0f,
    /* Left Of Triangle (Left) */
    -1.0f,-1.0f,-1.0f,
    /* Right Of Triangle (Left) */
    -1.0f,-1.0f,1.0f,
	
    };

    float VertexPositions2[]={

	
    /* Draw A Quad */

  
    /* Top Right Of The Quad (Top) */
    1.0f, 1.0f,-1.0f,
    /* Top Left Of The Quad (Top) */
    -1.0f, 1.0f, -1.0f,
    /* Bottom Right Of The Quad (Top) */
    1.0f,1.0f,1.0f,
    /* Bottom Left Of The Quad (Top) */
    -1.0f,1.0f,1.0f,
    /* Top Right Of The Quad (Bottom) */
    1.0f,-1.0f,1.0f,
    /* Top Left Of The Quad (Bottom) */
    -1.0f, -1.0f,1.0f,
    /* Bottom Right Of The Quad (Bottom) */
    1.0f,-1.0f,-1.0f,
    /* Bottom Left Of The Quad (Bottom) */
    -1.0f,-1.0f,-1.0f,
    /* Top Right Of The Quad (Front) */
    1.0f,1.0f,1.0f,
    /* Top Left Of The Quad (Front) */
    -1.0f,1.0f,1.0f,
    /* Bottom Right Of The Quad (Front) */
    1.0f,-1.0f,1.0f,
    /* Bottom Left Of The Quad (Front) */
    -1.0f,-1.0f,1.0f,
  
    /* Top Right Of The Quad (Back) */
    1.0f,-1.0f,-1.0f,
    /* Top Left Of The Quad (Back) */
    -1.0f,-1.0f,-1.0f,
    /* Bottom Right Of The Quad (Back) */
    1.0f, 1.0f, -1.0f,
    /* Bottom Left Of The Quad (Back) */
    -1.0f,1.0f,-1.0f,
  
    /* Top Right Of The Quad (Left) */
   -1.0f,1.0f,1.0f,
    /* Top Left Of The Quad (Left) */
    -1.0f,1.0f, -1.0f,
    /* Bottom Right Of The Quad (Left) */
    -1.0f,-1.0f,1.0f,
    /* Bottom Left Of The Quad (Left) */
    -1.0f,-1.0f,-1.0f,
    /* Top Right Of The Quad (Right) */
    1.0f,1.0f,-1.0f,
    /* Top Left Of The Quad (Right) */
    1.0f,1.0f,1.0f,
    /* Bottom Right Of The Quad (Right) */
    1.0f,-1.0f,-1.0f,
    /* Bottom Left Of The Quad (Right) */
    1.0f,-1.0f,1.0f

    };

    float VertexColors[] =
    {
        /* Red */
    1.0f, 0.0f, 0.0f, 1.0f,
    /* Green */
    0.0f, 1.0f, 0.0f, 1.0f,
    /* Blue */
    0.0f, 0.0f, 1.0f,1.0f,
    /* Red */
    1.0f, 0.0, 0.0f, 1.0f,
    /* Blue */
    0.0f, 0.0f, 1.0f, 1.0f,
    /* Green */
    0.0f, 1.0f, 0.0f, 1.0f,
    /* Red */
    1.0f, 0.0f, 0.0f,1.0f,
    /* Green */
    0.0f, 1.0f, 0.0f,1.0f,
    /* Blue */
    0.0f, 0.0f, 1.0f, 1.0f,
    /* Red */
    1.0f, 0.0f, 0.0f, 1.0f,
    /* Blue */
     0.0f, 0.0f, 1.0f,1.0f,
    /* Green */
    0.0f, 1.0f, 0.0f, 1.0f,
   
    };

 float VertexColors2[] ={

	   /* Red */
    1.0f, 0.0f, 0.0f, 1.0f,
       /* Red */
    1.0f, 0.0f, 0.0f, 1.0f,

    /* Green */
    0.0f, 1.0f, 0.0f, 1.0f,

     /* Green */
    0.0f, 1.0f, 0.0f, 1.0f,

    /* Blue */
    0.0f, 0.0f, 1.0f,1.0f,

     /* Blue */
    0.0f, 0.0f, 1.0f,1.0f,

    /* Red */
    1.0f, 0.0, 0.0f, 1.0f,
     /* Red */
    1.0f, 0.0, 0.0f, 1.0f,
    /* Blue */
    0.0f, 0.0f, 1.0f, 1.0f,
   /* Blue */
    0.0f, 0.0f, 1.0f, 1.0f,
    /* Green */
    0.0f, 1.0f, 0.0f, 1.0f,
     /* Green */
    0.0f, 1.0f, 0.0f, 1.0f,
    /* Red */
    1.0f, 0.0f, 0.0f,1.0f,
    /* Red */
    1.0f, 0.0f, 0.0f,1.0f,
    /* Green */
    0.0f, 1.0f, 0.0f,1.0f,
     /* Green */
    0.0f, 1.0f, 0.0f,1.0f,
    /* Blue */
    0.0f, 0.0f, 1.0f, 1.0f,
     /* Blue */
    0.0f, 0.0f, 1.0f, 1.0f,
    /* Red */
    1.0f, 0.0f, 0.0f, 1.0f,
     /* Red */
    1.0f, 0.0f, 0.0f, 1.0f,
    /* Blue */
     0.0f, 0.0f, 1.0f,1.0f,
        /* Green */
    0.0f, 1.0f, 0.0f, 1.0f,
     /* Blue */
     0.0f, 0.0f, 1.0f,1.0f,

     /* Green */
    0.0f, 1.0f, 0.0f, 1.0f
};

void render(float w, float h)
{
  static float fAngle = 0.0f;
    fAngle += 0.01f;
	
 
    // Rotate and translate the model view matrix
      float matModelView[16] = {0};
    matModelView[ 0] = +cosf( fAngle );
    matModelView[ 2] = +sinf( fAngle );
    matModelView[ 5] = 1.0f;
    matModelView[ 8] = -sinf( fAngle );
    matModelView[10] = +cosf( fAngle );
     matModelView[12] = 1.5f;
    matModelView[14] = -6.0f;
    matModelView[15] = 1.0f;


    // Build a perspective projection matrix
    float matProj[16] = {0};
    matProj[ 0] = cosf( 0.5f ) / sinf( 0.5f );
    matProj[ 5] = matProj[0] * (w/h) ;
    matProj[10] = -( 10.0f ) / ( 9.0f );
    matProj[11] = -1.0f;
    matProj[14] = -( 10.0f ) / ( 9.0f );


   // Clear the colorbuffer and depth-buffer
    glClearColor( 0.0f, 0.0f, 0.5f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Set some state
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );

    // Set the shader program
    glUseProgram( g_hShaderProgram );
    glUniformMatrix4fv( g_hModelViewMatrixLoc, 1, 0, matModelView );
    glUniformMatrix4fv( g_hProjMatrixLoc,      1, 0, matProj );

    // Bind the vertex attributes
    glVertexAttribPointer( g_hVertexLoc, 3, GL_FLOAT, 0, 0, VertexPositions );
    glEnableVertexAttribArray( g_hVertexLoc );

    glVertexAttribPointer( g_hColorLoc, 4, GL_FLOAT, 0, 0, VertexColors );
    glEnableVertexAttribArray( g_hColorLoc );


   glDrawArrays( GL_TRIANGLES, 0, 12 );


    


   matModelView[12] = -1.5f;
 // Set the shader program
    
    glUniformMatrix4fv( g_hModelViewMatrixLoc, 1, 0, matModelView );
    

    // Bind the vertex attributes
    glVertexAttribPointer( g_hVertexLoc, 3, GL_FLOAT, 0, 0, VertexPositions2 );
   

    glVertexAttribPointer( g_hColorLoc, 4, GL_FLOAT, 0, 0, VertexColors2 );
   


    /* Drawing Using Triangle strips, draw triangle strips using 4 vertices */
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
    glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);
    glDrawArrays(GL_TRIANGLE_STRIP, 12, 4);
    glDrawArrays(GL_TRIANGLE_STRIP, 16, 4);
    glDrawArrays(GL_TRIANGLE_STRIP, 20, 4);

 // Cleanup
    glDisableVertexAttribArray( g_hVertexLoc );
    glDisableVertexAttribArray( g_hColorLoc );
}


int init(void)
{
	printf("entering init\n");
	
	EGLint configAttribs[] =
	{
		EGL_RED_SIZE,       8,
		EGL_GREEN_SIZE,     8,
		EGL_BLUE_SIZE,      8,
		EGL_ALPHA_SIZE,     EGL_DONT_CARE,
		EGL_DEPTH_SIZE,     24,
		EGL_STENCIL_SIZE,   EGL_DONT_CARE,
		EGL_SAMPLE_BUFFERS, EGL_DONT_CARE,
		EGL_SAMPLES,        EGL_DONT_CARE,
		EGL_SURFACE_TYPE,   EGL_WINDOW_BIT,
		EGL_NONE
	};

	EGLint ctxAttribs[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

	EGLConfig configs[10];
	EGLint matchingConfigs;

	display = fbGetDisplay();

	{
	int w, h, t, l;
	//pthread_t pid;

	fbGetDisplayGeometry(display, &w, &h);

	window = fbCreateWindow(display, t, l, 1280 , 1024);

	//pthread_create(&pid, NULL, &InputThread, NULL);
	}
	eglDisplay = eglGetDisplay(display);
	if (!eglInitialize(eglDisplay, NULL, NULL))
	{
		return 1;
	}

	if (!eglChooseConfig(eglDisplay, configAttribs, &configs[0], 10, &matchingConfigs))
	{
		return 1;
	}

	if (matchingConfigs < 1)
	{
		return 1;
	}

	eglSurface = eglCreateWindowSurface(eglDisplay, configs[0], window, configAttribs);
	if (eglSurface == EGL_NO_SURFACE)
	{
		return 1;
	}

	eglContext = eglCreateContext(eglDisplay, configs[0], NULL, ctxAttribs);
	if (eglContext == EGL_NO_CONTEXT)
	{
		return 1;
	}

	eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
	
	GLfloat xmin, xmax, ymin, ymax;
	EGLint h, w;	
	eglQuerySurface(eglDisplay, eglSurface, EGL_WIDTH, &w);
	eglQuerySurface(eglDisplay, eglSurface, EGL_HEIGHT, &h);
    	
    	ymax = 0.1f * tan(45.0f * M_PI/360.0f);
    	ymin = -ymax;
	
    	xmin = ymin * ((GLfloat)w/(GLfloat)h);
    	xmax = ymax * ((GLfloat)w/(GLfloat)h);

	 {
        // Compile the shaders
        GLuint hVertexShader = glCreateShader( GL_VERTEX_SHADER );
        glShaderSource( hVertexShader, 1, &g_strVertexShader, NULL );
        glCompileShader( hVertexShader );

        // Check for compile success
        GLint nCompileResult = 0;
        glGetShaderiv( hVertexShader, GL_COMPILE_STATUS, &nCompileResult );
        if( 0 == nCompileResult )
        {
            char  strLog[1024];
            GLint nLength;
            glGetShaderInfoLog( hVertexShader, 1024, &nLength, strLog );
            return FALSE;
        }

        GLuint hFragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
        glShaderSource( hFragmentShader, 1, &g_strFragmentShader, NULL );
        glCompileShader( hFragmentShader );

        // Check for compile success
        glGetShaderiv( hFragmentShader, GL_COMPILE_STATUS, &nCompileResult );
        if( 0 == nCompileResult )
        {
            char  strLog[1024];
            GLint nLength;
            glGetShaderInfoLog( hFragmentShader, 1024, &nLength, strLog );
            return FALSE;
        }

        // Attach the individual shaders to the common shader program
        g_hShaderProgram = glCreateProgram();
        glAttachShader( g_hShaderProgram, hVertexShader );
        glAttachShader( g_hShaderProgram, hFragmentShader );

        // Init attributes BEFORE linking
        glBindAttribLocation( g_hShaderProgram, g_hVertexLoc,   "g_vPosition" );
        glBindAttribLocation( g_hShaderProgram, g_hColorLoc,    "g_vColor" );

        // Link the vertex shader and fragment shader together
        glLinkProgram( g_hShaderProgram );

        // Check for link success
        GLint nLinkResult = 0;
        glGetProgramiv( g_hShaderProgram, GL_LINK_STATUS, &nLinkResult );
        if( 0 == nLinkResult )
        {
            char strLog[1024];
            GLint nLength;
            glGetProgramInfoLog( g_hShaderProgram, 1024, &nLength, strLog );
            return FALSE;
        }

        // Get uniform locations
        g_hModelViewMatrixLoc = glGetUniformLocation( g_hShaderProgram, "g_matModelView" );
        g_hProjMatrixLoc      = glGetUniformLocation( g_hShaderProgram, "g_matProj" );

        glDeleteShader( hVertexShader );
        glDeleteShader( hFragmentShader );
	printf("end INIT\n");
    }
    	
    	return 1;
}

void Cleanup()
{
    
}

void deinit(void)
{
	Cleanup();
	eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	assert(eglGetError() == EGL_SUCCESS);
	eglTerminate(eglDisplay);
	assert(eglGetError() == EGL_SUCCESS);
	eglReleaseThread();
}

int main (void)
{
	assert( init() );
	while (currentFrame < 1000)
	{
		EGLint width = 0;
		EGLint height = 0;
		eglQuerySurface(eglDisplay, eglSurface, EGL_WIDTH, &width);
		eglQuerySurface(eglDisplay, eglSurface, EGL_HEIGHT, &height);
				
		render(width, height);
		currentFrame++;
		eglSwapBuffers(eglDisplay, eglSurface);
	}
	deinit();
return 0;
}

