#pragma once
#include <functional>
#include <vector>

typedef std::function<void(uint32_t)> cb_void_uint32;

class CallbackHandler
{
public:
	CallbackHandler();

	void registerCallback(cb_void_uint32 function);

	void triggerEvent(uint32_t value);

private:
	std::vector<cb_void_uint32> m_callbacks;
};

