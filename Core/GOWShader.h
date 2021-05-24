#pragma once
#ifndef __GOWSHADER_H__
#define __GOWSHADER_H__

#include "GOWEngine.h"

namespace GOW
{
	// GOWShader
	// ������ɫ��
	class GOWShader
	{
	public:
		EXPORT GOWShader();
		EXPORT ~GOWShader();

		EXPORT static void AddPath(const std::string& InPath);

		// ����͸�����ɫ���ļ�
		// InFileName ��ɫ���ļ�·��
		// InType ��ɫ������
		// �ɹ�����true������false
		EXPORT bool AttachFile(const std::string& InFileName, GLenum InType);

		// ����͸�����ɫ���ַ���
		// InShaderString ��ɫ���ַ���
		// InType ��ɫ������
		// �ɹ�����true������false
		EXPORT bool AttachString(const std::string& InShaderString, GLenum InType);

		// ����transform feedback �����¼�ı���
		// InVariables �������б�
		// InBufferMode ����д�뻺���ģʽ��������GL_INTERLEAVED_ATTRIBS����GL_SEPARATE_ATTRIBS
		// �����ɫ���Ѿ����ӣ�����������
		EXPORT void SetTransformFeedbackVariables(std::vector<std::string>& InVariables, GLenum InBufferMode);

		// ���±��룬������ɫ��
		EXPORT void ReCompile();

		// ������ɫ��
		EXPORT bool Link();

		// ʹ����ɫ��
		EXPORT void Use();

		// ͣ����ɫ��
		EXPORT void UnUse();

		// ����Attribute������λ��
		// InName Attribute ����������
		// ����Attribute������λ��,�������-1����ʾ������
		EXPORT int32 GetAttributeLocation(const std::string& InName);

		// ����Uniform������λ��
		// InName Uniform ����������
		// ����Uniform������λ��,�������-1����ʾ������
		EXPORT int32 GetUniformLocation(const std::string& InName);

		// ����Uniform
		// InLocation Uniform λ��
		// InV0 Uniform ֵ
		template <typename T>
		void SetUniform(int32 InLocation, T InV0);

		// ����Uniform
		// InName Uniform ����
		// InV0 Uniform ֵ
		template <typename T>
		void SetUniform(const std::string& InName, T InV0);

		// ����Uniform
		// InLocation Uniform λ��
		// InV0 Uniform ��һ��Ԫ��ֵ
		// InV1 Uniform �ڶ���Ԫ��ֵ
		template <typename T>
		void SetUniform(int32 InLocation, T InV0, T InV1);

		// ����Uniform
		// InName Uniform ����
		// InV0 Uniform ��һ��Ԫ��ֵ
		// InV1 Uniform �ڶ���Ԫ��ֵ
		template <typename T>
		void SetUniform(const std::string& InName, T InV0, T InV1);

		// ����Uniform
		// InLocation Uniform λ��
		// InV0 Uniform ��һ��Ԫ��ֵ
		// InV1 Uniform �ڶ���Ԫ��ֵ
		// InV2 Uniform ������Ԫ��ֵ
		template <typename T>
		void SetUniform(int32 InLocation, T InV0, T InV1, T InV2);

		// ����Uniform
		// InName Uniform ����
		// InV0 Uniform ��һ��Ԫ��ֵ
		// InV1 Uniform �ڶ���Ԫ��ֵ
		// InV2 Uniform ������Ԫ��ֵ
		template <typename T>
		void SetUniform(const std::string& InName, T InV0, T InV1, T InV2);

		// ����Uniform
		// InLocation Uniform λ��
		// InV0 Uniform ��һ��Ԫ��ֵ
		// InV1 Uniform �ڶ���Ԫ��ֵ
		// InV2 Uniform ������Ԫ��ֵ
		// InV3 Uniform ���ĸ�Ԫ��ֵ
		template <typename T>
		void SetUniform(int32 InLocation, T InV0, T InV1, T InV2, T InV3);

		// ����Uniform
		// InName Uniform ����
		// InV0 Uniform ��һ��Ԫ��ֵ
		// InV1 Uniform �ڶ���Ԫ��ֵ
		// InV2 Uniform ������Ԫ��ֵ
		// InV3 Uniform ���ĸ�Ԫ��ֵ
		template <typename T>
		void SetUniform(const std::string& InName, T InV0, T InV1, T InV2, T InV3);

		// ����Uniform
		// InLocation Uniform λ��
		// InCount Vector ����
		// InElements Ԫ������
		// InValue ����ָ��
		template <typename T>
		void SetUniform(int32 InLocation, 
						uint32 InCount, 
						uint32 InElements,
						const T* InValue);

		// ����Uniform
		// InName Uniform ����
		// InCount Vector ����
		// InElements Ԫ������
		// InValue ����ָ��
		template <typename T>
		void SetUniform(const std::string& InName, 
						uint32 InCount, 
						uint32 InElements, 
						const T* InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InCount Vector ����
		// InColumns ����������
		// InRows ����������
		// InTranspose �����Ƿ�ת��
		// InValue ����ָ��
		template <typename T>
		void SetUniform(int32 InLocation,
						uint32 InCount, 
						uint32 InColumns, 
						uint32 InRows,
						bool InTranspose, 
						const T* InValue);

		// ����Uniform
		// InName Uniform ����
		// InCount Vector ����
		// InColumns ����������
		// InRows ����������
		// InTranspose �����Ƿ�ת��
		// InValue ����ָ��
		template <typename T>
		void SetUniform(const std::string& InName, 
						uint32 InCount,
						uint32 InColumns, 
						uint32 InRows, 
						bool InTranspose, 
						const T* InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InValue Uniform ֵ
		EXPORT void SetUniform(int32 InLocation, const glm::vec2& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InValue Uniform ֵ
		EXPORT void SetUniform(int32 InLocation, const glm::dvec2& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InValue Uniform ֵ
		EXPORT void SetUniform(int32 InLocation, const glm::vec3& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InValue Uniform ֵ
		EXPORT void SetUniform(int32 InLocation, const glm::dvec3& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InValue Uniform ֵ
		EXPORT void SetUniform(int32 InLocation, const glm::vec4& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InValue Uniform ֵ
		EXPORT void SetUniform(int32 InLocation, const glm::dvec4& InValue);

		// ����Uniform
		// InName Uniform ����
		// InValue Uniform ֵ
		EXPORT void SetUniform(const std::string& InName, const glm::vec2& InValue);

		// ����Uniform
		// InName Uniform ����
		// InValue Uniform ֵ
		EXPORT void SetUniform(const std::string& InName, const glm::dvec2& InValue);

		// ����Uniform
		// InName Uniform ����
		// InValue Uniform ֵ
		EXPORT void SetUniform(const std::string& InName, const glm::vec3& InValue);

		// ����Uniform
		// InName Uniform ����
		// InValue Uniform ֵ
		EXPORT void SetUniform(const std::string& InName, const glm::dvec3& InValue);

		// ����Uniform
		// InName Uniform ����
		// InValue Uniform ֵ
		EXPORT void SetUniform(const std::string& InName, const glm::vec4& InValue);

		// ����Uniform
		// InName Uniform ����
		// InValue Uniform ֵ
		EXPORT void SetUniform(const std::string& InName, const glm::dvec4& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InTranspose �����Ƿ�ת��
		// InValue Uniform ֵ
		EXPORT void SetUniform(int32 InLocation, 
							bool InTranspose,
							const glm::mat2& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InTranspose �����Ƿ�ת��
		// InValue Uniform ֵ
		EXPORT void SetUniform(int32 InLocation,
							bool InTranspose,
							const glm::dmat2& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InTranspose �����Ƿ�ת��
		// InValue Uniform ֵ
		EXPORT void SetUniform(int32 InLocation, 
							bool InTranspose, 
							const glm::mat3& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InTranspose �����Ƿ�ת��
		// InValue Uniform ֵ
		EXPORT void SetUniform(int32 InLocation, 
							bool InTranspose, 
							const glm::dmat3& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InTranspose �����Ƿ�ת��
		// InValue Uniform ֵ
		EXPORT void SetUniform(int32 InLocation,
							bool InTranspose,
							const glm::mat4& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InTranspose �����Ƿ�ת��
		// InValue Uniform ֵ
		EXPORT void SetUniform(int32 InLocation, 
							bool InTranspose,
							const glm::dmat4& InValue);

		// ����Uniform
		// InName Uniform ����
		// InTranspose �����Ƿ�ת��
		// InValue Uniform ֵ
		EXPORT void SetUniform(const std::string& InName,
							bool InTranspose,
							const glm::mat2& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InTranspose �����Ƿ�ת��
		// InValue Uniform ֵ
		EXPORT void SetUniform(const std::string& InName,
							bool InTranspose, 
							const glm::dmat2& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InTranspose �����Ƿ�ת��
		// InValue Uniform ֵ
		EXPORT void SetUniform(const std::string& InName,
							bool InTranspose, 
							const glm::mat3& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InTranspose �����Ƿ�ת��
		// InValue Uniform ֵ
		EXPORT void SetUniform(const std::string& InName, 
							bool InTranspose, 
							const glm::dmat3& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InTranspose �����Ƿ�ת��
		// InValue Uniform ֵ
		EXPORT void SetUniform(const std::string& InName, 
							bool InTranspose, 
							const glm::mat4& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InTranspose �����Ƿ�ת��
		// InValue Uniform ֵ
		EXPORT void SetUniform(const std::string& InName,
							bool InTranspose, 
							const glm::dmat4& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InValue Uniform ֵ
		EXPORT void SetUniform(int32 InLocation, const std::vector<glm::vec2>& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InValue Uniform ֵ
		EXPORT void SetUniform(int32 InLocation, const std::vector<glm::dvec2>& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InValue Uniform ֵ
		EXPORT void SetUniform(int32 InLocation, const std::vector<glm::vec3>& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InValue Uniform ֵ
		EXPORT void SetUniform(int32 InLocation, const std::vector<glm::dvec3>& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InValue Uniform ֵ
		EXPORT void SetUniform(int32 InLocation, const std::vector<glm::vec4>& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InValue Uniform ֵ
		EXPORT void SetUniform(int32 InLocation, const std::vector<glm::dvec4>& InValue);

		// ����Uniform
		// InName Uniform ����
		// InValue Uniform ֵ
		EXPORT void SetUniform(const std::string& InName, const std::vector<glm::vec2>& InValue);

		// ����Uniform
		// InName Uniform ����
		// InValue Uniform ֵ
		EXPORT void SetUniform(const std::string& InName, const std::vector<glm::dvec2>& InValue);

		// ����Uniform
		// InName Uniform ����
		// InValue Uniform ֵ
		EXPORT void SetUniform(const std::string& InName, const std::vector<glm::vec3>& InValue);

		// ����Uniform
		// InName Uniform ����
		// InValue Uniform ֵ
		EXPORT void SetUniform(const std::string& InName, const std::vector<glm::dvec3>& InValue);

		// ����Uniform
		// InName Uniform ����
		// InValue Uniform ֵ
		EXPORT void SetUniform(const std::string& InName, const std::vector<glm::vec4>& InValue);

		// ����Uniform
		// InName Uniform ����
		// InValue Uniform ֵ
		EXPORT void SetUniform(const std::string& InName, const std::vector<glm::dvec4>& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InTranspose �����Ƿ�ת��
		// InValue Uniform ֵ
		EXPORT void SetUniform(int32 InLocation, 
							bool InTranspose, 
							const std::vector<glm::mat2>& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InTranspose �����Ƿ�ת��
		// InValue Uniform ֵ
		EXPORT void SetUniform(int32 InLocation, 
							bool InTranspose,
							const std::vector<glm::dmat2>& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InTranspose �����Ƿ�ת��
		// InValue Uniform ֵ
		EXPORT void SetUniform(int32 InLocation, 
							bool InTranspose,
							const std::vector<glm::mat3>& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InTranspose �����Ƿ�ת��
		// InValue Uniform ֵ
		EXPORT void SetUniform(int32 InLocation,
							bool InTranspose,
							const std::vector<glm::dmat3>& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InTranspose �����Ƿ�ת��
		// InValue Uniform ֵ
		EXPORT void SetUniform(int32 InLocation, 
							bool InTranspose,
							const std::vector<glm::mat4>& InValue);

		// ����Uniform
		// InLocation Uniform λ��
		// InTranspose �����Ƿ�ת��
		// InValue Uniform ֵ
		EXPORT void SetUniform(int32 InLocation, 
							bool InTranspose,
							const std::vector<glm::dmat4>& InValue);

		// ����Uniform
		// InName Uniform ����
		// InTranspose �����Ƿ�ת��
		// InValue Uniform ֵ
		EXPORT void SetUniform(const std::string& InName,
							bool InTranspose, 
							const std::vector<glm::mat2>& InValue);

		// ����Uniform
		// InName Uniform ����
		// InTranspose �����Ƿ�ת��
		// InValue Uniform ֵ
		EXPORT void SetUniform(const std::string& InName,
							bool InTranspose,
							const std::vector<glm::dmat2>& InValue);

		// ����Uniform
		// InName Uniform ����
		// InTranspose �����Ƿ�ת��
		// InValue Uniform ֵ
		EXPORT void SetUniform(const std::string& InName, 
							bool InTranspose,
							const std::vector<glm::mat3>& InValue);

		// ����Uniform
		// InName Uniform ����
		// InTranspose �����Ƿ�ת��
		// InValue Uniform ֵ
		EXPORT void SetUniform(const std::string& InName, 
							bool InTranspose,
							const std::vector<glm::dmat3>& InValue);

		// ����Uniform
		// InName Uniform ����
		// InTranspose �����Ƿ�ת��
		// InValue Uniform ֵ
		EXPORT void SetUniform(const std::string& InName,
							bool InTranspose,
							const std::vector<glm::mat4>& InValue);

		// ����Uniform
		// InName Uniform ����
		// InTranspose �����Ƿ�ת��
		// InValue Uniform ֵ
		EXPORT void SetUniform(const std::string& InName, 
							bool InTranspose, 
							const std::vector<glm::dmat4>& InValue);

	public:
		// �����true����ɫ����¼��䵽transform feedback
		bool bTransformFeedback;

		// ��ɫ������
		GLuint Program;
	private:
		EXPORT static int32 Counter;

		// ��ǰʹ�õ���ɫ��
		EXPORT static int32 UsedID;

		// ��ɫ������id
		int32 ID;

		bool bModify;
		bool bLinked;

		std::vector<GLuint> Attached;

		std::map<std::string, GLenum> ShaderPaths;
		std::map<std::string, GLenum> ShaderStrings;

		static std::vector<std::string> Paths;
	};

	template <>
	inline void GOWShader::SetUniform<int32>(int32 InLocation, int32 InV0)
	{
		Use();
		glUniform1i(InLocation, InV0);
	}

	template <>
	inline void GOWShader::SetUniform<uint32>(int32 InLocation, uint32 InV0)
	{
		Use();
		glUniform1ui(InLocation, InV0);
	}

	template <>
	inline void GOWShader::SetUniform<float>(int32 InLocation, float InV0)
	{
		Use();
		glUniform1f(InLocation, InV0);
	}

	template <>
	inline void GOWShader::SetUniform<double>(int32 InLocation, double InV0)
	{
		Use();
		glUniform1d(InLocation, InV0);
	}

	template <>
	inline void GOWShader::SetUniform<int32>(const std::string& InName, int32 InV0)
	{
		int32 Location = GetUniformLocation(InName);
		SetUniform(Location, InV0);
	}

	template <>
	inline void GOWShader::SetUniform<uint32>(const std::string& InName, uint32 InV0)
	{
		int32 Location = GetUniformLocation(InName);
		SetUniform(Location, InV0);
	}

	template <>
	inline void GOWShader::SetUniform<float>(const std::string& InName, float InV0)
	{
		int32 Location = GetUniformLocation(InName);
		SetUniform(Location, InV0);
	}

	template <>
	inline void GOWShader::SetUniform<double>(const std::string& InName, double InV0)
	{
		int32 Location = GetUniformLocation(InName);
		SetUniform(Location, InV0);
	}

	template <>
	inline void GOWShader::SetUniform<int32>(int32 InLocation, int32 InV0, int32 InV1)
	{
		Use();
		glUniform2i(InLocation, InV0, InV1);
	}

	template <>
	inline void GOWShader::SetUniform<uint32>(int32 InLocation, uint32 InV0, uint32 InV1)
	{
		Use();
		glUniform2ui(InLocation, InV0, InV1);
	}

	template <>
	inline void GOWShader::SetUniform<float>(int32 InLocation, float InV0, float InV1)
	{
		Use();
		glUniform2f(InLocation, InV0, InV1);
	}

	template <>
	inline void GOWShader::SetUniform<double>(int32 InLocation, double InV0, double InV1)
	{
		Use();
		glUniform2d(InLocation, InV0, InV1);
	}

	template <>
	inline void GOWShader::SetUniform<int32>(const std::string& InName, int32 InV0, int32 InV1)
	{
		int32 Location = GetUniformLocation(InName);
		SetUniform(Location, InV0, InV1);
	}

	template <>
	inline void GOWShader::SetUniform<uint32>(const std::string& InName, uint32 InV0, uint32 InV1)
	{
		int32 Location = GetUniformLocation(InName);
		SetUniform(Location, InV0, InV1);
	}

	template <>
	inline void GOWShader::SetUniform<float>(const std::string& InName, float InV0, float InV1)
	{
		int32 Location = GetUniformLocation(InName);
		SetUniform(Location, InV0, InV1);
	}

	template <>
	inline void GOWShader::SetUniform<double>(const std::string& InNamem, double InV0, double InV1)
	{
		int32 Location = GetUniformLocation(InNamem);
		SetUniform(Location, InV0, InV1);
	}

	template <>
	inline void GOWShader::SetUniform<int32>(int32 InLocation, int32 InV0, int32 InV1, int32 InV2)
	{
		Use();
		glUniform3i(InLocation, InV0, InV1, InV2);
	}

	template <>
	inline void GOWShader::SetUniform<uint32>(int32 InLocation, uint32 InV0, uint32 InV1, uint32 InV2)
	{
		Use();
		glUniform3ui(InLocation, InV0, InV1, InV2);
	}

	template <>
	inline void GOWShader::SetUniform<float>(int32 InLocation, float InV0, float InV1, float InV2)
	{
		Use();
		glUniform3f(InLocation, InV0, InV1, InV2);
	}

	template <>
	inline void GOWShader::SetUniform<double>(int32 InLocation, double InV0, double InV1, double InV2)
	{
		Use();
		glUniform3d(InLocation, InV0, InV1, InV2);
	}

	template <>
	inline void GOWShader::SetUniform<int32>(const std::string& InName, int32 InV0, int32 InV1, int32 InV2)
	{
		int32 Location = GetUniformLocation(InName);
		SetUniform(Location, InV0, InV1, InV2);
	}

	template <>
	inline void GOWShader::SetUniform<uint32>(const std::string& InName, uint32 InV0, uint32 InV1, uint32 InV2)
	{
		int32 Location = GetUniformLocation(InName);
		SetUniform(Location, InV0, InV1, InV2);
	}

	template <>
	inline void GOWShader::SetUniform<float>(const std::string& InName, float InV0, float InV1, float InV2)
	{
		int32 Location = GetUniformLocation(InName);
		SetUniform(Location, InV0, InV1, InV2);
	}

	template <>
	inline void GOWShader::SetUniform<double>(const std::string& InName, double InV0, double InV1, double InV2)
	{
		int32 Location = GetUniformLocation(InName);
		SetUniform(Location, InV0, InV1, InV2);
	}

	template <>
	inline void GOWShader::SetUniform<int32>(int32 InLocation, int32 InV0, int32 InV1, int32 InV2, int32 InV3)
	{
		Use();
		glUniform4i(InLocation, InV0, InV1, InV2, InV3);
	}

	template <>
	inline void GOWShader::SetUniform<uint32>(int32 InLocation, uint32 InV0, uint32 InV1, uint32 InV2, uint32 InV3)
	{
		Use();
		glUniform4ui(InLocation, InV0, InV1, InV2, InV3);
	}

	template <>
	inline void GOWShader::SetUniform<float>(int32 InLocation, float InV0, float InV1, float InV2, float InV3)
	{
		Use();
		glUniform4f(InLocation, InV0, InV1, InV2, InV3);
	}

	template <>
	inline void GOWShader::SetUniform<double>(int32 InLocation, double InV0, double InV1, double InV2, double InV3)
	{
		Use();
		glUniform4d(InLocation, InV0, InV1, InV2, InV3);
	}

	template <>
	inline void GOWShader::SetUniform<int32>(const std::string& InName, int32 InV0, int32 InV1, int32 InV2, int32 InV3)
	{
		int32 Location = GetUniformLocation(InName);
		SetUniform(Location, InV0, InV1, InV2, InV3);
	}

	template <>
	inline void GOWShader::SetUniform<uint32>(const std::string& InName, uint32 InV0, uint32 InV1, uint32 InV2, uint32 InV3)
	{
		int32 Location = GetUniformLocation(InName);
		SetUniform(Location, InV0, InV1, InV2, InV3);
	}

	template <>
	inline void GOWShader::SetUniform<float>(const std::string& InName, float InV0, float InV1, float InV2, float InV3)
	{
		int32 Location = GetUniformLocation(InName);
		SetUniform(Location, InV0, InV1, InV2, InV3);
	}

	template <>
	inline void GOWShader::SetUniform<double>(const std::string& InName, double InV0, double InV1, double InV2, double InV3)
	{
		int32 Location = GetUniformLocation(InName);
		SetUniform(Location, InV0, InV1, InV2, InV3);
	}

	template <>
	inline void GOWShader::SetUniform<int32>(int32 InLocation, uint32 InCount, uint32 InElements, const int32* InValue)
	{
		if (InLocation < 0)
			return;

		if (!InValue)
			return;

		Use();

		switch (InElements)
		{
		case 1:
			glUniform1iv(InLocation, InCount, InValue);
			break;
		case 2:
			glUniform2iv(InLocation, InCount, InValue);
			break;
		case 3:
			glUniform3iv(InLocation, InCount, InValue);
			break;
		case 4:
			glUniform4iv(InLocation, InCount, InValue);
			break;
		default:
			std::string Error = "Wrong number of elements given to"
				"the SetUniform function";
			GOWEngine::ErrorString.push_back(Error);
			throw std::runtime_error(Error);
			break;
		}
	}

	template <>
	inline void GOWShader::SetUniform<uint32>(int32 InLocation, uint32 InCount, uint32 InElements, const uint32* InValue)
	{
		if (InLocation < 0)
			return;

		if (!InValue)
			return;

		Use();

		switch (InElements)
		{
		case 1:
			glUniform1uiv(InLocation, InCount, InValue);
			break;
		case 2:
			glUniform2uiv(InLocation, InCount, InValue);
			break;
		case 3:
			glUniform3uiv(InLocation, InCount, InValue);
			break;
		case 4:
			glUniform4uiv(InLocation, InCount, InValue);
			break;
		default:
			std::string Error = "Wrong number of elements given to"
				"the SetUniform function";
			GOWEngine::ErrorString.push_back(Error);
			throw std::runtime_error(Error);
			break;
		}
	}

	template <>
	inline void GOWShader::SetUniform<float>(int32 InLocation, uint32 InCount, uint32 InElements, const float* InValue)
	{
		if (InLocation < 0)
			return;

		if (!InValue)
			return;

		switch (InElements)
		{
		case 1:
			glUniform1fv(InLocation, InCount, InValue);
			break;
		case 2:
			glUniform2fv(InLocation, InCount, InValue);
			break;
		case 3:
			glUniform3fv(InLocation, InCount, InValue);
			break;
		case 4:
			glUniform4fv(InLocation, InCount, InValue);
			break;
		default:
			std::string Error = "Wrong number of elements given to"
				"the SetUniform function";
			GOWEngine::ErrorString.push_back(Error);
			throw std::runtime_error(Error);
			break;
		}
	}

	template <>
	inline void GOWShader::SetUniform<double>(int32 InLocation, uint32 InCount, uint32 InElements, const double* InValue)
	{
		if (InLocation < 0)
			return;

		if (!InValue)
			return;

		switch (InElements)
		{
		case 1:
			glUniform1dv(InLocation, InCount, InValue);
			break;
		case 2:
			glUniform2dv(InLocation, InCount, InValue);
			break;
		case 3:
			glUniform3dv(InLocation, InCount, InValue);
			break;
		case 4:
			glUniform4dv(InLocation, InCount, InValue);
			break;
		default:
			std::string Error = "Wrong number of elements given to"
				"the SetUniform function";
			GOWEngine::ErrorString.push_back(Error);
			throw std::runtime_error(Error);
			break;
		}
	}

	template <>
	inline void GOWShader::SetUniform<int32>(const std::string& InName, uint32 InCount, uint32 InElements, const int32* InValue)
	{
		int32 Location = GetUniformLocation(InName);
		SetUniform(Location, InCount, InElements, InValue);
	}

	template <>
	inline void GOWShader::SetUniform<uint32>(const std::string& InName, uint32 InCount, uint32 InElements, const uint32* InValue)
	{
		int32 Location = GetUniformLocation(InName);
		SetUniform(Location, InCount, InElements, InValue);
	}

	template <>
	inline void GOWShader::SetUniform<float>(const std::string& InName, uint32 InCount, uint32 InElements, const float* InValue)
	{
		int32 Location = GetUniformLocation(InName);
		SetUniform(Location, InCount, InElements, InValue);
	}

	template <>
	inline void GOWShader::SetUniform<double>(const std::string& InName, uint32 InCount, uint32 InElements, const double* InValue)
	{
		int32 Location = GetUniformLocation(InName);
		SetUniform(Location, InCount, InElements, InValue);
	}

	template <>
	inline void GOWShader::SetUniform<float>(int32 InLocation,
											uint32 InCount,
											uint32 InColumns,
											uint32 InRows,
											bool InTranspose,
											const float* InValue)
	{
		if (InLocation < 0)
			return;

		if (InColumns < 2 || InRows < 2 || InColumns > 4 || InRows > 4)
			return;

		if (!InValue)
			return;

		Use();

		if (InColumns == InRows)
		{
			switch (InRows)
			{
			case 2:
				glUniformMatrix2fv(InLocation, InCount, InTranspose, InValue);
				break;
			case 3:
				glUniformMatrix3fv(InLocation, InCount, InTranspose, InValue);
				break;
			case 4:
				glUniformMatrix4fv(InLocation, InCount, InTranspose, InValue);
				break;
			default:
				std::string Error = "Wrong number of elements given to"
					"the SetUniform function";
				GOWEngine::ErrorString.push_back(Error);
				throw std::runtime_error(Error);
				break;
			}
		}
		else
		{
			if (InColumns == 2 && InRows == 3)
			{
				glUniformMatrix2x3fv(InLocation, InCount, InTranspose, InValue);
			}
			else if (InColumns == 3 && InRows == 2)
			{
				glUniformMatrix3x2fv(InLocation, InCount, InTranspose, InValue);
			}
			else if (InColumns == 2 && InRows == 4)
			{
				glUniformMatrix2x4fv(InLocation, InCount, InTranspose, InValue);
			}
			else if (InColumns == 4 && InRows == 2)
			{
				glUniformMatrix4x2fv(InLocation, InCount, InTranspose, InValue);
			}
			else if (InColumns == 3 && InRows == 4)
			{
				glUniformMatrix3x4fv(InLocation, InCount, InTranspose, InValue);
			}
			else if (InColumns == 4 && InRows == 3)
			{
				glUniformMatrix4x3fv(InLocation, InCount, InTranspose, InValue);
			}
			else
			{
				std::string Error = "Wrong number of elements given to"
					"the SetUniform function";
				GOWEngine::ErrorString.push_back(Error);
				throw std::runtime_error(Error);
			}
		}
	}

	template <>
	inline void GOWShader::SetUniform<double>(int32 InLocation,
											uint32 InCount,
											uint32 InColumns,
											uint32 InRows,
											bool InTranspose,
											const double* InValue)
	{
		if (InLocation < 0)
			return;

		if (InColumns < 2 || InRows < 2 || InColumns > 4 || InRows > 4)
			return;

		if (!InValue)
			return;

		Use();

		if (InColumns == InRows)
		{
			switch (InRows)
			{
			case 2:
				glUniformMatrix2dv(InLocation, InCount, InTranspose, InValue);
				break;
			case 3:
				glUniformMatrix3dv(InLocation, InCount, InTranspose, InValue);
				break;
			case 4:
				glUniformMatrix4dv(InLocation, InCount, InTranspose, InValue);
				break;
			default:
				std::string Error = "Wrong number of elements given to"
					"the SetUniform function";
				GOWEngine::ErrorString.push_back(Error);
				throw std::runtime_error(Error);
			}
		}
		else
		{
			if (InColumns == 2 && InRows == 3)
			{
				glUniformMatrix2x3dv(InLocation, InCount, InTranspose, InValue);
			}
			else if (InColumns == 3 && InRows == 2)
			{
				glUniformMatrix3x2dv(InLocation, InCount, InTranspose, InValue);
			}
			else if (InColumns == 2 && InRows == 4)
			{
				glUniformMatrix2x4dv(InLocation, InCount, InTranspose, InValue);
			}
			else if (InColumns == 4 && InRows == 2)
			{
				glUniformMatrix4x2dv(InLocation, InCount, InTranspose, InValue);
			}
			else if (InColumns == 3 && InRows == 4)
			{
				glUniformMatrix3x4dv(InLocation, InCount, InTranspose, InValue);
			}
			else if (InColumns == 4 && InRows == 3)
			{
				glUniformMatrix4x3dv(InLocation, InCount, InTranspose, InValue);
			}
			else
			{
				std::string Error = "Wrong number of elements given to"
					"the SetUniform function";
				GOWEngine::ErrorString.push_back(Error);
				throw std::runtime_error(Error);
			}
		}
	}

	template <>
	inline void GOWShader::SetUniform<float>(const std::string& InName,
											uint32 InCount,
											uint32 InColumns,
											uint32 InRows,
											bool InTranspose,
											const float* InValue)
	{
		int32 Location = GetUniformLocation(InName);
		SetUniform(Location, InCount, InColumns, InRows, InTranspose, InValue);
	}

	template <>
	inline void GOWShader::SetUniform<double>(const std::string& InName,
											uint32 InCount,
											uint32 InColumns,
											uint32 InRows,
											bool InTranspose,
											const double* InValue)
	{
		int32 Location = GetUniformLocation(InName);
		SetUniform(Location, InCount, InColumns, InRows, InTranspose, InValue);
	}
};

#endif