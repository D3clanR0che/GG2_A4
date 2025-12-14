#pragma once

namespace fw
{

	class SurvivorsCamera : public Camera
	{
	private:


	public:
		SurvivorsCamera(vec2 pos, float aspectRatio, float zoom);
		virtual ~SurvivorsCamera();

		virtual void update(float deltaTime);

		void setZoom(float zoom) { m_targetZoom = zoom; }
		void setPosition(vec2 pos) { m_position = pos; }

	private:
		float m_targetZoom = 0.0f;
	};
}