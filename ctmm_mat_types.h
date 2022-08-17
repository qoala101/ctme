#ifndef STONKS_CTMM_MATS_H_
#define STONKS_CTMM_MATS_H_

#include "ctmm_concepts.h"
#include "ctmm_mat_traits_size.h"

namespace ctmm {
  /**
   * @brief 
   * 
   * @tparam NumRows 
   * @tparam NumCols 
   */
template <int NumRows, int NumCols>
class Mat {
  static_assert(NumRows > 0);
  static_assert(NumCols > 0);
};

template <concepts::Mat LeftMat, concepts::Mat RightMat>
class MatProduct {
  static_assert(mat_traits::Size<LeftMat>::kNumCols ==
                mat_traits::Size<RightMat>::kNumRows);
};
}  // namespace ctmm

#endif  // STONKS_CTMM_MATS_H_
