#include "src_diagnostics.hpp"

namespace app_src_diagnostics_ {
using namespace ::app_src_semantic_;
bool hasErrorDiagnostics(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics) {
    const auto& _iterable_1 = diagnostics;
    for (const auto& diagnostic : *_iterable_1) {
        if (diagnostic->severity == std::string("error")) {
            return true;
        }
    }
    return false;
}
}
