#if defined _DEBUG and not defined DISABLE_WARNING
#include "warning.h"

namespace debug_impl {
namespace {
	template <typename Type>
	inline bool isInVector(const std::vector<Type> & vector, const Type & value)
	{
		return std::find(vector.begin(), vector.end(), value) != vector.end();
	}
} // unnamed namespace

	void handleWarning(const std::string_view & message, const std::string_view & position_in_code)
	{
		// Store warnings, that are ignored, globally
		static std::vector<std::string_view> ignored_warnings;

		// Check if this warning should be ignored
		if (isInVector(ignored_warnings, position_in_code))
			return;

		std::string_view info
		(
			"To ignore this warning and continue the application, press Ignore.\n\n"
			"To disable showing this particular warning in this application run, press Retry\n\n"
			"To exit apllication right now, press Abort\n"
			"\n"
			"Define DISABLE_WARNING before including \"application.h\" to disable showing any warnings at run time"
		);

		std::string final_message(message);
		final_message.append("\n\n");
		final_message.append(info);

		int result = MessageBoxA(NULL, final_message.c_str(), "DEBUG WARNING", MB_ABORTRETRYIGNORE | MB_ICONINFORMATION);

		switch (result)
		{
			// Ignore this warning in the future
		case IDRETRY:
			ignored_warnings.push_back(position_in_code);
			break;

			// Close application right now
		case IDABORT:
			exit(-1);

			//Ignore this warning right now 
		case IDIGNORE:
			return;
		}
	}
} // debug_impl namespace

#endif // #if defined _DEBUG and not defined DISABLE_WARNING