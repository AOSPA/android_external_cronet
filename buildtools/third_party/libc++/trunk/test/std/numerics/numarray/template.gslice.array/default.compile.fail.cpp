//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <valarray>

// template <class T> class gslice_array

// gslice_array() = delete;

#include <valarray>
#include <type_traits>

int main(int, char**)
{
    std::gslice_array<int> gs;

  return 0;
}
