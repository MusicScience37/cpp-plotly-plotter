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
 * \brief Test of figure class.
 */
#include "plotly_plotter/figure.h"

#include <type_traits>

#include <ApprovalTests.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/traces/box.h"
#include "plotly_plotter/traces/scatter.h"

TEST_CASE("plotly_plotter::figure") {
    plotly_plotter::figure figure;

    SECTION("set title") {
        figure.title("Test Title");

        const std::string json_string =
            figure.document().serialize_to_string(true);
        ApprovalTests::Approvals::verify(json_string,
            ApprovalTests::Options().fileOptions().withFileExtension(".json"));
    }
}

TEMPLATE_TEST_CASE("trace types in figures and frames", "",
    plotly_plotter::figure, plotly_plotter::animation_frame) {
    plotly_plotter::figure figure;
    auto frame = figure.add_frame();
    TestType* tested = nullptr;
    if constexpr (std::is_same_v<TestType, plotly_plotter::figure>) {
        tested = &figure;
    } else {
        tested = &frame;
    }

    SECTION("create traces") {
        plotly_plotter::traces::scatter scatter = tested->add_scatter();
        plotly_plotter::traces::scatter_gl scatter_gl =
            tested->add_scatter_gl();
        plotly_plotter::traces::box box = tested->add_box();
        plotly_plotter::traces::violin violin = tested->add_violin();
        plotly_plotter::traces::heatmap heatmap = tested->add_heatmap();

        (void)scatter;
        (void)scatter_gl;
        (void)box;
        (void)violin;
        (void)heatmap;
    }
}
