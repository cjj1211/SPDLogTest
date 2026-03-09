#include <iostream>
#include <cstdio>
#include <chrono>
#include <string>
#include <ctime>
#include "../include/spdlog/spdlog.h"
#include "../include/spdlog/cfg/env.h"
#include "../include/spdlog/fmt/ostr.h"
#include "../include/spdlog/sinks/basic_file_sink.h"
// ==============================
// 全局日志单例类
// ==============================
class Logger {
public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& instance() {
        static Logger instance;
        return instance;
    }

    std::shared_ptr<spdlog::logger> get_logger() {
        return logger_;
    }

private:
    // 生成带时间戳的新日志文件名
    std::string generate_log_filename() {
        auto now = std::chrono::system_clock::now();
        time_t t = std::chrono::system_clock::to_time_t(now);

        tm time_info{};
#ifdef _WIN32
        localtime_s(&time_info, &t);
#else
        localtime_r(&t, &time_info);
#endif

        char buf[64];
        strftime(buf, sizeof(buf), "logs/opt_%Y%m%d.log", &time_info);
        return buf;
    }

    Logger() {
        try {
            auto filename = generate_log_filename();
            auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(filename, false);
            file_sink->set_pattern("%Y-%m-%d %H:%M:%S.%e [%l] %v");
            logger_ = std::make_shared<spdlog::logger>("global_logger", file_sink);
            logger_->set_level(spdlog::level::trace);
            spdlog::register_logger(logger_);
            logger_->info("===== 全局日志初始化完成 =====");
        }
        catch (const spdlog::spdlog_ex& ex) {
            std::cerr << "日志初始化失败: " << ex.what() << std::endl;
        }
    }

    std::shared_ptr<spdlog::logger> logger_;
};

// ==============================
// 全局使用宏（任意文件直接用）
// ==============================
#define LOG_TRACE(...)    Logger::instance().get_logger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...)    Logger::instance().get_logger()->debug(__VA_ARGS__)
#define LOG_INFO(...)     Logger::instance().get_logger()->info(__VA_ARGS__)
#define LOG_WARN(...)     Logger::instance().get_logger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)    Logger::instance().get_logger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) Logger::instance().get_logger()->critical(__VA_ARGS__)
