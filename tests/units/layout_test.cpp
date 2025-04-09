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
 * \brief Test of layout class.
 */
#include "plotly_plotter/layout.h"

#include <string>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/figure.h"
#include "plotly_plotter/json_document.h"

TEST_CASE("plotly_plotter::layout") {
    plotly_plotter::figure figure;

    SECTION("set parameters") {
        figure.layout().xaxis().title().text("x-axis");
        figure.layout().xaxis().type("linear");
        figure.layout().xaxis(1).range(0, nullptr);
        figure.layout().xaxis(1).constrain("domain");
        figure.layout().xaxis(2).title().text("x-axis2");
        figure.layout().xaxis(2).type("log");
        figure.layout().xaxis(2).range(0, 2);
        figure.layout().xaxis(2).constrain("range");
        figure.layout().xaxis(2).matches("x");
        figure.layout().yaxis().title().text("y-axis");
        figure.layout().yaxis().type("log");
        figure.layout().yaxis(1).range(nullptr, "2025-01-01");
        figure.layout().yaxis(1).constrain("range");
        figure.layout().yaxis(2).title().text("y-axis2");
        figure.layout().yaxis(2).type("category");
        figure.layout().yaxis(2).range("A", "C");
        figure.layout().yaxis(2).constrain("domain");
        figure.layout().yaxis(2).matches("y");
        figure.layout().title().text("Test Title");
        figure.layout().grid().rows(2);
        figure.layout().grid().columns(3);
        figure.layout().grid().pattern("independent");
        figure.layout().grid().row_order("bottom to top");
        auto annotation = figure.layout().add_annotation();
        annotation.align("left");
        annotation.show_arrow(false);
        annotation.text("Test annotation1");
        annotation.x(0.5);   // NOLINT
        annotation.y(0.75);  // NOLINT
        annotation.x_ref("x");
        annotation.y_ref("y");
        annotation.x_shift(10.0);     // NOLINT
        annotation.y_shift(20.0);     // NOLINT
        annotation.text_angle(45.0);  // NOLINT
        annotation = figure.layout().add_annotation();
        annotation.align("right");
        annotation.show_arrow(true);
        annotation.text("Test annotation2");
        annotation.x(0.25);  // NOLINT
        annotation.y(0.5);   // NOLINT
        annotation.x_ref("x2 domain");
        annotation.y_ref("y2 domain");
        annotation.x_shift(30.0);     // NOLINT
        annotation.y_shift(40.0);     // NOLINT
        annotation.text_angle(90.0);  // NOLINT
        figure.layout().legend().title().text("Legend");
        figure.layout().legend().trace_group_gap(5);  // NOLINT
        figure.layout().box_mode("group");
        figure.layout().violin_mode("group");
        figure.layout().show_legend(true);

        const std::string json_string =
            figure.document().serialize_to_string(true);
        ApprovalTests::Approvals::verify(json_string,
            ApprovalTests::Options().fileOptions().withFileExtension(".json"));
    }
}
