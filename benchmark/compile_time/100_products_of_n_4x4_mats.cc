#include "ctme_evaluate_to_array.h"
#include "ctme_mat.h"
#include "ctme_mat_product.h"
#include "utils.h"

namespace {
template <unsigned I>
struct OneMat {
  static constexpr auto mat = ctme::EvaluateToArray<decltype(
#if N > 1
      ctme::Mat<4, 4>{} *
#endif
#if N > 2
      ctme::Mat<4, 4>{} *
#endif
#if N > 3
      ctme::Mat<4, 4>{} *
#endif
#if N > 4
      ctme::Mat<4, 4>{} *
#endif
      ctme::Mat<4, 4>{})>(
#if N > 1
      utils::CreateMat<4, 4>(),
#endif
#if N > 2
      utils::CreateMat<4, 4>(),
#endif
#if N > 3
      utils::CreateMat<4, 4>(),
#endif
#if N > 4
      utils::CreateMat<4, 4>(),
#endif
      utils::CreateMat<4, 4>());
};

template<unsigned I>
struct TenMats {
  static constexpr auto mat0 = OneMat<0>{};
  static constexpr auto mat1 = OneMat<1>{};
  static constexpr auto mat2 = OneMat<2>{};
  static constexpr auto mat3 = OneMat<3>{};
  static constexpr auto mat4 = OneMat<4>{};
  static constexpr auto mat5 = OneMat<5>{};
  static constexpr auto mat6 = OneMat<6>{};
  static constexpr auto mat7 = OneMat<7>{};
  static constexpr auto mat8 = OneMat<8>{};
  static constexpr auto mat9 = OneMat<9>{};
};

constexpr auto ten_mats0 = TenMats<0>{};
constexpr auto ten_mats1 = TenMats<1>{};
constexpr auto ten_mats2 = TenMats<2>{};
constexpr auto ten_mats3 = TenMats<3>{};
constexpr auto ten_mats4 = TenMats<4>{};
constexpr auto ten_mats5 = TenMats<5>{};
constexpr auto ten_mats6 = TenMats<6>{};
constexpr auto ten_mats7 = TenMats<7>{};
constexpr auto ten_mats8 = TenMats<8>{};
constexpr auto ten_mats9 = TenMats<9>{};
}  // namespace