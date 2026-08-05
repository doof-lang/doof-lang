#pragma once

// musl exposes the standard streams as macros. Generated Doof programs may
// legally use these names for fields and parameters, so consume the C header
// and remove the macros before compiling the generated source graph.
#include <cstddef>
#include <cstdio>

// The snapshot's crypto support uses this BSD interface. Alpine's libbsd
// provides the symbol, but including its overlay headers before every generated
// translation unit produces noisy compatibility warnings.
extern "C" void arc4random_buf(void* buffer, std::size_t size);

#undef stdin
#undef stdout
#undef stderr
