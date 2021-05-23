#ifndef __LLL_H__
#define __LLL_H__ 1
#include <stdint.h>
#include <stdio.h>



#ifdef _MSC_VER
#ifdef __LLL_LIB_COMPILATION__
#define __LLL_IMPORT_EXPORT __declspec(dllexport)
#else
#define __LLL_IMPORT_EXPORT __declspec(dllimport)
#endif
#define __LLL_CHECK_OUTPUT _Check_return_
#else
#define __LLL_IMPORT_EXPORT
#define __LLL_CHECK_OUTPUT __attribute__((warn_unused_result))
#endif

#define LLL_ERROR_UNKNOWN 0
#define LLL_ERROR_INTERNAL_STACK_OVERFLOW 1
#define LLL_ERROR_UNMATCHED_OPEN_PARENTHESES 2
#define LLL_ERROR_UNMATCHED_CLOSE_PARENTHESES 3
#define LLL_ERROR_UNMATCHED_OPEN_QUOTE 4
#define LLL_ERROR_UNMATCHED_CURLY_OPEN_BRACKETS 5
#define LLL_ERROR_UNMATCHED_CURLY_CLOSE_BRACKETS 6
#define LLL_ERROR_UNMATCHED_QUOTES 7
#define LLL_ERROR_EMPTY_CHAR_STRING 8
#define LLL_ERROR_UNTERMINATED_CHAR_STRING 9
#define LLL_ERROR_UNTERMINATED_ESCAPE_SEQUENCE 10
#define LLL_ERROR_UNKNOWN_ESCAPE_CHARACTER 11
#define LLL_ERROR_UNTERMINATED_HEX_ESCAPE_SEQUENCE 12
#define LLL_ERROR_UNKNOWN_HEXADECIMAL_CHARCTER 13
#define LLL_ERROR_UNKNOWN_DECIMAL_CHARCTER 14
#define LLL_ERROR_UNKNOWN_OCTAL_CHARCTER 15
#define LLL_ERROR_UNKNOWN_BINARY_CHARCTER 16
#define LLL_ERROR_UNKNOWN_SYMBOL 17
#define LLL_ERROR_UNKNOWN_MODIFIER 18
#define LLL_ERROR_UNKNOWN_OUTPUT_MODIFIER 19
#define LLL_ERROR_UNKNOWN_IDENTIFIER_CHARACTER 20
#define LLL_ERROR_UNEXPECTED_CHARACTER 21
#define LLL_ERROR_UNSUPPORTED_8BIT_FLOAT_SIZE 22
#define LLL_ERROR_UNSUPPORTED_16BIT_FLOAT_SIZE 23
#define LLL_ERROR_SYMBOL_TOO_LONG 24
#define LLL_ERROR_MODIFIER_TOO_LONG 25
#define LLL_ERROR_NO_SYMBOL 26
#define LLL_ERROR_TOO_MANY_ARGUMENTS 27
#define LLL_ERROR_TOO_MANY_STATEMENTS 28
#define LLL_ERROR_MATH_OP_NOT_ENOUGH_ARGUMENTS 29
#define LLL_ERROR_MATH_OP_TOO_MANY_ARGUMENTS 30
#define LLL_ERROR_MULTIPLE_OUTPUT_TYPE_MODIFIERS 31
#define LLL_ERROR_FOR_NOT_ENOUGH_ARGUMENTS 32
#define LLL_ERROR_SET_NOT_ENOUGH_ARGUMENTS 33
#define LLL_ERROR_SET_NO_INDENTIFIER 34
#define LLL_ERROR_MULTIPLE_SIZE_MODIFIERS 35
#define LLL_ERROR_UNUSED_MODIFIERS 36
#define LLL_ERROR_NO_STACK 37
#define LLL_ERROR_STACK_TOO_BIG 38
#define LLL_ERROR_FAILED_FILE_WRITE 39
#define LLL_ERROR_DIVISION_BY_ZERO 40
#define LLL_ERROR_INVALID_FILE_FORMAT 41
#define LLL_ERROR_ASSERTION 255
#define LLL_MAX_SYNTAX_ERROR LLL_ERROR_UNUSED_MODIFIERS

#define LLL_RETURN_ERROR 0
#define LLL_RETURN_NO_ERROR 1
#define LLL_RETURN_ERROR_AS_OBJECT(e) ((lll_object_t*)(e))

#define LLL_OBJECT_TYPE_UNKNOWN 0
#define LLL_OBJECT_TYPE_CHAR 1
#define LLL_OBJECT_TYPE_INT 2
#define LLL_OBJECT_TYPE_FLOAT 3
#define LLL_OBJECT_TYPE_NIL 4
#define LLL_OBJECT_TYPE_TRUE 5
#define LLL_OBJECT_TYPE_FALSE 6
#define LLL_OBJECT_TYPE_STRING 7
#define LLL_OBJECT_TYPE_IDENTIFIER 8
#define LLL_OBJECT_TYPE_CAST_CHAR 9
#define LLL_OBJECT_TYPE_CAST_STRING 10
#define LLL_OBJECT_TYPE_CAST_INT 11
#define LLL_OBJECT_TYPE_CAST_INT64 12
#define LLL_OBJECT_TYPE_CAST_FLOAT 13
#define LLL_OBJECT_TYPE_CAST_FLOAT64 14
#define LLL_OBJECT_TYPE_CAST_BOOL 15
#define LLL_OBJECT_TYPE_FUNC_PRINT 16
#define LLL_OBJECT_TYPE_FUNC_PTR 17
#define LLL_OBJECT_TYPE_FUNC_TYPEOF 18
#define LLL_OBJECT_TYPE_AND 19
#define LLL_OBJECT_TYPE_OR 20
#define LLL_OBJECT_TYPE_NOT 21
#define LLL_OBJECT_TYPE_SET 22
#define LLL_OBJECT_TYPE_FUNC 23
#define LLL_OBJECT_TYPE_IF 24
#define LLL_OBJECT_TYPE_FOR 25
#define LLL_OBJECT_TYPE_ADD 26
#define LLL_OBJECT_TYPE_SUB 27
#define LLL_OBJECT_TYPE_MULT 28
#define LLL_OBJECT_TYPE_DIV 29
#define LLL_OBJECT_TYPE_FLOOR_DIV 30
#define LLL_OBJECT_TYPE_MOD 31
#define LLL_OBJECT_TYPE_BIT_AND 32
#define LLL_OBJECT_TYPE_BIT_OR 33
#define LLL_OBJECT_TYPE_BIT_XOR 34
#define LLL_OBJECT_TYPE_BIT_NOT 35
#define LLL_OBJECT_TYPE_DIV_MOD 36
#define LLL_OBJECT_TYPE_POW 37
#define LLL_OBJECT_TYPE_ROOT 38
#define LLL_OBJECT_TYPE_FLOOR_ROOT 39
#define LLL_OBJECT_TYPE_LOG 40
#define LLL_OBJECT_TYPE_FLOOR_LOG 41
#define LLL_OBJECT_TYPE_LESS 42
#define LLL_OBJECT_TYPE_LESS_EQUAL 43
#define LLL_OBJECT_TYPE_EQUAL 44
#define LLL_OBJECT_TYPE_NOT_EQUAL 45
#define LLL_OBJECT_TYPE_MORE 46
#define LLL_OBJECT_TYPE_MORE_EQUAL 47
#define LLL_OBJECT_TYPE_OPERATION_LIST 62
#define LLL_OBJECT_TYPE_DEBUG_DATA 63
#define LLL_OBJECT_TYPE_NOP 0xff
#define LLL_OBJECT_TYPE_INT16_FLAG 0x40
#define LLL_OBJECT_TYPE_INT32_FLAG 0x80
#define LLL_OBJECT_TYPE_INT64_FLAG 0xc0
#define LLL_OBJECT_TYPE_INT_TYPE_MASK 0xc0
#define LLL_OBJECT_TYPE_FLOAT64_FLAG 0x40
#define LLL_OBJECT_TYPE_CONST 0x80
#define LLL_OBJECT_TYPE_MAX_INTEGRAL_TYPE LLL_OBJECT_TYPE_FALSE
#define LLL_OBJECT_TYPE_MAX_TYPE LLL_OBJECT_TYPE_IDENTIFIER
#define LLL_OBJECT_TYPE_MAX_FUNC LLL_OBJECT_TYPE_FUNC_TYPEOF
#define LLL_OBJECT_TYPE_MAX_FLOW LLL_OBJECT_TYPE_FOR
#define LLL_OBJECT_TYPE_MAX_MATH LLL_OBJECT_TYPE_FLOOR_LOG
#define LLL_OBJECT_TYPE_MAX_MATH_CHAIN LLL_OBJECT_TYPE_BIT_NOT
#define LLL_OBJECT_TYPE_MAX_COMPARE LLL_OBJECT_TYPE_MORE_EQUAL
#define LLL_OBJECT_TYPE_MIN_EXTRA LLL_OBJECT_TYPE_OPERATION_LIST
#define LLL_IS_OBJECT_INT16(o) (((o)->t&LLL_OBJECT_TYPE_INT_TYPE_MASK)==LLL_OBJECT_TYPE_INT16_FLAG)
#define LLL_IS_OBJECT_INT32(o) (((o)->t&LLL_OBJECT_TYPE_INT_TYPE_MASK)==LLL_OBJECT_TYPE_INT32_FLAG)
#define LLL_IS_OBJECT_INT64(o) (((o)->t&LLL_OBJECT_TYPE_INT_TYPE_MASK)==LLL_OBJECT_TYPE_INT64_FLAG)
#define LLL_IS_OBJECT_FLOAT64(o) ((o)->t&LLL_OBJECT_TYPE_FLOAT64_FLAG)
#define LLL_IS_OBJECT_TYPE_NOT_INTEGRAL(o) (LLL_GET_OBJECT_TYPE(o)>LLL_OBJECT_TYPE_MAX_INTEGRAL_TYPE)
#define LLL_IS_OBJECT_TYPE_TYPE(o) (LLL_GET_OBJECT_TYPE(o)<=LLL_OBJECT_TYPE_MAX_TYPE)
#define LLL_IS_OBJECT_TYPE_NOT_TYPE(o) (LLL_GET_OBJECT_TYPE(o)>LLL_OBJECT_TYPE_MAX_TYPE)
#define LLL_IS_OBJECT_TYPE_MATH(o) (LLL_GET_OBJECT_TYPE(o)>LLL_OBJECT_TYPE_MAX_FLOW&&LLL_GET_OBJECT_TYPE(o)<=LLL_OBJECT_TYPE_MAX_MATH)
#define LLL_IS_OBJECT_TYPE_MATH_CHAIN(o) (LLL_GET_OBJECT_TYPE(o)>LLL_OBJECT_TYPE_MAX_FLOW&&LLL_GET_OBJECT_TYPE(o)<=LLL_OBJECT_TYPE_MAX_MATH_CHAIN)
#define LLL_IS_OBJECT_TYPE_MATH_NO_CHAIN(o) (LLL_GET_OBJECT_TYPE(o)>LLL_OBJECT_TYPE_MAX_MATH_CHAIN&&LLL_GET_OBJECT_TYPE(o)<=LLL_OBJECT_TYPE_MAX_MATH)
#define LLL_IS_OBJECT_TYPE_COMPARE(o) (LLL_GET_OBJECT_TYPE(o)>LLL_OBJECT_TYPE_MAX_MATH&&LLL_GET_OBJECT_TYPE(o)<=LLL_OBJECT_TYPE_MAX_COMPARE)
#define LLL_IS_OBJECT_UNKNOWN(o) (!((o)->t&0x3f))
#define LLL_IS_OBJECT_CONST(o) ((o)->t>>7)
#define LLL_GET_OBJECT_TYPE(o) ((o)->t&0x3f)
#define LLL_GET_OBJECT_INTEGER_WIDTH(o) (1ull<<((o)->t>>6))
#define LLL_GET_OBJECT_ARGUMENT_COUNT(o) ((lll_arg_count_t*)LLL_GET_OBJECT_WITH_OFFSET((o),sizeof(lll_object_t)))
#define LLL_GET_OBJECT_ARGUMENT(o,i) ((lll_object_t*)LLL_GET_OBJECT_WITH_OFFSET((o),(i)))
#define LLL_GET_OBJECT_STATEMENT_COUNT(o) ((lll_statement_count_t*)LLL_GET_OBJECT_WITH_OFFSET((o),sizeof(lll_object_t)))
#define LLL_GET_OBJECT_STATEMENT(o,i) ((lll_object_t*)LLL_GET_OBJECT_WITH_OFFSET((o),(i)))
#define LLL_GET_OBJECT_AS_CHAR(o) (*((char*)LLL_GET_OBJECT_WITH_OFFSET((o),sizeof(lll_object_t))))
#define LLL_GET_OBJECT_AS_INT8(o) (*((int8_t*)LLL_GET_OBJECT_WITH_OFFSET((o),sizeof(lll_object_t))))
#define LLL_GET_OBJECT_AS_INT16(o) (*((int16_t*)LLL_GET_OBJECT_WITH_OFFSET((o),sizeof(lll_object_t))))
#define LLL_GET_OBJECT_AS_INT32(o) (*((int32_t*)LLL_GET_OBJECT_WITH_OFFSET((o),sizeof(lll_object_t))))
#define LLL_GET_OBJECT_AS_INT64(o) (*((int64_t*)LLL_GET_OBJECT_WITH_OFFSET((o),sizeof(lll_object_t))))
#define LLL_GET_OBJECT_AS_FLOAT32(o) (*((float*)LLL_GET_OBJECT_WITH_OFFSET((o),sizeof(lll_object_t))))
#define LLL_GET_OBJECT_AS_FLOAT64(o) (*((double*)LLL_GET_OBJECT_WITH_OFFSET((o),sizeof(lll_object_t))))
#define LLL_GET_OBJECT_STRING_LENGTH(o) (*((lll_string_length_t*)LLL_GET_OBJECT_WITH_OFFSET((o),sizeof(lll_object_t))))
#define LLL_GET_OBJECT_AS_IDENTIFIER(o) (*((lll_identifier_index_t*)LLL_GET_OBJECT_WITH_OFFSET((o),sizeof(lll_object_t))))
#define LLL_GET_OBJECT_AS_STRING(o) ((char*)LLL_GET_OBJECT_WITH_OFFSET((o),sizeof(lll_object_t)+sizeof(lll_string_length_t)))
#define LLL_GET_OBJECT_AFTER_NOP(o) ((lll_object_t*)LLL_GET_OBJECT_WITH_OFFSET((o),sizeof(lll_object_type_t)))
#define LLL_SET_OBJECT_AS_INT8(o,i) ((*((int8_t*)LLL_GET_OBJECT_WITH_OFFSET((o),sizeof(lll_object_t))))=((int8_t)(i)))
#define LLL_SET_OBJECT_AS_INT16(o,i) ((*((int16_t*)LLL_GET_OBJECT_WITH_OFFSET((o),sizeof(lll_object_t))))=((int16_t)(i)))
#define LLL_SET_OBJECT_AS_INT32(o,i) ((*((int32_t*)LLL_GET_OBJECT_WITH_OFFSET((o),sizeof(lll_object_t))))=((int32_t)(i)))
#define LLL_SET_OBJECT_AS_INT64(o,i) ((*((int64_t*)LLL_GET_OBJECT_WITH_OFFSET((o),sizeof(lll_object_t))))=((int64_t)(i)))
#define LLL_SET_OBJECT_AS_FLOAT32(o,f) ((*((float*)LLL_GET_OBJECT_WITH_OFFSET((o),sizeof(lll_object_t))))=((float)(f)))
#define LLL_SET_OBJECT_AS_FLOAT64(o,f) ((*((double*)LLL_GET_OBJECT_WITH_OFFSET((o),sizeof(lll_object_t))))=((double)(f)))
#define LLL_SET_OBJECT_STRING_LENGTH(o,sz) ((*((lll_string_length_t*)LLL_GET_OBJECT_WITH_OFFSET((o),sizeof(lll_object_t))))=((lll_string_length_t)(sz)))
#define LLL_SET_OBJECT_AS_IDENTIFIER(o,sz) ((*((lll_identifier_index_t*)LLL_GET_OBJECT_WITH_OFFSET((o),sizeof(lll_object_t))))=((lll_identifier_index_t)(sz)))

#define LLL_OBJECT_MODIFIER_FIXED 0x1
#define LLL_OBJECT_MODIFIER_UNSIGNED 0x2
#define LLL_OBJECT_MODIFIER_SIZE 0x4
#define LLL_OBJECT_MODIFIER_8BIT 0x0
#define LLL_OBJECT_MODIFIER_16BIT 0x8
#define LLL_OBJECT_MODIFIER_32BIT 0x10
#define LLL_OBJECT_MODIFIER_64BIT 0x18
#define LLL_OBJECT_MODIFIER_SIZE_MASK 0x18
#define LLL_OBJECT_MODIFIER_ARRAY 0x20
#define LLL_OBJECT_MODIFIER_LIST 0x40
#define LLL_OBJECT_MODIFIER_LAST 0x60
#define LLL_OBJECT_MODIFIER_OUTPUT_TYPE_MASK 0x60
#define LLL_GET_MODIFIER_OBJECT_MODIFIER(o) ((lll_object_modifier_t*)LLL_GET_OBJECT_WITH_OFFSET((o),sizeof(lll_object_t)))
#define LLL_GET_MODIFIER_OBJECT_CHILD(o) ((lll_object_t*)LLL_GET_OBJECT_WITH_OFFSET((o),sizeof(lll_object_t)+sizeof(lll_object_modifier_t)))

#define LLL_DEBUG_OBJECT_LINE_NUMBER_INT8 0x0
#define LLL_DEBUG_OBJECT_LINE_NUMBER_INT16 0x1
#define LLL_DEBUG_OBJECT_LINE_NUMBER_INT32 0x2
#define LLL_DEBUG_OBJECT_COLUMN_NUMBER_INT8 0x0
#define LLL_DEBUG_OBJECT_COLUMN_NUMBER_INT16 0x4
#define LLL_DEBUG_OBJECT_COLUMN_NUMBER_INT32 0x8
#define LLL_DEBUG_OBJECT_FILE_OFFSET_INT8 0x0
#define LLL_DEBUG_OBJECT_FILE_OFFSET_INT16 0x10
#define LLL_DEBUG_OBJECT_FILE_OFFSET_INT32 0x20
#define LLL_GET_DEBUG_OBJECT_LINE_NUMBER_WIDTH(o) (1ull<<((o)->f&0x3))
#define LLL_GET_DEBUG_OBJECT_COLUMN_NUMBER_WIDTH(o) (1ull<<(((o)->f>>2)&0x3))
#define LLL_GET_DEBUG_OBJECT_FILE_OFFSET_WIDTH(o) (1ull<<((o)->f>>4))
#define LLL_GET_DEBUG_OBJECT_DATA_UINT8(o,i) (*((uint8_t*)LLL_GET_OBJECT_WITH_OFFSET((o),(i))))
#define LLL_GET_DEBUG_OBJECT_DATA_UINT16(o,i) (*((uint16_t*)LLL_GET_OBJECT_WITH_OFFSET((o),(i))))
#define LLL_GET_DEBUG_OBJECT_DATA_UINT32(o,i) (*((uint32_t*)LLL_GET_OBJECT_WITH_OFFSET((o),(i))))
#define LLL_GET_DEBUG_OBJECT_CHILD(o,i) ((lll_object_t*)LLL_GET_OBJECT_WITH_OFFSET((o),(i)))
#define LLL_SET_DEBUG_OBJECT_DATA_UINT8(o,i,v) ((*((uint8_t*)LLL_GET_OBJECT_WITH_OFFSET((o),(i))))=((uint8_t)(v)))
#define LLL_SET_DEBUG_OBJECT_DATA_UINT16(o,i,v) ((*((uint16_t*)LLL_GET_OBJECT_WITH_OFFSET((o),(i))))=((uint16_t)(v)))
#define LLL_SET_DEBUG_OBJECT_DATA_UINT32(o,i,v) ((*((uint32_t*)LLL_GET_OBJECT_WITH_OFFSET((o),(i))))=((uint32_t)(v)))

#define LLL_GET_OBJECT_WITH_OFFSET(o,i) ((void*)(((uint64_t)(void*)(o))+(i)))

#define LLL_MAX_SHORT_IDENTIFIER_LENGTH 15
#define LLL_IDENTIFIER_GET_ARRAY_ID(i) ((i)&0xf)
#define LLL_IDENTIFIER_GET_ARRAY_INDEX(i) ((i)>>4)
#define LLL_CREATE_IDENTIFIER(i,j) (((i)<<4)|(j))

#define LLL_WRITE_MODE_RAW 0
#define LLL_WRITE_MODE_ASSEMBLY 1

#define LLL_END_OF_DATA (-1)
#define LLL_READ_FROM_INPUT_DATA_STREAM(is) ((is)->rf((is)))
#define LLL_READ_BUFFER_FROM_INPUT_DATA_STREAM(is,bf,sz) ((is)->rbf((is),(bf),(sz)))
#define LLL_GET_INPUT_DATA_STREAM_OFFSET(is) ((is)->_off)
#define LLL_GET_INPUT_DATA_STREAM_LINE_NUMBER(is) ((is)->_lc)
#define LLL_GET_INPUT_DATA_STREAM_LINE_OFFSET(is) ((is)->_loff)
#define LLL_INPUT_DATA_STREAM_RESTART_LINE(is,lp) ((is)->rlf((is),(lp)))

#define LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,c) ((os)->wcf((os),(c)))
#define LLL_WRITE_STRING_TO_OUTPUT_DATA_STREAM(os,s) ((os)->wsf((os),(s)))
#define LLL_WRITE_TO_OUTPUT_DATA_STREAM(os,bf,sz) ((os)->wf((os),(bf),(sz)))



struct __LLL_INPUT_DATA_SOURCE;
struct __LLL_OUTPUT_DATA_STREAM;
struct __LLL_OBJECT;
struct __LLL_DEBUG_OBJECT;
struct __LLL_SMALL_IDENTIFIER;
struct __LLL_IDENTIFIER_LIST;
struct __LLL_IDENTIFIER;
struct __LLL_IDENTIFIER_DATA;
struct __LLL_COMPILATION_DATA;
struct __LLL_ERROR_DATA_RANGE;
union __LLL_ERROR_DATA;
struct __LLL_ERROR;



typedef uint8_t lll_object_type_t;



typedef uint8_t lll_arg_count_t;



typedef uint8_t lll_object_modifier_t;



typedef uint8_t lll_error_type_t;



typedef uint16_t lll_statement_count_t;



typedef uint16_t lll_vector_length_t;



typedef uint32_t lll_string_length_t;



typedef uint32_t lll_identifier_index_t;



typedef int (*lll_input_data_stream_read_t)(struct __LLL_INPUT_DATA_SOURCE* is);



typedef uint8_t (*lll_input_data_stream_read_buffer_t)(struct __LLL_INPUT_DATA_SOURCE* is,uint8_t* bf,uint32_t sz);



typedef void (*lll_input_data_stream_restart_line_t)(struct __LLL_INPUT_DATA_SOURCE* is,uint32_t lp);



typedef uint8_t (*lll_output_data_stream_write_char_t)(struct __LLL_OUTPUT_DATA_STREAM* os,char c);



typedef uint8_t (*lll_output_data_stream_write_string_t)(struct __LLL_OUTPUT_DATA_STREAM* os,char* s);



typedef uint8_t (*lll_output_data_stream_write_t)(struct __LLL_OUTPUT_DATA_STREAM* os,uint8_t* bf,size_t sz);



typedef struct __LLL_INPUT_DATA_SOURCE{
	void* ctx;
	lll_input_data_stream_read_t rf;
	lll_input_data_stream_read_buffer_t rbf;
	lll_input_data_stream_restart_line_t rlf;
	uint32_t _lc;
	uint32_t _off;
	uint32_t _loff;
} lll_input_data_stream_t;



typedef struct __LLL_OUTPUT_DATA_STREAM{
	void* ctx;
	lll_output_data_stream_write_char_t wcf;
	lll_output_data_stream_write_string_t wsf;
	lll_output_data_stream_write_t wf;
} lll_output_data_stream_t;



typedef struct __LLL_OBJECT{
	lll_object_type_t t;
	lll_object_modifier_t m;
} lll_object_t;



typedef struct __LLL_DEBUG_OBJECT{
	lll_object_type_t t;
	lll_object_modifier_t m;
	uint8_t f;
} lll_debug_object_t;



typedef struct __LLL_SMALL_IDENTIFIER{
	char* v;
	uint32_t sc;
} lll_small_identifier_t;



typedef struct __LLL_IDENTIFIER_LIST{
	lll_small_identifier_t* dt;
	uint32_t l;
} lll_identifier_list_t;



typedef struct __LLL_IDENTIFIER{
	uint32_t sz;
	uint32_t sc;
	char v[];
} lll_identifier_t;



typedef struct __LLL_IDENTIFIER_DATA{
	lll_identifier_list_t s[LLL_MAX_SHORT_IDENTIFIER_LENGTH];
	lll_identifier_t** il;
	uint32_t ill;
} lll_identifier_data_t;



typedef struct __LLL_COMPILATION_DATA{
	char fp[512];
	uint16_t fpl;
	lll_input_data_stream_t* is;
	uint64_t tm;
	lll_object_t* h;
	lll_identifier_data_t i_dt;
} lll_compilation_data_t;



typedef struct __LLL_ERROR_DATA_RANGE{
	uint32_t off;
	uint32_t sz;
} lll_error_data_range_t;



typedef union __LLL_ERROR_DATA{
	char str[256];
	lll_error_data_range_t r;
} lll_error_data_t;



typedef struct __LLL_ERROR{
	lll_error_type_t t;
	lll_error_data_t dt;
} lll_error_t;



__LLL_IMPORT_EXPORT __LLL_CHECK_OUTPUT uint8_t lll_set_internal_stack(uint8_t* bf,uint32_t sz,lll_error_t* e);



__LLL_IMPORT_EXPORT void lll_init_compilation_data(const char* fp,lll_input_data_stream_t* is,lll_compilation_data_t* o);



__LLL_IMPORT_EXPORT void lll_create_input_data_stream(FILE* f,lll_input_data_stream_t* o);



__LLL_IMPORT_EXPORT void lll_create_output_data_stream(FILE* f,lll_output_data_stream_t* o);



__LLL_IMPORT_EXPORT void lll_print_error(lll_input_data_stream_t* is,lll_error_t* e);



__LLL_IMPORT_EXPORT void lll_print_object(lll_object_t* o,FILE* f);



__LLL_IMPORT_EXPORT __LLL_CHECK_OUTPUT uint8_t lll_insert_debug_object(lll_input_data_stream_t* is,lll_error_t* e);



__LLL_IMPORT_EXPORT __LLL_CHECK_OUTPUT lll_object_t* lll_read_object(lll_compilation_data_t* c_dt,lll_error_t* e);



__LLL_IMPORT_EXPORT __LLL_CHECK_OUTPUT uint8_t lll_read_all_objects(lll_compilation_data_t* c_dt,lll_error_t* e);



__LLL_IMPORT_EXPORT __LLL_CHECK_OUTPUT uint8_t lll_load_compiled_object(lll_input_data_stream_t* is,lll_compilation_data_t* c_dt,lll_error_t*);



__LLL_IMPORT_EXPORT __LLL_CHECK_OUTPUT uint8_t lll_optimize_object(lll_object_t* o,lll_error_t* e);



__LLL_IMPORT_EXPORT __LLL_CHECK_OUTPUT uint8_t lll_remove_object_debug_data(lll_object_t* o,lll_error_t* e);



__LLL_IMPORT_EXPORT __LLL_CHECK_OUTPUT uint8_t lll_remove_object_padding(lll_object_t* o,lll_error_t* e);



__LLL_IMPORT_EXPORT __LLL_CHECK_OUTPUT uint8_t lll_write_object(lll_output_data_stream_t* os,lll_object_t* o,uint8_t f,lll_error_t* e);



__LLL_IMPORT_EXPORT __LLL_CHECK_OUTPUT uint8_t lll_write_compiled_object(lll_output_data_stream_t* os,lll_compilation_data_t* c_dt,lll_error_t* e);



#endif