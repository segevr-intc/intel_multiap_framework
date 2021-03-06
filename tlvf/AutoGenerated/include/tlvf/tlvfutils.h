///////////////////////////////////////
// AUTO GENERATED FILE - DO NOT EDIT //
///////////////////////////////////////

/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * Copyright (c) 2016-2019 Intel Corporation
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#ifndef _TLVF_UTILS_H_
#define _TLVF_UTILS_H_

#include <cstddef>
#include <algorithm>

inline void tlvf_copy_string(char *dst, const char *src, size_t dst_len)
{
    const char* src_end = std::find((char*)src, ((char*)src) + dst_len, '\0');
    std::copy(src, src_end, dst);
    std::ptrdiff_t src_size = src_end - src;
    std::ptrdiff_t dst_size = dst_len;
    if(src_size < dst_size ){
        dst[src_size] = 0;
    }else{
        dst[dst_size - 1] = 0;
    }
}


#endif
