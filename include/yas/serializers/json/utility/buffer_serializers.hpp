
// Copyright (c) 2010-2014 niXman (i dot nixman dog gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//
//
// Boost Software License - Version 1.0 - August 17th, 2003
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef _yas__json__buffer_serializer_hpp
#define _yas__json__buffer_serializer_hpp

#include <yas/buffers.hpp>
#include <yas/detail/type_traits/properties.hpp>
#include <yas/detail/type_traits/selector.hpp>

namespace yas {
namespace detail {

/***************************************************************************/

template<>
struct serializer<
	type_prop::not_a_pod,
	ser_method::use_internal_serializer,
	archive_type::json,
	direction::out,
	intrusive_buffer
> {
	template<typename Archive>
	static Archive& apply(Archive& ar, const intrusive_buffer& buf) {
		ar & buf.size;
		ar.write(buf.data, buf.size);
		ar & ' ';
	}
};

/***************************************************************************/

template<>
struct serializer<
	type_prop::not_a_pod,
	ser_method::use_internal_serializer,
	archive_type::json,
	direction::out,
	shared_buffer
> {
	template<typename Archive>
	static Archive& apply(Archive& ar, const shared_buffer& buf) {
		ar & buf.size;
		ar.write(buf.data.get(), buf.size);
		ar & ' ';
	}
};

template<>
struct serializer<
	type_prop::not_a_pod,
	ser_method::use_internal_serializer,
	archive_type::json,
	direction::in,
	shared_buffer
> {
	template<typename Archive>
	static Archive& apply(Archive& ar, shared_buffer& buf) {
		std::uint32_t size = 0;
		ar & size;
		buf.data.reset(new char[size+1], &shared_buffer::deleter);
		assert(ar.read(buf.data.get(), size) == size);
		ar.snextc();
		buf.size = size;
		buf.data.get()[size] = 0;
	}
};

/***************************************************************************/

} // namespace detail
} // namespace yas

#endif // _yas__json__buffer_serializer_hpp
