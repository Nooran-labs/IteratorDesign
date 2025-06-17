/*
Mail - noorangnaim@gmail.com
*/

#ifndef MYCONTAINER_HPP
#define MYCONTAINER_HPP

// Standard library headers
#include <vector>        // For dynamic storage
#include <iostream>      // For output stream
#include <algorithm>     // For std::remove
#include <stdexcept>     // For throwing exceptions

// Custom iterator headers
#include "AscendingOrderIterator.hpp"
#include "DescendingOrderIterator.hpp"
#include "ReverseOrderIterator.hpp"
#include "SideCrossOrderIterator.hpp"
#include "OrderIterator.hpp"
#include "MiddleOutOrderIterator.hpp"

// Define project namespace
namespace nooran {

    // Generic container for comparable types (default is int)
    template<typename T = int>
    class MyContainer {
    private:
        std::vector<T> data;     // Holds the container's elements
        size_t version = 0;      // Used to track changes for iterator safety

    public:
        // Creates an empty container
        MyContainer() = default;

        // Adds an element to the container
        void addElement(const T& value) {
            data.push_back(value);   // Insert element at the end of the vector
            version++;               // Mark that the container has changed
        }

        // Removes all instances of the given element from the container
        // Throws an error if the element does not exist
        void removeElement(const T& value) {
            auto original_size = data.size(); // Save size before removal

            // Remove all instances of the value
            data.erase(std::remove(data.begin(), data.end(), value), data.end());

            // If size didn’t change, the element wasn’t found
            if (data.size() == original_size) {
                throw std::runtime_error("Element not found in container");
            }

            version++; // Mark that the container has changed
        }

        // Returns the number of elements in the container
        size_t size() const {
            return data.size(); // Just return the vector's size
        }

        // Returns the internal vector (used by iterators)
        const std::vector<T>& getData() const {
            return data;
        }

        // Returns the container version (used by iterators to detect changes)
        size_t getVersion() const {
            return version;
        }

        // Prints the container elements in a readable format, e.g. [1, 2, 3]
        friend std::ostream& operator<<(std::ostream& os, const MyContainer<T>& container) {
            os << "[";
            for (size_t i = 0; i < container.data.size(); ++i) {
                os << container.data[i];
                if (i != container.data.size() - 1) {
                    os << ", "; // Add comma between elements
                }
            }
            os << "]";
            return os;
        }

        // Type aliases so users can write: MyContainer::AscendingIterator
        AscendingOrderIterator<T> begin_ascending_order() const {  // Begin iterator for ascending order
            return AscendingOrderIterator<T>(*this, false);  // Return new iterator at start
        }

        /**
         * @return Iterator to the end of ascending order
         * @throws None
         */
        AscendingOrderIterator<T> end_ascending_order() const {  // End iterator for ascending order
            return AscendingOrderIterator<T>(*this, true);  // Return new iterator at end
        }

        /**
         * @return Iterator to the beginning of descending order
         * @throws None
         */
        DescendingOrderIterator<T> begin_descending_order() const {  // Begin iterator for descending order
            return DescendingOrderIterator<T>(*this, false);  // Return new iterator at start
        }

        /**
         * @return Iterator to the end of descending order
         * @throws None
         */
        DescendingOrderIterator<T> end_descending_order() const {  // End iterator for descending order
            return DescendingOrderIterator<T>(*this, true);  // Return new iterator at end
        }

        /**
         * @return Iterator to the beginning of side-cross order
         * @throws None
         */
        SideCrossOrderIterator<T> begin_side_cross_order() const {  // Begin iterator for side-cross order
            return SideCrossOrderIterator<T>(*this, false);  // Return new iterator at start
        }

        /**
         * @return Iterator to the end of side-cross order
         * @throws None
         */
        SideCrossOrderIterator<T> end_side_cross_order() const {  // End iterator for side-cross order
            return SideCrossOrderIterator<T>(*this, true);  // Return new iterator at end
        }

        /**
         * @return Iterator to the beginning of reverse order
         * @throws None
         */
        ReverseOrderIterator<T> begin_reverse_order() const {  // Begin iterator for reverse order
            return ReverseOrderIterator<T>(*this, false);  // Return new iterator at start
        }

        /**
         * @return Iterator to the end of reverse order
         * @throws None
         */
        ReverseOrderIterator<T> end_reverse_order() const {  // End iterator for reverse order
            return ReverseOrderIterator<T>(*this, true);  // Return new iterator at end
        }

        /**
         * @return Iterator to the beginning of insertion order
         * @throws None
         */
        OrderIterator<T> begin_order() const {  // Begin iterator for insertion order
            return OrderIterator<T>(*this, false);  // Return new iterator at start
        }

        /**
         * @return Iterator to the end of insertion order
         * @throws None
         */
        OrderIterator<T> end_order() const {  // End iterator for insertion order
            return OrderIterator<T>(*this, true);  // Return new iterator at end
        }

        /**
         * @return Iterator to the beginning of middle-out order
         * @throws None
         */
        MiddleOutOrderIterator<T> begin_middle_out_order() const {  // Begin iterator for middle-out order
            return MiddleOutOrderIterator<T>(*this, false);  // Return new iterator at start
        }

        /**
         * @return Iterator to the end of middle-out order
         * @throws None
         */
        MiddleOutOrderIterator<T> end_middle_out_order() const {  // End iterator for middle-out order
            return MiddleOutOrderIterator<T>(*this, true);  // Return new iterator at end
        }
    };

} // namespace nooran

#endif // MYCONTAINER_HPP
