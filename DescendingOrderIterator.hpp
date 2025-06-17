/*
Mail - noorangnaim@gmail.com
*/

#ifndef DESCENDINGORDERITERATOR_HPP
#define DESCENDINGORDERITERATOR_HPP

#include <vector>        // For storing sorted indices
#include <algorithm>     // For sorting
#include <stdexcept>     // For exceptions

namespace nooran {

    // Forward declaration of the container class
    template<typename T>
    class MyContainer;

    // Iterator that scans the container in descending order
    template<typename T>
    class DescendingOrderIterator {
    private:
        const MyContainer<T>* container;      // Pointer to the container being iterated
        std::vector<size_t> sorted_indices;   // Indices of elements sorted by descending value
        size_t index;                         // Current position in the sorted_indices
        size_t capturedVersion;               // Version of the container at iterator creation

    public:
        // Constructs a descending iterator (begin or end depending on is_end)
        DescendingOrderIterator(const MyContainer<T>& cont, bool is_end = false)
            : container(&cont), index(0) {

            capturedVersion = container->getVersion(); // Remember container version

            const std::vector<T>& data = container->getData(); // Access container data

            // Fill sorted_indices with 0, 1, 2, ..., n-1
            sorted_indices.resize(data.size());
            for (size_t i = 0; i < data.size(); ++i) {
                sorted_indices[i] = i;
            }

            // Sort indices so that data[sorted_indices[i]] is in descending order
            std::sort(sorted_indices.begin(), sorted_indices.end(),
                      [&](size_t a, size_t b) {
                          return data[a] > data[b];
                      });

            // If end iterator requested, set index to the end
            if (is_end) {
                index = sorted_indices.size();
            }
        }

        // Returns the element at the current iterator position
        T operator*() const {
            if (capturedVersion != container->getVersion()) {
                throw std::runtime_error("Container modified during iteration");
            }
            if (index >= sorted_indices.size()) {
                throw std::out_of_range("Iterator out of range");
            }
            return container->getData()[sorted_indices[index]];
        }

        // Moves the iterator to the next element (prefix)
        DescendingOrderIterator& operator++() {
            if (capturedVersion != container->getVersion()) {
                throw std::runtime_error("Container modified during iteration");
            }
            if (index >= sorted_indices.size()) {
                throw std::out_of_range("Cannot increment beyond end.");
            }
            ++index;
            return *this;
        }

        // Moves the iterator to the next element (postfix)
        DescendingOrderIterator operator++(int) {
            if (capturedVersion != container->getVersion()) {
                throw std::runtime_error("Container modified during iteration");
            }
            if (index >= sorted_indices.size()) {
                throw std::out_of_range("Cannot increment beyond end.");
            }
            DescendingOrderIterator temp = *this;
            ++(*this);
            return temp;
        }

        // Checks if two iterators are equal (same position and container)
        bool operator==(const DescendingOrderIterator& other) const {
            return container == other.container && index == other.index;
        }

        // Checks if two iterators are not equal
        bool operator!=(const DescendingOrderIterator& other) const {
            return !(*this == other);
        }
    };

} // namespace nooran

#endif // DESCENDINGORDERITERATOR_HPP
