#include <lll/_lll_internal.h>
#include <lll/common.h>
#include <lll/core.h>
#include <lll/types.h>
#include <stdint.h>
#include <stdlib.h>



lll_object_offset_t _mark_strings(lll_object_t* o,uint64_t* m){
	lll_object_offset_t eoff=0;
	while (o->t==LLL_OBJECT_TYPE_NOP){
		eoff++;
		o++;
	}
	switch (o->t){
		case LLL_OBJECT_TYPE_UNKNOWN:
		case LLL_OBJECT_TYPE_CHAR:
		case LLL_OBJECT_TYPE_IDENTIFIER:
		case LLL_OBJECT_TYPE_INT:
		case LLL_OBJECT_TYPE_FLOAT:
			return eoff+1;
		case LLL_OBJECT_TYPE_STRING:
			*(m+(o->dt.s>>6))|=1ull<<(o->dt.s&63);
			return eoff+1;
		case LLL_OBJECT_TYPE_FUNC:
		case LLL_OBJECT_TYPE_INTERNAL_FUNC:
			{
				lll_object_offset_t off=1;
				lll_arg_count_t l=o->dt.fn.ac;
				while (l){
					l--;
					off+=_mark_strings(o+off,m);
				}
				return off+eoff;
			}
		case LLL_OBJECT_TYPE_OPERATION_LIST:
			{
				lll_object_offset_t off=1;
				lll_statement_count_t l=o->dt.sc;
				while (l){
					l--;
					off+=_mark_strings(o+off,m);
				}
				return off+eoff;
			}
		case LLL_OBJECT_TYPE_DEBUG_DATA:
			*(m+(o->dt.dbg.fpi>>6))|=1ull<<(o->dt.dbg.fpi&63);
			return eoff+_mark_strings(o+1,m)+1;
	}
	lll_object_offset_t off=1;
	lll_arg_count_t l=o->dt.ac;
	while (l){
		l--;
		off+=_mark_strings(o+off,m);
	}
	return off+eoff;
}



lll_object_offset_t _update_strings(lll_object_t* o,lll_string_index_t* sm){
	lll_object_offset_t eoff=0;
	while (o->t==LLL_OBJECT_TYPE_NOP){
		eoff++;
		o++;
	}
	switch (o->t){
		case LLL_OBJECT_TYPE_UNKNOWN:
		case LLL_OBJECT_TYPE_CHAR:
		case LLL_OBJECT_TYPE_IDENTIFIER:
		case LLL_OBJECT_TYPE_INT:
		case LLL_OBJECT_TYPE_FLOAT:
			return eoff+1;
		case LLL_OBJECT_TYPE_STRING:
			o->dt.s=*(sm+o->dt.s);
			return eoff+1;
		case LLL_OBJECT_TYPE_FUNC:
		case LLL_OBJECT_TYPE_INTERNAL_FUNC:
			{
				lll_object_offset_t off=1;
				lll_arg_count_t l=o->dt.fn.ac;
				while (l){
					l--;
					off+=_update_strings(o+off,sm);
				}
				return off+eoff;
			}
		case LLL_OBJECT_TYPE_OPERATION_LIST:
			{
				lll_object_offset_t off=1;
				lll_statement_count_t l=o->dt.sc;
				while (l){
					l--;
					off+=_update_strings(o+off,sm);
				}
				return off+eoff;
			}
		case LLL_OBJECT_TYPE_DEBUG_DATA:
			o->dt.dbg.fpi=*(sm+o->dt.dbg.fpi);
			return eoff+_update_strings(o+1,sm)+1;
	}
	lll_object_offset_t off=1;
	lll_arg_count_t l=o->dt.ac;
	while (l){
		l--;
		off+=_update_strings(o+off,sm);
	}
	return off+eoff;
}



__LLL_FUNC void lll_optimize_metadata(lll_compilation_data_t* c_dt){
	uint32_t ml=(c_dt->st.l>>6)+1;
	uint64_t* m=malloc(ml*sizeof(uint64_t));
	for (uint32_t i=0;i<ml;i++){
		*(m+i)=0;
	}
	for (uint8_t i=0;i<LLL_MAX_SHORT_IDENTIFIER_LENGTH;i++){
		lll_identifier_list_t* l=c_dt->idt.s+i;
		for (lll_identifier_list_length_t j=0;j<l->l;j++){
			*(m+((l->dt+j)->i>>6))|=1ull<<((l->dt+j)->i&63);
		}
	}
	for (lll_identifier_list_length_t i=0;i<c_dt->idt.ill;i++){
		*(m+((c_dt->idt.il+i)->i>>6))|=1ull<<((c_dt->idt.il+i)->i&63);
	}
	_mark_strings(c_dt->h,m);
	lll_string_index_t* sm=malloc(c_dt->st.l*sizeof(lll_string_index_t));
	uint32_t k=0;
	uint32_t l=0;
	for (uint32_t i=0;i<ml;i++){
		uint64_t v=~(*(m+i));
		while (v){
			lll_string_index_t j=FIND_FIRST_SET_BIT(v)|(i<<6);
			if (j==c_dt->st.l){
				break;
			}
			for (uint32_t n=k;n<j;n++){
				*(c_dt->st.dt+n-l)=*(c_dt->st.dt+n);
				*(sm+n)=n-l;
			}
			free(*(c_dt->st.dt+j));
			k=j+1;
			l++;
			v&=v-1;
		}
	}
	free(m);
	for (uint32_t i=k;i<c_dt->st.l;i++){
		*(c_dt->st.dt+i-l)=*(c_dt->st.dt+i);
		*(sm+i)=i-l;
	}
	if (l){
		c_dt->st.l-=l;
		c_dt->st.dt=realloc(c_dt->st.dt,c_dt->st.l*sizeof(lll_string_t*));
		for (uint8_t i=0;i<LLL_MAX_SHORT_IDENTIFIER_LENGTH;i++){
			lll_identifier_list_t* e=c_dt->idt.s+i;
			for (lll_identifier_list_length_t j=0;j<e->l;j++){
				(e->dt+j)->i=*(sm+(e->dt+j)->i);
			}
		}
		for (lll_identifier_list_length_t i=0;i<c_dt->idt.ill;i++){
			(c_dt->idt.il+i)->i=*(sm+(c_dt->idt.il+i)->i);
		}
		_update_strings(c_dt->h,sm);
	}
	free(sm);
}