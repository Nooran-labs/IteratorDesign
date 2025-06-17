
/*
 * Mail - noorangnaim@gmail.com
 */

#include <iostream>
#include "MyContainer.hpp"

using namespace nooran;  // Use the project namespace

/**
 * @brief Helper function to print all orders supported by the container.
 * @tparam T Type of elements in the container.
 * @param container The container instance to print.
 * @param label A descriptive label for the print block.
 */
template<typename T>
void printAllOrders(const MyContainer<T>& container, const std::string& label) {
    std::cout << "--- " << label << " ---" << std::endl;
    std::cout << "Size: " << container.size() << std::endl;

    std::cout << "Ascending Order: ";
    for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it)
        std::cout << *it << ' ';
    std::cout << std::endl;

    std::cout << "Descending Order: ";
    for (auto it = container.begin_descending_order(); it != container.end_descending_order(); ++it)
        std::cout << *it << ' ';
    std::cout << std::endl;

    std::cout << "SideCross Order: ";
    for (auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); ++it)
        std::cout << *it << ' ';
    std::cout << std::endl;

    std::cout << "Reverse Order: ";
    for (auto it = container.begin_reverse_order(); it != container.end_reverse_order(); ++it)
        std::cout << *it << ' ';
    std::cout << std::endl;

    std::cout << "Order (original): ";
    for (auto it = container.begin_order(); it != container.end_order(); ++it)
        std::cout << *it << ' ';
    std::cout << std::endl;

    std::cout << "MiddleOut Order: ";
    for (auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it)
        std::cout << *it << ' ';
    std::cout << "\n" << std::endl;
}

int main() {
    // Odd number of unique values
    MyContainer<int> oddContainer;
    oddContainer.addElement(13);
    oddContainer.addElement(2);
    oddContainer.addElement(25);
    oddContainer.addElement(8);
    oddContainer.addElement(4);
    std::cout << "Odd Container: " << oddContainer << std::endl;
    printAllOrders(oddContainer, "Odd-sized container [5 items]");

    // Even number of unique values
    MyContainer<int> evenContainer;
    evenContainer.addElement(5);
    evenContainer.addElement(11);
    evenContainer.addElement(6);
    evenContainer.addElement(9);
    evenContainer.addElement(17);
    evenContainer.addElement(3);
    std::cout << "Even Container: " << evenContainer << std::endl;
    printAllOrders(evenContainer, "Even-sized container [6 items]");


    // Empty container
    MyContainer<int> emptyContainer;
    std::cout << "Empty Container: " << emptyContainer << std::endl;
    printAllOrders(emptyContainer, "Empty container [0 items]");

    // All elements are the same
    MyContainer<int> duplicateContainer;
    for (int i = 0; i < 5; ++i)
        duplicateContainer.addElement(21);
    std::cout << "Duplicate Container: " << duplicateContainer << std::endl;
    printAllOrders(duplicateContainer, "Duplicate-elements container [5 identical items]");

    // Larger container with patterned values
    MyContainer<int> largeContainer;
    for (int i = 10; i < 30; i += 2)
        largeContainer.addElement(i);
    std::cout << "Large Container: " << largeContainer << std::endl;
    printAllOrders(largeContainer, "Large container [10 elements, step by 2]");

    return 0;
}
