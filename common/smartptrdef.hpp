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
#include <memory>
#elif defined(BOOST_NAMESPACES)
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>
#include <boost/move/unique_ptr.hpp>
#endif

namespace ebooks
{
namespace common
{

#if defined(STD_NAMESPACES) || !defined(BOOST_NAMESPACES)

// from std namespace
using std::shared_ptr;
using std::weak_ptr;
using std::unique_ptr;

using std::enable_shared_from_this;
using std::make_shared;
using std::dynamic_pointer_cast;

#elif defined(BOOST_NAMESPACES)

using boost::shared_ptr;
using boost::weak_ptr;
using boost::movelib::unique_ptr;

using boost::enable_shared_from_this;
using boost::make_shared;
using boost::dynamic_pointer_cast;

#endif

}
}
