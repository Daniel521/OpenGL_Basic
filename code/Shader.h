#pragma once
#include <string>
#include <GL/glew.h>
#include "Transform.h"
#include "Camera.h"


class Shader {
public:
  enum { TRANSFORM_U, NUM_UNIFORMS };
  static const unsigned int NUM_SHADERS = 2;
public:
  Shader(const std::string& file_name);
  virtual ~Shader();

  void bind();
  void update(const Transform& transform, const Camera& camera);

private:
  GLuint program_;
  GLuint shaders_[NUM_SHADERS];
  GLuint uniforms_[NUM_UNIFORMS];

};
