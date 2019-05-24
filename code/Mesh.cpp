#include <vector>
#include "Mesh.h"
#include "obj_loader.h"

Mesh::Mesh(Vertex* vertices, unsigned int num_vertices, unsigned int* indices, unsigned int num_indices) {
  IndexedModel model;

  for (unsigned int i = 0; i < num_vertices; ++i) {
    model.positions.push_back(vertices[i].pos());
    model.texCoords.push_back(vertices[i].tex_coord());
    model.normals.push_back(vertices[i].normal());
  }

  for (unsigned int i = 0; i < num_indices; ++i) {
    model.indices.push_back(indices[i]);
  }

  init_mesh(model);
}

Mesh::Mesh(const std::string& file_name) {
  IndexedModel model = OBJModel(file_name).ToIndexedModel();
  init_mesh(model);
}

Mesh::~Mesh() {
  glDeleteVertexArrays(1, &vertex_array_object_);
}

void Mesh::draw() {
  glBindVertexArray(vertex_array_object_);
  glDrawElements(GL_TRIANGLES, draw_count_, GL_UNSIGNED_INT, 0);
  //glDrawArrays(GL_TRIANGLES, 0, draw_count_);
  glBindVertexArray(0);
}

void Mesh::init_mesh(const IndexedModel& model) {
  draw_count_ = model.indices.size();

  glGenVertexArrays(1, &vertex_array_object_);
  glBindVertexArray(vertex_array_object_);

  glGenBuffers(NUM_BUFFERS, vertex_array_buffer_);

  glBindBuffer(GL_ARRAY_BUFFER, vertex_array_buffer_[POSITION_VB]);
  glBufferData(GL_ARRAY_BUFFER, model.positions.size()*sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(POSITION_VB);
  glVertexAttribPointer(POSITION_VB, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, vertex_array_buffer_[TEX_COORD_VB]);
  glBufferData(GL_ARRAY_BUFFER, model.positions.size()*sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(TEX_COORD_VB);
  glVertexAttribPointer(TEX_COORD_VB, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, vertex_array_buffer_[NORMAL_VB]);
  glBufferData(GL_ARRAY_BUFFER, model.normals.size()*sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_array_buffer_[INDEX_VB]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size()*sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

  glBindVertexArray(0);
}
