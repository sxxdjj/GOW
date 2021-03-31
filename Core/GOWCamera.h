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
		// InDirection 相机视口方向向量
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
	protected:
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

	// class GOWPerspectiveGamera
	// 管理透视相机
	class GOWPerspectiveGamera : public GOWCamera
	{
	public:
		EXPORT GOWPerspectiveGamera();

		// InCamera 被拷贝的相机
		EXPORT GOWPerspectiveGamera(const GOW::GOWPerspectiveGamera& InCamera);

		// InPosition 相机位置
		// InDirection 相机视口方向向量
		// InUp 相机向上向量
		EXPORT GOWPerspectiveGamera(glm::vec3 InPosition, glm::vec3 InDirection, glm::vec3 InUp);

		// InPosition 相机位置
		// InDirection 相机视口方向向量
		// InUp 相机向上向量
		// InFovy 视锥角度
		// InWidth 视口宽度
		// InHeight 视口高度
		// InNearPlane 近平面
		// InFarPlane 远平面
		EXPORT GOWPerspectiveGamera(glm::vec3 InPosition,
			glm::vec3 InDirection,
			glm::vec3 InUp, float InFovy,
			float InWidth,
			float InHeight,
			float InNearPlane,
			float InFarPlane);

		EXPORT ~GOWPerspectiveGamera();

		// 更新投影矩阵
		EXPORT void UpdateProjectionMatrix();

		// 计算视锥八个角点的坐标
		// 返回一个包含了所有世界坐标点的vector
		// 0 - near_bottom_left
		// 1 - near_bottom_right
		// 2 - near_top_right
		// 3 - near_top_left
		// 4 - far-bottom-left
		// 5 - far-bottom-right
		// 6 - far-top-right
		// 7 - far-top-left
		EXPORT std::vector<glm::vec3> CalculateFrustumPoints();

		// 计算一个点到视锥所有平面的距离，正值表示这个点在视锥平面内侧
		// InPoint 所计算的点
		// 返回一个包含点到所有平面距离的向量
		// 0 - near
		// 1 - far
		// 2 - left
		// 3 - right
		// 4 - top
		// 5 - bottom
		EXPORT std::vector<float> CalculateFrustumDistance(glm::vec3 InPoint);
	};

	// class GOWOrthographicCamera
	// 管理正交相机
	class GOWOrthographicCamera : public GOWCamera
	{
	public:
		EXPORT GOWOrthographicCamera();

		// InCamera 被拷贝的相机
		EXPORT GOWOrthographicCamera(const GOWOrthographicCamera& InCamera);

		// InPosition 相机位置
		// InDirection 相机视口方向向量
		// InUp 相机向上向量
		EXPORT GOWOrthographicCamera(glm::vec3 InPosition, glm::vec3 InDirection, glm::vec3 InUp);

		// InPosition 相机位置
		// InDirection 相机视口方向向量
		// InUp 相机向上向量
		// InWidth 视口宽度
		// InHeight 视口高度
		// InNearPlane 近平面
		// InFarPlane 远平面
		EXPORT GOWOrthographicCamera(glm::vec3 InPosition, 
									glm::vec3 InDirection, 
									glm::vec3 InUp, 
									float InWidth, 
									float InHeight, 
									float InNearPlane, 
									float InFarPlane);

		EXPORT ~GOWOrthographicCamera();

		// 更新投影矩阵
		EXPORT void UpdateProjectionMatrix();

		// 计算视锥八个角点的坐标
		// 返回一个包含了所有世界坐标点的vector
		// 0 - near_bottom_left
		// 1 - near_bottom_right
		// 2 - near_top_right
		// 3 - near_top_left
		// 4 - far-bottom-left
		// 5 - far-bottom-right
		// 6 - far-top-right
		// 7 - far-top-left
		EXPORT std::vector<glm::vec3> CalculateFrustumPoints();

		// 计算一个点到视锥所有平面的距离，正值表示这个点在视锥平面内侧
		// InPoint 所计算的点
		// 返回一个包含点到所有平面距离的向量
		// 0 - near
		// 1 - far
		// 2 - left
		// 3 - right
		// 4 - top
		// 5 - bottom
		EXPORT std::vector<float> CalculateFrustumDistance(glm::vec3 InPoint);

		// 通过传入相机和方向向量，计算一个视锥包围盒和这个向量对齐，并更新相机参数
		// InCamera 用于计算包围盒的正交相机
		// InDirection 包围盒对齐的向量
		// InOffset 视锥平面偏移量
		void UpdateCameraByBounding(GOWOrthographicCamera& InCamera, glm::vec3 InDirection, float InOffset);

		// 通过传入相机和方向向量，计算一个视锥包围盒和这个向量对齐，并更新相机参数
		// InCamera 用于计算包围盒的透视相机
		// InDirection 包围盒对齐的向量
		// InOffset 视锥平面偏移量
		void UpdateCameraByBounding(GOWPerspectiveGamera& InCamera, glm::vec3 InDirection, float InOffset);
	};

	// class GOWIPCamera
	// 管理无限远透视相机
	class GOWIPCamera : public GOWCamera
	{
	public:
		EXPORT GOWIPCamera();

		// InCamera 被拷贝的相机
		EXPORT GOWIPCamera(const GOWIPCamera& InCamera);

		// InPosition 相机位置
		// InDirection 相机视口方向向量
		// InUp 相机向上向量
		EXPORT GOWIPCamera(glm::vec3 InPosition, glm::vec3 InDirection, glm::vec3 InUp);

		// InPosition 相机位置
		// InDirection 相机视口方向向量
		// InUp 相机向上向量
		// InFovy 视锥角度
		// InWidth 视口宽度
		// InHeight 视口高度
		// InNearPlane 近平面
		EXPORT GOWIPCamera(glm::vec3 InPosition, 
							glm::vec3 InDirection, 
							glm::vec3 InUp, 
							float InFovy, 
							float InWidth, 
							float InHeight, 
							float InNearPlane);
		EXPORT ~GOWIPCamera();

		// 更新投影矩阵
		EXPORT void UpdateProjectionMatrix();

		// 计算视锥八个角点的坐标
		// 返回一个包含了所有世界坐标点的vector
		// 0 - near_bottom_left
		// 1 - near_bottom_right
		// 2 - near_top_right
		// 3 - near_top_left
		EXPORT std::vector<glm::vec3> CalculateFrustumPoints();
	};
};

#endif