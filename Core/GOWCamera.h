#pragma once
#ifndef __GOWCamera_H__
#define __GOWCamera_H__

#include "GOWEngine.h"
namespace GOW
{
	// Class GOWCamera
	// �������
	class GOWCamera
	{
	public:
		// InPosition ���λ��
		// InDirection ����ӿڷ�������
		// InUp �����������
		EXPORT GOWCamera(glm::vec3 InPosition, glm::vec3 InDirection, glm::vec3 InUp);
		EXPORT ~GOWCamera();

		// ������ͼ����
		EXPORT void UpdateViewMatrix();

		// ����ͶӰ����
		EXPORT virtual void UpdateProjectionMatrix() = 0;

		// ������Ϸ����ƶ�
		// InDelta ����ƶ�����
		EXPORT void MoveUp(float InDelta);

		// ������ҷ����ƶ�
		EXPORT void MoveRight(float InDelta);

		// �����ǰ�����ƶ�
		EXPORT void MoveForward(float InDelta);

		// �����һ�������ƶ�(x, y, z)
		EXPORT void MoveBy(float InX, float InY, float InZ);

		// �����һ�������ƶ�
		EXPORT void MoveBy(glm::vec3 InVector);

		// ���������������ת��Ҳ������ƫ��������ת
		EXPORT void Yaw(float InAngle);

		// �������ǰ������ת��Ҳ�����ڷ���������ת
		EXPORT void Roll(float InAngle);

		// ���������������ת��Ҳ�����ڸ���������ת
		EXPORT void Pitch(float InAngle);
	protected:
		// ��ͼ����
		glm::mat4 ViewMatrix;

		// ͶӰ����
		glm::mat4 ProjectionMatrix;

		// �ӿڿ��
		float Width;

		// �ӿڸ߶�
		float Height;

		// ��׶�Ƕ�
		float Fovy;

		// ���Զƽ��
		float FarPlane;

		// �����ƽ��
		float NearPlane;

		// �������
		glm::vec3 Position;

		// �������
		glm::vec3 Direction;

		// ������Ϸ���
		glm::vec3 Up;

		// ���������
		glm::vec3 Right;
	};

	// class GOWPerspectiveGamera
// ����͸�����
	class GOWPerspectiveGamera : public GOWCamera
	{
	public:
		EXPORT GOWPerspectiveGamera();

		// InCamera �����������
		EXPORT GOWPerspectiveGamera(const GOW::GOWPerspectiveGamera& InCamera);

		// InPosition ���λ��
		// InDirection ����ӿڷ�������
		// InUp �����������
		EXPORT GOWPerspectiveGamera(glm::vec3 InPosition, glm::vec3 InDirection, glm::vec3 InUp);

		// InPosition ���λ��
		// InDirection ����ӿڷ�������
		// InUp �����������
		// InFovy ��׶�Ƕ�
		// InWidth �ӿڿ��
		// InHeight �ӿڸ߶�
		// InNearPlane ��ƽ��
		// InFarPlane Զƽ��
		EXPORT GOWPerspectiveGamera(glm::vec3 InPosition,
			glm::vec3 InDirection,
			glm::vec3 InUp, float InFovy,
			float InWidth,
			float InHeight,
			float InNearPlane,
			float InFarPlane);

		EXPORT ~GOWPerspectiveGamera();

		// ����ͶӰ����
		EXPORT void UpdateProjectionMatrix();

		// ������׶�˸��ǵ������
		// ����һ����������������������vector
		// 0 - near_bottom_left
		// 1 - near_bottom_right
		// 2 - near_top_right
		// 3 - near_top_left
		// 4 - far-bottom-left
		// 5 - far-bottom-right
		// 6 - far-top-right
		// 7 - far-top-left
		EXPORT std::vector<glm::vec3> CalculateFrustumPoints();

		// ����һ���㵽��׶����ƽ��ľ��룬��ֵ��ʾ���������׶ƽ���ڲ�
		// InPoint ������ĵ�
		// ����һ�������㵽����ƽ����������
		// 0 - far
		// 1 - near
		// 2 - left
		// 3 - right
		// 4 - top
		// 5 - bottom
		EXPORT std::vector<float> CalculateFrustumDistance(glm::vec3 InPoint);
	};
};

#endif