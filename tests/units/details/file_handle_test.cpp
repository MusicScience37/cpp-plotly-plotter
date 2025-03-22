/*
 * Copyright 2025 MusicScience37 (Kenta Kabashima)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*!
 * \file
 * \brief Test of file_handle class.
 */
#include "plotly_plotter/details/file_handle.h"

#include <cstdio>
#include <fstream>
#include <string>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("plotly_plotter::details::file_handle") {
    using plotly_plotter::details::file_handle;

    SECTION("write to a file") {
        const std::string file_path = "file_handle_test.txt";
        (void)std::remove(file_path.c_str());
        {
            file_handle file(file_path, "w");
            file.write("Test string.");
        }
        {
            std::ifstream stream(file_path);
            REQUIRE(stream.is_open());
            const std::string contents =
                std::string(std::istreambuf_iterator<char>(stream),
                    std::istreambuf_iterator<char>());
            CHECK(contents == "Test string.");
        }
    }

    SECTION("try to open a file in non-existing directory") {
        const std::string file_path = "non_existing_dir/test_file_handle.txt";
        CHECK_THROWS_AS(file_handle(file_path, "w"), std::runtime_error);
    }

    SECTION("move constructor") {
        file_handle file1("file_handle_test.txt", "w");
        file_handle file2(std::move(file1));
        CHECK(file1.get() == nullptr);
        CHECK(file2.get() != nullptr);
    }

    SECTION("move assignment operator") {
        file_handle file1("file_handle_test.txt", "w");
        file_handle file2("file_handle_test2.txt", "w");
        file2 = std::move(file1);
        CHECK(file1.get() == nullptr);
        CHECK(file2.get() != nullptr);
    }
}
