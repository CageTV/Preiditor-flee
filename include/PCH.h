#pragma once

#include <spdlog/sinks/basic_file_sink.h>

#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"

namespace logger = SKSE::log;
using namespace std::literals;

// CommonLib callbacks take the object by reference in CharmedBaryon's build and by pointer in alandtse's: a generic lambda plus this works with both
namespace compat
{
	template <class T>
	inline T* Ptr(T& a_ref) { return &a_ref; }
	template <class T>
	inline T* Ptr(T* a_ptr) { return a_ptr; }
}

using FormID = RE::FormID;
using RefID = RE::FormID;

const RefID player_refid = 20;