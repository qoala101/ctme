#include <benchmark/benchmark.h>

#include <vector>

#include "ctme_evaluate_to_vector.h"
#include "ctme_mat.h"
#include "ctme_mat_product.h"
#include "utils.h"

namespace p_n_4x4_vector {
struct Inputs {
  // clang-format off
  const std::vector<std::vector<double>>
      values0_4_4{utils::GenerateRandomValues<utils::AsVector, 4, 4>()},
      values1_4_4{utils::GenerateRandomValues<utils::AsVector, 4, 4>()},
      values2_4_4{utils::GenerateRandomValues<utils::AsVector, 4, 4>()},
      values3_4_4{utils::GenerateRandomValues<utils::AsVector, 4, 4>()},
      values4_4_4{utils::GenerateRandomValues<utils::AsVector, 4, 4>()},
      values5_4_4{utils::GenerateRandomValues<utils::AsVector, 4, 4>()},
      values6_4_4{utils::GenerateRandomValues<utils::AsVector, 4, 4>()},
      values7_4_4{utils::GenerateRandomValues<utils::AsVector, 4, 4>()},
      values8_4_4{utils::GenerateRandomValues<utils::AsVector, 4, 4>()},
      values9_4_4{utils::GenerateRandomValues<utils::AsVector, 4, 4>()};
  // clang-format on
};

[[nodiscard]] auto GetInputs() -> auto& {
  static const auto kInputs = Inputs{};
  return kInputs;
}

void MultiplyMatsWithLoops(benchmark::State& state) {
  const auto& inputs = GetInputs();
  auto result = std::vector<std::vector<double>>{};

  for (auto unused : state) {
    // clang-format off
    if (state.range() >= 2) { result = utils::MultiplyWithLoops<utils::AsVector, 4, 4, 4>(inputs.values0_4_4, inputs.values1_4_4); }
    if (state.range() >= 3) { result = utils::MultiplyWithLoops<utils::AsVector, 4, 4, 4>(result, inputs.values2_4_4); }
    if (state.range() >= 4) { result = utils::MultiplyWithLoops<utils::AsVector, 4, 4, 4>(result, inputs.values3_4_4); }
    if (state.range() >= 5) { result = utils::MultiplyWithLoops<utils::AsVector, 4, 4, 4>(result, inputs.values4_4_4); }
    if (state.range() >= 6) { result = utils::MultiplyWithLoops<utils::AsVector, 4, 4, 4>(result, inputs.values5_4_4); }
    if (state.range() >= 7) { result = utils::MultiplyWithLoops<utils::AsVector, 4, 4, 4>(result, inputs.values6_4_4); }
    if (state.range() >= 8) { result = utils::MultiplyWithLoops<utils::AsVector, 4, 4, 4>(result, inputs.values7_4_4); }
    if (state.range() >= 9) { result = utils::MultiplyWithLoops<utils::AsVector, 4, 4, 4>(result, inputs.values8_4_4); }
    if (state.range() >= 10) { result = utils::MultiplyWithLoops<utils::AsVector, 4, 4, 4>(result, inputs.values9_4_4); }
    // clang-format on
  }
}

void MultiplyMatsWithCtme(benchmark::State& state) {
  const auto& inputs = GetInputs();
  auto result = std::vector<std::vector<double>>{};

  for (auto unused : state) {
    // clang-format off
    if (state.range() == 2) { result = ctme::EvaluateToVector<decltype(ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{})>(inputs.values0_4_4, inputs.values1_4_4); }
    if (state.range() == 3) { result = ctme::EvaluateToVector<decltype(ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{})>(inputs.values0_4_4, inputs.values1_4_4, inputs.values2_4_4); }
    if (state.range() == 4) { result = ctme::EvaluateToVector<decltype(ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{})>(inputs.values0_4_4, inputs.values1_4_4, inputs.values2_4_4, inputs.values3_4_4); }
    if (state.range() == 5) { result = ctme::EvaluateToVector<decltype(ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{})>(inputs.values0_4_4, inputs.values1_4_4, inputs.values2_4_4, inputs.values3_4_4, inputs.values4_4_4); }
    if (state.range() == 6) { result = ctme::EvaluateToVector<decltype(ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{})>(inputs.values0_4_4, inputs.values1_4_4, inputs.values2_4_4, inputs.values3_4_4, inputs.values4_4_4, inputs.values5_4_4); }
    if (state.range() == 7) { result = ctme::EvaluateToVector<decltype(ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{})>(inputs.values0_4_4, inputs.values1_4_4, inputs.values2_4_4, inputs.values3_4_4, inputs.values4_4_4, inputs.values5_4_4, inputs.values6_4_4); }
    if (state.range() == 8) { result = ctme::EvaluateToVector<decltype(ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{})>(inputs.values0_4_4, inputs.values1_4_4, inputs.values2_4_4, inputs.values3_4_4, inputs.values4_4_4, inputs.values5_4_4, inputs.values6_4_4, inputs.values7_4_4); }
    if (state.range() == 9) { result = ctme::EvaluateToVector<decltype(ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{})>(inputs.values0_4_4, inputs.values1_4_4, inputs.values2_4_4, inputs.values3_4_4, inputs.values4_4_4, inputs.values5_4_4, inputs.values6_4_4, inputs.values7_4_4, inputs.values8_4_4); }
    if (state.range() == 10) { result = ctme::EvaluateToVector<decltype(ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{} * ctme::Mat<4, 4>{})>(inputs.values0_4_4, inputs.values1_4_4, inputs.values2_4_4, inputs.values3_4_4, inputs.values4_4_4, inputs.values5_4_4, inputs.values6_4_4, inputs.values7_4_4, inputs.values8_4_4, inputs.values9_4_4); }
    // clang-format on
  }
}
}  // namespace p_n_4x4_vector

namespace {
BENCHMARK(p_n_4x4_vector::MultiplyMatsWithLoops)
    ->Name("Product of N 4x4 std::vector<double> mats with loops")
    ->ArgName("N")
    ->DenseRange(2, 10);

BENCHMARK(p_n_4x4_vector::MultiplyMatsWithCtme)
    ->Name("Product of N 4x4 std::vector<double> mats with CTME")
    ->ArgName("N")
    ->DenseRange(2, 10);
}  // namespace