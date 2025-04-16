#include <string.h>

#define MAX_ERROR_SIZE 250

#pragma once

struct Result {
    enum ResultEnum {
        Ok,
        Error,
    } result_enum;

    struct Option {
        enum OptionEnum {
            Some,
            None,
        } option_enum ;

        void *data_ptr;
    } option_type;

    char error_message[MAX_ERROR_SIZE];
};
