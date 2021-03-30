#include "GOWCamera.h"

using namespace GOW;

GOWPerspectiveGamera::GOWPerspectiveGamera()
:GOWCamera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f))
{
	UpdateProjectionMatrix();
}

GOWPerspectiveGamera::GOWPerspectiveGamera(const GOW::GOWPerspectiveGamera& InCamera)
:GOWCamera(InCamera.Position, InCamera.Direction, InCamera.Up)
{
	Fovy = InCamera.Fovy;
	Width = InCamera.Width;
	Height = InCamera.Height;
	NearPlane = InCamera.NearPlane;
	FarPlane = InCamera.FarPlane;
	UpdateProjectionMatrix();
}

GOWPerspectiveGamera::GOWPerspectiveGamera(glm::vec3 InPosition, glm::vec3 InDirection, glm::vec3 InUp)
:GOWCamera(InPosition, InDirection, InUp)
{

}

GOWPerspectiveGamera::GOWPerspectiveGamera(glm::vec3 InPosition,
		glm::vec3 InDirection,
		glm::vec3 InUp,
		float InFovy,
		float InWidth,
		float InHeight,
		float InNearPlane,
		float InFarPlane)
:GOWCamera(InPosition, InDirection, InUp)
{
	Fovy = InFovy;
	Width = InWidth;
	Height = InHeight;
	NearPlane = InNearPlane;
	FarPlane = InFarPlane;
	UpdateProjectionMatrix();
}

GOWPerspectiveGamera::~GOWPerspectiveGamera()
{

}

void GOWPerspectiveGamera::UpdateProjectionMatrix()
{
	ProjectionMatrix = glm::perspective(Fovy, (GLfloat)Width / (GLfloat)Height, NearPlane, FarPlane);
}

std::vector<glm::vec3> GOWPerspectiveGamera::CalculateFrustumPoints()
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

	glm::vec4 Tmp;
	std::vector<glm::vec3> Ret(Ndc.size());

	for (uint32 i = 0; i < Ndc.size(); i++)
	{
		Tmp = Mat * Ndc[i];
		Ret[i] = glm::vec3(Tmp) / Tmp[3];
	}

	return Ret;
}

std::vector<float> GOWPerspectiveGamera::CalculateFrustumDistance(glm::vec3 InPoint)
{
	glm::vec3 CameraDirection = glm::normalize(Direction);

	std::vector<glm::vec3> CornerPoints = CalculateFrustumPoints();

	glm::vec3 LeftNormal = glm::normalize(glm::cross(CornerPoints[7]- CornerPoints[3],
													CornerPoints[0] - CornerPoints[3]));
	glm::vec3 RightNormal = glm::normalize(glm::cross(CornerPoints[1] - CornerPoints[2], 
													CornerPoints[6] - CornerPoints[2]));
	glm::vec3 TopNormal = glm::normalize(glm::cross(CornerPoints[2] - CornerPoints[3], 
													CornerPoints[7] - CornerPoints[3]));
	glm::vec3 BottomNormal = glm::normalize(glm::cross(CornerPoints[4] - CornerPoints[0], 
													CornerPoints[1] - CornerPoints[0]));

	std::vector<float> Ret(6);

	Ret[0] = glm::dot(-CameraDirection, CornerPoints[3] - InPoint);
	Ret[1] = glm::dot(CameraDirection, CornerPoints[7] - InPoint);
	Ret[2] = glm::dot(LeftNormal, CornerPoints[3] - InPoint);
	Ret[3] = glm::dot(RightNormal, CornerPoints[2] - InPoint);
	Ret[4] = glm::dot(TopNormal, CornerPoints[3] - InPoint);
	Ret[5] = glm::dot(BottomNormal, CornerPoints[0] - InPoint);

	return Ret;
}