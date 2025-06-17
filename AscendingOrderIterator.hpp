/*
Mail - noorangnaim@gmail.com
*/

#ifndef ASCENDINGORDERITERATOR_HPP
#define ASCENDINGORDERITERATOR_HPP

#include <vector>        // For internal index tracking
#include <algorithm>     // For sorting
#include <cstddef>       // For size_t
#include <stdexcept>     // For exceptions

namespace nooran {

    // Forward declaration of the container
    template<typename T>
    class MyContainer;

    // Iterator that scans the container in ascending order
    template<typename T>
    class AscendingOrderIterator {
    private:
        const MyContainer<T>* container;   // Pointer to the container we are iterating over
        std::vector<size_t> sorted_indices; // Stores the indices of elements in sorted order
        size_t index;                       // Current position in sorted_indices
        size_t capturedVersion;             // Snapshot of container version for mutation checks

    public:
        // Constructs an iterator at the beginning or end
        AscendingOrderIterator(const MyContainer<T>& cont, bool is_end = false)
            : container(&cont), index(0) {

            // Capture version to detect modifications
            capturedVersion = container->getVersion();

            // Reference to actual data
            const std::vector<T>& data = container->getData();

            // Prepare sorted indices
            sorted_indices.resize(data.size());
            for (size_t i = 0; i < data.size(); ++i) {
                sorted_indices[i] = i;
            }

            // Sort indices based on actual element values
            std::sort(sorted_indices.begin(), sorted_indices.end(),
                      [&](size_t a, size_t b) {
                          return data[a] < data[b];
                      });

            // If asked to create an end iterator, jump to end
            if (is_end) {
                index = sorted_indices.size();
            }
        }

        // Dereference: returns the current element
        T operator*() const {
            // Validate that container hasn't changed
            if (capturedVersion != container->getVersion()) {
                throw std::runtime_error("Container modified during iteration");
            }

            // Ensure we are not out of bounds
            if (index >= sorted_indices.size()) {
                throw std::out_of_range("Iterator out of range");
            }

            // Return the element at the sorted position
            return container->getData()[sorted_indices[index]];
        }

        // Prefix increment: moves to the next element
        AscendingOrderIterator& operator++() {
            if (capturedVersion != container->getVersion()) {
                throw std::runtime_error("Container modified during iteration");
            }

            if (index >= sorted_indices.size()) {
                throw std::out_of_range("Cannot increment beyond end.");
            }

            ++index;
            return *this;
        }

        // Postfix increment: same as prefix but returns previous state
        AscendingOrderIterator operator++(int) {
            if (capturedVersion != container->getVersion()) {
                throw std::runtime_error("Container modified during iteration");
            }

            if (index >= sorted_indices.size()) {
                throw std::out_of_range("Cannot increment beyond end.");
            }

            AscendingOrderIterator temp = *this;
            ++(*this);
            return temp;
        }

        // Equality comparison: true if same container and same index
        bool operator==(const AscendingOrderIterator& other) const {
            return container == other.container && index == other.index;
        }

        // Inequality comparison
        bool operator!=(const AscendingOrderIterator& other) const {
            return !(*this == other);
        }
    };

} // namespace nooran

#endif // ASCENDINGORDERITERATOR_HPP
