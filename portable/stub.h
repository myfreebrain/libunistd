// stub.h
// Copyright 2016 Robin.Rowe@CinePaint.org
// License open source MIT

#ifndef stub_h
#define stub_h

#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#else
#define inline __inline
#endif

#ifdef STUB_VERBOSE
inline
void StubBug(const char* msg)
{	puts(msg);
}

#else
inline
void StubBug(const char* msg)
{	(void) msg;
}

#endif

#define BUG(x)	StubBug("BUG: " x)
#define TODO(x)	StubBug("TO-DO: " x)

#define STUB(functionName) StubBug("STUB:" #functionName)
#define STUB0(functionName) StubBug("STUB:" #functionName); return 0
#define STUB_MSG(functionName) StubBug("STUB:" #functionName)

#ifdef __cplusplus
}
#endif

#endif

