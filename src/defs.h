#pragma once

// 声明默认的构造函数
#define DECLARE_DEFAULTS(class_name) \
    class_name() = default; \
    class_name(const class_name&) = default; \
    class_name(class_name&&) = default; \
    class_name& operator=(const class_name&) = default; \
    class_name& operator=(class_name&&) = default;

