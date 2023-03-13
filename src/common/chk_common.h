#pragma once

#include <fmt/core.h>

#include <memory>
#include <stdexcept>
#include <string>

#define CHK_NON_COPYABLE(ClassName)                   \
	ClassName(const ClassName &) = delete;            \
	ClassName &operator=(const ClassName &) = delete; \
	ClassName(ClassName &&) = default;                \
	ClassName &operator=(ClassName &&) = default

#define CHK_NON_COPYABLE_NON_MOVABLE(ClassName)       \
	ClassName(const ClassName &) = delete;            \
	ClassName &operator=(const ClassName &) = delete; \
	ClassName(ClassName &&) = delete;                 \
	ClassName &operator=(ClassName &&) = delete\
