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
 * \brief Test of config class.
 */
#include "plotly_plotter/config.h"

#include <string>

#include <ApprovalTests.hpp>
#include <catch2/catch_test_macros.hpp>

#include "plotly_plotter/figure.h"
#include "plotly_plotter/json_document.h"

TEST_CASE("plotly_plotter::config") {
    plotly_plotter::figure figure;

    SECTION("set parameters") {
        figure.config().scroll_zoom(true);
        figure.config().editable(true);
        figure.config().static_plot(false);
        figure.config().display_mode_bar(true);
        figure.config().responsive(true);

        const std::string json_string =
            figure.document().serialize_to_string(true);
        ApprovalTests::Approvals::verify(json_string,
            ApprovalTests::Options().fileOptions().withFileExtension(".json"));
    }
}
