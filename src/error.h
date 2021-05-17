#ifndef ERROR_H
#define ERROR_H

#include <assert.h>

#include "warning.h"

#ifdef _DEBUG
#define DEBUG_ASSERT(cond, mess) assert(cond && mess)
#else
#define DEBUG_ASSERT(cond, mess)
#endif // _DEBUG

#endif // ERROR_H
