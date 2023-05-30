# Compile Time Matrix Evaluation

[![Tests](https://github.com/qoala101/ctme/actions/workflows/tests.yml/badge.svg)](https://github.com/qoala101/ctme/actions/workflows/tests.yml)
[![Codecov](https://codecov.io/gh/qoala101/ctme/branch/master/graph/badge.svg?token=HEU7FNKJVY)](https://codecov.io/gh/qoala101/ctme)
[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![GitHub Releases](https://img.shields.io/github/release/qoala101/ctme.svg)](https://github.com/qoala101/ctme/releases)

## Description

Fast header-only C++ matrix evaluation library with zero memory overhead.

## Install

Copy headers to your build tree.

## Features

- No additional matrices are created during the computation to store intermediate results.
- Fast run time evaluation due to absence of loops (see [benchmarks](#benchmarks) below). All the loops are unrolled using TMP.
- Compile time evaluation of complex matrix expressions given compile time inputs.
- Compile time expression correctness check (e.g. multiplying matrices of wrong sizes would not compile).
- Supports any containers which support [unsigned][unsigned] syntax.
- Supports any combination of value types for which operations used in expressions are available (e.g. \*, +, etc.).
- Matrix expressions can be formed as either objects or types.
- Currently supported matrix operations: \*, +.

## Usage

#### Form matrix expression with matrices which dimensions are known at the compile time

```c++
#include <ctme_mat.h>
#include <ctme_mat_product.h>

constexpr auto mat_product = ctme::Mat<2, 3>{} * ctme::Mat<3, 2>{};
constexpr auto product_of_products = mat_product * (ctme::Mat<2, 1>{} * ctme::Mat<1, 5>{});

```

---

#### Provide values for each matrix in any container which supports [unsigned][unsigned] syntax

```c++
constexpr auto array_2_3 = std::array<std::array<int, 3>, 2>{};
const auto vector_3_2 = std::vector<std::vector<int64_t>>(3, std::vector<int64_t>(2));
const auto c_array_2_1 = new float[2][1];
const auto client_container_1_5 = ClientContainer<double>{1, 5};
```

---

#### Evaluate the result to standard containers

```c++
#include <ctme_evaluate_to_array.h>
#include <ctme_evaluate_to_vector.h>

const auto result_vector_2_5 = ctme::EvaluateToVector(
    product_of_products, array_2_3, vector_3_2, c_array_2_1, client_container_1_5);

const auto result_array_2_2 = ctme::EvaluateToArray(mat_product, array_2_3, vector_3_2);
```

---

#### Query result type and size prior to evaluation

```c++
#include <ctme_result_traits.h>

using ResultTraits = decltype(ctme::GetResultTraits(mat_product, array_2_3, vector_3_2));

static_assert(std::is_same_v<ResultTraits::ValueType, int64_t>);
static_assert(ResultTraits::kNumRows == 2);
static_assert(ResultTraits::kNumCols == 2);
```

---

#### Evaluate the result to any container which supports [unsigned][unsigned] syntax

```c++
#include <ctme_evaluate_to_container.h>

auto result = std::unique_ptr<ResultTraits::ValueType[][2]>{
    new ResultTraits::ValueType[ResultTraits::kNumRows][ResultTraits::kNumCols]{}};

ctme::EvaluateTo(mat_product, result, array_2_3, vector_3_2);
```

---

#### Evaluate single cell

```c++
#include <ctme_evaluate_cell.h>

const auto cell_0_0 = ctme::EvaluateCell<0, 0>(mat_product, array_2_3, vector_3_2);
const auto cell_0_1 = ctme::EvaluateCell<0, 1>(mat_product, array_2_3, vector_3_2);
const auto cell_1_0 = ctme::EvaluateCell<1, 0>(mat_product, array_2_3, vector_3_2);
const auto cell_1_1 = ctme::EvaluateCell<1, 1>(mat_product, array_2_3, vector_3_2);
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
constexpr auto cell_0_0 = ctme::EvaluateCell<0, 0>(mat_product, array, vector);
```

---

#### Evaluation logic is a property of expression type, so all APIs also support type syntax

```c++
using ProductManualSyntax = ctme::MatProduct<ctme::Mat<2, 3>, ctme::Mat<3, 2>>;
using ProductDecltypeSyntax = decltype(ctme::Mat<2, 3>{} * ctme::Mat<3, 2>{});

constexpr auto result = ctme::EvaluateToArray<ProductManualSyntax>(array_2_3, array_3_2);
constexpr auto cell_0_0 = ctme::EvaluateCell<ProductDecltypeSyntax, 0, 0>(array, vector);
```

---

## Benchmarks

#### Benchmarks below were done on:

- Debian GNU/Linux 11, 64-bit
- Intel® Core™ i5-1035G1 CPU @ 1.00GHz × 8, 7.6 GiB RAM
- clang++-15, libstdc++11, Release

### Compile time multiplication

```
-----------------------------------------------------
Benchmark                           Time   Iterations
-----------------------------------------------------
Product of 2 NxN mats/N:6        43.2 ms          100
Product of 2 NxN mats/N:9       121.1 ms          100
Product of 2 NxN mats/N:12        299 ms          100
Product of 2 NxN mats/N:15      457.6 ms          100

Product of N 4x4 mats/N:2        10.4 ms          100
Product of N 4x4 mats/N:3        13.6 ms          100
Product of N 4x4 mats/N:4          38 ms          100
Product of N 4x4 mats/N:5       127.1 ms          100
```

### Runtime multiplication compared to simple for-loop multiplication

```
------------------------------------------------------------------------------------------------------
Benchmark                                                            Time             CPU   Iterations
------------------------------------------------------------------------------------------------------
Product of two NxN std::array<double> mats with loops/N:1         1.71 ns         1.71 ns    394803286
Product of two NxN std::array<double> mats with loops/N:2         1.69 ns         1.69 ns    405356393
Product of two NxN std::array<double> mats with loops/N:3         8.10 ns         8.09 ns     85607652
Product of two NxN std::array<double> mats with loops/N:4         14.8 ns         14.8 ns     41535017
Product of two NxN std::array<double> mats with loops/N:5         28.5 ns         28.5 ns     24432150
Product of two NxN std::array<double> mats with loops/N:6         46.0 ns         46.0 ns     13704161
Product of two NxN std::array<double> mats with loops/N:7         74.0 ns         74.0 ns      8458790
Product of two NxN std::array<double> mats with loops/N:8         1.12 ns         1.12 ns    588478177
Product of two NxN std::array<double> mats with loops/N:9         1.69 ns         1.69 ns    409890033
Product of two NxN std::array<double> mats with loops/N:10         184 ns          184 ns      3965429
Product of two NxN std::array<double> mats with loops/N:12         313 ns          313 ns      2366088
Product of two NxN std::array<double> mats with loops/N:14         493 ns          493 ns      1274778
Product of two NxN std::array<double> mats with loops/N:16         876 ns          876 ns       787861
Product of two NxN std::array<double> mats with loops/N:18        1151 ns         1151 ns       568005

Product of two NxN std::array<double> mats with CTME/N:1          1.68 ns         1.68 ns    411042888
Product of two NxN std::array<double> mats with CTME/N:2          1.68 ns         1.68 ns    408020456
Product of two NxN std::array<double> mats with CTME/N:3          1.67 ns         1.67 ns    408269925
Product of two NxN std::array<double> mats with CTME/N:4          18.1 ns         18.1 ns     38963530
Product of two NxN std::array<double> mats with CTME/N:5          36.0 ns         36.0 ns     19449406
Product of two NxN std::array<double> mats with CTME/N:6          65.2 ns         65.2 ns     10097615
Product of two NxN std::array<double> mats with CTME/N:7           100 ns          100 ns      6717005
Product of two NxN std::array<double> mats with CTME/N:8           153 ns          153 ns      4475937
Product of two NxN std::array<double> mats with CTME/N:9           241 ns          241 ns      2952693
Product of two NxN std::array<double> mats with CTME/N:10          321 ns          321 ns      2165307
Product of two NxN std::array<double> mats with CTME/N:12          674 ns          674 ns      1005128
Product of two NxN std::array<double> mats with CTME/N:14         1081 ns         1081 ns       625950
Product of two NxN std::array<double> mats with CTME/N:16         1648 ns         1648 ns       420580
Product of two NxN std::array<double> mats with CTME/N:18         2217 ns         2217 ns       311841
------------------------------------------------------------------------------------------------------
Product of two NxN std::vector<double> mats with loops/N:1        41.5 ns         41.5 ns     16853762
Product of two NxN std::vector<double> mats with loops/N:2        58.6 ns         58.6 ns     11678222
Product of two NxN std::vector<double> mats with loops/N:3        84.2 ns         84.2 ns      8194652
Product of two NxN std::vector<double> mats with loops/N:4         106 ns          106 ns      6515420
Product of two NxN std::vector<double> mats with loops/N:5         140 ns          140 ns      4961457
Product of two NxN std::vector<double> mats with loops/N:6         181 ns          181 ns      3829147
Product of two NxN std::vector<double> mats with loops/N:7         241 ns          241 ns      2891138
Product of two NxN std::vector<double> mats with loops/N:8         311 ns          311 ns      2251380
Product of two NxN std::vector<double> mats with loops/N:9         404 ns          404 ns      1309874
Product of two NxN std::vector<double> mats with loops/N:10        511 ns          511 ns      1052969
Product of two NxN std::vector<double> mats with loops/N:12        798 ns          798 ns       793425
Product of two NxN std::vector<double> mats with loops/N:14       1274 ns         1274 ns       511671
Product of two NxN std::vector<double> mats with loops/N:16       1945 ns         1945 ns       342874
Product of two NxN std::vector<double> mats with loops/N:18       2886 ns         2886 ns       242487

Product of two NxN std::vector<double> mats with CTME/N:1         41.3 ns         41.3 ns     16976839
Product of two NxN std::vector<double> mats with CTME/N:2         58.8 ns         58.8 ns     11540014
Product of two NxN std::vector<double> mats with CTME/N:3         79.5 ns         79.5 ns      7716385
Product of two NxN std::vector<double> mats with CTME/N:4          107 ns          107 ns      6307674
Product of two NxN std::vector<double> mats with CTME/N:5          146 ns          146 ns      4636277
Product of two NxN std::vector<double> mats with CTME/N:6          199 ns          199 ns      3474046
Product of two NxN std::vector<double> mats with CTME/N:7          270 ns          270 ns      2560345
Product of two NxN std::vector<double> mats with CTME/N:8          425 ns          425 ns      1642890
Product of two NxN std::vector<double> mats with CTME/N:9          548 ns          548 ns      1202664
Product of two NxN std::vector<double> mats with CTME/N:10         724 ns          724 ns       916461
Product of two NxN std::vector<double> mats with CTME/N:12        1226 ns         1226 ns       548613
Product of two NxN std::vector<double> mats with CTME/N:14        1949 ns         1949 ns       341916
Product of two NxN std::vector<double> mats with CTME/N:16        2538 ns         2538 ns       270785
Product of two NxN std::vector<double> mats with CTME/N:18       10947 ns        10945 ns       196061
------------------------------------------------------------------------------------------------------
Product of N 4x4 std::array<double> mats with loops/N:2           14.3 ns         14.3 ns     48012719
Product of N 4x4 std::array<double> mats with loops/N:3           30.2 ns         30.2 ns     23083700
Product of N 4x4 std::array<double> mats with loops/N:4           45.4 ns         45.4 ns     15383484
Product of N 4x4 std::array<double> mats with loops/N:5           60.4 ns         60.4 ns     10695037
Product of N 4x4 std::array<double> mats with loops/N:6           75.7 ns         75.7 ns      8724968
Product of N 4x4 std::array<double> mats with loops/N:7           90.6 ns         90.6 ns      7301274
Product of N 4x4 std::array<double> mats with loops/N:8            105 ns          105 ns      6446397
Product of N 4x4 std::array<double> mats with loops/N:9            119 ns          119 ns      5677311
Product of N 4x4 std::array<double> mats with loops/N:10           133 ns          133 ns      5046654

Product of N 4x4 std::array<double> mats with CTME/N:2            17.6 ns         17.6 ns     38600128
Product of N 4x4 std::array<double> mats with CTME/N:3            79.0 ns         79.0 ns      8315448
Product of N 4x4 std::array<double> mats with CTME/N:4             137 ns          137 ns      4888551
Product of N 4x4 std::array<double> mats with CTME/N:5             612 ns          612 ns      1066220
Product of N 4x4 std::array<double> mats with CTME/N:6            2492 ns         2492 ns       276753
Product of N 4x4 std::array<double> mats with CTME/N:7           15357 ns        15356 ns        44117
Product of N 4x4 std::array<double> mats with CTME/N:8           61528 ns        61528 ns         9801
Product of N 4x4 std::array<double> mats with CTME/N:9          166435 ns       166436 ns         4091
Product of N 4x4 std::array<double> mats with CTME/N:10         675104 ns       675112 ns          964
------------------------------------------------------------------------------------------------------
Product of N 4x4 std::vector<double> mats with loops/N:2           104 ns          104 ns      6598113
Product of N 4x4 std::vector<double> mats with loops/N:3           205 ns          205 ns      3341055
Product of N 4x4 std::vector<double> mats with loops/N:4           308 ns          308 ns      2258260
Product of N 4x4 std::vector<double> mats with loops/N:5           410 ns          410 ns      1703349
Product of N 4x4 std::vector<double> mats with loops/N:6           518 ns          518 ns      1342441
Product of N 4x4 std::vector<double> mats with loops/N:7           616 ns          616 ns      1074179
Product of N 4x4 std::vector<double> mats with loops/N:8           725 ns          726 ns       928152
Product of N 4x4 std::vector<double> mats with loops/N:9           825 ns          825 ns       830767
Product of N 4x4 std::vector<double> mats with loops/N:10          924 ns          924 ns       736626

Product of N 4x4 std::vector<double> mats with CTME/N:2            110 ns          110 ns      6314852
Product of N 4x4 std::vector<double> mats with CTME/N:3            176 ns          176 ns      3965052
Product of N 4x4 std::vector<double> mats with CTME/N:4            249 ns          249 ns      2792584
Product of N 4x4 std::vector<double> mats with CTME/N:5            803 ns          804 ns       843749
Product of N 4x4 std::vector<double> mats with CTME/N:6           2932 ns         2932 ns       237173
Product of N 4x4 std::vector<double> mats with CTME/N:7          11612 ns        11613 ns        58308
Product of N 4x4 std::vector<double> mats with CTME/N:8          46985 ns        46989 ns        11493
Product of N 4x4 std::vector<double> mats with CTME/N:9         191355 ns       191368 ns         3617
Product of N 4x4 std::vector<double> mats with CTME/N:10        773427 ns       773501 ns          851
```

### Conclusion

- Runtime performance is worse than expected, especially when multiplying many matrices in single expression.
- Compile time multiplication is limited to 5 4x4 or 2 15x15 matrices in the single expression by the maximum template depth.
