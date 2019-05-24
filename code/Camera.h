#pragma once
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

class Camera {
public:
  Camera(const glm::vec3& pos, float fov, float aspect, float near, float far)
    : perspective_(glm::perspective(fov, aspect, near, far)),
     position_(pos), forward_(glm::vec3(0,0,-1)), up_(glm::vec3(0,1,0)) {}

  glm::mat4 view_projection() const {
    return perspective_ * glm::lookAt(position_, position_ + forward_, up_);
  }

private:
  glm::mat4 perspective_;
  glm::vec3 position_;
  glm::vec3 forward_;
  glm::vec3 up_;
};
