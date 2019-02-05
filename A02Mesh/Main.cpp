/* 
  Filename: Main.cpp
  Authors: Gary M. Zoppetti & Chad Hogg & Henry Schmale
  Course: CSCI375
  Assignment: A02Mesh
  Description: A beginning OpenGL program that uses OpenGL 3.3 to draw a 
    triangle. The triangle is now specified with 3D coordinates.
   A virtual camera has been defined and limited key-based movement has been 
    added.
*/

/******************************************************************/
// System includes
#include <cstdio>
#include <cstdlib>
#include <vector>

// Use GLEW so we can access the latest OpenGL functionality
// Always include GLEW before GLFW!
#include <GL/glew.h>
// Use GLFW so we can create windows and handle events in a
//   platform-independent way
#include <GLFW/glfw3.h>

// GLM is a header-only library, so we do not need to link to it
// It provides matrix classes and mathematical functions
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
// Need for "value_ptr", which allows us to get a pointer from a matrix
#include <glm/gtc/type_ptr.hpp>
// Transforms like lookat, perspective, rotate, scale, translate
#include <glm/gtc/matrix_transform.hpp>

/******************************************************************/
// Local includes
#include "ShaderProgram.h"
#include "Mesh.h"

/******************************************************************/
// Type declarations/globals variables/prototypes

// We use one VAO for each object we draw
std::vector<Mesh*> g_vaos;

// Need a shader program to transform and light the primitives
ShaderProgram* g_shaderProgram;

// A type for a virtual camera, or eye point
struct Camera
{
  // Location of camera
  glm::vec3 position;
  // Point camera is looking at
  glm::vec3 at;
  // Camera's up vector
  glm::vec3 up;
  // Projection (defines view volume)
  glm::mat4 projection;
};

Camera g_camera;

/******************************************************************/

// Initializes all of the libraries.
void
init (GLFWwindow*& window);

// Initializes the GLFW library -- should only be called by init().
void
initGlfw ();

// Initializes the GLEW library -- should only be called by init().
void
initGlew ();

// Creates and initializes the window -- should only be called by init().
void
initWindow (GLFWwindow*& window);

// Re-renders the window -- should be called when size changes.
void
resetViewport (GLFWwindow* window, int width, int height);

// Creates the geometric objects -- should only be called by init().
void
initScene ();

// Sets up our shader programs -- should only be called by init().
void
initShaders ();

// Initializes the camera -- should only be called by init().
void
initCamera ();

// Move geometric objects around using game logic.
void
updateScene (double time);

// Draws the scene onto the window.
void
drawScene (GLFWwindow* window);

// Respond to any user input.
void
processKeys (GLFWwindow* window, int key, int scanCode, int action,
	     int modifiers);

// Clean up as program exits.
void
releaseGlResources ();

// Prints an error from GLFW.
void
outputGlfwError (int error, const char* description);

/******************************************************************/

int
main (int argc, char* argv[])
{
  GLFWwindow* window;
  init (window);

  // Game/render loop
  double previousTime = glfwGetTime ();
  while (!glfwWindowShouldClose (window))
  {
    double currentTime = glfwGetTime ();
    // Compute frame times, which we can use later for frame rate computation,
    //   animation, and physics.
    double deltaTime = currentTime - previousTime;
    previousTime = currentTime;
    updateScene (deltaTime);
    drawScene (window);
    // Process events in the event queue, which results in callbacks
    //   being invoked.
    glfwPollEvents ();
  }

  releaseGlResources ();
  // Destroying the window destroys the OpenGL context
  glfwDestroyWindow (window);
  glfwTerminate ();

  return EXIT_SUCCESS;
}

/******************************************************************/

void
init (GLFWwindow*& window)
{
  // Always initialize GLFW before GLEW
  initGlfw ();
  initWindow (window);
  initGlew ();
  initShaders ();
  initCamera ();
  initScene ();
}

/******************************************************************/

void
initGlfw ()
{
  glfwSetErrorCallback (outputGlfwError);
  if (!glfwInit ())
  {
    fprintf (stderr, "Failed to init GLFW -- exiting\n");
    exit (EXIT_FAILURE);
  }
}

/******************************************************************/

void
initWindow (GLFWwindow*& window)
{
  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
  // Necessary on MacOS! Was needed in one case on Linux too.
  glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
  window = glfwCreateWindow (1200, 900, "OpenGL Engine", nullptr, nullptr);
  if (window == nullptr)
  {
    fprintf (stderr, "Failed to init the window -- exiting\n");
    glfwTerminate ();
    exit (EXIT_FAILURE);
  }
  glfwSetWindowPos (window, 200, 100);

  glfwMakeContextCurrent (window);
  // Swap buffers after 1 frame
  glfwSwapInterval (1);
  glfwSetKeyCallback (window, processKeys);
  glfwSetFramebufferSizeCallback (window, resetViewport);

  // Specify background color
  glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
  // Enable depth testing so occluded surfaces aren't drawn
  glEnable (GL_DEPTH_TEST);
  // Enable the culling of back-facing triangles
  // A triangle must be wound CCW in window coordinates to be front facing
  // If it is wound CW it is back facing and will NOT be displayed!
  glEnable (GL_CULL_FACE);
  // The next two setting are default, but we'll be explicit.
  glFrontFace (GL_CCW);
  glCullFace (GL_BACK);
  // Set initial viewport size
  int width, height;
  glfwGetFramebufferSize (window, &width, &height);
  glViewport (0, 0, width, height);
}

/******************************************************************/

void
initGlew ()
{
  GLenum status = glewInit ();
  if (status != GLEW_OK)
  {
    fprintf (stderr, "Failed to initialize GLEW -- exiting"
	     " (%s).\n",
	     glewGetErrorString (status));
    exit (EXIT_FAILURE);
  }
  const GLubyte* version = glewGetString (GLEW_VERSION);
  fprintf (stderr, "Using GLEW version %s.\n", version);
  version = glGetString (GL_VERSION);
  fprintf (stderr, "Using OpenGL version %s\n", version);
}

/******************************************************************/

void
resetViewport (GLFWwindow* window, int width, int height)
{
  // Render into entire window
  // Origin for window coordinates is lower-left of window
  glViewport (0, 0, width, height);
}

/******************************************************************/

void
initScene ()
{
  // These control how our C++ program communicates with the shaders
/*
  const GLint POSITION_ATTRIB_INDEX = 0;
  const GLint COLOR_ATTRIB_INDEX = 1;

  const unsigned NUM_VAOS = 1;
  g_vaos.resize (NUM_VAOS);
  glGenVertexArrays (NUM_VAOS, g_vaos.data ());

  //////////////////////////////
  // Set up triangle geometry
  glBindVertexArray (g_vaos[0]);
  GLuint triVbo;
  glGenBuffers (1, &triVbo);
  glBindBuffer (GL_ARRAY_BUFFER, triVbo);
  // 3 3D points, followed by 3 RGB colors
*/
  std::vector<float> triVertices {
      0.0f, 5.0f, 0.0f,   // 3-d coordinates of first vertex (X, Y, Z)
      1.0f, 0.0f, 0.0f,   // color of first vertex (R, G, B)
      -5.0f, -5.0f, 0.0f, // 3-d coordinates of second vertex (X, Y, Z)
      0.0f, 1.0f, 0.0f,   // color of second vertex (R, G, B)
      5.0f, -5.0f, 0.0f,  // 3-d coordinates of third vertex (X, Y, Z)
      0.0f, 0.0f, 1.0f    // color of third vertex (R, G, B)
      };

    g_vaos.push_back(new Mesh());
    
    g_vaos[0]->addGeometry(triVertices);

/*
  glBufferData (GL_ARRAY_BUFFER, triVertices.size () * sizeof(float),
		triVertices.data (),
		GL_STATIC_DRAW);
  // Tell the shaders how the data in the array is laid out
  glEnableVertexAttribArray (POSITION_ATTRIB_INDEX);
  // Positions have 3 parts, each are floats, and start at beginning of array
  glVertexAttribPointer (POSITION_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, 0,
			 reinterpret_cast<void*> (0));
  glEnableVertexAttribArray (COLOR_ATTRIB_INDEX);
  // Colors have 3 parts, each are floats, and start at 10th position in array
  glVertexAttribPointer (COLOR_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, 0,
			 reinterpret_cast<void*> (9 * sizeof(float)));
  glBindVertexArray (0);
*/
}

/******************************************************************/

void
initShaders ()
{
  // Create shader programs, which consist of linked shaders.
  // No need to use the program until we draw or set uniform variables.
  g_shaderProgram = new ShaderProgram ();
  g_shaderProgram->createVertexShader ("Vec3.vert");
  g_shaderProgram->createFragmentShader ("Vec3.frag");
  g_shaderProgram->link ();
}

/******************************************************************/

void
initCamera ()
{
  // Define the projection, which will remain constant
  float verticalFov = glm::radians (50.0f);
  float aspectRatio = 1200.0f / 900;
  // Near plane
  float nearZ = 0.01f;
  // Far plane
  float farZ = 40.0f;
  g_camera.projection = glm::perspective (verticalFov, aspectRatio, nearZ,
					  farZ);
  // Enable shader program so we can set uniforms
  g_shaderProgram->enable ();
  g_shaderProgram->setUniformMatrix ("uProjection", g_camera.projection);
  // Define the camera's coordinate system
  g_camera.position = glm::vec3 (0, 0, 12.0f);
  g_camera.at = glm::vec3 (0, 0, 0);
  g_camera.up = glm::vec3 (0, 1, 0);
}

/******************************************************************/

void
updateScene (double time)
{
  // No updates in this simple program.
}

/******************************************************************/

void
drawScene (GLFWwindow* window)
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Iterate over each object in scene and draw it
  // The shader program is already enabled, but we do not want to
  //   make that assumption in general.
  g_shaderProgram->enable ();
  // Set shader uniforms
  // Only the model-view matrix needs set, since the projection is
  //   already set and it will persist.
  // Create view matrix
  glm::mat4 modelView = glm::lookAt (g_camera.position, g_camera.at, g_camera.up);
  g_shaderProgram->setUniformMatrix ("uModelView", modelView);

  for (auto mesh : g_vaos) {
    mesh->draw();
  }
  g_shaderProgram->disable ();

  // Swap the front and back buffers.
  // We draw to the back buffer, which is then swapped with the front
  //   for display.
  glfwSwapBuffers (window);
}


/******************************************************************/

void
processKeys (GLFWwindow* window, int key, int scanCode, int action,
	     int modifiers)
{
  // Actions are GLFW_PRESS, GLFW_RELEASE, and GLFW_REPEAT
  // Exit if ESC is pressed
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose (window, GL_TRUE);
    return;
  }

  // Translate camera/eye point using WASD keys
  const float MOVEMENT_DELTA = 1.0f;
  if (key == GLFW_KEY_W && action == GLFW_PRESS)
    g_camera.position.z -= MOVEMENT_DELTA;
  else if (key == GLFW_KEY_S && action == GLFW_PRESS)
    g_camera.position.z += MOVEMENT_DELTA;
  // TODO: Add support for movement along x and y axes
  if (key == GLFW_KEY_A && action == GLFW_PRESS)
    g_camera.position.x -= MOVEMENT_DELTA;
  else if (key == GLFW_KEY_D && action == GLFW_PRESS)
    g_camera.position.x += MOVEMENT_DELTA;
  
  if (key == GLFW_KEY_C && action == GLFW_PRESS)
    g_camera.position.y -= MOVEMENT_DELTA;
  else if (key == GLFW_KEY_F && action == GLFW_PRESS)
    g_camera.position.y += MOVEMENT_DELTA;
}

/******************************************************************/

void
releaseGlResources ()
{
  // Delete OpenGL resources, particularly important if program will
  //   continue running
  delete g_shaderProgram;
  for (auto mesh : g_vaos) {
    delete mesh;
  }
}

/******************************************************************/

void
outputGlfwError (int error, const char* description)
{
  fprintf (stderr, "GLFW error: %s, code %d\n", description, error);
}

/******************************************************************/
