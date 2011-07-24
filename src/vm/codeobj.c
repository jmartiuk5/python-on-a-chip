/*
# This file is Copyright 2003, 2006, 2007, 2009, 2010 Dean Hall.
#
# This file is part of the PyMite VM.
# The PyMite VM is free software: you can redistribute it and/or modify
# it under the terms of the GNU GENERAL PUBLIC LICENSE Version 2.
#
# The PyMite VM is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# A copy of the GNU GENERAL PUBLIC LICENSE Version 2
# is seen in the file COPYING in this directory.
*/


#undef __FILE_ID__
#define __FILE_ID__ 0x01


/**
 * \file
 * \brief CodeObj Type
 *
 * CodeObj type operations.
 */


#include "pm.h"


PmReturn_t
co_getFromNames(pPmObj_t pco, uint16_t n, pPmObj_t *r_pname)
{
    return tuple_getItem((pPmObj_t)((pPmCo_t)pco)->co_names, n, r_pname);
}


PmReturn_t
co_getConst(pPmObj_t pco, uint16_t n, pPmObj_t *r_pconst)
{
    return tuple_getItem((pPmObj_t)((pPmCo_t)pco)->co_consts, n, r_pconst);
}


PmReturn_t
co_getName(pPmObj_t pco, pPmObj_t *r_pname)
{
    return co_getConst(pco, -1, r_pname);
}


PmReturn_t
co_getFileName(pPmObj_t pco, pPmObj_t *r_pname)
{
    return co_getConst(pco, -2, r_pname);
}


PmReturn_t
co_getCellVar(pPmObj_t pco, uint16_t n, pPmObj_t *r_pcvar)
{
    return tuple_getItem((pPmObj_t)((pPmCo_t)pco)->co_cellvars, n, r_pcvar);
}


PmReturn_t
co_getBcodeAtOffset(pPmObj_t pco, uint16_t n, uint8_t *r_pbc)
{
    *r_pbc = ((pPmCo_t)pco)->co_code->val[n];
    return PM_RET_OK;
}


PmReturn_t
co_getBcodeArgAtOffset(pPmObj_t pco, uint16_t n, int16_t *r_parg)
{
    uint8_t blo, bhi;

    blo = ((pPmCo_t)pco)->co_code->val[n];
    bhi = ((pPmCo_t)pco)->co_code->val[n+1];

    *r_parg = (bhi << 8) | blo;
    return PM_RET_OK;
}


PmReturn_t
co_getLnotabLen(pPmObj_t pco, uint16_t *r_len)
{
    *r_len = ((pPmCo_t)pco)->co_lnotab->length;
    return PM_RET_OK;
}


PmReturn_t
co_getLnotabAtOffset(pPmObj_t pco, uint16_t n, uint8_t *r_pbyte)
{
    *r_pbyte = ((pPmCo_t)pco)->co_lnotab->val[n];
    return PM_RET_OK;
}


PmReturn_t
co_getNlocals(pPmObj_t pco, uint8_t *r_pn)
{
    *r_pn = ((pPmCo_t)pco)->co_nlocals;
    return PM_RET_OK;
}


PmReturn_t
co_getFirstlineno(pPmObj_t pco, uint16_t *r_plineno)
{
    *r_plineno = ((pPmCo_t)pco)->co_firstlineno;
    return PM_RET_OK;
}


PmReturn_t
co_new(pPmObj_t *r_pco)
{
    PmReturn_t retval;
    uint8_t *pchunk;

    retval = heap_getChunk(sizeof(PmCob_t), &pchunk);
    PM_RETURN_IF_ERROR(retval);
    *r_pco = (pPmObj_t)pchunk;
    OBJ_SET_TYPE(*r_pco, OBJ_TYPE_COB);

    ((pPmCob_t)*r_pco)->co_code = C_NULL;
    ((pPmCob_t)*r_pco)->co_lnotab = C_NULL;
    ((pPmCob_t)*r_pco)->co_names = C_NULL;
    ((pPmCob_t)*r_pco)->co_consts = C_NULL;
    ((pPmCob_t)*r_pco)->co_cellvars = C_NULL;
    ((pPmCob_t)*r_pco)->co_firstlineno = 0;
    ((pPmCob_t)*r_pco)->co_argcount = 0;
    ((pPmCob_t)*r_pco)->co_flags = 0;
    ((pPmCob_t)*r_pco)->co_stacksize = 0;
    ((pPmCob_t)*r_pco)->co_nlocals = 0;
    ((pPmCob_t)*r_pco)->co_nfreevars = 0;
    return retval;
}