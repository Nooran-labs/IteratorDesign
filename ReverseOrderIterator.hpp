/*
Mail - noorangnaim@gmail.com
*/

#ifndef REVERSEORDERITERATOR_HPP
#define REVERSEORDERITERATOR_HPP

#include <vector>        // For accessing container data
#include <stdexcept>     // For throwing exceptions

namespace nooran {

    // Forward declaration of the container
    template<typename T>
    class MyContainer;

    // Iterator that scans elements in reverse of insertion order
    template<typename T>
    class ReverseOrderIterator {
    private:
        const MyContainer<T>* container;  // Pointer to the container
        size_t index;                     // Current index (reverse scan)
        size_t capturedVersion;           // Version at time of iterator creation

    public:
        // Constructs a reverse iterator (begin = last, end = before first)
        ReverseOrderIterator(const MyContainer<T>& cont, bool is_end = false)
            : container(&cont) {

            capturedVersion = container->getVersion();  // Track version for safety

            if (container->getData().empty()) {
	    index = static_cast<size_t>(-1);  // Empty container: both begin and end should be the same
	    } else if (is_end) {
	    index = static_cast<size_t>(-1);
	    } else {
	    index = container->getData().size() - 1;
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

        // Moves to the previous element (prefix)
        ReverseOrderIterator& operator++() {
            if (capturedVersion != container->getVersion()) {
                throw std::runtime_error("Container modified during iteration");
            }
            if (index == static_cast<size_t>(-1)) {
                throw std::out_of_range("Cannot increment beyond beginning.");
            }
            --index;
            return *this;
        }

        // Moves to the previous element (postfix)
        ReverseOrderIterator operator++(int) {
            if (capturedVersion != container->getVersion()) {
                throw std::runtime_error("Container modified during iteration");
            }
            if (index == static_cast<size_t>(-1)) {
                throw std::out_of_range("Cannot increment beyond beginning.");
            }
            ReverseOrderIterator temp = *this;
            --index;
            return temp;
        }
        


        // Equality: same container and same index
        bool operator==(const ReverseOrderIterator& other) const {
            return container == other.container && index == other.index;
        }

        // Inequality: different position or container
        bool operator!=(const ReverseOrderIterator& other) const {
            return !(*this == other);
        }
    };

} // namespace nooran

#endif // REVERSEORDERITERATOR_HPP
