#pragma once
#ifndef __GOWBUFFER_H_
#define __GOWBUFFER_H_

#include "GOWEngine.h"

namespace GOW
{
	// Class GOWBuffer
	// 管理缓冲对象
	class GOWBuffer
	{
		GLenum Usage;
		GLenum Target;

	public:
		// InTarget 缓冲对象绑定的缓冲目标
		GOWBuffer(GLenum InTarget = GL_ARRAY_BUFFER)
		{
			Target = InTarget;
			glGenBuffers(1, &Buffer);
		}

		// 将缓冲对象绑定到先前缓冲目标
		// 如果之前未将缓冲对象绑定到缓冲目标，则将其绑定到GL_ARRAY_BUFFER
		void Bind()
		{
			glBindBuffer(Target, Buffer);
		}

		// 将缓冲对象绑定到缓冲目标
		// InTarget 缓冲对象绑定的缓冲目标
		void Bind(GLenum InTarget)
		{
			Target = InTarget;
			glBindBuffer(InTarget, Buffer);
		}

		// 将缓冲对象绑定到缓冲目标，并绑定到索引指定的绑定点
		// InTarget 缓冲对象绑定的缓冲目标
		// InIndex 索引指定的绑定点，并且和缓冲目标指定的数组关联
		// 如果缓冲目标不是GL_ATOMIC_COUNTER_BUFFER,
		// GL_TRANSFORM_FEEDBACK_BUFFER, GL_UNIFORM_BUFFER, GL_SHADER_STORAGE_BUFFER, 索引忽略
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

		// 解绑缓冲对象绑定的缓冲目标
		void Unbind()
		{
			glBindBuffer(Target, 0);
		}

		// 创建空的缓冲
		// InNumElemets 元素个数
		// InUsage 缓冲的读写权限
		// 有效值：GL_{STREAM,STATIC,DYNAMIC}_{DRAW,READ,COPY}
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

		// 填充数据到缓冲
		// InData 填充的数据
		// InUsage 缓冲的读写权限
		// 有效值：GL_{STREAM,STATIC,DYNAMIC}_{DRAW,READ,COPY}
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

		// 填充数据到缓冲
		// InNumElements 元素个数
		// InData 填充数据
		// InUsage 缓冲的读写权限
		// 有效值：GL_{STREAM,STATIC,DYNAMIC}_{DRAW,READ,COPY}
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

		// 把缓冲内容写入内存中
		// InOffset 缓冲对象中偏移量，以字节为单位
		// InSize 存储大小
		// InStorage 存储数据内存
		// 成功返回true，否则返回false
		// 为了确保着色器已完成对缓冲区的操作，应在调用此函数之前调用glMemoryBarrier
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

		// 从另一个缓冲对象拷贝数据
		// InSource 原缓冲对象
		// InReadOffset 原缓冲对象读取的偏移量
		// InWriteOffset 写入目标缓冲对象的偏移量
		// InSize 拷贝的数据大小，以字节为单位
		// 成功返回true，否则返回false
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

		// 从另一个缓冲对象拷贝数据
		// InSource 原缓冲对象
		// InReadOffset 原缓冲对象读取的偏移量
		// InWriteOffset 写入目标缓冲对象的偏移量
		// InSize 拷贝的数据大小，以字节为单位
		// 成功返回true，否则返回false
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

		// 把缓冲对象数据映射到客户端的地址空间
		// InAcces 读写权限(GL_READ_ONLY, GL_WRITE_ONLY, GL_RED_WRITE)
		// 缓冲对象完成所有操作后，返回一个指向映射范围的起始地址
		void* Map(GLenum InAcces)
		{
			Bind(GL_ARRAY_BUFFER);
			void* Ptr = glMapBuffer(Target, InAcces);
			Unbind();

			return Ptr;
		}

		// 解除映射
		void Unmap()
		{
			Bind(GL_ARRAY_BUFFER);
			glUnmapBuffer(Target);
			Unbind();
		}

		// 覆盖顶点缓冲中所有数据
		// InData 覆盖所需数据
		template <typename T>
		void ReplaceData(const std::vector<T>& InData)
		{
			Bind();
			uint32 NewSize = InData.size() * sizeof(T);

			if (Size != NewSize)
			{
				// 重新分配内存，替换旧数据
				Size = NewSize;
				glBufferData(Target, NewSize, InData.data(), Usage);
			}
			else
			{
				// 不需要重新分配内存，直接替换旧数据
				glBufferSubData(Target, 0, Size, InData.data());
			}

			Unbind();
		}

		// 覆盖顶点缓冲中所有数据
		// InData 覆盖所需数据
		// InNumElements 元素个数
		template <typename T>
		void ReplaceData(const T* InData, uint32 InNumElements)
		{
			Bind();
			
			uint32 NewSize = InNumElements * sizeof(T);

			if (Size != NewSize)
			{
				// 重新分配内存，替换旧数据
				Size = NewSize;
				glBufferData(Target, NewSize, InData, Usage);
			}
			else
			{
				// 不需要重新分配内存，直接替换旧数据
				glBufferSubData(Target, 0, Size, InData);
			}

			Unbind();
		}

		// 覆盖缓冲中指定偏移量的数据
		// InOffset 缓冲中起始偏移量
		// InData 覆盖所需数据
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

		// 覆盖缓冲中指定偏移量的数据
		// InOffset 缓冲中起始偏移量
		// InData 覆盖所需数据
		// InNumElements 元素个数
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
		// 缓冲对象名字
		GLuint Buffer;

		// 缓冲对象大小，单位bytes
		uint32 Size;

		// 缓冲中包含元素的个数
		uint32 NumElements;
	};
};

#endif