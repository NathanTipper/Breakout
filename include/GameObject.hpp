#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "Texture2D.h"

class SpriteRenderer;

class GameObject 
{
public:
	GameObject();
	GameObject(glm::vec2 position, glm::vec2 size, Texture2D texture, glm::vec3 color = glm::vec3(1.0f), 
				glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	virtual void Draw(SpriteRenderer* renderer);

	inline glm::vec2 GetPosition() const { return m_position; }
	inline void SetPosition(const glm::vec2 newPosition) { m_position = newPosition; }

	inline glm::vec2 GetSize() const { return m_size; }
	inline void SetSize(const glm::vec2 newSize) { m_size = newSize; }

	inline glm::vec2 GetVelocity() const { return m_velocity; }
	inline void SetVelocity(const glm::vec2 newVelocity) { m_velocity = newVelocity; }

	inline glm::vec3 GetColor() const { return m_color; }
	inline void SetColor(const glm::vec3 newColor) { m_color = newColor; }

	inline float GetRotation() const { return m_rotation; }
	inline void SetRotation(const float newRotation) { m_rotation = newRotation; }

	inline Texture2D GetTexture() const { return m_texture; }
	inline void SetTexture(const Texture2D newTexture) { m_texture = newTexture; }

	inline float IsSolid() const { return m_isSolid; }
	inline void SetIsSolid(const float newIsSolid) { m_isSolid = newIsSolid; }
	
	inline float IsDestroyed() const { return m_isDestroyed; }
	inline void SetIsDestroyed(const float newIsDestroyed) { m_isDestroyed = newIsDestroyed; }
private:
	glm::vec2 m_position, m_size, m_velocity;
	glm::vec3 m_color;
	float m_rotation;
	bool m_isSolid;
	bool m_isDestroyed;
	Texture2D m_texture;
};
#endif
