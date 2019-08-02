#include "Callbacks.h"
#include "VirtualClient.h"


class Test : public VirtualClient
{
public:
	void update(uint32_t evnt) override final
	{
		printf("Virtual client 'test' received event: %i\n", evnt);
	}
};

class Test2 : public VirtualClient
{
public:
	void update(uint32_t evnt) override final
	{
		printf("Virtual client 'test2' received event: %i\n", evnt);
	}
};

int main()
{
	CallbackClient cb1;
	CallbackClient cb2;

	CallbackHandler cbh;

	Test test1;
	test1.registerToHandler(cbh);

	Test2 test2;
	test2.registerToHandler(cbh);


	cb1.registerToHandler(cbh);
	cb2.registerToHandler(cbh);

	cbh.triggerEvent(12345);

	getchar();

	return 0;
}