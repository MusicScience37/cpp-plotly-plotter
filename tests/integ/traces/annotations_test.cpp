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
 * \brief Test of annotations.
 */
#include <string>
#include <string_view>
#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/figure.h"
#include "plotly_plotter/layout.h"
#include "plotly_plotter/traces/scatter.h"
#include "plotly_plotter/write_html.h"

TEST_CASE("annotations") {
    plotly_plotter::figure figure;

    SECTION("annotation to a point") {
        auto scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)

        auto annotation = figure.layout().add_annotation();
        annotation.x_ref("x");
        annotation.y_ref("y");
        annotation.x(2);
        annotation.y(5);  // NOLINT(*-magic-numbers)
        annotation.text("Annotation text");
        annotation.show_arrow(true);
        annotation.align("left");

        figure.layout().title().text("Annotation to a Point");

        const std::string file_path = "annotation_to_a_point.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("annotations to subplots") {
        auto scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)
        scatter.xaxis("x");

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{5, 6, 7});  // NOLINT(*-magic-numbers)
        scatter.xaxis("x2");

        scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{6, 7, 8});  // NOLINT(*-magic-numbers)
        scatter.xaxis("x3");

        figure.layout().grid().rows(1);
        figure.layout().grid().columns(3);

        auto annotation = figure.layout().add_annotation();
        annotation.x_ref("x domain");
        annotation.y_ref("y domain");
        annotation.x(0.0);       // NOLINT(*-magic-numbers)
        annotation.y(1.0);       // NOLINT(*-magic-numbers)
        annotation.x_shift(10);  // NOLINT(*-magic-numbers)
        annotation.y_shift(20);  // NOLINT(*-magic-numbers)
        annotation.show_arrow(false);
        annotation.align("left");
        annotation.text("Annotation text 1");

        annotation = figure.layout().add_annotation();
        annotation.x_ref("x2 domain");
        annotation.y_ref("y domain");
        annotation.x(0.5);       // NOLINT(*-magic-numbers)
        annotation.y(1.0);       // NOLINT(*-magic-numbers)
        annotation.x_shift(0);   // NOLINT(*-magic-numbers)
        annotation.y_shift(20);  // NOLINT(*-magic-numbers)
        annotation.show_arrow(false);
        annotation.align("center");
        annotation.text("Annotation text 2");

        annotation = figure.layout().add_annotation();
        annotation.x_ref("x3 domain");
        annotation.y_ref("y domain");
        annotation.x(1.0);        // NOLINT(*-magic-numbers)
        annotation.y(1.0);        // NOLINT(*-magic-numbers)
        annotation.x_shift(-10);  // NOLINT(*-magic-numbers)
        annotation.y_shift(20);   // NOLINT(*-magic-numbers)
        annotation.show_arrow(false);
        annotation.align("right");
        annotation.text("Annotation text 3");

        annotation = figure.layout().add_annotation();
        annotation.x_ref("x3 domain");
        annotation.y_ref("y domain");
        annotation.x(1.0);       // NOLINT(*-magic-numbers)
        annotation.y(0.5);       // NOLINT(*-magic-numbers)
        annotation.x_shift(20);  // NOLINT(*-magic-numbers)
        annotation.show_arrow(false);
        annotation.align("center");
        annotation.text_angle(90.0);  // NOLINT(*-magic-numbers)
        annotation.text("Annotation text 4");

        figure.layout().xaxis(1).title().text("x1");
        figure.layout().xaxis(2).title().text("x2");
        figure.layout().xaxis(3).title().text("x3");

        figure.layout().yaxis().title().text("y");

        figure.layout().title().text("Annotations to Subplots");

        const std::string file_path = "annotations_to_subplots.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }
}
