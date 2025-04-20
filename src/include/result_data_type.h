#define MAX_ERROR_MESSAGE_SIZE 250

#pragma once

enum ResultEnum {
	Ok,
	Error,
};

typedef struct Result {
	enum ResultEnum result_enum;
	char error_message[MAX_ERROR_MESSAGE_SIZE];
} ResultType;
