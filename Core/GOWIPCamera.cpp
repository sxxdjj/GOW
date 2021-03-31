#include "GOWCamera.h"

using namespace GOW;

GOWIPCamera::GOWIPCamera()
:GOWCamera(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 1))
{
	UpdateProjectionMatrix();
}

GOWIPCamera::GOWIPCamera(const GOWIPCamera& InCamera)
:GOWCamera(InCamera.Position, InCamera.Direction, InCamera.Up)
{
	Fovy = InCamera.Fovy;
	Width = InCamera.Width;
	Height = InCamera.Height;
	NearPlane = InCamera.NearPlane;
	UpdateProjectionMatrix();
}

GOWIPCamera::GOWIPCamera(glm::vec3 InPosition, glm::vec3 InDirection, glm::vec3 InUp)
:GOWCamera(InPosition, InDirection, InUp)
{
	UpdateProjectionMatrix();
}

GOWIPCamera::GOWIPCamera(glm::vec3 InPosition, glm::vec3 InDirection, glm::vec3 InUp, float InFovy, float InWidth, float InHeight, float InNearPlane)
:GOWIPCamera(InPosition, InDirection, InUp)
{
	Fovy = InFovy;
	Width = InWidth;
	Height = InHeight;
	NearPlane = InNearPlane;

	UpdateProjectionMatrix();
}

GOWIPCamera::~GOWIPCamera()
{

}

void GOWIPCamera::UpdateProjectionMatrix()
{
	ProjectionMatrix = glm::infinitePerspective(Fovy, (GLfloat)Width / (GLfloat)Height, NearPlane);
}

std::vector<glm::vec3> GOWIPCamera::CalculateFrustumPoints()
{
	std::vector<glm::vec4> Ndc = {
		glm::vec4(-1, -1, -1, 1),
		glm::vec4(1, -1, -1, 1),
		glm::vec4(1, 1, -1, 1),
		glm::vec4(-1, 1, -1, 1)
	};

	glm::mat4 Mat = glm::inverse(ProjectionMatrix * ViewMatrix);

	glm::vec4 Tmp;
	std::vector<glm::vec3> Ret(Ndc.size());
	for (uint32 i = 0; i < Ndc.size(); i++)
	{
		Tmp = Mat * Ndc[i];
		Ret[i] = glm::vec3(Tmp / Tmp[3]);
	}

	return Ret;
}