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
 * \brief Test of animations.
 */
#include <cstddef>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/figure.h"
#include "plotly_plotter/json_document.h"
#include "plotly_plotter/json_value.h"
#include "plotly_plotter/layout.h"
#include "plotly_plotter/traces/scatter.h"
#include "plotly_plotter/write_html.h"

TEST_CASE("animation") {
    plotly_plotter::figure figure;

    SECTION("animation using buttons") {
        auto scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)
        scatter.mode("lines+markers");
        scatter.name("scatter");

        auto frame = figure.add_frame();
        frame.name("frame1");
        scatter = frame.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)

        frame = figure.add_frame();
        frame.name("frame2");
        scatter = frame.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{5, 6, 7});  // NOLINT(*-magic-numbers)

        frame = figure.add_frame();
        frame.name("frame3");
        scatter = frame.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{6, 7, 8});  // NOLINT(*-magic-numbers)

        // NOLINTNEXTLINE(*-magic-numbers)
        figure.layout().yaxis().range(4, 8);

        auto menu = figure.layout().add_menu();
        auto button = menu.add_button();
        button.label(1);
        button.method("animate");
        button.args(std::vector<std::vector<std::string>>{
            std::vector<std::string>{"frame1"}});

        button = menu.add_button();
        button.label(2);
        button.method("animate");
        button.args(std::vector<std::vector<std::string>>{
            std::vector<std::string>{"frame2"}});

        button = menu.add_button();
        button.label(3);
        button.method("animate");
        button.args(std::vector<std::vector<std::string>>{
            std::vector<std::string>{"frame3"}});

        figure.title("Animation Using Buttons");

        const std::string file_path = "animation_using_buttons.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }

    SECTION("animation using a slider") {
        auto scatter = figure.add_scatter();
        scatter.x(std::vector{1, 2, 3});
        scatter.y(std::vector{4, 5, 6});  // NOLINT(*-magic-numbers)
        scatter.mode("lines+markers");
        scatter.name("scatter");

        constexpr std::size_t num_frames = 20;
        for (std::size_t i = 0; i < num_frames; ++i) {
            auto frame = figure.add_frame();
            frame.name("frame" + std::to_string(i));
            scatter = frame.add_scatter();
            scatter.x(std::vector{1, 2, 3});
            scatter.y(
                std::vector{4 + i, 5 + i, 6 + i});  // NOLINT(*-magic-numbers)
        }

        // NOLINTNEXTLINE(*-magic-numbers)
        figure.layout().yaxis().range(3, 6 + num_frames);

        auto slider = figure.layout().add_slider();
        slider.current_value().visible(true);
        slider.current_value().prefix("Frame: ");
        for (std::size_t i = 0; i < num_frames; ++i) {
            auto step = slider.add_step();
            step.label(std::to_string(i));
            step.method("animate");
            step.args(std::vector<std::vector<std::string>>{
                std::vector<std::string>{"frame" + std::to_string(i)}});
        }
        slider.pad().l(120.0);  // NOLINT

        auto menu = figure.layout().add_menu();
        menu.type("buttons");
        menu.x_anchor("left");
        menu.y_anchor("top");
        menu.x(0.0);
        menu.y(0.0);
        menu.direction("left");
        menu.pad().t(40.0);  // NOLINT
        auto button = menu.add_button();
        button.label("\u25B6");
        button.method("animate");
        plotly_plotter::json_document animation_options;
        animation_options.root()["mode"] = "immediate";
        animation_options.root()["fromcurrent"] = true;
        animation_options.root()["frame"]["redraw"] = false;
        button.args(std::make_tuple(nullptr, animation_options.root()));
        button = menu.add_button();
        button.label("\u25FC");
        button.method("animate");
        animation_options = plotly_plotter::json_document();
        animation_options.root()["mode"] = "immediate";
        animation_options.root()["frame"]["redraw"] = false;
        button.args(
            std::make_tuple(std::vector{nullptr}, animation_options.root()));

        figure.title("Animation Using a Slider");

        const std::string file_path = "animation_using_a_slider.html";
        plotly_plotter::write_html(file_path, figure);

        ApprovalTests::Approvals::verify(
            ApprovalTests::FileUtils::readFileThrowIfMissing(file_path),
            ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    }
}
