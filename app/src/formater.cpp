#include "formater.h"

void token_worlds(const wchar_t *str, std::list<std::wstring> *tokens)
{
    std::wstring delimiter = L" \t\n";
    size_t pos = 0;
    std::wstring tmp = str;
    std::wstring token;
    std::list<std::wstring>::iterator it;

    while ((pos = tmp.find_first_of(delimiter)) != std::wstring::npos)
    {
        token = tmp.substr(0, pos);
        if (!token.empty())
        {
            tokens->push_back(token);
        }
        tmp.erase(0, pos + 1);
    }

    if (!tmp.empty())
        tokens->push_back(tmp);
}

bool check_size_t_format(const wchar_t *str)
{
    bool err = EXIT_SUCCESS;
    std::wstring tmp = str;
    std::wregex regex(L"^[+]?\\d+$");
    size_t value;

    while (!tmp.empty() && (std::iswspace(tmp.front()) || tmp.front() == L'\t' || tmp.front() == L'\n'))
        tmp.erase(0, 1);

    while (!tmp.empty() && (std::iswspace(tmp.back()) || tmp.back() == L'\t' || tmp.back() == L'\n'))
        tmp.pop_back();

    std::wistringstream iss(tmp);

    if (!std::regex_match(tmp, regex))
    {
        err = EXIT_FAILURE;
    }

    if (!err && !(iss >> value))
    {
        err = EXIT_FAILURE;
    }

    return !err;
}

bool check_float_format(const wchar_t *str)
{
    std::wstring tmp = str;
    std::wregex regex(L"^[-+]?[0-9]{1,7}(\\.[0-9]{1,6})?$");

    while (!tmp.empty() && (std::iswspace(tmp.front()) || tmp.front() == L'\t' || tmp.front() == L'\n'))
        tmp.erase(0, 1);

    while (!tmp.empty() && (std::iswspace(tmp.back()) || tmp.back() == L'\t' || tmp.back() == L'\n'))
        tmp.pop_back();

    return std::regex_match(tmp, regex);
}

bool check_point_format(const wchar_t *str)
{
    std::list<std::wstring> tokens;
    std::list<std::wstring>::iterator it;

    token_worlds(str, &tokens);

    it = tokens.begin();
    return tokens.size() == 2 && check_float_format(it->data()) && check_float_format((++it)->data());
}

bool convert_str_to_size_t(const wchar_t *str, size_t *value)
{
    bool result = true;
    wchar_t* endptr;

    try
    {
        *value = std::wcstoull(str, &endptr, 10);

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

bool convert_str_to_point(const wchar_t *str, float *x, float *y)
{
    std::list<std::wstring> tokens;
    std::list<std::wstring>::iterator it;

    token_worlds(str, &tokens);

    it = tokens.begin();
    return tokens.size() == 2 && convert_str_to_float(it->data(), x) && convert_str_to_float((++it)->data(), y);
}

bool is_equal_str_points(const wchar_t *str1, const wchar_t *str2)
{
    std::list<std::wstring> tokens1;
    std::list<std::wstring>::iterator it1;

    std::list<std::wstring> tokens2;
    std::list<std::wstring>::iterator it2;

    token_worlds(str1, &tokens1);
    token_worlds(str2, &tokens2);

    it1 = tokens1.begin();
    it2 = tokens2.begin();

    return tokens1.size() == 2 && tokens2.size() == 2 && wcscmp(it1->c_str(), it2->c_str()) == 0 && wcscmp((++it1)->c_str(), (++it2)->c_str()) == 0;
}