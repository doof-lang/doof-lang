#include "src_progress.hpp"

namespace app_src_progress_ {
std::string renderProgressBar(int32_t completed, int32_t total, int32_t width) {
    const auto barWidth = ((width < 1) ? 1 : width);
    const auto safeTotal = ((total < 0) ? 0 : total);
    const auto safeCompleted = ((completed < 0) ? 0 : ((completed > safeTotal) ? safeTotal : completed));
    const auto filled = ((safeTotal == 0) ? barWidth : ((safeCompleted * barWidth) / total));
    return ((((((std::string("[") + doof::string_repeat(std::string("#"), filled)) + doof::string_repeat(std::string("-"), (barWidth - filled))) + std::string("] ")) + doof::to_string(safeCompleted)) + std::string("/")) + doof::to_string(safeTotal));
}
int32_t boundedWorkerCount(int32_t itemCount, int32_t maximumWorkers) {
    if ((itemCount <= 0) || (maximumWorkers <= 0)) {
        return 0;
    }
    return ((itemCount < maximumWorkers) ? itemCount : maximumWorkers);
}
}
