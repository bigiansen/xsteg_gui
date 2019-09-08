#pragma once

#include <imgui.h>

namespace guim
{
	struct color
	{
		float r = 0, g = 0, b = 0, a = 0;

		constexpr color() noexcept { }

		constexpr color(float fr, float fg, float fb)
		{
			r = fr;
			g = fg;
			b = fb;
		}

		constexpr color(float fr, float fg, float fb, float fa)
		{
			r = fr;
			g = fg;
			b = fb;
			a = fa;
		}

		operator ImVec4() const;
	};
}