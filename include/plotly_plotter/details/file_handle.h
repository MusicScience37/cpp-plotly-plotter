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
 * \brief Definition of file_handle class.
 */
#pragma once

#include <cstdio>
#include <string>
#include <string_view>
#include <utility>

namespace plotly_plotter::details {

/*!
 * \brief Class of handles of files.
 *
 * This class is for RAII of `std::FILE*`.
 */
class file_handle {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] file_path File path.
     * \param[in] mode Mode.
     */
    file_handle(const std::string& file_path, const char* mode)
        : file_(std::fopen(file_path.c_str(), mode)) {
        if (file_ == nullptr) {
            throw std::runtime_error("Failed to open file: " + file_path);
        }
    }

    file_handle(const file_handle&) = delete;
    file_handle& operator=(const file_handle&) = delete;

    /*!
     * \brief Move constructor.
     *
     * \param[in,out] other Object to move from.
     */
    file_handle(file_handle&& other) noexcept
        : file_(std::exchange(other.file_, nullptr)) {}

    /*!
     * \brief Move assignment operator.
     *
     * \param[in,out] other Object to move from.
     * \return This object.
     */
    file_handle& operator=(file_handle&& other) noexcept {
        if (this != &other) {
            close();
            file_ = std::exchange(other.file_, nullptr);
        }
        return *this;
    }

    /*!
     * \brief Destructor.
     */
    ~file_handle() { close(); }

    /*!
     * \brief Close the file.
     */
    void close() {
        if (file_ != nullptr) {
            (void)std::fclose(file_);
            file_ = nullptr;
        }
    }

    /*!
     * \brief Get the file pointer.
     *
     * \return File pointer.
     */
    [[nodiscard]] std::FILE* get() const noexcept { return file_; }

    /*!
     * \brief Write a string to the file.
     *
     * \param[in] string String to write.
     */
    void write(std::string_view string) {
        if (file_ == nullptr) {
            throw std::runtime_error("File is not opened.");
        }
        if (std::fwrite(string.data(), 1, string.size(), file_) !=
            string.size()) {
            throw std::runtime_error("Failed to write to file.");
        }
    }

private:
    //! File pointer.
    std::FILE* file_{nullptr};
};

}  // namespace plotly_plotter::details
