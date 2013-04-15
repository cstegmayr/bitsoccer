#pragma once

#include "Vec2.h"
#include <vector>

namespace bitsoccer
{
	struct Frame
	{
		Vec2 position;
		float rotation;
		float time;
	};

	class AnimatableObject
	{
	public:
		AnimatableObject();
		~AnimatableObject();

		void ClearKeyFrames();
		void AddKeyFrame(const Frame& keyFrame);
		const Frame& GetLastKeyFrame() const;
		const Frame& GetCurrentFrame() const;

		void SetAbsoluteTime(float time);
		void AddTime(float deltaTime);
		float GetCurrentTime() const { return m_currentTime; }
		float GetTotalTime() const;
		bool HasPlayedToEnd() const { return GetCurrentTime() >= GetTotalTime(); }
		bool HasKeyFrames() const { return !m_keyFrames.empty(); }

	private:
		void FindCurrentFrame(int startFrame);
		void RecalculateCurrentFrame();

		typedef std::vector<Frame> FrameList_t;
		FrameList_t m_keyFrames;
		Frame m_currentFrame;
		int m_currentKeyFrame;
		float m_currentTime;
	};
}