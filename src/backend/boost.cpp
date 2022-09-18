#include <hyperoute/backend/boost.hpp>
#include <backend/boost_router.hpp>

namespace hyperoute::backend
{
    std::shared_ptr<router_backend> make_boost()
    {
        return std::make_shared<boost_router>();
    }
}
