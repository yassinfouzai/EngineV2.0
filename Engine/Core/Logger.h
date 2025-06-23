#pragma once
#include <iostream>

#define LOG_INFO(x)  std::cout << "[INFO]  " << x << std::endl
#define LOG_WARN(x)  std::cout << "[WARN]  " << x << std::endl
#define LOG_ERROR(x) std::cerr << "[ERROR] " << x << std::endl
