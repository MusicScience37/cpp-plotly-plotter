#!/bin/bash

# usage: convert_sbom.sh <build_dir>

BUILD_DIR=$1

find $BUILD_DIR/vcpkg_installed -name "*.spdx.json" | while read file; do
    out_file="${file%.spdx.json}.cyclonedx.json"
    cyclonedx convert --input-file "$file" --input-format spdxjson \
        --output-format json --output-file "$out_file"
done
