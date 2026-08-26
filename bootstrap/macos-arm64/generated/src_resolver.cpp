#include "src_resolver.hpp"

namespace app_src_resolver_ {
using namespace ::app_src_semantic_;
#line 13 "/src/resolver.do"
doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>> noSourceLoader(const std::string& path) {
    return doof::Success<std::shared_ptr<::app_src_semantic_::SourceFile>>{ nullptr };
}

#line 22 "/src/resolver.do"
std::shared_ptr<::app_src_semantic_::SourceFile> ModuleResolver::find(const std::string& path) {
#line 23 "/src/resolver.do"
    const auto& _iterable_2 = this->sources;
    for (const auto& source : *_iterable_2) {
#line 23 "/src/resolver.do"
        if (source->path == path) {
#line 23 "/src/resolver.do"
            return source;
        }
    }
#line 24 "/src/resolver.do"
    const auto& _iterable_4 = this->loadedPaths;
    for (const auto& loaded : *_iterable_4) {
#line 24 "/src/resolver.do"
        if (loaded == path) {
#line 24 "/src/resolver.do"
            return nullptr;
        }
    }
#line 25 "/src/resolver.do"
    this->loadedPaths->push_back(path);
#line 26 "/src/resolver.do"
    auto _binding_value_5 = this->loader.call(path);
    if (doof::is_failure(_binding_value_5)) {
        const auto diagnostic = doof::failure_error(_binding_value_5);
#line 27 "/src/resolver.do"
        this->failedPaths->push_back(path);
#line 28 "/src/resolver.do"
        this->diagnostics->push_back(diagnostic);
#line 29 "/src/resolver.do"
        return nullptr;
    }
    const auto loaded = doof::success_value(_binding_value_5);
#line 31 "/src/resolver.do"
    if (!doof::is_null(loaded)) {
#line 32 "/src/resolver.do"
        this->sources->push_back(doof::unwrap_optional(loaded));
#line 33 "/src/resolver.do"
        return doof::unwrap_optional(loaded);
    }
#line 35 "/src/resolver.do"
    return nullptr;
}
#line 38 "/src/resolver.do"
bool ModuleResolver::failed(const std::string& path) {
#line 39 "/src/resolver.do"
    const auto& _iterable_7 = this->failedPaths;
    for (const auto& failed : *_iterable_7) {
#line 39 "/src/resolver.do"
        if (failed == path) {
#line 39 "/src/resolver.do"
            return true;
        }
    }
#line 40 "/src/resolver.do"
    return false;
}
#line 43 "/src/resolver.do"
std::string ModuleResolver::resolve(const std::string& importer, const std::string& specifier) {
#line 44 "/src/resolver.do"
    const auto base = (doof::string_startsWith(specifier, std::string(".")) ? relativeBase(importer, specifier) : (std::string("/") + specifier));
#line 47 "/src/resolver.do"
    const auto exact = withExtension(base);
#line 48 "/src/resolver.do"
    if (doof::string_endsWith(base, std::string(".do"))) {
#line 48 "/src/resolver.do"
        return exact;
    }
#line 49 "/src/resolver.do"
    if (!doof::is_null(find(exact))) {
#line 49 "/src/resolver.do"
        return exact;
    }
#line 50 "/src/resolver.do"
    const auto barrel = (base + std::string("/index.do"));
#line 51 "/src/resolver.do"
    if (!doof::is_null(find(barrel))) {
#line 51 "/src/resolver.do"
        return barrel;
    }
#line 52 "/src/resolver.do"
    return exact;
}
#line 56 "/src/resolver.do"
std::string withExtension(const std::string& path) {
#line 57 "/src/resolver.do"
    if (doof::string_endsWith(path, std::string(".do"))) {
#line 57 "/src/resolver.do"
        return path;
    }
#line 58 "/src/resolver.do"
    return (path + std::string(".do"));
}
#line 61 "/src/resolver.do"
std::string relativeBase(const std::string& importer, const std::string& specifier) {
#line 62 "/src/resolver.do"
    auto directory = parentDirectory(importer);
#line 63 "/src/resolver.do"
    auto remaining = specifier;
#line 64 "/src/resolver.do"
    while (doof::string_startsWith(remaining, std::string("../"))) {
#line 65 "/src/resolver.do"
        (directory = parentDirectory(directory));
#line 66 "/src/resolver.do"
        (remaining = doof::string_substring(remaining, 3, static_cast<int32_t>(remaining.size())));
    }
#line 68 "/src/resolver.do"
    while (doof::string_startsWith(remaining, std::string("./"))) {
#line 69 "/src/resolver.do"
        (remaining = doof::string_substring(remaining, 2, static_cast<int32_t>(remaining.size())));
    }
#line 71 "/src/resolver.do"
    if (directory == std::string("/")) {
#line 71 "/src/resolver.do"
        return (std::string("/") + remaining);
    }
#line 72 "/src/resolver.do"
    return ((directory + std::string("/")) + remaining);
}
#line 75 "/src/resolver.do"
std::string parentDirectory(const std::string& path) {
#line 76 "/src/resolver.do"
    auto end = (static_cast<int32_t>(path.size()) - 1);
#line 77 "/src/resolver.do"
    while ((end >= 0) && (doof::string_at(path, end, "src/resolver", 77) == U'\u002F')) {
#line 77 "/src/resolver.do"
        (end = (end - 1));
    }
#line 78 "/src/resolver.do"
    while ((end >= 0) && (doof::string_at(path, end, "src/resolver", 78) != U'\u002F')) {
#line 78 "/src/resolver.do"
        (end = (end - 1));
    }
#line 79 "/src/resolver.do"
    if (end <= 0) {
#line 79 "/src/resolver.do"
        return std::string("/");
    }
#line 80 "/src/resolver.do"
    return doof::string_substring(path, 0, end);
}
#line 1 "<doof-generated>"
}
