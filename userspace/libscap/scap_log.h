#pragma once

enum khulnasoft_log_severity
{
	KHULNASOFT_LOG_SEV_FATAL = 1,
	KHULNASOFT_LOG_SEV_CRITICAL = 2,
	KHULNASOFT_LOG_SEV_ERROR = 3,
	KHULNASOFT_LOG_SEV_WARNING = 4,
	KHULNASOFT_LOG_SEV_NOTICE = 5,
	KHULNASOFT_LOG_SEV_INFO = 6,
	KHULNASOFT_LOG_SEV_DEBUG = 7,
	KHULNASOFT_LOG_SEV_TRACE = 8,
};

typedef void (*khulnasoft_log_fn)(const char* component, const char* msg, const enum khulnasoft_log_severity sev);
