#include "ctme_evaluate_to_array.h"
#include "ctme_mat.h"
#include "ctme_mat_product.h"
#include "utils.h"

namespace {
template <unsigned I>
struct TenMats {
  // clang-format off
  static constexpr auto mat0 = ctme::EvaluateToArray<decltype(ctme::Mat<N, N>{} * ctme::Mat<N, N>{})>(utils::CreateMat<N, N>(), utils::CreateMat<N, N>());
  static constexpr auto mat1 = ctme::EvaluateToArray<decltype(ctme::Mat<N, N>{} * ctme::Mat<N, N>{})>(utils::CreateMat<N, N>(), utils::CreateMat<N, N>());
  static constexpr auto mat2 = ctme::EvaluateToArray<decltype(ctme::Mat<N, N>{} * ctme::Mat<N, N>{})>(utils::CreateMat<N, N>(), utils::CreateMat<N, N>());
  static constexpr auto mat3 = ctme::EvaluateToArray<decltype(ctme::Mat<N, N>{} * ctme::Mat<N, N>{})>(utils::CreateMat<N, N>(), utils::CreateMat<N, N>());
  static constexpr auto mat4 = ctme::EvaluateToArray<decltype(ctme::Mat<N, N>{} * ctme::Mat<N, N>{})>(utils::CreateMat<N, N>(), utils::CreateMat<N, N>());
  static constexpr auto mat5 = ctme::EvaluateToArray<decltype(ctme::Mat<N, N>{} * ctme::Mat<N, N>{})>(utils::CreateMat<N, N>(), utils::CreateMat<N, N>());
  static constexpr auto mat6 = ctme::EvaluateToArray<decltype(ctme::Mat<N, N>{} * ctme::Mat<N, N>{})>(utils::CreateMat<N, N>(), utils::CreateMat<N, N>());
  static constexpr auto mat7 = ctme::EvaluateToArray<decltype(ctme::Mat<N, N>{} * ctme::Mat<N, N>{})>(utils::CreateMat<N, N>(), utils::CreateMat<N, N>());
  static constexpr auto mat8 = ctme::EvaluateToArray<decltype(ctme::Mat<N, N>{} * ctme::Mat<N, N>{})>(utils::CreateMat<N, N>(), utils::CreateMat<N, N>());
  static constexpr auto mat9 = ctme::EvaluateToArray<decltype(ctme::Mat<N, N>{} * ctme::Mat<N, N>{})>(utils::CreateMat<N, N>(), utils::CreateMat<N, N>());
  // clang-format on
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