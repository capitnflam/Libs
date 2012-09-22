#include <iostream>

#include <WinUnit.h>

#include <DesignPatterns.h>

namespace
{
	class RElement
		: public DesignPatterns::RegistryElement
	{
	public:
		virtual ~RElement ()
		{
		}
	protected:
	private:
		int foo;
		int bar;
		char acter;
	};
}

BEGIN_TEST(RegistryIsSingleton)
{
	DesignPatterns::RegistryManager& rm = DesignPatterns::RegistryManager::getInstance();

	WIN_ASSERT_EQUAL(&rm, &DesignPatterns::RegistryManager::getInstance());
}
END_TEST

FIXTURE(RegistrySetup1);
SETUP(RegistrySetup1)
{
	DesignPatterns::RegistryManager& rm = DesignPatterns::RegistryManager::getInstance();

	rm.addElement("foobar", new RElement());
	rm.addElement("azerty:qwerty", new RElement());
}
TEARDOWN(RegistrySetup1)
{
	DesignPatterns::RegistryManager& rm = DesignPatterns::RegistryManager::getInstance();

	delete rm.getElement("foobar");
	delete rm.getElement("azerty:qwerty");
}

BEGIN_TESTF(OnePresent, RegistrySetup1)
{
	DesignPatterns::RegistryManager& rm = DesignPatterns::RegistryManager::getInstance();

	WIN_ASSERT_NOT_NULL(rm.getElement("foobar"));
}
END_TESTF

BEGIN_TESTF(OneNotPresent, RegistrySetup1)
{
	DesignPatterns::RegistryManager& rm = DesignPatterns::RegistryManager::getInstance();

	WIN_ASSERT_NULL(rm.getElement("bazqux"));
}
END_TESTF

BEGIN_TESTF(Dump, RegistrySetup1)
{
	DesignPatterns::RegistryManager& rm = DesignPatterns::RegistryManager::getInstance();

	rm.Dump(std::cout);

	WIN_ASSERT_NULL((void*)0);
}
END_TESTF