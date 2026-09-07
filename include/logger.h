#pragma once
#include <spdlog/sinks/basic_file_sink.h>


namespace logger = SKSE::log;

inline void SetupLog() {
    auto logsFolder = SKSE::log::log_directory();
    if (!logsFolder) SKSE::stl::report_and_fail("SKSE log_directory not provided, logs disabled.");
    auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();
    auto logFilePath = *logsFolder / std::format("{}.log", pluginName);
    auto fileLoggerPtr = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFilePath.string(), true);
    auto loggerPtr = std::make_shared<spdlog::logger>("log", std::move(fileLoggerPtr));
    spdlog::set_default_logger(std::move(loggerPtr));
    // Forced to trace regardless of build config while diagnosing the flee logic -- dial back
    // to info once the behavior is confirmed working end-to-end.
    spdlog::set_level(spdlog::level::trace);
    spdlog::flush_on(spdlog::level::trace);
    logger::info("Name of the plugin is {}.", pluginName);
    // NOTE: logging SKSE::PluginDeclaration::GetSingleton()->GetVersion() directly fails to
    // compile against this fmt v12 -- REL::Version's custom formatter isn't const-qualified the
    // way fmt v12 requires. Not essential; skip it rather than fight the library version.
}


