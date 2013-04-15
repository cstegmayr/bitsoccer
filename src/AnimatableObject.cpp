#include "AnimatableObject.h"

namespace bitsoccer
{
	AnimatableObject::AnimatableObject() 
		: m_currentKeyFrame(0)
		, m_currentTime(0.0f)
	{
		ClearKeyFrames();
	}

	AnimatableObject::~AnimatableObject()
	{}



	void AnimatableObject::ClearKeyFrames()
	{
		m_keyFrames.clear();
		m_currentKeyFrame = 0;
		m_currentTime = 0.0f;

		m_currentFrame.position = Vec2(0.0f, 0.0f);
		m_currentFrame.rotation = 0.0f;
		m_currentFrame.time = 0.0f;
	}

	void AnimatableObject::AddKeyFrame(const Frame& keyFrame)
	{
		if (keyFrame.time >= GetTotalTime())
		{
			m_keyFrames.push_back(keyFrame);
		}
		else
		{
			FrameList_t::iterator iter = m_keyFrames.begin();
			FrameList_t::iterator endIter = m_keyFrames.begin();
			for (; iter != endIter; ++iter)
			{
				Frame& currentFrame = *iter;
				if (currentFrame.time > keyFrame.time)
				{
					break;
				}
			}
			m_keyFrames.insert(iter, keyFrame);
		}

		FindCurrentFrame(0);
	}

	const Frame& AnimatableObject::GetCurrentFrame() const
	{
		return m_currentFrame;
	}

	void AnimatableObject::SetAbsoluteTime(float time)
	{
		m_currentTime = time;
		FindCurrentFrame(0);
	}

	void AnimatableObject::AddTime(float deltaTime)
	{
		m_currentTime += deltaTime;
		FindCurrentFrame(m_currentKeyFrame);
	}

	float AnimatableObject::GetTotalTime() const
	{
		int lastPos = m_keyFrames.size() - 1;
		return lastPos >= 0 ? m_keyFrames[lastPos].time : 0.0f;
	}

	const Frame& AnimatableObject::GetLastKeyFrame() const
	{
		int lastPos = m_keyFrames.size() - 1;
		return lastPos >= 0 ? m_keyFrames[lastPos] : m_currentFrame;		
	}

	//////////////////////////////////////////////////
	// PRIVATE METHODS
	//////////////////////////////////////////////////

	void AnimatableObject::FindCurrentFrame(int startFrame)
	{
		int numKeyFrames = m_keyFrames.size();
		for (int i = startFrame; i < numKeyFrames; ++i)
		{
			int index = i % numKeyFrames;
			Frame& currentFrame = m_keyFrames[index];
			if (currentFrame.time > m_currentTime)
			{
				m_currentKeyFrame = index - 1;
				break;
			}
		}

		RecalculateCurrentFrame();
	}

	void AnimatableObject::RecalculateCurrentFrame()
	{
		m_currentFrame = m_keyFrames[m_currentKeyFrame];

		const Frame& nextFrame = m_keyFrames[m_currentKeyFrame+1];
		float f = (m_currentTime - m_currentFrame.time) / (nextFrame.time - m_currentFrame.time);
		m_currentFrame.position += f * (nextFrame.position - m_currentFrame.position);
		m_currentFrame.rotation += f * (nextFrame.rotation - m_currentFrame.rotation);

	}
}