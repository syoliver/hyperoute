
#include <translate.hpp>
#include <error_category.hpp>
#include <hyperoute/error.hpp>
#include <sstream>
#include <iostream>

namespace hyperoute
{

std::pair<std::string, std::vector<capture_t>> translate_route(const std::string_view route, const bool prefix_mode, std::error_condition& ec)
{
    std::ostringstream oss_regex;
    std::vector<capture_t> captures;
    oss_regex << '^';

    auto iter = std::cbegin(route);
    auto token_begin = iter;
    auto capture_begin = iter;
    const auto end = std::cend(route);

    bool in_capture = false;
    bool in_regex = false;
    std::size_t brace_cnt = 0;
    std::size_t current_group = 0;

    bool want_next_skip = false;
    bool skip = true;
    while(iter != end && !ec)
    {
        skip = want_next_skip;
        want_next_skip = false;
        if(in_capture)
        {
            if(in_regex == false && *iter == ':')
            {
                captures.back().name = std::string_view(token_begin, (iter-token_begin));
                captures.back().has_regex = true;
                token_begin = iter+1;
                in_regex = true;
            }
            else if(*iter == '}')
            {
                if(brace_cnt == 0)
                {
                    if(captures.back().name.empty())
                    {
                        captures.back().name = std::string_view(token_begin, (iter-token_begin));
                        oss_regex << "([^\\/]+)";
                    }
                    else
                    {
                        oss_regex << '(' << std::string_view(token_begin, (iter-token_begin)) << ')';
                    }

                    token_begin = iter+1;
                    in_regex = false;
                    in_capture = false;
                }
                else
                {
                    --brace_cnt;
                }
            }
            else if(in_regex)
            {
                if(*iter == '\\')
                {
                    want_next_skip = true;
                }
                else if(want_next_skip == false)
                {
                    if(*iter == '(')
                    {
                        ++current_group;
                    }
                    else if(*iter == '{')
                    {
                        ++brace_cnt;
                    }
                    else if(*iter == '}')
                    {
                        if(brace_cnt == 0)
                        {
                            ec = make_error_condition(error::unbalanced_brace);
                        }
                        --brace_cnt;
                    }
                }
            }
        }
        else
        {
            switch(*iter)
            {
                case '{':
                {
                    if(skip)
                    {
                        oss_regex << "\\{";
                    }
                    else
                    {
                        oss_regex << std::string_view(token_begin, (iter-token_begin));
                        token_begin = iter+1;
                        captures.emplace_back();
                        ++current_group;
                        captures.back().has_regex = false;
                        captures.back().group = current_group;
                        in_capture = true;
                    }
                    break;
                }
                case '}':
                {
                    if(skip)
                    {
                        oss_regex << "\\}";
                    }
                    else
                    {
                        ec = make_error_condition(error::unbalanced_brace);
                    }
                }
                case '\\':
                {
                    want_next_skip = true;
                    break;
                }
                case '/':
                case '.':
                case '?':
                case '(':
                case ')':
                case '[':
                case ']':
                case '*':
                case '+':
                case '^':
                {
                    oss_regex << std::string_view(token_begin, (iter-token_begin));
                    oss_regex << '\\';
                    token_begin = iter;
                    break;
                }
                default:
                    /* nothing */
                    break;
            }
        }
        ++iter;
    }

    if(brace_cnt > 0)
    {
        ec = make_error_condition(error::unbalanced_brace);
    }

    oss_regex << std::string_view(token_begin, (iter-token_begin));
    
    if(prefix_mode == false)
    {
        oss_regex << '$';
    }
    
    return std::pair(oss_regex.str(), std::move(captures));
}

}
