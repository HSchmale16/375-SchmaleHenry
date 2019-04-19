/* Filename: Main.cpp
Authors: Gary M. Zoppetti & Chad Hogg & Henry Schmale
Course: CSCI375
Assignment: A03 Camera
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
#include <cmath>

// Use GLEW so we can access the latest OpenGL functionality
// Always include GLEW before GLFW!
#include <GL/glew.h>
// Use GLFW so we can create windows and handle events in a
//   platform-independent way
#include <GLFW/glfw3.h>


/******************************************************************/
// Local includes
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Camera.h"
#include "KeyBuffer.h"

/******************************************************************/
// Type declarations/globals variables/prototypes

// We use one VAO for each object we draw
std::vector<Mesh*> g_vaos;
size_t activeMeshId = 0;

// Need a shader program to transform and light the primitives
ShaderProgram* g_shaderProgram;
ShaderProgram* g_normalShader;

KeyBuffer g_keybuffer;
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

void
dealWithKeys();

void
handleScrollEvents(GLFWwindow*, double, double);

void
updateProjection();

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
        dealWithKeys();
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
// #ifdef __APPLE__
    // Necessary on MacOS! Was needed in one case on Linux too.
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
// #endif
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
    glfwSetScrollCallback(window, handleScrollEvents);
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
    g_camera.setProjectionSymmetricPerspective(
                60.f, (float)width / (float)height, 5, 4000);
    updateProjection();
}

/******************************************************************/

void 
push_color(std::vector<float>& v) {
    static int colorNum = 0;
    v.push_back(sin(colorNum));
    colorNum += 1;
    v.push_back(cos(colorNum));
    colorNum += 1;
    v.push_back((colorNum & 7) == 0 ? 1.0f : 0.0f);
    colorNum += 1;
}

void
initScene ()
{
    g_vaos.push_back(new Mesh(AiScene("bear.obj")));

    g_vaos.push_back(new Mesh(AiScene("bear2.obj")));
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

    g_normalShader = new ShaderProgram ();
    g_normalShader->createVertexShader("Vec3Norm.vert");
    g_normalShader->createFragmentShader("Vec3.frag");
    g_normalShader->link();
}

/******************************************************************/

void
initCamera ()
{
    // Define the projection, which will remain constant
    float aspectRatio = 1200.0f / 900;
    // Near plane
    float nearZ = 0.01f;
    // Far plane
    float farZ = 4000.0f;

    g_camera = Camera(Vector3(0, 0, 12.f), Vector3(0.f, 0.f, 1.f), nearZ, farZ, aspectRatio, 50.0f);
    // Enable shader program so we can set uniforms
    g_shaderProgram->enable ();
    g_shaderProgram->setUniformMatrix ("uProjection", g_camera.getProjectionMatrix());

    g_normalShader->enable ();
    g_normalShader->setUniformMatrix("uProjection", g_camera.getProjectionMatrix());
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

    
    // Set shader uniforms
    // Only the model-view matrix needs set, since the projection is
    //   already set and it will persist.
    // Create view matrix
    Transform view = g_camera.getViewMatrix();
    //g_shaderProgram->setUniformMatrix ("uModelView", modelView);

    for (auto mesh : g_vaos) {
        if (mesh->getUsesNormals()) {
            mesh->draw(g_normalShader, view);
        } else {
            mesh->draw(g_shaderProgram, view);
        }
    }

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
    switch(action) {
        case GLFW_PRESS:
            g_keybuffer.setKeyDown(key);
            if ((modifiers & GLFW_MOD_SHIFT) == GLFW_MOD_SHIFT) {
                if (key == GLFW_KEY_COMMA) {
                    activeMeshId = (activeMeshId - 1) % g_vaos.size();
                    printf("Previous Mesh (ID=%ld)\n", activeMeshId);
                }
                if (key == GLFW_KEY_PERIOD) {
                    activeMeshId = (activeMeshId + 1) % g_vaos.size();
                    printf("Next Mesh (ID=%ld)\n", activeMeshId);
                }
            }
            break;
        case GLFW_RELEASE:
            g_keybuffer.setKeyUp(key);
            break;
    }
}

/******************************************************************/

void
releaseGlResources ()
{
    // Delete OpenGL resources, particularly important if program will
    //   continue running
    delete g_shaderProgram;
    delete g_normalShader;
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

void
updateProjection() {

    Matrix4 proj = g_camera.getProjectionMatrix();
    g_shaderProgram->enable();
    g_shaderProgram->setUniformMatrix("uProjection", proj);
    g_shaderProgram->disable();

    g_normalShader->enable();
    g_normalShader->setUniformMatrix("uProjection", proj);
    g_normalShader->disable();
}

void
dealWithKeys() 
{
    // Translate camera/eye point using WASD keys
    const float MOVEMENT_DELTA = 1.0f;
    if (g_keybuffer.isKeyDown(GLFW_KEY_W))
        g_camera.moveBack(-MOVEMENT_DELTA);
    else if (g_keybuffer.isKeyDown(GLFW_KEY_S))
        g_camera.moveBack(MOVEMENT_DELTA);

    // A & D
    if (g_keybuffer.isKeyDown(GLFW_KEY_A))
        g_camera.moveRight(-MOVEMENT_DELTA);
    else if (g_keybuffer.isKeyDown(GLFW_KEY_D))
        g_camera.moveRight(MOVEMENT_DELTA);

    // C & F
    if (g_keybuffer.isKeyDown(GLFW_KEY_C))
        g_camera.moveUp(-MOVEMENT_DELTA);
    else if (g_keybuffer.isKeyDown(GLFW_KEY_F))
        g_camera.moveUp(MOVEMENT_DELTA);

    // ROTATION
    // J & L - yaw
    if (g_keybuffer.isKeyDown(GLFW_KEY_J))
        g_camera.yaw(MOVEMENT_DELTA);
    else if (g_keybuffer.isKeyDown(GLFW_KEY_L))
        g_camera.yaw(-MOVEMENT_DELTA);
   

    // I & K - PITCH
    if (g_keybuffer.isKeyDown(GLFW_KEY_I))
        g_camera.pitch(MOVEMENT_DELTA);
    else if (g_keybuffer.isKeyDown(GLFW_KEY_K))
        g_camera.pitch(-MOVEMENT_DELTA);
   
    // N & M - ROLL 
    if (g_keybuffer.isKeyDown(GLFW_KEY_N))
       g_camera.roll(MOVEMENT_DELTA);
    else if (g_keybuffer.isKeyDown(GLFW_KEY_M))
       g_camera.roll(-MOVEMENT_DELTA); 

    // R - Reset
    if (g_keybuffer.isKeyDown(GLFW_KEY_R))
        g_camera.reset();

    // MESH CONTROLS
    if (g_keybuffer.isKeyDown(GLFW_KEY_1)) {
        g_vaos[activeMeshId]->moveRight(MOVEMENT_DELTA);
    }

    if (g_keybuffer.isKeyDown(GLFW_KEY_2)) {
        g_vaos[activeMeshId]->moveUp(MOVEMENT_DELTA);
    }

    if (g_keybuffer.isKeyDown(GLFW_KEY_3)) {
        g_vaos[activeMeshId]->moveWorld(MOVEMENT_DELTA, Vector3(-1, -1, -1));
    }

    if (g_keybuffer.isKeyDown(GLFW_KEY_4)) {
        g_vaos[activeMeshId]->pitch(MOVEMENT_DELTA);
    }

    if (g_keybuffer.isKeyDown(GLFW_KEY_5)) {
        g_vaos[activeMeshId]->yaw(MOVEMENT_DELTA); 
    } 

    if (g_keybuffer.isKeyDown(GLFW_KEY_6)) {
        g_vaos[activeMeshId]->roll(MOVEMENT_DELTA);
    }

    if (g_keybuffer.isKeyDown(GLFW_KEY_7)) {
        g_vaos[activeMeshId]->alignWithWorldY();
    }

    if (g_keybuffer.isKeyDown(GLFW_KEY_8)) {
        g_vaos[activeMeshId]->scaleLocal(1.1f);
    }

    if (g_keybuffer.isKeyDown(GLFW_KEY_9)) {
        g_vaos[activeMeshId]->scaleWorld(1.1f);
    }

    if (g_keybuffer.isKeyDown(GLFW_KEY_0)) {
        g_vaos[activeMeshId]->shearLocalXByYz(1.1f, 1.2f);
    }

    // Camera projection types
    if (g_keybuffer.isKeyDown(GLFW_KEY_P)) {
        g_camera.setProjectionSymmetricPerspective(
                60.f, 1200.f / 900.f, 5, 4000);
        updateProjection();
    }

    if (g_keybuffer.isKeyDown(GLFW_KEY_LEFT_BRACKET)) {
        g_camera.setProjectionAsymmetricPerspective(
                -10, 20, -30, 40, 5, 4000);
        updateProjection();
    }

    if (g_keybuffer.isKeyDown(GLFW_KEY_O)) {
        g_camera.setProjectionOrthographic(-10, 20, -30, 40, 5, 4000);
        updateProjection();
    }
}

void
handleScrollEvents(GLFWwindow* wnd, double xoff, double yoff) {
    printf("scroll x = %lf, y = %lf\n", xoff, yoff);
    g_camera.zoom(yoff);
    updateProjection();
}

