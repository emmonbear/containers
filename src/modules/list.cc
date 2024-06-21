/**
 * @file list.cc
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief Implementation of the list class
 * @version 1.0
 * @date 2024-06-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/list.h"

namespace containers {

/**
 * @brief Default constructor for the list class.
 *
 * @details
 *
 * Constructs an empty list, initializing head, tail, and size to default
 * values. The constructor is noexcept, indicating it does not throw exceptions.
 *
 * @tparam value_type The type of elements stored in the list.
 */
template <typename value_type>
list<value_type>::list() noexcept = default;

}  // namespace containers
