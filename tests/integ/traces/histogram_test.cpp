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
 * \brief Test of histograms.
 */
#include <random>
#include <string>
#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/figure.h"
#include "plotly_plotter/utils/calculate_histogram_bin_width.h"
#include "plotly_plotter/write_html.h"

TEST_CASE("histogram") {
    plotly_plotter::figure figure;

    SECTION("simple histogram") {
        auto histogram = figure.add_histogram();
        // NOLINTNEXTLINE(*-magic-numbers)
        histogram.x(std::vector<double>{1, 3, 4, 5, 5, 6, 7, 7, 8, 10});

        const std::string file_path = "histogram_simple.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("change color") {
        auto histogram = figure.add_histogram();
        // NOLINTNEXTLINE(*-magic-numbers)
        histogram.x(std::vector<double>{1, 3, 4, 5, 5, 6, 7, 7, 8, 10});
        histogram.marker().color("red");

        const std::string file_path = "histogram_change_color.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("multiple histograms") {
        auto histogram = figure.add_histogram();
        // NOLINTNEXTLINE(*-magic-numbers)
        histogram.x(std::vector<double>{1, 3, 4, 5, 5, 6, 7, 7, 8, 10});
        // NOLINTNEXTLINE(*-magic-numbers)
        histogram.opacity(0.5);
        histogram.name("Histogram 1");

        histogram = figure.add_histogram();
        // NOLINTNEXTLINE(*-magic-numbers)
        histogram.x(std::vector<double>{3, 4, 5, 6, 6, 6, 7, 8});
        // NOLINTNEXTLINE(*-magic-numbers)
        histogram.opacity(0.5);
        histogram.name("Histogram 2");

        SECTION("overlay") {
            figure.layout().bar_mode("overlay");

            const std::string file_path = "histogram_multiple_overlay.html";
            plotly_plotter::write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }

        SECTION("stack") {
            figure.layout().bar_mode("stack");

            const std::string file_path = "histogram_multiple_stack.html";
            plotly_plotter::write_html(file_path, figure);

            ApprovalTests::Approvals::verify(
                ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
                ApprovalTests::Options().fileOptions().withFileExtension(
                    ".html"));
        }
    }

    SECTION("set bin width") {
        const auto input = std::vector<double>{1, 3, 4, 5, 5, 6, 7, 7, 8, 10};

        auto histogram = figure.add_histogram();
        // NOLINTNEXTLINE(*-magic-numbers)
        histogram.x(input);

        histogram.x_bins().size(1);

        const std::string file_path = "histogram_set_bin_width.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("create vertical histogram") {
        const auto input = std::vector<double>{1, 3, 4, 5, 5, 6, 7, 7, 8, 10};

        auto histogram = figure.add_histogram();
        // NOLINTNEXTLINE(*-magic-numbers)
        histogram.y(input);

        histogram.y_bins().size(1);

        const std::string file_path = "histogram_create_vertical.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("calculate bin width") {
        constexpr std::size_t num_values = 1000;
        std::mt19937 engine;  // NOLINT: for reproducibility.
        std::normal_distribution<> dist1(2.0, 1.0);  // NOLINT
        std::normal_distribution<> dist2(8.0, 0.5);  // NOLINT
        std::vector<double> values;
        values.reserve(num_values);
        for (std::size_t i = 0; i < num_values / 2; ++i) {
            values.push_back(dist1(engine));
        }
        for (std::size_t i = 0; i < num_values / 2; ++i) {
            values.push_back(dist2(engine));
        }
        constexpr double min_value = -2.0;
        constexpr double max_value = 12.0;
        for (double& value : values) {
            value = std::min(std::max(value, min_value), max_value);
        }

        auto histogram = figure.add_histogram();
        histogram.x(values);

        SECTION("Freedman-Diaconis rule") {
            histogram.x_bins().size(
                plotly_plotter::utils::calculate_histogram_bin_width(values,
                    plotly_plotter::utils::histogram_bin_width_method::
                        freedman_diaconis));

            const std::string file_path =
                "histogram_bin_width_freedman_diaconis.html";
            plotly_plotter::write_html(file_path, figure);

            // Omit verification due to differences among platforms.
        }
    }

    SECTION("use a template") {
        auto histogram = figure.add_histogram();
        // NOLINTNEXTLINE(*-magic-numbers)
        histogram.x(std::vector<double>{1, 3, 4, 5, 5, 6, 7, 7, 8, 10});
        histogram.name("Histogram 1");

        histogram = figure.add_histogram();
        // NOLINTNEXTLINE(*-magic-numbers)
        histogram.x(std::vector<double>{3, 4, 5, 6, 6, 6, 7, 8});
        histogram.name("Histogram 2");

        // NOLINTNEXTLINE(*-magic-numbers)
        figure.add_histogram_template().opacity(0.5);

        figure.layout().bar_mode("overlay");

        const std::string file_path = "histogram_use_template.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }
}
