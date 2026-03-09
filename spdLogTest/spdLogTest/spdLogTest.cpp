
//

#include "CLogger.h"

int main()
{ 
    std::cout << "Hello World!\n";
    std::cout << "Hello World!\n";

    // ======================
    // 全局随便用！任何地方都能用！
    // ======================
    LOG_INFO("欢迎使用全局单例日志");
    LOG_WARN("这是一条警告");
    LOG_ERROR("这是一条错误");
    LOG_DEBUG("调试信息");
    LOG_CRITICAL("严重错误！");

    LOG_INFO("版本 {}.{}.{}", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);
    LOG_INFO("数字格式化 {:08d}", 12);
    LOG_INFO("浮点数 {:.2f}", 1.23456);

    // 你原来的代码都可以正常用
    spdlog::set_level(spdlog::level::info);
    spdlog::info("默认日志器也能用");
}


