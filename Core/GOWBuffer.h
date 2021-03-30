#pragma once
#ifndef __GOWBUFFER_H_
#define __GOWBUFFER_H_

#include "GOWEngine.h"

namespace GOW
{
	// Class GOWBuffer
	// ���������
	class GOWBuffer
	{
		GLenum Usage;
		GLenum Target;

	public:
		// InTarget �������󶨵Ļ���Ŀ��
		GOWBuffer(GLenum InTarget = GL_ARRAY_BUFFER)
		{
			Target = InTarget;
			glGenBuffers(1, &Buffer);
		}

		// ���������󶨵���ǰ����Ŀ��
		// ���֮ǰδ���������󶨵�����Ŀ�꣬����󶨵�GL_ARRAY_BUFFER
		void Bind()
		{
			glBindBuffer(Target, Buffer);
		}

		// ���������󶨵�����Ŀ��
		// InTarget �������󶨵Ļ���Ŀ��
		void Bind(GLenum InTarget)
		{
			Target = InTarget;
			glBindBuffer(InTarget, Buffer);
		}

		// ���������󶨵�����Ŀ�꣬���󶨵�����ָ���İ󶨵�
		// InTarget �������󶨵Ļ���Ŀ��
		// InIndex ����ָ���İ󶨵㣬���Һͻ���Ŀ��ָ�����������
		// �������Ŀ�겻��GL_ATOMIC_COUNTER_BUFFER,
		// GL_TRANSFORM_FEEDBACK_BUFFER, GL_UNIFORM_BUFFER, GL_SHADER_STORAGE_BUFFER, ��������
		void Bind(GLenum InTarget, uint32 InIndex)
		{
			Target = InTarget;
			switch (InTarget)
			{
				case GL_ATOMIC_COUNTER_BUFFER:
				case GL_TRANSFORM_FEEDBACK_BUFFER:
				case GL_UNIFORM_BUFFER:
				case GL_SHADER_STORAGE_BUFFER:
					glBindBufferBase(InTarget, InIndex, Buffer);
					break;
				default:
					glBindBuffer(InTarget, Buffer);
			}
		}

		// ��󻺳����󶨵Ļ���Ŀ��
		void Unbind()
		{
			glBindBuffer(Target, 0);
		}

		// �����յĻ���
		// InNumElemets Ԫ�ظ���
		// InUsage ����Ķ�дȨ��
		// ��Чֵ��GL_{STREAM,STATIC,DYNAMIC}_{DRAW,READ,COPY}
		template <typename T>
		void CreateEmptyBuffer(uint32 InNumElements, GLenum InUsage)
		{
			Usage = InUsage;
			Size = InNumElements * sizeof(T);
			NumElements = InNumElements;
			Bind();
			glBufferData(Target, Size, nullptr, Usage);
			Unbind();
		}

		// ������ݵ�����
		// InData ��������
		// InUsage ����Ķ�дȨ��
		// ��Чֵ��GL_{STREAM,STATIC,DYNAMIC}_{DRAW,READ,COPY}
		template <typename T>
		void Load(const std::vector<T>& InData, GLenum InUsage)
		{
			Usage = InUsage;
			Size = InData.size() * sizeof(T);
			NumElements = InData.size();
			Bind();
			glBufferData(Target, Size, InData.data(), InUsage);
			Unbind();
		}

		// ������ݵ�����
		// InNumElements Ԫ�ظ���
		// InData �������
		// InUsage ����Ķ�дȨ��
		// ��Чֵ��GL_{STREAM,STATIC,DYNAMIC}_{DRAW,READ,COPY}
		template <typename T>
		void Load(uint32 InNumElements, const T* InData, GLenum InUsage)
		{
			Usage;
			Size = InNumElements * sizeof(T);
			NumElements = InNumElements;
			Bind();
			glBufferData(Target, Size, InData, InUsage);
			Unbind();
		}

		// �ѻ�������д���ڴ���
		// InOffset ���������ƫ���������ֽ�Ϊ��λ
		// InSize �洢��С
		// InStorage �洢�����ڴ�
		// �ɹ�����true�����򷵻�false
		// Ϊ��ȷ����ɫ������ɶԻ������Ĳ�����Ӧ�ڵ��ô˺���֮ǰ����glMemoryBarrier
		bool Store(uint32 InOffset, uint32 InSize, void* InStorage)
		{
			if (InOffset >= Size)
				return false;

			if (InSize < (Size - InOffset))
				return false;

			if (!InStorage)
				return false;

			Bind(GL_COPY_READ_BUFFER);
			glGetBufferSubData(GL_COPY_READ_BUFFER, InOffset, InSize, InStorage);
			Unbind();
		}

		// ����һ��������󿽱�����
		// InSource ԭ�������
		// InReadOffset ԭ��������ȡ��ƫ����
		// InWriteOffset д��Ŀ�껺������ƫ����
		// InSize ���������ݴ�С�����ֽ�Ϊ��λ
		// �ɹ�����true�����򷵻�false
		bool Copy(Buffer& InSource, uint32 InReadOffset, uint32 InWriteOffset, uint32 InSize)
		{
			if (InReadOffset >= InSource.Size || InReadOffset + InSize >= InSource.Size)
				return false;

			if (InWriteOffset >= Size || InWriteOffset + InSize >= Size)
				return false;

			InSource.Bind(GL_COPY_READ_BUFFER);
			Bind(GL_COPY_WRITE_BUFFER);
			glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, InReadOffset, InWriteOffset, InSize);
			InSource.Unbind();
			Unbind();

			return true;
		}

		// ����һ��������󿽱�����
		// InSource ԭ�������
		// InReadOffset ԭ��������ȡ��ƫ����
		// InWriteOffset д��Ŀ�껺������ƫ����
		// InSize ���������ݴ�С�����ֽ�Ϊ��λ
		// �ɹ�����true�����򷵻�false
		bool Copy(Buffer* InSource, uint32 InReadOffset, uint32 InWriteOffset, uint32 InSize)
		{
			if (!InSource)
				return false;

			if (InReadOffset >= InSource->Size || InReadOffset + InSize >= InSource->Size)
				return false;

			if (InWriteOffset >= Size || InWriteOffset + InSize >= Size)
				return false;

			InSource->Bind(GL_COPY_READ_BUFFER);
			Bind(GL_COPY_WRITE_BUFFER);
			glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, InReadOffset, InWriteOffset, InSize);
			InSource->Unbind();
			Unbind();
		}

		// �ѻ����������ӳ�䵽�ͻ��˵ĵ�ַ�ռ�
		// InAcces ��дȨ��(GL_READ_ONLY, GL_WRITE_ONLY, GL_RED_WRITE)
		// �������������в����󣬷���һ��ָ��ӳ�䷶Χ����ʼ��ַ
		void* Map(GLenum InAcces)
		{
			Bind(GL_ARRAY_BUFFER);
			void* Ptr = glMapBuffer(Target, InAcces);
			Unbind();

			return Ptr;
		}

		// ���ӳ��
		void Unmap()
		{
			Bind(GL_ARRAY_BUFFER);
			glUnmapBuffer(Target);
			Unbind();
		}

		// ���Ƕ��㻺������������
		// InData ������������
		template <typename T>
		void ReplaceData(const std::vector<T>& InData)
		{
			Bind();
			uint32 NewSize = InData.size() * sizeof(T);

			if (Size != NewSize)
			{
				// ���·����ڴ棬�滻������
				Size = NewSize;
				glBufferData(Target, NewSize, InData.data(), Usage);
			}
			else
			{
				// ����Ҫ���·����ڴ棬ֱ���滻������
				glBufferSubData(Target, 0, Size, InData.data());
			}

			Unbind();
		}

		// ���Ƕ��㻺������������
		// InData ������������
		// InNumElements Ԫ�ظ���
		template <typename T>
		void ReplaceData(const T* InData, uint32 InNumElements)
		{
			Bind();
			
			uint32 NewSize = InNumElements * sizeof(T);

			if (Size != NewSize)
			{
				// ���·����ڴ棬�滻������
				Size = NewSize;
				glBufferData(Target, NewSize, InData, Usage);
			}
			else
			{
				// ����Ҫ���·����ڴ棬ֱ���滻������
				glBufferSubData(Target, 0, Size, InData);
			}

			Unbind();
		}

		// ���ǻ�����ָ��ƫ����������
		// InOffset ��������ʼƫ����
		// InData ������������
		template <typename T>
		bool ReplacePartialData(uint32 InOffset, const std::vector<T>& InData)
		{
			uint32 DataSize = InData.size() * sizeof(T);

			if (InOffset + DataSize > Size)
				return false;

			Bind();
			glBufferSubData(Target, InOffset, DataSize, InData.data());
			Unbind();

			return true;
		}

		// ���ǻ�����ָ��ƫ����������
		// InOffset ��������ʼƫ����
		// InData ������������
		// InNumElements Ԫ�ظ���
		template <typename T>
		bool ReplacePartialData(uint32 InOffset, const T* InData, uint32 InNumElements)
		{
			uint32 DataSize = InNumElements * sizeof(T);

			if (InOffset + DataSize > Size)
				return false;

			Bind();
			glBufferSubData(Target, InOffset, DataSize, InData);
			Unbind();

			return true;
		}

	public:
		// �����������
		GLuint Buffer;

		// ��������С����λbytes
		uint32 Size;

		// �����а���Ԫ�صĸ���
		uint32 NumElements;
	};
};

#endif