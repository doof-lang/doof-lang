#include "src_diagnostics.hpp"
#include <cmath>
#include "src_semantic.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_diagnostics_ {
using namespace ::app_src_semantic_;
bool hasErrorDiagnostics(std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics) {
    const auto& _iterable_1 = diagnostics;
    for (const auto& diagnostic : *_iterable_1) {
        if (diagnostic->severity == std::string("error")) {
            return true;
        }
    }
    return false;
}
}
