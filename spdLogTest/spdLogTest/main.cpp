
#include "CLogger.h"
#include  "CDraw.h"
int main() {
    std::cout << "Hello World!\n";

    // ======================
    // 全局随便用！不乱码！
    // ======================
    LOG_INFO("欢迎使用全局单例日志");
    LOG_WARN("这是警告信息");
    LOG_ERROR("这是错误信息");
    LOG_INFO("程序版本 {}.{}.{}", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);
	CDraw DAW;
    return 0;
}