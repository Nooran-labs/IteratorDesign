/*
Mail - noorangnaim@gmail.com
*/

#ifndef MIDDLEOUTORDERITERATOR_HPP
#define MIDDLEOUTORDERITERATOR_HPP

#include <vector>        // For internal index storage
#include <stdexcept>     // For exceptions

namespace nooran {

    // Forward declaration of the container class
    template<typename T>
    class MyContainer;

    // Iterator that starts from the middle and alternates left and right
    template<typename T>
    class MiddleOutOrderIterator {
    private:
        const MyContainer<T>* container;         // Pointer to the container
        std::vector<size_t> middle_out_indices;  // Indices in middle-out order
        size_t index;                            // Current position in the index vector
        size_t capturedVersion;                  // Version of container at iterator creation

    public:
        // Constructs a middle-out iterator (begin or end)
        MiddleOutOrderIterator(const MyContainer<T>& cont, bool is_end = false)
	    : container(&cont), index(0) {

	    capturedVersion = container->getVersion(); // Save version for validation
	    const std::vector<T>& data = container->getData();
	    size_t n = data.size();
	    middle_out_indices.reserve(n);

	    if (n == 0) return;

	    int mid = n / 2;
	    middle_out_indices.push_back(mid);

	    for (int offset = 1; middle_out_indices.size() < n; ++offset) {
		if (mid - offset >= 0)
		    middle_out_indices.push_back(mid - offset);
		if (mid + offset < (int)n)
		    middle_out_indices.push_back(mid + offset);
	    }

	    if (is_end) {
		index = middle_out_indices.size(); // Move to end
	    }
	}



        // Returns the current element
        T operator*() const {
            if (capturedVersion != container->getVersion()) {
                throw std::runtime_error("Container modified during iteration");
            }
            if (index >= middle_out_indices.size()) {
                throw std::out_of_range("Iterator out of range");
            }
            return container->getData()[middle_out_indices[index]];
        }

        // Moves to the next element (prefix)
        MiddleOutOrderIterator& operator++() {
           
	    if (index + 1 > middle_out_indices.size()) {
		throw std::out_of_range("Cannot increment beyond end.");
	    }
            if (capturedVersion != container->getVersion()) {
                throw std::runtime_error("Container modified during iteration");
            }
            if (index >= middle_out_indices.size()) {
                throw std::out_of_range("Cannot increment beyond end.");
            }
            ++index;
            return *this;
        }

        // Moves to the next element (postfix)
        MiddleOutOrderIterator operator++(int) {
            if (capturedVersion != container->getVersion()) {
                throw std::runtime_error("Container modified during iteration");
            }
            if (index >= middle_out_indices.size()) {
                throw std::out_of_range("Cannot increment beyond end.");
            }
            MiddleOutOrderIterator temp = *this;
            ++(*this);
            return temp;
        }

        // Checks if iterators are equal (same container and index)
        bool operator==(const MiddleOutOrderIterator& other) const {
            return container == other.container && index == other.index;
        }

        // Checks if iterators are not equal
        bool operator!=(const MiddleOutOrderIterator& other) const {
            return !(*this == other);
        }
    };

} // namespace nooran

#endif // MIDDLEOUTORDERITERATOR_HPP
