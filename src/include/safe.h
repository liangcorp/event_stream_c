enum Result {
    Ok,
    Error,
};

enum Option {
    Some,
    None,
};

typedef struct {
    enum Result execution_result;
    short data;
} ResultInt16;

typedef struct {
    enum Result execution_result;
    int data;
} ResultInt32;

typedef struct {
    enum Result execution_result;
    long data;
} ResultInt64;

typedef struct {
    enum Result execution_result;
    long long data;
} ResultInt128;

typedef struct {
    enum Result execution_result;
    float data;
} ResultFloat32;

typedef struct {
    enum Result execution_result;
    double data;
} ResultFloat64;


typedef struct {
    enum Result execution_result;
    char data;
} ResultChar;

typedef struct {
    enum Result execution_result;
    char data;
    unsigned int length;
} ResultString;
