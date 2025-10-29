#pragma once

#ifndef TO_STRING_UTIL_H
#define TO_STRING_UTIL_H

#include <string>
#include <sstream>

namespace Orca
{
    template<typename T>
    inline std::string to_string_generic(const T& value)
    {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }

    template<>
    inline std::string to_string_generic<std::string>(const std::string& value)
    {
        return value;
    }

    template<>
    inline std::string to_string_generic<const char*>(const char* const& value)
    {
        return value;
    }
}

#endif