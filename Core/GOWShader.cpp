#include "GOWShader.h"

using namespace GOW;

int32 GOWShader::Counter = 0;
int32 GOWShader::UsedID = -1;
std::vector<std::string> GOWShader::Paths = { "./" };

void GOWShader::AddPath(const std::string& InPath)
{
	std::string Path = InPath;

	if (Path[Path.length() - 1] != '/')
		Path += '/';

	if (std::find(Paths.begin(), Paths.end(), Path) == Paths.end())
		Paths.push_back(Path);
}

GOWShader::GOWShader()
{
	if (Counter < 0)
	{
		std::string Error("Error creating new shader program");
		GOWEngine::ErrorString.push_back(Error);
		throw std::runtime_error(Error);
	}

	ID = Counter;
	Counter++;
	bTransformFeedback = false;
	bModify = true;
	bLinked = false;

	Program = glCreateProgram();

	if (!Program)
	{
		std::string Error("Error creating new shader program");
		GOWEngine::ErrorString.push_back(Error);
		throw std::runtime_error(Error);
	}
}

GOWShader::~GOWShader()
{
	glDeleteProgram(Program);
}

bool GOWShader::AttachFile(const std::string& InFileName, GLenum InType)
{
	std::string Path;
	GLint Compiled;
	int32 InfoLogLength = 0;
	std::ifstream File;
	const char* Code;
	GLint ShaderName;
	GLint Size;

	if ((InFileName.length() > 1 && InFileName[0] == '/') ||
		(InFileName.length() > 2 && InFileName[1] == ':'))
	{
		File.open(InFileName.c_str(), std::ifstream::in | std::ifstream::binary);
		Path = InFileName;
	}
	else
	{
		for (uint32 i = 0; i < Paths.size(); i++)
		{
			File.open((Paths[i] + InFileName).c_str(), std::ifstream::in | std::ifstream::binary);
			if (File)
			{
				Path = Paths[i] + InFileName;
				break;
			}
		}
	}

	if (!File)
	{
		GOWEngine::ErrorString.push_back(std::string("Could not open shader file: ") + InFileName);
		return false;
	}

	File.seekg(0, File.end);
	Size = static_cast<GLint>(File.tellg());
	File.seekg(0, File.beg);
	std::unique_ptr<char[]> Buffer = std::make_unique<char[]>(Size);
	File.read(Buffer.get(), Size);

	File.close();

	Code = Buffer.get();

	ShaderName = glCreateShader(InType);
	glShaderSource(ShaderName, 1, &Code, &Size);
	glCompileShader(ShaderName);
	glGetShaderiv(ShaderName, GL_COMPILE_STATUS, &Compiled);

	if (!Compiled)
	{
		glGetShaderiv(ShaderName, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::unique_ptr<char[]> InfoLog = std::make_unique<char[]>(InfoLogLength);
		glGetShaderInfoLog(ShaderName, InfoLogLength, &InfoLogLength, InfoLog.get());
		std::cerr << "CompileShader() infolog " 
				<< InFileName 
				<< std::endl
				<< InfoLog.get()
				<< std::endl;

		glDeleteShader(ShaderName);
		return false;
	}

	glAttachShader(Program, ShaderName);
	Attached.push_back(ShaderName);

	if (bModify)
	{
		ShaderPaths[Path] = InType;
	}
	
	glDeleteShader(ShaderName);
	return true;
}

bool GOWShader::AttachString(const std::string& InShaderString, GLenum InType)
{
	GLint Compiled;
	const char* StringPtr = InShaderString.c_str();
	int32 Size = InShaderString.length();
	int32 InfoLogLength = 0;

	GLint ShaderName = glCreateShader(InType);
	glShaderSource(ShaderName, 1, &(StringPtr), &Size);
	glCompileShader(ShaderName);
	glGetShaderiv(ShaderName, GL_COMPILE_STATUS, &Compiled);

	if (!Compiled)
	{
		glGetShaderiv(ShaderName, GL_INFO_LOG_LENGTH, &InfoLogLength);

		std::unique_ptr<char[]> InfoLog = std::make_unique<char[]>(InfoLogLength);

		glGetShaderInfoLog(ShaderName, sizeof(InfoLog), &InfoLogLength, InfoLog.get());
		std::cerr << "CompileShader() infolog " << std::endl << InfoLog.get() << std::endl;
		glDeleteShader(ShaderName);

		return false;
	}

	glAttachShader(Program, ShaderName);
	Attached.push_back(ShaderName);

	if (bModify)
	{
		ShaderStrings[InShaderString] = InType;
	}

	glDeleteShader(ShaderName);

	return true;
}

void GOWShader::SetTransformFeedbackVariables(std::vector<std::string>& InVariables, GLenum InBufferMode)
{
	bTransformFeedback = true;
	std::vector<const char*> Variables(InVariables.size());

	for (uint32 i = 0; i < Variables.size(); i++)
	{
		Variables[i] = InVariables[i].c_str();
	}

	glTransformFeedbackVaryings(Program, InVariables.size(), Variables.data(), InBufferMode);

	if (bLinked)
	{
		Link();
	}
}

void  GOWShader::ReCompile()
{
	bModify = false;

	UnUse();
	glDeleteShader(Program);

	Program = glCreateProgram();

	for (const std::pair<std::string, GLenum>& It : ShaderPaths)
	{
		AttachFile(It.first, It.second);
	}

	for (const std::pair<std::string, GLenum>& It : ShaderStrings)
	{
		AttachString(It.first, It.second);
	}

	Link();

	bModify = true;
}

bool GOWShader::Link()
{
	GLint IsLinked = 0;
	glLinkProgram(Program);
	glGetProgramiv(Program, GL_LINK_STATUS, &IsLinked);

	if (IsLinked == GL_FALSE)
	{
		bLinked = false;
		return false;
	}

	for (GLuint ShaderName : Attached)
	{
		glDetachShader(Program, ShaderName);
	}

	bLinked = true;
	return true;
}

void GOWShader::Use()
{
	if (UsedID == ID)
		return;

	UsedID = ID;
	glUseProgram(Program);
}

void GOWShader::UnUse()
{
	if (UsedID = ID)
		glUseProgram(0);

	UsedID = -1;
}

int32 GOWShader::GetAttributeLocation(const std::string& InName)
{
	return glGetAttribLocation(Program, InName.c_str());
}

int32 GOWShader::GetUniformLocation(const std::string& InName)
{
	return glGetUniformLocation(Program, InName.c_str());
}

void GOWShader::SetUniform(int32 InLocation, const glm::vec2& InValue)
{
	SetUniform(InLocation, InValue.x, InValue.y);
}

void GOWShader::SetUniform(int32 InLocation, const glm::dvec2& InValue)
{
	SetUniform(InLocation, InValue.x, InValue.y);
}

void GOWShader::SetUniform(int32 InLocation, const glm::vec3& InValue)
{
	SetUniform(InLocation, InValue.x, InValue.y, InValue.z);
}

void GOWShader::SetUniform(int32 InLocation, const glm::dvec3& InValue)
{
	SetUniform(InLocation, InValue.x, InValue.y, InValue.z);
}

void GOWShader::SetUniform(int32 InLocation, const glm::vec4& InValue)
{
	SetUniform(InLocation, InValue.x, InValue.y, InValue.z, InValue.w);
}

void GOWShader::SetUniform(int32 InLocaiton, const glm::dvec4& InValue)
{
	SetUniform(InLocaiton, InValue.x, InValue.y, InValue.z, InValue.w);
}

void GOWShader::SetUniform(const std::string& InName, const glm::vec2& InValue)
{
	SetUniform(InName, InValue.x, InValue.y);
}

void GOWShader::SetUniform(const std::string& InName, const glm::dvec2& InValue)
{
	SetUniform(InName, InValue.x, InValue.y);
}

void GOWShader::SetUniform(const std::string& InName, const glm::vec3& InValue)
{
	SetUniform(InName, InValue.x, InValue.y, InValue.z);
}

void GOWShader::SetUniform(const std::string& InName, const glm::dvec3& InValue)
{
	SetUniform(InName, InValue.x, InValue.y, InValue.z);
}

void GOWShader::SetUniform(const std::string& InName, const glm::vec4& InValue)
{
	SetUniform(InName, InValue.x, InValue.y, InValue.z, InValue.w);
}

void GOWShader::SetUniform(const std::string& InName, const glm::dvec4& InValue)
{
	SetUniform(InName, InValue.x, InValue.y, InValue.z, InValue.z);
}

void GOWShader::SetUniform(int32 InLocation, bool InTranspose, const glm::mat2& InValue)
{
	SetUniform(InLocation, 1, 2, 2, InTranspose, glm::value_ptr(InValue));
}

void GOWShader::SetUniform(int32 InLocation, bool InTranspose, const glm::dmat2& InValue)
{
	SetUniform(InLocation, 1, 2, 2, InTranspose, glm::value_ptr(InValue));
}

void GOWShader::SetUniform(int32 InLocation, bool InTranspose, const glm::mat3& InValue)
{
	SetUniform(InLocation, 1, 3, 3, InTranspose, glm::value_ptr(InValue));
}

void GOWShader::SetUniform(int32 InLocation, bool InTranspose, const glm::dmat3& InValue)
{
	SetUniform(InLocation, 1, 3, 3, InTranspose, glm::value_ptr(InValue));
}

void GOWShader::SetUniform(int32 InLocation, bool InTranspose, const glm::mat4& InValue)
{
	SetUniform(InLocation, 1, 4, 4, InTranspose, glm::value_ptr(InValue));
}

void GOWShader::SetUniform(int32 InLocation, bool InTranspose, const glm::dmat4& InValue)
{
	SetUniform(InLocation, 1, 4, 4, InTranspose, glm::value_ptr(InValue));
}

void GOWShader::SetUniform(const std::string& InName, bool InTranspose, const glm::mat2& InValue)
{
	SetUniform(InName, 1, 2, 2, InTranspose, glm::value_ptr(InValue));
}

void GOWShader::SetUniform(const std::string& InName, bool InTranspose, const glm::dmat2& InValue)
{
	SetUniform(InName, 1, 2, 2, InTranspose, glm::value_ptr(InValue));
}

void GOWShader::SetUniform(const std::string& InName, bool InTranspose, const glm::mat3& InValue)
{
	SetUniform(InName, 1, 3, 3, InTranspose, glm::value_ptr(InValue));
}

void GOWShader::SetUniform(const std::string& InName, bool InTranspose, const glm::dmat3& InValue)
{
	SetUniform(InName, 1, 3, 3, InTranspose, glm::value_ptr(InValue));
}

void GOWShader::SetUniform(const std::string& InName, bool InTranspose, const glm::mat4& InValue)
{
	SetUniform(InName, 1, 4, 4, InTranspose, glm::value_ptr(InValue));
}

void GOWShader::SetUniform(const std::string& InName, bool InTranspose, const glm::dmat4& InValue)
{
	SetUniform(InName, 1, 4, 4, InTranspose, glm::value_ptr(InValue));
}

void GOWShader::SetUniform(int32 InLocation, const std::vector<glm::vec2>& InValue)
{
	if (InValue.size() == 0)
		return;

	SetUniform(InLocation, InValue.size(), 2, glm::value_ptr(InValue[0]));
}

void GOWShader::SetUniform(int32 InLocation, const std::vector<glm::dvec2>& InValue)
{
	if (InValue.size() == 0)
		return;

	SetUniform(InLocation, InValue.size(), 2, glm::value_ptr(InValue[0]));
}

void GOWShader::SetUniform(int32 InLocation, const std::vector<glm::vec3>& InValue)
{
	if (InValue.size() == 0)
		return;

	SetUniform(InLocation, InValue.size(), 3, glm::value_ptr(InValue[0]));
}

void GOWShader::SetUniform(int32 InLocation, const std::vector<glm::dvec3>& InValue)
{
	if (InValue.size() == 0)
		return;

	SetUniform(InLocation, InValue.size(), 3, glm::value_ptr(InValue[0]));
}

void GOWShader::SetUniform(int32 InLocation, const std::vector<glm::vec4>& InValue)
{
	if (InValue.size() == 0)
		return;

	SetUniform(InLocation, InValue.size(), 4, glm::value_ptr(InValue[0]));
}

void GOWShader::SetUniform(int32 InLocation, const std::vector<glm::dvec4>& InValue)
{
	if (InValue.size() == 0)
		return;

	SetUniform(InLocation, InValue.size(), 4, glm::value_ptr(InValue[0]));
}

void GOWShader::SetUniform(const std::string& InName, const std::vector<glm::vec2>& InValue)
{
	if (InValue.size() == 0)
		return;

	SetUniform(InName, InValue.size(), 2, glm::value_ptr(InValue[0]));
}

void GOWShader::SetUniform(const std::string& InName, const std::vector<glm::dvec2>& InValue)
{
	if (InValue.size() == 0)
		return;

	SetUniform(InName, InValue.size(), 2, glm::value_ptr(InValue[0]));
}

void GOWShader::SetUniform(const std::string& InName, const std::vector<glm::vec3>& InValue)
{
	if (InValue.size() == 0)
		return;

	SetUniform(InName, InValue.size(), 3, glm::value_ptr(InValue[0]));
}

void GOWShader::SetUniform(const std::string& InName, const std::vector<glm::dvec3>& InValue)
{
	if (InValue.size() == 0)
		return;

	SetUniform(InName, InValue.size(), 3, glm::value_ptr(InValue[0]));
}

void GOWShader::SetUniform(const std::string& InName, const std::vector<glm::vec4>& InValue)
{
	if (InValue.size() == 0)
		return;

	SetUniform(InName, InValue.size(), 4, glm::value_ptr(InValue[0]));
}

void GOWShader::SetUniform(const std::string& InName, const std::vector<glm::dvec4>& InValue)
{
	if (InValue.size() == 0)
		return;

	SetUniform(InName, InValue.size(), 4, glm::value_ptr(InValue[0]));
}

void GOWShader::SetUniform(int32 InLocation, bool InTranspose, const std::vector<glm::mat2>& InValue)
{
	if (InValue.size() == 0)
		return;

	SetUniform(InLocation, InValue.size(), 2, 2, InTranspose, glm::value_ptr(InValue[0]));
}

void GOWShader::SetUniform(int32 InLocation, bool InTranspose, const std::vector<glm::dmat2>& InValue)
{
	if (InValue.size() == 0)
		return;

	SetUniform(InLocation, InValue.size(), 2, 2, InTranspose, glm::value_ptr(InValue[0]));
}

void GOWShader::SetUniform(int32 InLocation, bool InTranspose, const std::vector<glm::mat3>& InValue)
{
	if (InValue.size() == 0)
		return;

	SetUniform(InLocation, InValue.size(), 3, 3, InTranspose, glm::value_ptr(InValue[0]));
}

void GOWShader::SetUniform(int32 InLocation, bool InTranspose, const std::vector<glm::dmat3>& InValue)
{
	if (InValue.size() == 0)
		return;

	SetUniform(InLocation, InValue.size(), 3, 3, InTranspose, glm::value_ptr(InValue[0]));
}

void GOWShader::SetUniform(int32 InLocation, bool InTranspose, const std::vector<glm::mat4>& InValue)
{
	if (InValue.size() == 0)
		return;

	SetUniform(InLocation, InValue.size(), 4, 4, InTranspose, glm::value_ptr(InValue[0]));
}

void GOWShader::SetUniform(int32 InLocation, bool InTranspose, const std::vector<glm::dmat4>& InValue)
{
	if (InValue.size() == 0)
		return;

	SetUniform(InLocation, InValue.size(), 4, 4, InTranspose, glm::value_ptr(InValue[0]));
}

void GOWShader::SetUniform(const std::string& InName, bool InTranspose, const std::vector<glm::mat2>& InValue)
{
	if (InValue.size() == 0)
		return;

	SetUniform(InName, InValue.size(), 2, 2, InTranspose, glm::value_ptr(InValue[0]));
}

void GOWShader::SetUniform(const std::string& InName, bool InTranspose, const std::vector<glm::dmat2>& InValue)
{
	if (InValue.size() == 0)
		return;

	SetUniform(InName, InValue.size(), 2, 2, InTranspose, glm::value_ptr(InValue[0]));
}

void GOWShader::SetUniform(const std::string& InName, bool InTranspose, const std::vector<glm::mat3>& InValue)
{
	if (InValue.size() == 0)
		return;

	SetUniform(InName, InValue.size(), 3, 3, InTranspose, glm::value_ptr(InValue[0]));
}

void GOWShader::SetUniform(const std::string& InName, bool InTranspose, const std::vector<glm::dmat3>& InValue)
{
	if (InValue.size() == 0)
		return;

	SetUniform(InName, InValue.size(), 3, 3, InTranspose, glm::value_ptr(InValue[0]));
}

void GOWShader::SetUniform(const std::string& InName, bool InTranspose, const std::vector<glm::mat4>& InValue)
{
	if (InValue.size() == 0)
		return;

	SetUniform(InName, InValue.size(), 4, 4, InTranspose, glm::value_ptr(InValue[0]));
}

void GOWShader::SetUniform(const std::string& InName, bool InTranspose, const std::vector<glm::dmat4>& InValue)
{
	if (InValue.size() == 0)
		return;

	SetUniform(InName, InValue.size(), 4, 4, InTranspose, glm::value_ptr(InValue[0]));
}
