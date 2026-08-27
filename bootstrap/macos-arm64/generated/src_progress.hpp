#pragma once
#include "doof_runtime.hpp"
namespace app_src_progress_ {
    std::string renderProgressBar(int32_t completed, int32_t total, int32_t width);
    int32_t boundedWorkerCount(int32_t itemCount, int32_t maximumWorkers);
}
