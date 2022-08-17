#ifndef CTMM_IMPL_H_
#define CTMM_IMPL_H_

#include "ctmm_concepts.h"

namespace ctmm {
template <int, int>
class Mat;

template <concepts::Mat, concepts::Mat>
class MatProduct;

namespace mat_traits {
template <concepts::Mat T>
class Size;

template <int NumRows, int NumCols>
class Size<Mat<NumRows, NumCols>> {
 public:
  static constexpr int kNumRows = NumRows;
  static constexpr int kNumCols = NumCols;
  static constexpr int kNumInputs = 1;
};

template <concepts::Mat LeftMat, concepts::Mat RightMat>
class Size<MatProduct<LeftMat, RightMat>> {
 public:
  static constexpr int kNumRows = Size<LeftMat>::kNumRows;
  static constexpr int kNumCols = Size<RightMat>::kNumCols;
  static constexpr int kNumInputs =
      Size<LeftMat>::kNumInputs + Size<RightMat>::kNumInputs;
};
}  // namespace mat_traits
}  // namespace ctmm

#endif  // CTMM_IMPL_H_
