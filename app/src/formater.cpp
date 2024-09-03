#include "formater.h"

bool convert_str_to_float(const wchar_t *str, float *value)
{
    bool result = true;
    wchar_t* endptr;

    try
    {
        *value = std::wcstof(str, &endptr);

        if (str == endptr)
        {
            throw std::invalid_argument("No digits were found");
        }
    }
    catch (const std::invalid_argument& e)
    {
        // Invalid argument
        // e.what()
        result = false;
    }
    catch (const std::out_of_range& e)
    {
        // Out of range
        // e.what()
        result = false;
    }

    return result;
}

bool convert_str_to_int(const wchar_t *str, long *value)
{
    bool result = true;
    wchar_t* endptr;

    try
    {
        *value = std::wcstol(str, &endptr, 10);

        if (str == endptr)
        {
            throw std::invalid_argument("No digits were found");
        }
    }
    catch (const std::invalid_argument& e)
    {
        // Invalid argument
        // e.what()
        result = false;
    }
    catch (const std::out_of_range& e)
    {
        // Out of range
        // e.what()
        result = false;
    }

    return result;
}