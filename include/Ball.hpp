#ifndef BALL_H
#define BALL_H

#include "GameObject.hpp"

#define DEFAULT_BALL_RADIUS 12.5f

class Ball : public GameObject
{
	public:
		Ball();
		Ball(glm::vec2 position, Texture2D texture, float radius = DEFAULT_BALL_RADIUS, glm::vec3 color = glm::vec3(1.f),
				float rotation = 0.f, glm::vec2 velocity = glm::vec2(0.f));
		
		void Init(float radius, bool stuck);

		float GetRadius() const { return m_radius; }
		void SetRadius(float newRadius) { m_radius = newRadius; }

		bool IsStuck() const { return m_stuck; }
		void SetIsStuck(bool newIsStuck) { m_stuck = newIsStuck; }

		glm::vec2 Move(float dt, unsigned int windowWidth);
		void Reset(glm::vec2 pos, glm::vec2 velocity);
	private:
		float m_radius;
		bool m_stuck;

};

#endif // BALL_H
