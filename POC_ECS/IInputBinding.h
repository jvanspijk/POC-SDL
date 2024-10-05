#pragma once
#include <string>

class IInputBinding
{
public:
	std::string actionName;
	virtual bool isActionTriggered() const = 0;
};

