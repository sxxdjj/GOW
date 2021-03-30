#pragma once
#ifndef __GOWCamera_H__
#define __GOWCamera_H__

#include "GOWEngine.h"
namespace GOW
{
	// Class GOWCamera
	// 管理相机
	class GOWCamera
	{
	public:
		// InPosition 相机位置
		// InDirection 相机可视方向向量
		// InUp 相机向上向量
		EXPORT GOWCamera(glm::vec3 InPosition, glm::vec3 InDirection, glm::vec3 InUp);
		EXPORT ~GOWCamera();

		// 更新视图矩阵
		EXPORT void UpdateViewMatrix();

		// 更新投影矩阵
		EXPORT virtual void UpdateProjectionMatrix() = 0;

		// 相机沿上方向移动
		// InDelta 相机移动距离
		EXPORT void MoveUp(float InDelta);

		// 相机沿右方向移动
		EXPORT void MoveRight(float InDelta);

		// 相机沿前方向移动
		EXPORT void MoveForward(float InDelta);

		// 相机沿一个向量移动(x, y, z)
		EXPORT void MoveBy(float InX, float InY, float InZ);

		// 相机沿一个向量移动
		EXPORT void MoveBy(glm::vec3 InVector);

		// 相机绕向上向量旋转，也就是在偏航角上旋转
		EXPORT void Yaw(float InAngle);

		// 相机绕向前向量旋转，也就是在翻滚角上旋转
		EXPORT void Roll(float InAngle);

		// 相机绕向右向量旋转，也就是在俯仰角上旋转
		EXPORT void Pitch(float InAngle);
	public:
		// 视图矩阵
		glm::mat4 ViewMatrix;

		// 投影矩阵
		glm::mat4 ProjectionMatrix;

		// 视口宽度
		float Width;

		// 视口高度
		float Height;

		// 视锥角度
		float Fovy;

		// 相机远平面
		float FarPlane;

		// 相机近平面
		float NearPlane;

		// 相机坐标
		glm::vec3 Position;

		// 相机朝向
		glm::vec3 Direction;

		// 相机向上方向
		glm::vec3 Up;

		// 相机朝左方向
		glm::vec3 Right;
	};
};
#endif