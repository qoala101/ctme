#ifndef STONKS_CTMM_IMPL_H_
#define STONKS_CTMM_IMPL_H_

#include "ctmm_concepts.h"

namespace ctmm {
template <int, int>
class Mat;

template <concepts::Mat, concepts::Mat>
class MatProduct;

template <concepts::Mat T>
class MatTrait;

template <int NumRows, int NumCols>
class MatTrait<Mat<NumRows, NumCols>> {
 public:
  static constexpr int kNumRows = NumRows;
  static constexpr int kNumCols = NumCols;
  static constexpr int kNumInputs = 1;
};

template <concepts::Mat LeftMat, concepts::Mat RightMat>
class MatTrait<MatProduct<LeftMat, RightMat>> {
 public:
  static constexpr int kNumRows = MatTrait<LeftMat>::kNumRows;
  static constexpr int kNumCols = MatTrait<RightMat>::kNumCols;
  static constexpr int kNumInputs = MatTrait<LeftMat>::kNumInputs + MatTrait<RightMat>::kNumInputs;
};
}  // namespace ctmm

#endif  // STONKS_CTMM_IMPL_H_
