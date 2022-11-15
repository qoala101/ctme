#include <benchmark/benchmark.h>

#include <vector>

#include "ctme_evaluate_to_vector.h"
#include "ctme_mat.h"
#include "ctme_mat_product.h"
#include "utils.h"

namespace {
struct Inputs {
  // clang-format off
  const std::vector<std::vector<double>>
      values0_1_1{utils::GenerateRandomValues<utils::AsVector, 1, 1>()}, values1_1_1{utils::GenerateRandomValues<utils::AsVector, 1, 1>()},
      values0_2_2{utils::GenerateRandomValues<utils::AsVector, 2, 2>()}, values1_2_2{utils::GenerateRandomValues<utils::AsVector, 2, 2>()},
      values0_3_3{utils::GenerateRandomValues<utils::AsVector, 3, 3>()}, values1_3_3{utils::GenerateRandomValues<utils::AsVector, 3, 3>()},
      values0_4_4{utils::GenerateRandomValues<utils::AsVector, 4, 4>()}, values1_4_4{utils::GenerateRandomValues<utils::AsVector, 4, 4>()},
      values0_5_5{utils::GenerateRandomValues<utils::AsVector, 5, 5>()}, values1_5_5{utils::GenerateRandomValues<utils::AsVector, 5, 5>()},
      values0_6_6{utils::GenerateRandomValues<utils::AsVector, 6, 6>()}, values1_6_6{utils::GenerateRandomValues<utils::AsVector, 6, 6>()},
      values0_7_7{utils::GenerateRandomValues<utils::AsVector, 7, 7>()}, values1_7_7{utils::GenerateRandomValues<utils::AsVector, 7, 7>()},
      values0_8_8{utils::GenerateRandomValues<utils::AsVector, 8, 8>()}, values1_8_8{utils::GenerateRandomValues<utils::AsVector, 8, 8>()},
      values0_9_9{utils::GenerateRandomValues<utils::AsVector, 9, 9>()}, values1_9_9{utils::GenerateRandomValues<utils::AsVector, 9, 9>()},
      values0_10_10{utils::GenerateRandomValues<utils::AsVector, 10, 10>()}, values1_10_10{utils::GenerateRandomValues<utils::AsVector, 10, 10>()},
      values0_12_12{utils::GenerateRandomValues<utils::AsVector, 12, 12>()}, values1_12_12{utils::GenerateRandomValues<utils::AsVector, 12, 12>()},
      values0_14_14{utils::GenerateRandomValues<utils::AsVector, 14, 14>()}, values1_14_14{utils::GenerateRandomValues<utils::AsVector, 14, 14>()},
      values0_16_16{utils::GenerateRandomValues<utils::AsVector, 16, 16>()}, values1_16_16{utils::GenerateRandomValues<utils::AsVector, 16, 16>()},
      values0_18_18{utils::GenerateRandomValues<utils::AsVector, 18, 18>()}, values1_18_18{utils::GenerateRandomValues<utils::AsVector, 18, 18>()};
  // clang-format on
};

auto GetInputs [[nodiscard]] () -> auto& {
  static const auto kInputs = Inputs{};
  return kInputs;
}

void MultiplyMatsWithLoops(benchmark::State& state) {
  const auto& inputs = GetInputs();

  for (auto unused : state) {
    // clang-format off
    if (state.range() == 1) { auto result = utils::MultiplyWithLoops<utils::AsVector, 1, 1, 1>(inputs.values0_1_1, inputs.values1_1_1); }
    if (state.range() == 2) { auto result = utils::MultiplyWithLoops<utils::AsVector, 2, 2, 2>(inputs.values0_2_2, inputs.values1_2_2); }
    if (state.range() == 3) { auto result = utils::MultiplyWithLoops<utils::AsVector, 3, 3, 3>(inputs.values0_3_3, inputs.values1_3_3); }
    if (state.range() == 4) { auto result = utils::MultiplyWithLoops<utils::AsVector, 4, 4, 4>(inputs.values0_4_4, inputs.values1_4_4); }
    if (state.range() == 5) { auto result = utils::MultiplyWithLoops<utils::AsVector, 5, 5, 5>(inputs.values0_5_5, inputs.values1_5_5); }
    if (state.range() == 6) { auto result = utils::MultiplyWithLoops<utils::AsVector, 6, 6, 6>(inputs.values0_6_6, inputs.values1_6_6); }
    if (state.range() == 7) { auto result = utils::MultiplyWithLoops<utils::AsVector, 7, 7, 7>(inputs.values0_7_7, inputs.values1_7_7); }
    if (state.range() == 8) { auto result = utils::MultiplyWithLoops<utils::AsVector, 8, 8, 8>(inputs.values0_8_8, inputs.values1_8_8); }
    if (state.range() == 9) { auto result = utils::MultiplyWithLoops<utils::AsVector, 9, 9, 9>(inputs.values0_9_9, inputs.values1_9_9); }
    if (state.range() == 10) { auto result = utils::MultiplyWithLoops<utils::AsVector, 10, 10, 10>(inputs.values0_10_10, inputs.values1_10_10); }
    if (state.range() == 12) { auto result = utils::MultiplyWithLoops<utils::AsVector, 12, 12, 12>(inputs.values0_12_12, inputs.values1_12_12); }
    if (state.range() == 14) { auto result = utils::MultiplyWithLoops<utils::AsVector, 14, 14, 14>(inputs.values0_14_14, inputs.values1_14_14); }
    if (state.range() == 16) { auto result = utils::MultiplyWithLoops<utils::AsVector, 16, 16, 16>(inputs.values0_16_16, inputs.values1_16_16); }
    if (state.range() == 18) { auto result = utils::MultiplyWithLoops<utils::AsVector, 18, 18, 18>(inputs.values0_18_18, inputs.values1_18_18); }
    // clang-format on
  }
}

void MultiplyMatsWithCtme(benchmark::State& state) {
  const auto& inputs = GetInputs();

  for (auto unused : state) {
    // clang-format off
    if (state.range() == 1) { auto result = ctme::EvaluateToVector<decltype(ctme::Mat<1, 1>{} * ctme::Mat<1, 1>{})>(inputs.values0_1_1, inputs.values1_1_1); }
    if (state.range() == 2) { auto result = ctme::EvaluateToVector<decltype(ctme::Mat<2, 2>{} * ctme::Mat<2, 2>{})>(inputs.values0_2_2, inputs.values1_2_2); }
    if (state.range() == 3) { auto result = ctme::EvaluateToVector<decltype(ctme::Mat<3, 3>{} * ctme::Mat<3, 3>{})>(inputs.values0_3_3, inputs.values1_3_3); }
    if (state.range() == 4) { auto result = ctme::EvaluateToVector<decltype(ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{})>(inputs.values0_4_4, inputs.values1_4_4); }
    if (state.range() == 5) { auto result = ctme::EvaluateToVector<decltype(ctme::Mat<5, 5>{} * ctme::Mat<5, 5>{})>(inputs.values0_5_5, inputs.values1_5_5); }
    if (state.range() == 6) { auto result = ctme::EvaluateToVector<decltype(ctme::Mat<6, 6>{} * ctme::Mat<6, 6>{})>(inputs.values0_6_6, inputs.values1_6_6); }
    if (state.range() == 7) { auto result = ctme::EvaluateToVector<decltype(ctme::Mat<7, 7>{} * ctme::Mat<7, 7>{})>(inputs.values0_7_7, inputs.values1_7_7); }
    if (state.range() == 8) { auto result = ctme::EvaluateToVector<decltype(ctme::Mat<8, 8>{} * ctme::Mat<8, 8>{})>(inputs.values0_8_8, inputs.values1_8_8); }
    if (state.range() == 9) { auto result = ctme::EvaluateToVector<decltype(ctme::Mat<9, 9>{} * ctme::Mat<9, 9>{})>(inputs.values0_9_9, inputs.values1_9_9); }
    if (state.range() == 10) { auto result = ctme::EvaluateToVector<decltype(ctme::Mat<10, 10>{} * ctme::Mat<10, 10>{})>(inputs.values0_10_10, inputs.values1_10_10); }
    if (state.range() == 12) { auto result = ctme::EvaluateToVector<decltype(ctme::Mat<12, 12>{} * ctme::Mat<12, 12>{})>(inputs.values0_12_12, inputs.values1_12_12); }
    if (state.range() == 14) { auto result = ctme::EvaluateToVector<decltype(ctme::Mat<14, 14>{} * ctme::Mat<14, 14>{})>(inputs.values0_14_14, inputs.values1_14_14); }
    if (state.range() == 16) { auto result = ctme::EvaluateToVector<decltype(ctme::Mat<16, 16>{} * ctme::Mat<16, 16>{})>(inputs.values0_16_16, inputs.values1_16_16); }
    if (state.range() == 18) { auto result = ctme::EvaluateToVector<decltype(ctme::Mat<18, 18>{} * ctme::Mat<18, 18>{})>(inputs.values0_18_18, inputs.values1_18_18); }
    // clang-format on
  }
}

BENCHMARK(MultiplyMatsWithLoops)
    ->Name("Product of two NxN std::vector<double> mats with loops")
    ->ArgName("N")
    ->DenseRange(1, 9)
    ->DenseRange(10, 18, 2);

BENCHMARK(MultiplyMatsWithCtme)
    ->Name("Product of two NxN std::vector<double> mats with CTME")
    ->ArgName("N")
    ->DenseRange(1, 9)
    ->DenseRange(10, 18, 2);
}  // namespace