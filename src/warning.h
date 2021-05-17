#ifndef WARNING_H
#define WARNING_H

#if defined _DEBUG and not defined DISABLE_WARNING
#	if defined _WIN32
#	include <Windows.h>
#	include <string_view>
#	include <vector>
#	include <algorithm> // std::find

namespace debug_impl {
	void handleWarning(const std::string_view & message, const std::string_view & position_in_code);
} // debug_impl namespace

#define DEBUG_ASSERT_WARNING(cond, mess, ...)                                              \
{                                                                                          \
	if(!cond)                                                                              \
	{                                                                                      \
		/*Differentiate warnings based on the position in the code*/                       \
		constexpr size_t position_size = 1024;                                             \
		char position_in_code_c_str[position_size];                                        \
		sprintf_s(position_in_code_c_str, position_size, "%s, %d", __FILE__, __LINE__);    \
																					       \
		std::string_view position_in_code(position_in_code_c_str);                         \
																					       \
		constexpr size_t buffer_size = 512;                                                \
		char buffer[buffer_size];                                                          \
		sprintf_s(buffer, buffer_size, mess, __VA_ARGS__);                                 \
																					       \
		std::string_view message(buffer);                                                  \
																					       \
		debug_impl::handleWarning(message, position_in_code);                              \
	}                                                                                      \
}

#	else // not _WIN32
#		error Platforms other than Windows are not supported yet
#	endif // _WIN32

#else // _DEBUG not defined or DISABLE_WARNING defined
#	define DEBUG_ASSERT_WARNING(cond, mess, ...)
#endif // defined _DEBUG and not defined DISABLE_WARNING

#endif // WARNING_H