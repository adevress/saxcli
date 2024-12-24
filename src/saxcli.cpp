/**
 * Copyright (c) 2018, Adrien Devresse <adrien.devresse@epfl.ch>
 *
 * Boost Software License - Version 1.0
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#include <algorithm>
#include <array>
#include <concepts>
#include <numeric>
#include <optional>
#include <span>
#include <sstream>

#include <saxcli/saxcli.hpp>

#include <doctest/doctest.h>
#include <string>
#include <string_view>

namespace saxcli {

const std::string_view _help_opt = "--help";

namespace tests {

TEST_CASE("test: basic option handling with interleave") {

  std::string prog_name;
  bool found_hello = false;

  auto argv = std::to_array<const char *>({"prog1", "--hello", nullptr});

  args_handler args{};
  args.prog_name([&](std::string_view sv){
    prog_name = sv;
  });

  args.options({option_handler("hello", [&](std::string_view sv) ->  void { found_hello = true; },
      "An hello option")
});

  auto result = parse_args(args, argv.size() - 1,
                                const_cast<char **>(argv.data()));
  CHECK(result.has_value());
  CHECK(prog_name == "prog1");
  CHECK(found_hello == true);
}

TEST_CASE("test error: no progname") {

  std::string prog_name;

  auto argv = std::to_array<const char *>({nullptr});

  args_handler args{};

  auto result = parse_args(args, argv.size() - 1,
                                const_cast<char **>(argv.data()));

  CHECK(!result.has_value());
}

} // namespace tests

} // namespace saxcli
