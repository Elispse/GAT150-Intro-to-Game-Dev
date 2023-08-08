#pragma once
#include "Framework/Resource/Resource.h"
#include <string>

struct _TTF_Font;

namespace Jackster 
{
	class Font : public Resource
	{
	public:
		Font() = default;
		Font(const std::string& fileName, int fontSize);
		~Font();

		virtual bool Create(std::string filename, ...) override;
		bool Load(const std::string& fileName, int fontSize);


		friend class Text;

	private:
		_TTF_Font* m_ttfFont = nullptr;
	};
}