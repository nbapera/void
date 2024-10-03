#pragma once

namespace bridgeassist {
	void sneak();
	void unsneak();

	inline bool is_edge = false;
	inline bool enabled = false;
	inline bool m_prev = false;
	inline bool jumped = false;
}