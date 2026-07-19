#pragma once
#include "doof_runtime.hpp"
#include <cstdint>
#include <cmath>
#include <functional>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <variant>
#include <vector>
namespace app_src_ast_ { struct Block; }
namespace app_src_ast_ { struct ExportList; }
namespace app_src_ast_ { struct FunctionDeclaration; }
namespace app_src_ast_ { struct NamedType; }
namespace app_src_ast_ { struct Program; }
namespace app_src_emitter_module_ { struct CoverageModuleMetadata; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_test_runner_ {
    struct CoverageFileReport;
    struct CoverageReport;
    struct DiscoveredTest;
    struct TestDiscovery;
}

#include "src_ast.hpp"
#include "src_emitter_module.hpp"

namespace app_src_test_runner_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct CoverageFileReport : public std::enable_shared_from_this<CoverageFileReport> {
    std::string path;
    int32_t covered;
    int32_t total;
    int32_t percentTenths;
    std::shared_ptr<std::vector<int32_t>> hitLines = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
    std::shared_ptr<std::vector<int32_t>> missedLines = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
    CoverageFileReport(std::string path, int32_t covered, int32_t total, int32_t percentTenths, std::shared_ptr<std::vector<int32_t>> hitLines = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}), std::shared_ptr<std::vector<int32_t>> missedLines = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{})) : path(path), covered(covered), total(total), percentTenths(percentTenths), hitLines(hitLines), missedLines(missedLines) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<CoverageFileReport>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct CoverageReport : public std::enable_shared_from_this<CoverageReport> {
    int32_t totalCovered = 0;
    int32_t totalLines = 0;
    int32_t totalPercentTenths = 1000;
    std::shared_ptr<std::vector<std::shared_ptr<CoverageFileReport>>> files = std::make_shared<std::vector<std::shared_ptr<CoverageFileReport>>>(std::vector<std::shared_ptr<CoverageFileReport>>{});
    CoverageReport(int32_t totalCovered = 0, int32_t totalLines = 0, int32_t totalPercentTenths = 1000, std::shared_ptr<std::vector<std::shared_ptr<CoverageFileReport>>> files = std::make_shared<std::vector<std::shared_ptr<CoverageFileReport>>>(std::vector<std::shared_ptr<CoverageFileReport>>{})) : totalCovered(totalCovered), totalLines(totalLines), totalPercentTenths(totalPercentTenths), files(files) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<CoverageReport>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct DiscoveredTest : public std::enable_shared_from_this<DiscoveredTest> {
    std::string id;
    std::string name;
    std::string modulePath;
    std::string moduleDisplayPath;
    DiscoveredTest(std::string id, std::string name, std::string modulePath, std::string moduleDisplayPath) : id(id), name(name), modulePath(modulePath), moduleDisplayPath(moduleDisplayPath) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<DiscoveredTest>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct TestDiscovery : public std::enable_shared_from_this<TestDiscovery> {
    std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> tests = std::make_shared<std::vector<std::shared_ptr<DiscoveredTest>>>(std::vector<std::shared_ptr<DiscoveredTest>>{});
    std::shared_ptr<std::vector<std::string>> errors = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    TestDiscovery(std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> tests = std::make_shared<std::vector<std::shared_ptr<DiscoveredTest>>>(std::vector<std::shared_ptr<DiscoveredTest>>{}), std::shared_ptr<std::vector<std::string>> errors = std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) : tests(tests), errors(errors) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<TestDiscovery>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    std::shared_ptr<TestDiscovery> discoverModuleTests(std::shared_ptr<::app_src_ast_::Program> program, std::string modulePath, std::string rootDirectory);
    std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> filterDiscoveredTests(std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> tests, std::string filter);
    std::string generateTestHarness(std::string harnessPath, std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> tests);
    std::string testDisplayPath(std::string rootDirectory, std::string modulePath);
    std::string formatParseFailure(std::string modulePath, std::string source, int32_t line, int32_t column, std::string message);
    void mergeCoverageOutput(std::string output, std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>> modules, std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> hitsByModule);
    std::string stripCoverageLines(std::string output);
    std::shared_ptr<CoverageReport> buildCoverageReport(std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>> modules, std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> hitsByModule, std::string rootDirectory);
    std::string renderCoverageJson(std::shared_ptr<CoverageReport> report);
    std::string renderCoverageHtml(std::shared_ptr<CoverageReport> report, std::string fileDirectoryName);
    std::string renderCoverageFileHtml(std::shared_ptr<CoverageFileReport> file, std::string source, std::string indexHref);
    std::string coverageFileRelativePath(std::string path);
    int32_t parseCoverageInteger(std::string value);
    void appendUniqueLine(std::shared_ptr<std::vector<int32_t>> lines, int32_t line);
    bool containsLine(std::shared_ptr<std::vector<int32_t>> lines, int32_t line);
    int32_t coveragePercentTenths(int32_t covered, int32_t total);
    std::string coveragePercentText(int32_t tenths);
    std::string renderLineArray(std::shared_ptr<std::vector<int32_t>> lines);
    std::string escapeJson(std::string value);
    std::string escapeHtml(std::string value);
    void addDiscoveredTest(std::shared_ptr<TestDiscovery> result, std::shared_ptr<::app_src_ast_::FunctionDeclaration> declaration, std::string exportedName, std::string modulePath, std::string rootDirectory);
    bool returnsVoid(std::shared_ptr<::app_src_ast_::FunctionDeclaration> declaration);
    std::shared_ptr<::app_src_ast_::FunctionDeclaration> findFunction(std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>> statements, std::string name);
    std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> copyTests(std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> tests);
    std::string relativeImportSpecifier(std::string harnessPath, std::string modulePath);
    std::shared_ptr<std::vector<std::string>> parentComponents(std::string path);
    std::string withoutExtension(std::string path);
    std::string trimTrailingSlashes(std::string path);
    std::string escapeDoofString(std::string value);
}

namespace app_src_test_runner_ {
}
