struct Result {
    enum ResultEnum {
        Ok,
        Error,
    };

    struct Option {
        enum OptionEnum {
            Some,
            None,
        };

        void *data_ptr;
    };
};
