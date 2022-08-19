# Compile Time Matrix Evaluation

Header-only C++ matrix evaluation library.

## Install

Copy headers to your build tree.

## Usage

#### Form matrix expression

```c++
#include <ctme_mat.h>
#include <ctme_mat_product.h>

constexpr auto mat_product = ctme::Mat<2, 3>{} * ctme::Mat<3, 2>{};
constexpr auto product_of_products = mat_product * (ctme::Mat<2, 1>{} * ctme::Mat<1, 3>{});

```

---

#### Provide values for each matrix in any container which supports [unsigned][unsigned] syntax

```c++
const auto array_2_3 = std::array<std::array<int, 3>, 2>{};
const auto vector_3_2 = std::vector<std::vector<int64_t>>(3, std::vector<int64_t>(2));
const auto c_array_2_1 = new float[2][1];
const auto client_container_1_3 = ClientContainer<double>{1, 3};
```

---

#### Evaluate the result to standard containers

```c++
const auto result_vector = ctme::EvaluateToVector(
    product_of_products, array_2_3, vector_3_2, c_array_2_1, client_container_1_3);

const auto result_array = ctme::EvaluateToArray(mat_product, array_2_3, vector_3_2);
```

---

#### Query result type and size prior to evaluation

```c++
using ResultTraits = decltype(ctme::GetResultTraits(mat_product, array_2_3, vector_3_2));

static_assert(std::is_same_v<ResultTraits::ValueType, int64_t>);
static_assert(ResultTraits::kNumRows == 2);
static_assert(ResultTraits::kNumCols == 2);
```

---

#### Evaluate the result to any container which supports [unsigned][unsigned] syntax

```c++
auto result = std::unique_ptr<ResultTraits::ValueType[][2]>{
    new ResultTraits::ValueType[ResultTraits::kNumRows][ResultTraits::kNumCols]{}};
ctme::EvaluateTo(mat_product, result, array_2_3, vector_3_2);
```

---

#### Evaluate single cell

```c++
const auto cell_0_0 = ctme::Evaluate<0, 0>(mat_product, array_2_3, vector_3_2);
const auto cell_0_1 = ctme::Evaluate<0, 1>(mat_product, array_2_3, vector_3_2);
const auto cell_1_0 = ctme::Evaluate<1, 0>(mat_product, array_2_3, vector_3_2);
const auto cell_1_1 = ctme::Evaluate<1, 1>(mat_product, array_2_3, vector_3_2);
```

---

#### Evaluation is constexpr if inputs are constexpr

```c++
constexpr auto mat_product = ctme::Mat<2, 3>{} * ctme::Mat<3, 2>{};

constexpr auto array_2_3 = std::array<std::array<int, 3>, 2>{
    std::array<int, 3>{11, 12, 13}, {14, 15, 16}};
constexpr auto array_3_2 = std::array<std::array<float, 2>, 3>{
    std::array<float, 2>{21.1, 22.1}, {23.1, 24.1}, {25.1, 26.1}};

constexpr auto result = ctme::EvaluateToArray(mat_product, array_2_3, array_3_2);
constexpr auto cell_0_0 = ctme::Evaluate<0, 0>(mat_product, array, vector);
```

---

## Benchmarks

Below are some [benchmarks](LINK_TO_BENCHMARK.cc) done in Ubuntu 64 bit, Intel i7-4770 CPU @ 3.40GHz

#### Synchronous mode

```

```

#### Asynchronous mode

```

```
