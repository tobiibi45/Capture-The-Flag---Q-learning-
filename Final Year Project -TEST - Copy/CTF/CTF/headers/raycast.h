#pragma once
#include <Box2D/Box2D.h>

namespace KStudio
{
	class raycast : public b2RayCastCallback
	{
	public:
		raycast() : m_fixture(NULL) {}

		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override
		{
			m_fixture = fixture;
			m_normal.Set(normal.x, normal.y);

			if(fraction < this->m_closest_fraction)
			{
				this->m_closest_fraction = fraction;
				this->m_point.Set(point.x, point.y);
			}
			return 1;
		}

		void draw_line()
		{
			glColor3f(1, 0, 0); //Red
			glBegin(GL_LINES);
			glVertex2f(m_point.x, m_point.y);
			glVertex2f(m_normal.x, m_normal.y);
			glEnd();
		}

		b2Fixture* m_fixture;
		b2Vec2 m_point;
		b2Vec2 m_normal;
		float m_closest_fraction = 1.f;

	};
}
