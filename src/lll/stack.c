#include <lll/common.h>
#include <lll/core.h>
#include <lll/types.h>
#include <stdint.h>



__LLL_FUNC void lll_set_assembly_data_stack(lll_assembly_data_t* a_dt,lll_buffer_t bf,lll_stack_offset_t sz){
	a_dt->_s.ptr=bf;
	a_dt->_s.off=0;
	a_dt->_s.sz=sz;
}



__LLL_FUNC void lll_set_compilation_data_stack(lll_compilation_data_t* c_dt,lll_buffer_t bf,lll_stack_offset_t sz){
	c_dt->_s.ptr=bf;
	c_dt->_s.off=0;
	c_dt->_s.sz=sz;
}



__LLL_FUNC void lll_setup_stack(lll_stack_data_t* o,lll_buffer_t bf,lll_stack_offset_t sz){
	o->ptr=bf;
	o->off=0;
	o->sz=sz;
}