#include <lll/_lll_internal.h>
#include <lll/common.h>
#include <lll/core.h>
#include <lll/types.h>
#include <stdint.h>
#include <stdio.h>



#define PRINT_STATIC_STRING(s,os) LLL_WRITE_TO_OUTPUT_DATA_STREAM((os),(lll_buffer_t)(s),sizeof(s)-1)



void _print_int(int64_t v,lll_output_data_stream_t* os){
	if (!v){
		LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'0');
		return;
	}
	if (v<0){
		v=-v;
		LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'-');
	}
	char bf[20];
	uint8_t i=0;
	while (v){
		bf[i]=v%10;
		v/=10;
		i++;
	}
	while (i){
		i--;
		LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,bf[i]+48);
	}
}



void _print_float(double v,lll_output_data_stream_t* os){
	char bf[128];
	int sz=snprintf(bf,128,"%.16lg",v);
	LLL_WRITE_TO_OUTPUT_DATA_STREAM(os,(uint8_t*)bf,sz*sizeof(char));
}



lll_object_offset_t _print_object_internal(const lll_compilation_data_t* c_dt,const lll_object_t* o,lll_output_data_stream_t* os){
	lll_object_offset_t eoff=0;
	while (o->t==LLL_OBJECT_TYPE_NOP){
		eoff++;
		o++;
	}
	if (LLL_IS_OBJECT_TYPE_NOT_TYPE(o)&&o->t!=LLL_OBJECT_TYPE_OPERATION_LIST&&o->t!=LLL_OBJECT_TYPE_DEBUG_DATA){
		LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'(');
	}
	switch (o->t){
		case LLL_OBJECT_TYPE_UNKNOWN:
			PRINT_STATIC_STRING("(unknown)",os);
			return eoff+1;
		case LLL_OBJECT_TYPE_CHAR:
			{
				LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'\'');
				char c=o->dt.c;
				if (c=='\''||c=='"'||c=='\\'){
					LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'\\');
				}
				else if (c=='\t'){
					LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'\\');
					c='t';
				}
				else if (c=='\n'){
					LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'\\');
					c='n';
				}
				else if (c=='\v'){
					LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'\\');
					c='v';
				}
				else if (c=='\f'){
					LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'\\');
					c='f';
				}
				else if (c=='\r'){
					LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'\\');
					c='r';
				}
				else if (c<32||c>126){
					LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'\\');
					LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'x');
					LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,(((uint8_t)c)>>4)+(((uint8_t)c)>159?87:48));
					c=(c&0xf)+((c&0xf)>9?87:48);
				}
				LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,c);
				LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'\'');
				return eoff+1;
			}
		case LLL_OBJECT_TYPE_INT:
			_print_int(o->dt.i,os);
			return eoff+1;
		case LLL_OBJECT_TYPE_FLOAT:
			_print_float(o->dt.f,os);
			return eoff+1;
		case LLL_OBJECT_TYPE_STRING:
			{
				LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'"');
				lll_string_t* s=*(c_dt->st.dt+o->dt.s);
				for (lll_string_length_t i=0;i<s->l;i++){
					char c=s->v[i];
					if (c=='\''||c=='"'||c=='\\'){
						LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'\\');
					}
					else if (c=='\t'){
						LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'\\');
						c='t';
					}
					else if (c=='\n'){
						LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'\\');
						c='n';
					}
					else if (c=='\v'){
						LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'\\');
						c='v';
					}
					else if (c=='\f'){
						LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'\\');
						c='f';
					}
					else if (c=='\r'){
						LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'\\');
						c='r';
					}
					else if (c<32||c>126){
						LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'\\');
						LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'x');
						LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,(((uint8_t)c)>>4)+(((uint8_t)c)>159?87:48));
						c=(c&0xf)+((c&0xf)>9?87:48);
					}
					LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,c);
				}
				LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'"');
				return eoff+1;
			}
		case LLL_OBJECT_TYPE_IDENTIFIER:
			{
				lll_identifier_index_t i=o->dt.id;
				lll_identifier_list_length_t j=LLL_IDENTIFIER_GET_ARRAY_ID(i);
				if (j==LLL_MAX_SHORT_IDENTIFIER_LENGTH){
					lll_string_t* s=*(c_dt->st.dt+(c_dt->idt.il+LLL_IDENTIFIER_GET_ARRAY_INDEX(i))->i);
					for (lll_string_length_t k=0;k<s->l;k++){
						LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,s->v[k]);
					}
					LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'$');
					_print_int((c_dt->idt.il+LLL_IDENTIFIER_GET_ARRAY_INDEX(i))->sc,os);
				}
				else{
					lll_char_t* s=(*(c_dt->st.dt+(c_dt->idt.s[j].dt+LLL_IDENTIFIER_GET_ARRAY_INDEX(i))->i))->v;
					for (lll_string_length_t k=0;k<j+1;k++){
						LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,*(s+k));
					}
					LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'$');
					_print_int((c_dt->idt.s[j].dt+LLL_IDENTIFIER_GET_ARRAY_INDEX(i))->sc,os);
				}
				return eoff+1;
			}
		case LLL_OBJECT_TYPE_PRINT:
			PRINT_STATIC_STRING(":>",os);
			break;
		case LLL_OBJECT_TYPE_INPUT:
			PRINT_STATIC_STRING("<:",os);
			break;
		case LLL_OBJECT_TYPE_AND:
			PRINT_STATIC_STRING("&&",os);
			break;
		case LLL_OBJECT_TYPE_OR:
			PRINT_STATIC_STRING("||",os);
			break;
		case LLL_OBJECT_TYPE_NOT:
			PRINT_STATIC_STRING("!",os);
			break;
		case LLL_OBJECT_TYPE_ASSIGN:
			PRINT_STATIC_STRING("=",os);
			break;
		case LLL_OBJECT_TYPE_FUNC:
		case LLL_OBJECT_TYPE_INTERNAL_FUNC:
			{
				if (o->t==LLL_OBJECT_TYPE_FUNC){
					PRINT_STATIC_STRING(",,,",os);
				}
				else{
					PRINT_STATIC_STRING("... #",os);
					_print_int(o->dt.fn.id,os);
				}
				lll_stack_offset_t off=1;
				lll_arg_count_t l=o->dt.fn.ac;
				while (l){
					l--;
					LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,' ');
					off+=_print_object_internal(c_dt,o+off,os);
				}
				LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,')');
				return off+eoff;
			}
		case LLL_OBJECT_TYPE_CALL:
			PRINT_STATIC_STRING("<-",os);
			break;
		case LLL_OBJECT_TYPE_IF:
			PRINT_STATIC_STRING("?",os);
			break;
		case LLL_OBJECT_TYPE_FOR:
			PRINT_STATIC_STRING("->",os);
			break;
		case LLL_OBJECT_TYPE_WHILE:
			PRINT_STATIC_STRING(">-",os);
			break;
		case LLL_OBJECT_TYPE_LOOP:
			PRINT_STATIC_STRING("><",os);
			break;
		case LLL_OBJECT_TYPE_ADD:
			PRINT_STATIC_STRING("+",os);
			break;
		case LLL_OBJECT_TYPE_SUB:
			PRINT_STATIC_STRING("-",os);
			break;
		case LLL_OBJECT_TYPE_MULT:
			PRINT_STATIC_STRING("*",os);
			break;
		case LLL_OBJECT_TYPE_DIV:
			PRINT_STATIC_STRING("/",os);
			break;
		case LLL_OBJECT_TYPE_FLOOR_DIV:
			PRINT_STATIC_STRING("//",os);
			break;
		case LLL_OBJECT_TYPE_MOD:
			PRINT_STATIC_STRING("%",os);
			break;
		case LLL_OBJECT_TYPE_BIT_AND:
			PRINT_STATIC_STRING("&",os);
			break;
		case LLL_OBJECT_TYPE_BIT_OR:
			PRINT_STATIC_STRING("|",os);
			break;
		case LLL_OBJECT_TYPE_BIT_XOR:
			PRINT_STATIC_STRING("^",os);
			break;
		case LLL_OBJECT_TYPE_BIT_NOT:
			PRINT_STATIC_STRING("~",os);
			break;
		case LLL_OBJECT_TYPE_LESS:
			PRINT_STATIC_STRING("<",os);
			break;
		case LLL_OBJECT_TYPE_LESS_EQUAL:
			PRINT_STATIC_STRING("<=",os);
			break;
		case LLL_OBJECT_TYPE_EQUAL:
			PRINT_STATIC_STRING("==",os);
			break;
		case LLL_OBJECT_TYPE_NOT_EQUAL:
			PRINT_STATIC_STRING("!=",os);
			break;
		case LLL_OBJECT_TYPE_MORE:
			PRINT_STATIC_STRING(">",os);
			break;
		case LLL_OBJECT_TYPE_MORE_EQUAL:
			PRINT_STATIC_STRING(">=",os);
			break;
		case LLL_OBJECT_TYPE_RETURN:
			PRINT_STATIC_STRING("@@",os);
			break;
		case LLL_OBJECT_TYPE_EXIT:
			PRINT_STATIC_STRING("@",os);
			break;
		case LLL_OBJECT_TYPE_OPERATION_LIST:
			{
				LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'{');
				lll_stack_offset_t off=1;
				lll_statement_count_t sc=o->dt.sc;
				for (lll_statement_count_t i=0;i<sc;i++){
					if (i){
						LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,' ');
					}
					off+=_print_object_internal(c_dt,o+off,os);
				}
				LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'}');
				return off+eoff;
			}
		case LLL_OBJECT_TYPE_DEBUG_DATA:
			{
				LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,'[');
				lll_string_t* fp=*(c_dt->st.dt+o->dt.dbg.fpi);
				for (lll_string_length_t i=0;i<fp->l;i++){
					LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,fp->v[i]);
				}
				LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,':');
				_print_int(o->dt.dbg.ln+1,os);
				LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,':');
				_print_int(o->dt.dbg.cn+1,os);
				LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,']');
				return eoff+_print_object_internal(c_dt,o+1,os)+1;
			}
		default:
			UNREACHABLE();
	}
	lll_stack_offset_t off=1;
	lll_arg_count_t l=o->dt.ac;
	while (l){
		l--;
		LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,' ');
		off+=_print_object_internal(c_dt,o+off,os);
	}
	LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,')');
	return off+eoff;
}



__LLL_FUNC void lll_print_assembly(const lll_assembly_data_t* a_dt,lll_output_data_stream_t* os){
	lll_assembly_instruction_t* ai=a_dt->h;
	for (lll_instruction_index_t i=0;i<a_dt->ic;i++){
		if (i){
			LLL_WRITE_CHAR_TO_OUTPUT_DATA_STREAM(os,',');
		}
		switch (LLL_ASSEMBLY_INSTRUCTION_GET_TYPE(ai)){
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_NOP:
				PRINT_STATIC_STRING("NOP",os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_POP:
				PRINT_STATIC_STRING("POP",os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_POP_TWO:
				PRINT_STATIC_STRING("POP & POP",os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_ROT:
				PRINT_STATIC_STRING("ROT",os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_ROT_POP:
				PRINT_STATIC_STRING("ROT & POP",os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_DUP:
				PRINT_STATIC_STRING("DUP",os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_PUSH_INT:
				PRINT_STATIC_STRING("PUSH ",os);
				_print_int(ai->dt.i,os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_PUSH_MINUS_ONE:
				PRINT_STATIC_STRING("PUSH -1",os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_PUSH_ZERO:
				PRINT_STATIC_STRING("PUSH 0",os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_PUSH_ONE:
				PRINT_STATIC_STRING("PUSH 1",os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_PUSH_TWO:
				PRINT_STATIC_STRING("PUSH 2",os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_PUSH_THREE:
				PRINT_STATIC_STRING("PUSH 3",os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_PUSH_FOUR:
				PRINT_STATIC_STRING("PUSH 4",os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_PUSH_FLOAT:
				PRINT_STATIC_STRING("PUSH ",os);
				_print_float(ai->dt.f,os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_PUSH_CHAR:
				PRINT_STATIC_STRING("PUSH c",os);
				_print_int(ai->dt.c,os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_LOAD:
				PRINT_STATIC_STRING("LOAD $",os);
				_print_int(ai->dt.v,os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_LOADS:
				PRINT_STATIC_STRING("LOADS #",os);
				_print_int(ai->dt.s,os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_STORE:
				PRINT_STATIC_STRING("STORE $",os);
				_print_int(ai->dt.v,os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_STORE_POP:
				PRINT_STATIC_STRING("STORE $",os);
				_print_int(ai->dt.v,os);
				PRINT_STATIC_STRING(" & POP",os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_STORE_MINUS_ONE:
				PRINT_STATIC_STRING("PUSH -1 & STORE $",os);
				_print_int(ai->dt.v,os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_STORE_ZERO:
				PRINT_STATIC_STRING("PUSH 0 & STORE $",os);
				_print_int(ai->dt.v,os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_STORE_ONE:
				PRINT_STATIC_STRING("PUSH 1 & STORE $",os);
				_print_int(ai->dt.v,os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_STORE_TWO:
				PRINT_STATIC_STRING("PUSH 2 & STORE $",os);
				_print_int(ai->dt.v,os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_STORE_THREE:
				PRINT_STATIC_STRING("PUSH 3 & STORE $",os);
				_print_int(ai->dt.v,os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_STORE_FOUR:
				PRINT_STATIC_STRING("PUSH 4 & STORE $",os);
				_print_int(ai->dt.v,os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_JMP:
				PRINT_STATIC_STRING("JMP .",os);
				_print_int((LLL_ASSEMBLY_INSTRUCTION_IS_RELATIVE(ai)?ai->dt.rj:ai->dt.j),os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_JB:
				PRINT_STATIC_STRING("JB .",os);
				_print_int((LLL_ASSEMBLY_INSTRUCTION_IS_RELATIVE(ai)?ai->dt.rj:ai->dt.j),os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_JBE:
				PRINT_STATIC_STRING("JBE .",os);
				_print_int((LLL_ASSEMBLY_INSTRUCTION_IS_RELATIVE(ai)?ai->dt.rj:ai->dt.j),os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_JA:
				PRINT_STATIC_STRING("JA .",os);
				_print_int((LLL_ASSEMBLY_INSTRUCTION_IS_RELATIVE(ai)?ai->dt.rj:ai->dt.j),os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_JAE:
				PRINT_STATIC_STRING("JAE .",os);
				_print_int((LLL_ASSEMBLY_INSTRUCTION_IS_RELATIVE(ai)?ai->dt.rj:ai->dt.j),os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_JE:
				PRINT_STATIC_STRING("JE .",os);
				_print_int((LLL_ASSEMBLY_INSTRUCTION_IS_RELATIVE(ai)?ai->dt.rj:ai->dt.j),os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_JNE:
				PRINT_STATIC_STRING("JNE .",os);
				_print_int((LLL_ASSEMBLY_INSTRUCTION_IS_RELATIVE(ai)?ai->dt.rj:ai->dt.j),os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_JZ:
				PRINT_STATIC_STRING("JZ .",os);
				_print_int((LLL_ASSEMBLY_INSTRUCTION_IS_RELATIVE(ai)?ai->dt.rj:ai->dt.j),os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_JNZ:
				PRINT_STATIC_STRING("JNZ .",os);
				_print_int((LLL_ASSEMBLY_INSTRUCTION_IS_RELATIVE(ai)?ai->dt.rj:ai->dt.j),os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_NOT:
				if (LLL_ASSEMBLY_INSTRUCTION_IS_INPLACE(ai)){
					PRINT_STATIC_STRING("NOT $",os);
					_print_int(ai->dt.v,os);
				}
				else{
					PRINT_STATIC_STRING("NOT",os);
				}
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_INC:
				PRINT_STATIC_STRING("INC $",os);
				_print_int(ai->dt.v,os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_DEC:
				PRINT_STATIC_STRING("DEC $",os);
				_print_int(ai->dt.v,os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_ADD:
				if (LLL_ASSEMBLY_INSTRUCTION_IS_INPLACE(ai)){
					PRINT_STATIC_STRING("ADD $",os);
					_print_int(ai->dt.v,os);
				}
				else{
					PRINT_STATIC_STRING("ADD",os);
				}
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_SUB:
				if (LLL_ASSEMBLY_INSTRUCTION_IS_INPLACE(ai)){
					PRINT_STATIC_STRING("SUB $",os);
					_print_int(ai->dt.v,os);
				}
				else{
					PRINT_STATIC_STRING("SUB",os);
				}
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_MULT:
				if (LLL_ASSEMBLY_INSTRUCTION_IS_INPLACE(ai)){
					PRINT_STATIC_STRING("MULT $",os);
					_print_int(ai->dt.v,os);
				}
				else{
					PRINT_STATIC_STRING("MULT",os);
				}
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_DIV:
				if (LLL_ASSEMBLY_INSTRUCTION_IS_INPLACE(ai)){
					PRINT_STATIC_STRING("DIV $",os);
					_print_int(ai->dt.v,os);
				}
				else{
					PRINT_STATIC_STRING("DIV",os);
				}
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_FDIV:
				if (LLL_ASSEMBLY_INSTRUCTION_IS_INPLACE(ai)){
					PRINT_STATIC_STRING("FDIV $",os);
					_print_int(ai->dt.v,os);
				}
				else{
					PRINT_STATIC_STRING("FDIV",os);
				}
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_MOD:
				if (LLL_ASSEMBLY_INSTRUCTION_IS_INPLACE(ai)){
					PRINT_STATIC_STRING("MOD $",os);
					_print_int(ai->dt.v,os);
				}
				else{
					PRINT_STATIC_STRING("MOD",os);
				}
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_AND:
				if (LLL_ASSEMBLY_INSTRUCTION_IS_INPLACE(ai)){
					PRINT_STATIC_STRING("AND $",os);
					_print_int(ai->dt.v,os);
				}
				else{
					PRINT_STATIC_STRING("AND",os);
				}
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_OR:
				if (LLL_ASSEMBLY_INSTRUCTION_IS_INPLACE(ai)){
					PRINT_STATIC_STRING("OR $",os);
					_print_int(ai->dt.v,os);
				}
				else{
					PRINT_STATIC_STRING("OR",os);
				}
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_XOR:
				if (LLL_ASSEMBLY_INSTRUCTION_IS_INPLACE(ai)){
					PRINT_STATIC_STRING("XOR $",os);
					_print_int(ai->dt.v,os);
				}
				else{
					PRINT_STATIC_STRING("XOR",os);
				}
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_INV:
				if (LLL_ASSEMBLY_INSTRUCTION_IS_INPLACE(ai)){
					PRINT_STATIC_STRING("INV $",os);
					_print_int(ai->dt.v,os);
				}
				else{
					PRINT_STATIC_STRING("INV",os);
				}
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_PRINT:
				PRINT_STATIC_STRING("PRINT",os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_PRINT_CHAR:
				PRINT_STATIC_STRING("PRINT c",os);
				_print_int(ai->dt.c,os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_PRINT_STR:
				PRINT_STATIC_STRING("PRINT #",os);
				_print_int(ai->dt.s,os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_PRINT_VAR:
				PRINT_STATIC_STRING("PRINT $",os);
				_print_int(ai->dt.v,os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_CALL:
				PRINT_STATIC_STRING("CALL ",os);
				_print_int(ai->dt.ac,os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_CALL_POP:
				PRINT_STATIC_STRING("CALL ",os);
				_print_int(ai->dt.ac,os);
				PRINT_STATIC_STRING(" & POP",os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_CALL_ZERO:
				PRINT_STATIC_STRING("PUSH ",os);
				_print_int(ai->dt.i,os);
				PRINT_STATIC_STRING(" & CALL 0",os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_CALL_ONE:
				PRINT_STATIC_STRING("PUSH ",os);
				_print_int(ai->dt.i,os);
				PRINT_STATIC_STRING(" & CALL 1",os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_RET:
				PRINT_STATIC_STRING("RET",os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_RET_INT:
				PRINT_STATIC_STRING("RET ",os);
				_print_int(ai->dt.i,os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_RET_ZERO:
				PRINT_STATIC_STRING("RET 0",os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_RET_FLOAT:
				PRINT_STATIC_STRING("RET ",os);
				_print_float(ai->dt.f,os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_RET_CHAR:
				PRINT_STATIC_STRING("RET c",os);
				_print_int(ai->dt.c,os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_RET_STR:
				PRINT_STATIC_STRING("RET #",os);
				_print_int(ai->dt.s,os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_RET_VAR:
				PRINT_STATIC_STRING("RET $",os);
				_print_int(ai->dt.v,os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_END:
				PRINT_STATIC_STRING("END",os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_END_ZERO:
				PRINT_STATIC_STRING("END 0",os);
				break;
			case LLL_ASSEMBLY_INSTRUCTION_TYPE_END_ONE:
				PRINT_STATIC_STRING("END 1",os);
				break;
			default:
				UNREACHABLE();
		}
		ai++;
	}
}



__LLL_FUNC void lll_print_object(const lll_compilation_data_t* c_dt,const lll_object_t* o,lll_output_data_stream_t* os){
	_print_object_internal(c_dt,o,os);
}