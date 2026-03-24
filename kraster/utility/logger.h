#ifndef KRASTER_LOGGER_H
#define KRASTER_LOGGER_H

enum kraster_logger_level {
	KRASTER_LOGGER_INFO,
	KRASTER_LOGGER_DEBUG,
	KRASTER_LOGGER_WARN,
	KRASTER_LOGGER_ERROR,
	KRASTER_LOGGER_FATAL,
	KRASTER_LOGGER_TRACE
};

void kraster_log(enum kraster_logger_level level, const char *file, int line, const char *fmt, ...);

#ifndef NLOG
	#define kraster_info(...) kraster_log(KRASTER_LOGGER_INFO, __FILE__, __LINE__, __VA_ARGS__)
	#define kraster_debug(...) kraster_log(KRASTER_LOGGER_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
	#define kraster_warn(...) kraster_log(KRASTER_LOGGER_WARN, __FILE__, __LINE__, __VA_ARGS__)
	#define kraster_error(...) kraster_log(KRASTER_LOGGER_ERROR, __FILE__, __LINE__, __VA_ARGS__)
	#define kraster_fatal(...) kraster_log(KRASTER_LOGGER_FATAL, __FILE__, __LINE__, __VA_ARGS__)
	#define kraster_trace(...) kraster_log(KRASTER_LOGGER_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#else
	#define kraster_info(...)
	#define kraster_debug(...)
	#define kraster_warn(...)
	#define kraster_error(...)
	#define kraster_fatal(...)
	#define kraster_trace(...)
#endif

#endif
