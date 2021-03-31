#include "GOWCamera.h"

using namespace GOW;

GOWOrthographicCamera::GOWOrthographicCamera()
:GOWCamera(glm::vec3(0, 0, -1), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0))
{
	UpdateProjectionMatrix();
}

GOWOrthographicCamera::GOWOrthographicCamera(const GOWOrthographicCamera& InCamera)
:GOWCamera(InCamera.Position, InCamera.Direction, InCamera.Up)
{
	Width = InCamera.Width;
	Height = InCamera.Height;
	NearPlane = InCamera.NearPlane;
	FarPlane = InCamera.FarPlane;

	UpdateProjectionMatrix();
}

GOWOrthographicCamera::GOWOrthographicCamera(glm::vec3 InPosition, glm::vec3 InDirection, glm::vec3 InUp)
:GOWCamera(InPosition, InDirection, InUp)
{
	UpdateProjectionMatrix();
}

GOWOrthographicCamera::GOWOrthographicCamera(glm::vec3 InPosition,
											glm::vec3 InDirection,
											glm::vec3 InUp,
											float InWidth,
											float InHeight,
											float InNearPlane,
											float InFarPlane)
:GOWCamera(InPosition, InDirection, InUp)
{
	Width = InWidth;
	Height = InHeight;
	NearPlane = InNearPlane;
	FarPlane = InFarPlane;

	UpdateProjectionMatrix();
}

GOWOrthographicCamera::~GOWOrthographicCamera()
{

}

void GOWOrthographicCamera::UpdateProjectionMatrix()
{
	ProjectionMatrix = glm::ortho(-Width * 0.5f, Width * 0.5f, -Height * 0.5f, Height * 0.5f, NearPlane, FarPlane);
}

std::vector<glm::vec3> GOWOrthographicCamera::CalculateFrustumPoints()
{
	std::vector<glm::vec4> Ndc = {
		glm::vec4(-1, -1, -1, 1),
		glm::vec4(1, -1, -1, 1),
		glm::vec4(1, 1, -1, 1),
		glm::vec4(-1, 1, -1, 1),
		glm::vec4(-1, -1, 1, 1),
		glm::vec4(1, -1, 1, 1),
		glm::vec4(1, 1, 1, 1),
		glm::vec4(-1, 1, 1, 1)
	};

	glm::mat4 Mat = glm::inverse(ProjectionMatrix * ViewMatrix);

	std::vector<glm::vec3> Ret(Ndc.size());

	for (uint32 i = 0; i < Ndc.size(); i++)
	{
		Ret[i] = glm::vec3(Mat * Ndc[i]);
	}

	return Ret;
}

std::vector<float> GOWOrthographicCamera::CalculateFrustumDistance(glm::vec3 InPoint)
{
	glm::vec3 CameraDirection = glm::normalize(Direction);

	std::vector<glm::vec3> CornerPoints = CalculateFrustumPoints();

	glm::vec3 LeftNormal = glm::normalize(glm::cross(CornerPoints[7] - CornerPoints[3], CornerPoints[0] - CornerPoints[3]));
	glm::vec3 RightNormal = glm::normalize(glm::cross(CornerPoints[1] - CornerPoints[2], CornerPoints[6] - CornerPoints[2]));
	glm::vec3 TopNormal = glm::normalize(glm::cross(CornerPoints[7] - CornerPoints[3], CornerPoints[2] - CornerPoints[3]));
	glm::vec3 BottomNormal = glm::normalize(glm::cross(CornerPoints[1] - CornerPoints[0], CornerPoints[4] - CornerPoints[0]));

	std::vector<float> Ret(6);
	Ret[0] = glm::dot(CornerPoints[3] - InPoint, -CameraDirection);
	Ret[1] = glm::dot(CornerPoints[7] - InPoint, CameraDirection);
	Ret[2] = glm::dot(CornerPoints[3] - InPoint, LeftNormal);
	Ret[3] = glm::dot(CornerPoints[2] - InPoint, RightNormal);
	Ret[4] = glm::dot(CornerPoints[3] - InPoint, TopNormal);
	Ret[5] = glm::dot(CornerPoints[0] - InPoint, BottomNormal);

	return Ret;
}

void GOWOrthographicCamera::UpdateCameraByBounding(GOWOrthographicCamera& InCamera, glm::vec3 InDirection, float InOffset)
{

}

void GOWOrthographicCamera::UpdateCameraByBounding(GOWPerspectiveGamera& InCamera, glm::vec3 InDirection, float InOffset)
{

}