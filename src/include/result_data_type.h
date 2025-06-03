#pragma once

#define MAX_ERROR_MESSAGE_SIZE 250

enum ResultEnum
{
    OK,
    ERROR
};

typedef struct Result
{
    enum ResultEnum result_enum;
    char error_message[MAX_ERROR_MESSAGE_SIZE];
} Result_t;
