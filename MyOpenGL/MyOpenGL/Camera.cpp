#include "Camera.h"

//look at version
Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp) {

	Camera::Position = position;
	Camera::WorldUp = worldUp;
	Camera::Forward = glm::normalize(target - position);
	Camera::Right = glm::normalize(glm::cross(Camera::Forward, Camera::WorldUp));
	Camera::Up = glm::normalize(glm::cross(Camera::Right, Camera::Forward));
}

//Euler version
Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp) {
	Camera::Position = position;
	Camera::WorldUp = worldUp;
	Camera::Pitch = pitch;
	Camera::Yaw = yaw;

	Camera::Forward.x = glm::cos(Camera::Pitch) * glm::sin(Camera::Yaw);
	Camera::Forward.y = glm::sin(Camera::Pitch);
	Camera::Forward.z = glm::cos(Camera::Pitch) * glm::cos(Camera::Yaw);
	Camera::Right = glm::normalize(glm::cross(Camera::Forward, Camera::WorldUp));
	Camera::Up = glm::normalize(glm::cross(Camera::Right, Camera::Forward));
}

glm::mat4  Camera::GetViewMatrix() {

	return glm::lookAt(Camera::Position, Camera::Position + Camera::Forward, Camera::WorldUp);
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY) {
	Camera::Pitch -= deltaY;
	Camera::Yaw -= deltaX;

	UpdateCameraPosition();
}

void Camera::UpdateCameraPosition() {
	Camera::Forward.x = glm::cos(Camera::Pitch) * glm::sin(Camera::Yaw);
	Camera::Forward.y = glm::sin(Camera::Pitch);
	Camera::Forward.z = glm::cos(Camera::Pitch) * glm::cos(Camera::Yaw);
	Camera::Right = glm::normalize(glm::cross(Camera::Forward, Camera::WorldUp));
	Camera::Up = glm::normalize(glm::cross(Camera::Forward, Camera::Right));
}
