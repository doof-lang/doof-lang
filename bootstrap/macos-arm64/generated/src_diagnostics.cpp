#include "src_diagnostics.hpp"

namespace app_src_diagnostics_ {
using namespace ::app_src_semantic_;
#line 5 "/src/diagnostics.do"
bool hasErrorDiagnostics(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics) {
#line 6 "/src/diagnostics.do"
    const auto& _iterable_2 = diagnostics;
    for (const auto& diagnostic : *_iterable_2) {
#line 7 "/src/diagnostics.do"
        if (diagnostic->severity == std::string("error")) {
#line 7 "/src/diagnostics.do"
            return true;
        }
    }
#line 9 "/src/diagnostics.do"
    return false;
}
#line 1 "<doof-generated>"
}
