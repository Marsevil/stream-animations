#ifndef __ENTITY_TEST_HPP
#define __ENTITY_TEST_HPP

#include <godot_cpp/classes/node.hpp>

namespace entities {
    class TestNode: public godot::Node {
        GDCLASS(TestNode, Node)

        public:
        static void _bind_methods();

        TestNode() = default;
        ~TestNode() = default;
        TestNode(const TestNode&) = delete;

        void _ready() override;
        protected:
        private:
    };
}

#endif // __ENTITY_TEST_HPP
