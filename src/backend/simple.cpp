#include <hyperoute/backend/simple.hpp>
#include <backend/simple_router.hpp>

namespace hyperoute::backend
{
    std::shared_ptr<router_backend> make_simple()
    {
        return std::make_shared<simple_router>();
    }
}
