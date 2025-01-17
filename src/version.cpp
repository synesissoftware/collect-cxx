/* /////////////////////////////////////////////////////////////////////////
 * File:    src/api.c
 *
 * Purpose: Primary implementation file for collect-cxx core library.
 *
 * Created: 16th January 2025
 * Updated: 17th January 2025
 *
 * Home:    https://github.com/synesissoftware/collect-cxx/
 *
 * Copyright (c) 2025, Matthew Wilson and Synesis Information Systems
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer;
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution;
 * - Neither the name of the copyright holder nor the names of its
 *   ontributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * feature control
 */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <collect-cxx/common.hpp>


/* /////////////////////////////////////////////////////////////////////////
 * macros
 */


/* /////////////////////////////////////////////////////////////////////////
 * types
 */


/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */


/* /////////////////////////////////////////////////////////////////////////
 * global state
 */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

namespace collect_cxx {


/* /////////////////////////////////////////////////////////////////////////
 * API functions
 */

/** The
 *
 */
std::uint32_t
api_version()
{
    return COLLECT_CXX_VER;
}


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

} /* namespace collect_cxx */


/* ///////////////////////////// end of file //////////////////////////// */

