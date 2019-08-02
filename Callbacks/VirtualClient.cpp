#include "VirtualClient.h"


//TODO : Try to implement a std bind with virtual (or google if its possible)
VirtualClient::VirtualClient()
{
}

void VirtualClient::registerToHandler(CallbackHandler & handler)
{
	handler.registerCallback(std::bind(&VirtualClient::update, this, std::placeholders::_1));
}
