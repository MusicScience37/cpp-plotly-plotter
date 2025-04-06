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
 * \brief Test of color sequences.
 */
#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/data_table.h"
#include "plotly_plotter/figure_builders/scatter.h"
#include "plotly_plotter/write_html.h"

TEST_CASE("color sequences") {
    using plotly_plotter::data_table;
    using plotly_plotter::write_html;
    using plotly_plotter::figure_builders::scatter;

    constexpr int num_groups = 12;

    SECTION("plot scatters") {
        data_table data;
        auto x = data.emplace<int>("x");
        auto y = data.emplace<int>("y");
        auto group = data.emplace<int>("group");
        for (int i = 0; i < num_groups; ++i) {
            x->push_back(1);
            x->push_back(2);
            x->push_back(3);
            y->push_back(i + 1);
            y->push_back(i + 2);
            y->push_back(i + 3);
            group->push_back(i);
            group->push_back(i);
            group->push_back(i);
        }

        const auto figure = scatter(data)
                                .x("x")
                                .y("y")
                                .group("group")
                                .mode("lines+markers")
                                .title("Color Sequences")
                                .create();

        const std::string file_path = "color_sequences_plot_scatters.html";
        write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }
}
