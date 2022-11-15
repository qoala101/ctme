#ifndef CTME_DEBUG_LOGGER_H_
#define CTME_DEBUG_LOGGER_H_

#ifdef CTME_DEBUG
#include <iostream>
#include <map>
#include <string>

#include "ctme_concepts.h"  // IWYU pragma: keep

namespace ctme::debug {
namespace detail {
auto GetAddress [[nodiscard]] (const auto &object) {
  // NOLINTNEXTLINE(*-reinterpret-cast)
  return reinterpret_cast<int64_t>(std::addressof(object));
}
}  // namespace detail

/**
 * @brief Used to compose and visualize the order of operations on matrices.
 * Output example:
 *   Evaluating cell (0, 0):
 *   m1[0][2] * m2[2][0] +
 *   m1[0][1] * m2[1][0] +
 *   m1[0][0] * m2[0][0
 */
class Logger {
 public:
  /**
   * @brief Gives the logger instance.
   */
  static auto Instance [[nodiscard]] () -> auto & {
    static auto instance = Logger{};
    return instance;
  }

  /**
   * @brief Matrix would have the specified name when logged.
   * @remark Address of container is used by default.
   */
  void RegisterMatName(const MatValues auto &mat, std::string_view name) {
    mat_names_[detail::GetAddress(mat)] = name;
  }

  /**
   * @brief Prints inputs.
   */
  // NOLINTNEXTLINE(*-convert-member-functions-to-static)
  auto Print [[nodiscard]] () const -> auto & { return std::cout; }

  /**
   * @brief Prints matrix cell being read.
   */
  void PrintCell(const MatValues auto &mat, unsigned row_index,
                 unsigned column_index) const {
    Print() << GetMatName(mat) << "[" << row_index << "][" << column_index
            << "]";
  }

  /**
   * @brief Prints the cell being evaluated.
   */
  void PrintEvaluatingCell(unsigned row_index, unsigned column_index) const {
    Print() << "\n\nEvaluating cell (" << row_index << ", " << column_index
            << "):\n";
  }

 private:
  auto GetMatName [[nodiscard]] (const MatValues auto &mat) const {
    const auto address = detail::GetAddress(mat);
    const auto registered_name = mat_names_.find(address);

    if (registered_name == mat_names_.end()) {
      return std::to_string(address);
    }

    return registered_name->second;
  }

  std::string message_{};
  std::map<int64_t, std::string> mat_names_{};
};
}  // namespace ctme::debug
#endif  // CTME_DEBUG

#endif  // CTME_DEBUG_LOGGER_H_
