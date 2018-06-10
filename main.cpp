#define GLEW_STATIC
#include <GL/glew.h>
// Need to include glew.h first
#include <GLFW/glfw3.h>
// This means we'll be using OpenGL 3.0, which is very general.
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <cerrno>
#include <math.h>


void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
std::string slurp(const char *filename);

int main() {
  const GLfloat vertices[] = {
    -.5f, -.5f, 0.0f,
    .5f, -.5f, 0.0f,
    0.0f, .5f, 0.0f,
  
    -1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    0.0f, .7f, 0.0f
  };

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  // Load our shaders
  std::string vertex = slurp("vertex.glsl");
  std::string fragment = slurp("fragment.glsl");

  // Create our window and check for problems
  GLFWwindow *window = glfwCreateWindow(800, 600, "Learn OpenGL", nullptr, nullptr);
  if( window == nullptr ) {
    glfwTerminate();
    puts("Failed to create OpenGL window!");
    return -1;
  }
  // Now we can grab the main thread
  glfwMakeContextCurrent(window);
  // We want GLEW to wrangle in the OpenGL functions for us
  glewExperimental = GL_TRUE;
  if( glewInit() != GLEW_OK ) {
    puts("Failed to initialize GLEW!");
    return -1;
  }
  // Viewport starting at the lower left and stretching the entire size of the window
  glViewport(0,0,800,600);
  // Key handling callback
  glfwSetKeyCallback(window, keyCallback);
  // Window clearing color
  glClearColor(.2f,.3f,.3f,1.0f);
  // Render setup
  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
    GLuint VBO;
    glGenBuffers(1, &VBO);
    // We want to set the current array buffer to our VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Now send our vertices over the to the GPU, in VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Configure OpenGL to use our vertex array like we intend
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
  glBindVertexArray(0); // Unbind vertex array so it isn't accidentally reconfigured later
  // Compile the vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  const char *a = vertex.data();
  glShaderSource(vertexShader, 1, &a, NULL);
  glCompileShader(vertexShader);
  // Compile the fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  const char *b = fragment.data();
  glShaderSource(fragmentShader, 1, &b, NULL);
  glCompileShader(fragmentShader);
  // Now tie together the shader program
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram); // We'll only be using the one program but it's obvious you could have more
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader); 
  // Now find the green uniform
  GLint greenLocation = glGetUniformLocation(shaderProgram, "green");
  // Window loop
  while(!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(VAO);
    glUniform1f(greenLocation, (sin(glfwGetTime()) / 2) + 0.0f);
    glDrawArrays(GL_TRIANGLES, 0, 6); 
    glfwSwapBuffers(window);
  }
  glfwTerminate(); 
  return 0;
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

std::string slurp(const char *filename) {
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if(in) {
    std::ostringstream contents;
    contents << in.rdbuf();
    in.close();
    return contents.str();
  }
  throw(errno);
}
