#pragma once
#include "dynamicCast.h"

namespace dynamicCast {
	template<class T1, class T2>
	T1* my_dynamic_cast(T2*) {
		//
	}


	template<class T1, class T2>
	T1& my_dynamic_cast(T2&) {
		//
	}
}