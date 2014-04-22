/*****************************************************************************
 * Licensed to Qualys, Inc. (QUALYS) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * QUALYS licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ****************************************************************************/

#ifndef _IB_PATH_H_
#define _IB_PATH_H_

/**
 * @file
 * @brief IronBee --- Utility Path Functions
 *
 * @author Nick LeRoy <nleroy@qualys.com>
 * @uathor Christopher Alfeld <calfeld@qualys.com>
 */

#include <ironbee/build.h>
#include <ironbee/mm.h>
#include <ironbee/types.h>

#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup IronBeeUtilPath Utility Path Functions
 * @ingroup IronBeeUtil
 *
 * Code to perform path operations
 *
 * @{
 */

/**
 * Create a directory path.
 *
 * @param path Path to create.
 * @param mode If a directory must be created, its mode will be @a mode.
 *
 * @returns
 * - IB_OK On success.
 * - IB_EALLOC If allocating an internal work buffer fails.
 * - IB_EINVAL If @a path is zero length.
 * - Other on API failures. Check @c errno.
 *
 * @internal
 * Implemented in: util/path.c
 * Tested in: tests/test_util_path.cpp
 */
ib_status_t DLL_PUBLIC ib_util_mkpath(
    const char   *path,
    mode_t        mode);

/**
 * Create a file path relative to a reference file.
 *
 * If @a file_path looks like an absolute path (it starts with a '/'),
 * a copy of @a file_path is returned.  If not, the directory portion
 * of @a ref_file is joined with @a file_path using ib_util_path_join,
 * and the resulting path is returned.
 *
 * @param[in] mm Memory Manager to use for allocations
 * @param[in] ref_file Reference file path
 * @param[in] file_path New file's path
 *
 * @return Pointer to new path, or NULL if unable to allocate memory
 *
 * @internal
 * Implemented in: util/path.c
 * Tested in: tests/test_util_path.cpp
 */
char DLL_PUBLIC *ib_util_relative_file(
    ib_mm_t       mm,
    const char   *ref_file,
    const char   *file_path);

/**
 * Join two path components (similar to os.path.join() in Python)
 *
 * @param[in] mm Memory Manager to use for allocations
 * @param[in] parent Parent portion of path
 * @param[in] file_path Child portion of path
 *
 * @return Pointer to new path, or NULL if unable to allocate memory
 *
 * @internal
 * Implemented in: util/path.c
 * Tested in: tests/test_util_path.cpp
 */
char DLL_PUBLIC *ib_util_path_join(
    ib_mm_t       mm,
    const char   *parent,
    const char   *file_path);

/**
 * Normalize a path (copy-on-write / ex version)
 *
 * @param[in] mm Memory Manager for allocations
 * @param[in] data_in Buffer to operate on
 * @param[in] dlen_in Length of @a data_in
 * @param[in] win Handle Windows style '\' as well as '/'
 * @param[out] data_out Output data
 * @param[out] dlen_out Length of @a data_out
 *
 * @returns Status code
 * - IB_OK: Success
 * - IB_EALLOC: Allocation error
 *
 * @internal
 * Implemented in: util/path.c
 * Tested in: tests/test_util_path.cpp
 */
ib_status_t DLL_PUBLIC ib_util_normalize_path(
    ib_mm_t         mm,
    const uint8_t  *data_in,
    size_t          dlen_in,
    bool            win,
    uint8_t       **data_out,
    size_t         *dlen_out);


/**
 * @} IronBeeUtilPath
 */

#ifdef __cplusplus
}
#endif

#endif /* _IB_PATH_H_ */
