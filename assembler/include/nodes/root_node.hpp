#ifndef __TRK8_MASTER_NODE_HPP
#define __TRK8_MASTER_NODE_HPP

#include <vector>
#include <sstream>

#include "node.hpp"

class RootNode : public Node {
    public:
        RootNode() = default;

        void add_node(node_t node) {
            this->nodes.push_back(std::move(node));
        }

        const std::vector<node_t>& get_nodes() const {
            return this->nodes;
        }

        std::string to_string() const override {
            std::ostringstream stream;

            stream << "ROOTNODE {\n";

            for (const node_t& node : nodes) {
                stream << node->to_string() << "\n";
            }

            stream << "}";

            return stream.str();
        }

    private:
        std::vector<node_t> nodes;
};

using root_node_t = std::unique_ptr<RootNode>;

#endif
