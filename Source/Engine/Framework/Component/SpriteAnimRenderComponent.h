#pragma once
#include "Sprite.h"

namespace Jackster
{
	class SpriteAnimRenderComponent : public Sprite
	{
	public:
		struct AnimSequence
		{
			std::string name;

			float fps = 0;
			int numColumns = 0;
			int numRows = 0;

			int paddingL = 0;
			int paddingR = 0;
			int paddingD = 0;
			int paddingU = 0;

			int startFrame = 0;
			int endFrame = 0;

			bool loop = true;

			std::shared_ptr<Texture> texture;
		};

	public:
		CLASS_DECLARATION(SpriteAnimRenderComponent)

		bool Initialize() override;
		void Update(float dt) override;

		void SetSequence(const std::string& name, bool update = true);
		void UpdateSource();

	public:
		int frame = 0;
		float frameTimer = 0;

	private:
		std::string defaultSequenceName;
		std::map<std::string, AnimSequence> m_sequences;
		AnimSequence* m_sequence = nullptr;
		
	};
}