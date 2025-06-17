/*
Mail - noorangnaim@gmail.com
*/

#ifndef ORDERITERATOR_HPP
#define ORDERITERATOR_HPP

#include <vector>        // For accessing container data
#include <stdexcept>     // For exception handling

namespace nooran {

    // Forward declaration of the container class
    template<typename T>
    class MyContainer;

    // Iterator that returns elements in the same order they were added
    template<typename T>
    class OrderIterator {
    private:
        const MyContainer<T>* container;  // Pointer to the container
        size_t index;                     // Current position
        size_t capturedVersion;           // Version snapshot to detect modification

    public:
        // Constructor for iterator
        OrderIterator(const MyContainer<T>& cont, bool is_end = false)
            : container(&cont), index(0) {
            capturedVersion = cont.getVersion();  // Save version at creation
            if (is_end) {
                index = container->getData().size();  // Move to end position
            }
        }

        // Returns the current element
        T operator*() const {
            if (capturedVersion != container->getVersion()) {
                throw std::runtime_error("Container modified during iteration");
            }
            const auto& data = container->getData();
            if (index >= data.size()) {
                throw std::out_of_range("Iterator out of range");
            }
            return data[index];
        }

        // Moves to the next element (prefix)
        OrderIterator& operator++() {
            if (capturedVersion != container->getVersion()) {
                throw std::runtime_error("Container modified during iteration");
            }
            if (index >= container->getData().size()) {
                throw std::out_of_range("Cannot increment beyond end.");
            }
            ++index;
            return *this;
        }

        // Moves to the next element (postfix)
        OrderIterator operator++(int) {
            if (capturedVersion != container->getVersion()) {
                throw std::runtime_error("Container modified during iteration");
            }
            if (index >= container->getData().size()) {
                throw std::out_of_range("Cannot increment beyond end.");
            }
            OrderIterator temp = *this;
            ++(*this);
            return temp;
        }

        // Checks if iterators are equal
        bool operator==(const OrderIterator& other) const {
            return container == other.container && index == other.index;
        }

        // Checks if iterators are not equal
        bool operator!=(const OrderIterator& other) const {
            return !(*this == other);
        }
    };

} // namespace nooran

#endif // ORDERITERATOR_HPP
