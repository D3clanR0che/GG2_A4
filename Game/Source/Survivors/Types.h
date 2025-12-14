#pragma once
#include <vector>

using vec2 = fw::vec2;
using ivec2 = fw::ivec2;
using color4f = fw::color4f;

namespace fw
{
	class Enemy;

	using EnemyList = std::vector<Enemy*>;
}