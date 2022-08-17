#ifndef STONKS_CTMM_OPERATIONS_H_
#define STONKS_CTMM_OPERATIONS_H_

#include "ctmm_concepts.h"
#include "ctmm_mat_types.h"

/**
 * @file Supported matrix operations.
 */
namespace ctmm {
/**
 * @brief Produces an object of type representing matrix product.
 * @param left_mat Left matrix.
 * @param right_mat Right matrix. Number of columns should be the same
 * as number of rows in the left matrix.
 * @return Matrix product.
 */
[[nodiscard]] constexpr auto operator*(const concepts::Mat auto &left_mat,
                                       const concepts::Mat auto &right_mat)
    -> concepts::Mat auto{
  return MatProduct<std::decay_t<decltype(left_mat)>,
                    std::decay_t<decltype(right_mat)>>{};
}
}  // namespace ctmm

#endif  // STONKS_CTMM_OPERATIONS_H_
