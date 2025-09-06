#ifndef __TRK8_NODE_HPP
#define __TRK8_NODE_HPP

#include <string>
#include <memory>

class Node {
    public:
        virtual ~Node() = default;

        virtual std::string to_string() const = 0;
};

using node_t = std::unique_ptr<Node>;

#endif
