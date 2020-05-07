#pragma once

enum DiagnosticLevel : int
{
	DIAG_ERROR = 0,
	DIAG_WARNING,
	DIAG_INFO,
	DIAG_DEBUG,
	DIAG_VERBOSE
};

// Convenience macros for logging
#define DIAG_VERBOSE(msg, ...) Diagnostics::log(DIAG_VERBOSE, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define DIAG_DEBUG(msg, ...) Diagnostics::log(DIAG_DEBUG, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define DIAG_INFO(msg, ...) Diagnostics::log(DIAG_INFO,  __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define DIAG_WARNING(msg, ...) Diagnostics::log(DIAG_WARNING, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define DIAG_ERROR(msg, ...) Diagnostics::log(DIAG_ERROR, __FILE__, __LINE__, msg, ##__VA_ARGS__)

class Diagnostics
{
public:
	/// Ignore all messages below this level.
	static void setMaxLevel(DiagnosticLevel level);

	/// Log a message to stdout/stderr (depending on the level); see macros for usage example.
	/// Message for msg is similar to C printf.
	static void log(DiagnosticLevel level, const char* file, int line, const char* const msg, ...);
};
