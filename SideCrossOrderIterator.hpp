/*
Mail - noorangnaim@gmail.com
*/

#ifndef SIDECROSSORDERITERATOR_HPP
#define SIDECROSSORDERITERATOR_HPP

#include <vector>        // For internal storage
#include <algorithm>     // For sorting
#include <stdexcept>     // For exceptions

namespace nooran {

    // Forward declaration of the container class
    template<typename T>
    class MyContainer;

    // Iterator that alternates between smallest and largest element: left, right, left2, right2...
    template<typename T>
    class SideCrossOrderIterator {
    private:
        const MyContainer<T>* container;       // Pointer to the container
        std::vector<size_t> cross_indices;     // Indices ordered in side-cross fashion
        size_t index;                          // Current position in cross_indices
        size_t capturedVersion;                // Version at the time of iterator creation

    public:
        // Constructs a side-cross iterator
        SideCrossOrderIterator(const MyContainer<T>& cont, bool is_end = false)
            : container(&cont), index(0) {

            capturedVersion = container->getVersion(); // Save version to detect modifications

            const std::vector<T>& data = container->getData();
            size_t size = data.size();

            if (size == 0) {
                // For empty container
                cross_indices = {};
                if (is_end) {
                    index = 0;
                }
                return;
            }

            // Initialize indices
            std::vector<size_t> sorted_indices(size);
            for (size_t i = 0; i < size; ++i) {
                sorted_indices[i] = i;
            }

            // Sort by actual values
            std::sort(sorted_indices.begin(), sorted_indices.end(),
                      [&](size_t a, size_t b) {
                          return data[a] < data[b];
                      });

            // Build cross order: smallest, largest, 2nd smallest, 2nd largest...
            size_t left = 0;
            size_t right = size - 1;
            while (left <= right) {
                cross_indices.push_back(sorted_indices[left]);
                if (left != right) {
                    cross_indices.push_back(sorted_indices[right]);
                }
                left++;
                right--;
            }

            if (is_end) {
                index = cross_indices.size(); // Move to end
            }
        }

        // Returns the current element
	T operator*() const {
	    if (capturedVersion != container->getVersion()) {
		throw std::runtime_error("Container modified during iteration");
	    }
	    if (!container || index >= cross_indices.size()) {
		throw std::out_of_range("Iterator out of range");
	    }
	    return container->getData()[cross_indices[index]];
	}

	// Moves to the next element (prefix)
	SideCrossOrderIterator& operator++() {
	    if (capturedVersion != container->getVersion()) {
		throw std::runtime_error("Container modified during iteration");
	    }
	    if (!container || index >= cross_indices.size()) {
		throw std::out_of_range("Cannot increment beyond end.");
	    }
	    ++index;
	    return *this;
	}

	// Moves to the next element (postfix)
	SideCrossOrderIterator operator++(int) {
	    if (capturedVersion != container->getVersion()) {
		throw std::runtime_error("Container modified during iteration");
	    }
	    if (!container || index >= cross_indices.size()) {
		throw std::out_of_range("Cannot increment beyond end.");
	    }
	    SideCrossOrderIterator temp = *this;
	    ++(*this);
	    return temp;
	}


        // Checks if two iterators are equal
        bool operator==(const SideCrossOrderIterator& other) const {
            return container == other.container && index == other.index;
        }

        // Checks if two iterators are not equal
        bool operator!=(const SideCrossOrderIterator& other) const {
            return !(*this == other);
        }
    };

} // namespace nooran

#endif // SIDECROSSORDERITERATOR_HPP
