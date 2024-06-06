#pragma once

#include <utility> // For std::pair
#include <functional> // For std::hash

namespace std
{
    template <>
    struct hash<std::pair<int, int>>
    {
        std::size_t operator()( const std::pair<int, int>& p ) const noexcept
        {
            return std::hash<int>{}( p.first ) ^ ( std::hash<int>{}( p.second ) << 1 );
        }
    };
}
