
#include <translate.hpp>
#include <sstream>

namespace hyperoute
{

std::pair<std::string, std::vector<capture_t>> translate_route(const std::string_view route, const bool prefix_mode)
{
    std::ostringstream oss_regex;
    std::vector<capture_t> captures;
    oss_regex << '^';

    auto iter = std::cbegin(route);
    auto token_begin = iter;
    const auto end = std::cend(route);

    bool in_capture = false;
    bool in_regex = false;
    std::size_t brace_cnt = 0;
    std::size_t current_group = 0;

    while(iter != end)
    {
        if(in_capture)
        {
            if(in_regex == false && *iter == ':')
            {
                captures.back().name = std::string_view(token_begin, (iter-token_begin));
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
                if(*iter == '(')
                {
                    ++current_group;
                }
                else if(*iter == '{')
                {
                    ++brace_cnt;
                }
            }
        }
        else
        {
            switch(*iter)
            {
                case '{':
                {
                    oss_regex << std::string_view(token_begin, (iter-token_begin));
                    token_begin = iter+1;
                    captures.emplace_back();
                    ++current_group;
                    captures.back().group = current_group;
                    in_capture = true;
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

    oss_regex << std::string_view(token_begin, (iter-token_begin));
    
    if(prefix_mode == false)
    {
        oss_regex << '$';
    }

    return std::pair(oss_regex.str(), std::move(captures));
}

}
