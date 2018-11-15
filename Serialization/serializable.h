#pragma once

#include "Serializator.h"

class Serializator;

class Serializable {
public:
	virtual void serialize(Serializator&) const = 0;
	virtual void deserialize(Serializator&) = 0;
};