#include <iostream>
#include <GL/glew.h>
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

#define WIDTH 600
#define HEIGHT 400

int main() {

  Display display(WIDTH, HEIGHT, "Hello World!");
  Shader shader("./res/basic_shader");
  Vertex vertices[] = { Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5,1.0)),
                        Vertex(glm::vec3(-0.5,-0.5, 0), glm::vec2(0.0,0.0)),
                        Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0,0.0)) };
  unsigned int indices[] = {0, 1, 2};
  Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
  Mesh mesh2("./res/monkey3.obj");
  Texture texture("./res/bricks.jpg");
  Camera camera(glm::vec3(0,0,5), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
  Transform transform;

  float counter = 0.0f;

  while (!display.is_closed()) {
    display.clear(0.0f, 0.15f, 0.3f, 1.0f);

    float sin_counter = sinf(counter);
    float cos_counter = cosf(counter);

    transform.position().x = sin_counter;
    transform.position().z = cos_counter;
    transform.rotation().x = counter;
    transform.rotation().y = counter;
    transform.rotation().z = counter;



    shader.bind();
    texture.bind(0);
    shader.update(transform, camera);
    mesh2.draw();
    display.update();
    counter += 0.002f;
  }

  return 0;
}
