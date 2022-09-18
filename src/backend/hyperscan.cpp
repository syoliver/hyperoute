#include <hyperoute/backend/hyperscan.hpp>
#include <backend/hyperscan_router.hpp>

namespace hyperoute::backend
{
    std::shared_ptr<router_backend> make_hyperscan()
    {
        return std::make_shared<hyperscan_router>();
    }
}
