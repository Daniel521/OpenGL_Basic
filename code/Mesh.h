#pragma once
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "obj_loader.h"

class Vertex {
public:
  Vertex(const glm::vec3& pos, const glm::vec2& tex_coord, const glm::vec3& norm = glm::vec3(0,0,0))
  : pos_(pos), tex_coord_(tex_coord), normal_(norm) {}

  inline glm::vec3& pos() {return pos_;}
  inline glm::vec2& tex_coord() {return tex_coord_;}
  inline glm::vec3& normal() {return normal_;}

private:
  glm::vec3 pos_;
  glm::vec2 tex_coord_;
  glm::vec3 normal_;
};

class Mesh {
public:
  enum {
    POSITION_VB,
    TEX_COORD_VB,
    NORMAL_VB,
    INDEX_VB,
    NUM_BUFFERS};
public:
  Mesh(Vertex* vertices, unsigned int num_vertices, unsigned int* indices, unsigned int num_indices);
  Mesh(const std::string& file_name);
  virtual ~Mesh();

  void draw();
private:
  void init_mesh(const IndexedModel& model);

private:
  GLuint vertex_array_object_;
  GLuint vertex_array_buffer_[NUM_BUFFERS];
  unsigned int draw_count_;
};
