#pragma once
#include "rttiInfo.h"

namespace rtti {

	class RttiBase {
	public:
		RttiBase() {};
		virtual RttiClassInfo getRttiInfo() = 0;
		virtual void rttiRegister() = 0;
	};
}
