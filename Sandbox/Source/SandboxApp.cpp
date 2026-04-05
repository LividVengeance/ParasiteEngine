#include "ParasiteEngine.h"

class Sandbox : public Parasite::CApplication
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Parasite::CApplication* Parasite::CreateApplication()
{
	return new Sandbox();
}