#pragma once

/*
    Enumeration for managing various types of errors.
*/
typedef enum {
    no_error                = 0,

    too_many_parameters     = 1,
    too_few_parameters      = 2,

    array_not_found         = 3,
    array_already_existing  = 4,

    overflow_detected       = 5,
    underflow_detected      = 6,
    conversion_failed       = 7,

    invalid_name            = 8,

    array_size_too_big      = 9,

    parameter_not_found     =10,

    number_needed           =11,

    command_not_found       =12,

    syntax_error            =13,

    index_out_of_bounds     =14,

    alias_not_found         =15,
    alias_already_defined   =16,

    csv_not_found           =17,
    csv_type_undefined      =18,

    file_not_found          =19,

    invalid_number          =20,
    invalid_string          =21,
    
    value_info_needed       =22,

    out_of_memory           =23,

    really_bad_error        =24
    
} error_code;