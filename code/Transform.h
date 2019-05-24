#pragma once
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>


class Transform {
public:
  Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scaling = glm::vec3(1.0,1.0,1.0))
    : pos_(pos), rot_(rot), scale_(scaling) {

  }
  virtual ~Transform() {}

  glm::mat4 model() const {
    glm::mat4 pos_matrix = glm::translate(pos_);
    glm::mat4 rot_x_matrix = glm::rotate(rot_.x,glm::vec3(1,0,0));
    glm::mat4 rot_y_matrix = glm::rotate(rot_.y,glm::vec3(0,1,0));
    glm::mat4 rot_z_matrix = glm::rotate(rot_.z,glm::vec3(0,0,1));
    glm::mat4 scale_matrix = glm::scale(scale_);

    glm::mat4 rot_matrix = rot_z_matrix * rot_y_matrix * rot_x_matrix;

    return pos_matrix * rot_matrix * scale_matrix;
  }

  glm::vec3& position() {return pos_;}
  glm::vec3& rotation() {return rot_;}
  glm::vec3& scale()    {return scale_;}

  void position(const glm::vec3& position)  {pos_ = position;}
  void rotation(const glm::vec3& rotation)  {rot_ = rotation;}
  void scale(const glm::vec3& scaling) {scale_ = scaling;}

private:
  glm::vec3 pos_;
  glm::vec3 rot_;
  glm::vec3 scale_;
};
