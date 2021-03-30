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
		// InDirection ������ӷ�������
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
	public:
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
};
#endif