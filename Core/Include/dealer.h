#pragma once
#include "hand.h"

namespace dealer
{
	enum class action : uint8_t
	{
		hit = 1,
		stand
	};

	class dealer
	{
		public:
			hand::hand d_hand{ true };
	};
}