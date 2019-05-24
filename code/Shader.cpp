#include <iostream>
#include <fstream>
#include "Shader.h"


static void check_shader_error(GLuint shader, GLuint flag, bool is_program, const std::string& error_message);
static std::string load_shader(const std::string& file_name);
static GLuint create_shader(const std::string& text, GLenum shader_type);

Shader::Shader(const std::string& file_name) {
  program_ = glCreateProgram();
  shaders_[0] = create_shader(load_shader(file_name + ".vertexshader"), GL_VERTEX_SHADER);
  shaders_[1] = create_shader(load_shader(file_name + ".fragmentshader"), GL_FRAGMENT_SHADER);

  for (unsigned int i = 0; i < NUM_SHADERS; ++i)
    glAttachShader(program_, shaders_[i]);

  glBindAttribLocation(program_, 0, "position");
  glBindAttribLocation(program_, 1, "tex_coord");
  glBindAttribLocation(program_, 2, "normal");

  glLinkProgram(program_);
  check_shader_error(program_, GL_LINK_STATUS, true, "Error: Program linking failed: ");

  glValidateProgram(program_);
  check_shader_error(program_, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");

  uniforms_[TRANSFORM_U] = glGetUniformLocation(program_, "transform");
}

Shader::~Shader() {
  for (unsigned int i = 0; i < NUM_SHADERS; ++i) {
    glDetachShader(program_, shaders_[i]);
    glDeleteShader(shaders_[i]);
  }
  glDeleteProgram(program_);
}

void Shader::bind() {
  glUseProgram(program_);
}

void Shader::update(const Transform& transform, const Camera& camera) {
  glm::mat4 model = camera.view_projection() * transform.model();
  glUniformMatrix4fv(uniforms_[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}


static std::string load_shader(const std::string& file_name) {
  std::ifstream file;
  file.open(file_name.c_str());

  std::string output;
  std::string line;
  if (file.is_open()) {
      while (file.good()) {
        getline(file,line);
        output.append(line + '\n');
      }
  }
  else {
    std::cerr << "Unable to load shader: " << file_name << std::endl;
  }
  return output;
}

static void check_shader_error(GLuint shader, GLuint flag, bool is_program, const std::string& error_message) {
  GLint success = 0;
  GLchar error[1024] = {0};

  if (is_program)
    glGetProgramiv(shader, flag, &success);
  else
    glGetShaderiv(shader, flag, &success);

  if (success == GL_FALSE) {
    if (is_program)
      glGetProgramInfoLog(shader, sizeof(error), NULL, error);
    else
      glGetShaderInfoLog(shader, sizeof(error), NULL, error);
    std::cerr << error_message << ": '" << error << "'" << std::endl;
  }
}

static GLuint create_shader(const std::string& text, GLenum shader_type) {
  GLuint shader = glCreateShader(shader_type);

  if (shader == 0)
    std::cerr << "Error: Shader creation failed!" << std::endl;

  const GLchar* shader_source_string[1];
  GLint shader_source_string_size[1];
  shader_source_string[0] = text.c_str();
  shader_source_string_size[0] = text.length();

  glShaderSource(shader, 1, shader_source_string, shader_source_string_size);
  glCompileShader(shader);

  check_shader_error(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed!");

  return shader;
}
