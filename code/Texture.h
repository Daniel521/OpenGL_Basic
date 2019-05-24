#pragma once
#include <string>
#include <GL/glew.h>

class Texture {
public:
  Texture(const std::string& file_name);
  virtual ~Texture();

  void bind(unsigned int unit);
private:
  GLuint texture_;
};
