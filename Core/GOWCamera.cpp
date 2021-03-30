#include "GOWCamera.h"

using namespace GOW;

GOWCamera::GOWCamera(glm::vec3 InPosition, glm::vec3 InDirection, glm::vec3 InUp)
{
	Position = InPosition;
	Direction = glm::normalize(InDirection);
	Right = glm::normalize(glm::cross(InDirection, glm::normalize(InUp)));
	Up = glm::normalize(glm::cross(Right, Direction));

	Width = 640.0f;
	Height = 480.0f;

	Fovy = (float)M_PI;

	NearPlane = 1.0f;
	FarPlane = 800.0f;

	UpdateViewMatrix();
}

GOWCamera::~GOWCamera()
{

}

void GOWCamera::UpdateViewMatrix()
{
	ViewMatrix = glm::lookAt(Position, Position + Direction, Up);
}

void GOWCamera::MoveUp(float InDelta)
{
	Position += glm::normalize(Up) * InDelta;
}

void GOWCamera::MoveRight(float InDelta)
{
	Position += glm::normalize(Right) * InDelta;
}

void GOWCamera::MoveForward(float InDelta)
{
	Position += glm::normalize(Direction) * InDelta;
}

void GOWCamera::MoveBy(float InX, float InY, float InZ)
{
	Position.x += InX;
	Position.y += InY;
	Position.z += InZ;
}

void GOWCamera::MoveBy(glm::vec3 InVector)
{
	Position += InVector;
}

void GOWCamera::Yaw(float InAngle)
{
	glm::mat3 RotationMatrix = glm::mat3(glm::rotate(InAngle, Up));

	Direction = glm::normalize(RotationMatrix * Direction);
	Right = glm::normalize(RotationMatrix * Right);
}

void GOWCamera::Roll(float InAngle)
{
	glm::mat3 RotationMatrix = glm::mat3(glm::rotate(InAngle, Direction));

	Up = glm::normalize(RotationMatrix * Up);
	Right = glm::normalize(RotationMatrix * Right);
}

void GOWCamera::Pitch(float InAngle)
{
	glm::mat3 RotationMatrix = glm::mat3(glm::rotate(InAngle, Right));
	Up = glm::normalize(RotationMatrix * Up);
	Direction = glm::normalize(RotationMatrix * Direction);
}