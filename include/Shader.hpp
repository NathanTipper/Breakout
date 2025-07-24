#ifndef SHADER_H
#define SHADER_H

#include "glm/glm.hpp"
enum ShaderType
{
	SHADERTYPE_VERTEX,
	SHADERTYPE_FRAGMENT,
	SHADERTYPE_GEOMETRY,
	SHADERTYPE_COUNT
};

#define SHADER_SOURCE_FILENAME_SIZE 32
class ShaderProgram
{
public:
	ShaderProgram();

	void Use();
	bool Compile();

	void SetFloat(const char* name, const float value);
	void SetInt(const char* name, const int value);
	void SetMatrix(const char* name, const float* value);
	void SetVec3(const char* name, const glm::vec3 value);

	void SetSource(ShaderType type, const char* filename);
	void Delete();

	inline unsigned int GetID() const { return m_id; }
private:
	unsigned int m_id;
	char shader_source[SHADERTYPE_COUNT][SHADER_SOURCE_FILENAME_SIZE];
	unsigned int shaders[SHADERTYPE_COUNT];
};

#endif
