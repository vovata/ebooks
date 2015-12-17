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

#include "common/typetraitdef.hpp"

namespace ebooks
{
namespace util
{

/**
 * @brief Helper to access the value of the underlying type of an enum
 */
template <typename T>
typename common::enable_if<common::is_enum<T>::value, typename common::underlying_type<T>::type>::type
integral(T value)
{
    return static_cast<typename common::underlying_type<T>::type>(value);
}

template <typename T>
typename common::enable_if<common::is_enum<T>::value, T>::type
arrange(typename common::underlying_type<T>::type value)
{
    return static_cast<T>(value);
}

template <typename T>
static inline typename common::enable_if<common::is_enum<T>::value, T>::type
operator |(T a, T b)
{
    return arrange(integral(a) | integral(b));
}

template <typename T>
static inline typename common::enable_if<common::is_enum<T>::value, T>::type
operator &(T a, T b)
{
    return arrange<T>(integral(a) & integral(b));
}

}
}
