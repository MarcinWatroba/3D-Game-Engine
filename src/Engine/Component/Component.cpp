#include <Engine/Component/Component.h>

std::string Component::get_Type()
{
	return typeid(*this).name();
}