#include <cassert>
#include <iostream>
#include "stb_image.h"
#include "Texture.h"


Texture::Texture(const std::string& file_name) {
  int width, height, num_components;
  unsigned char* img = stbi_load(file_name.c_str(), &width, &height, &num_components, 4);
  if (img == NULL) {
    std::cerr << "Texture loading failed: " << file_name << std::endl;
  }

  glGenTextures(1, &texture_);
  glBindTexture(GL_TEXTURE_2D, texture_);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);

  stbi_image_free(img);
}

Texture::~Texture() {
  glDeleteTextures(1, &texture_);
}

void Texture::bind(unsigned int unit) {
  assert(unit >= 0 && unit <= 31);
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, texture_);
}
