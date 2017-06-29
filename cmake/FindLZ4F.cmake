

# Copyright 2017 Niclas Rosenvik 
#
# Permission to use, copy, modify, and/or distribute this file for
# any purpose with or without fee is hereby granted, provided that the
# above copyright notice and this permission notice appear in all
# copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL 
# WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED 
# WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE 
# AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL 
# DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR 
# PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER 
# TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR 
# PERFORMANCE OF THIS SOFTWARE.
# 
# 

include(FindPackageHandleStandardArgs)

find_path(LZ4F_INCLUDE_DIR NAMES lz4frame.h)
find_library(LZ4_LIB NAMES lz4 liblz4)

if (LZ4F_INCLUDE_DIR)
    file(READ /usr/pkg/include/lz4frame.h LZ4FRAME_H_CONTENTS)
    string(REGEX MATCH "#define LZ4F_VERSION [0-9]+" LZ4F_VERSION "${LZ4FRAME_H_CONTENTS}")
    string(REGEX REPLACE "#define LZ4F_VERSION ([0-9]+)" "\\1" LZ4F_VERSION "${LZ4F_VERSION}")
endif (LZ4F_INCLUDE_DIR)

find_package_handle_standard_args(LZ4F REQUIRED_VARS LZ4F_INCLUDE_DIR LZ4_LIB LZ4F_VERSION VERSION_VAR LZ4F_VERSION)

mark_as_advanced(LZ4F_INCLUDE_DIR LZ4_LIB LZ4F_VERSION)
