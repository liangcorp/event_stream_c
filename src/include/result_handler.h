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
};
