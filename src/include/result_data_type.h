#define MAX_ERROR_MESSAGE_SIZE 250

#pragma once

enum ResultEnum {
	Ok,
	Error,
};
enum OptionEnum {
	Some,
	None,
};

typedef struct Result {
	enum ResultEnum result_enum;

	void *data_ptr;
	char error_message[MAX_ERROR_MESSAGE_SIZE];
} ResultType;

typedef struct ResultOption {
	enum ResultEnum result_enum;

	struct Option {
		enum OptionEnum option_enum;

		void *data_ptr;
	} option_type;

	char error_message[MAX_ERROR_MESSAGE_SIZE];
} ResultOptionType;
