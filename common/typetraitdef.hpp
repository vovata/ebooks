/*
 * Copyright (c) 2013-2014 vovata@gmail.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#if defined(STD_NAMESPACES) || !defined(BOOST_NAMESPACES)
#include <type_traits>
#elif defined(BOOST_NAMESPACES)
#include <boost/type_traits.hpp>
#include <boost/core/underlying_type.hpp>
#endif

namespace ebooks
{
namespace common
{

#if defined(STD_NAMESPACES) || !defined(BOOST_NAMESPACES)
// from std namespace
using std::underlying_type;
using std::enable_if;
using std::is_enum;

#elif defined(BOOST_NAMESPACES)
using boost::underlying_type;
template< bool B, class T = void >
using enable_if = typename boost::enable_if_c<B,T>;
using boost::is_enum;

#endif

}
}
