
// Copyright (c) 2010-2017 niXman (i dot nixman dog gmail dot com). All
// rights reserved.
//
// This file is part of YAS(https://github.com/niXman/yas) project.
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

#ifndef _yas_test__boost_cont_list_hpp__included_
#define _yas_test__boost_cont_list_hpp__included_

/***************************************************************************/

template<typename archive_traits>
bool boost_cont_list_test(const char* archive_type) {
	boost::container::list<int> ilist1, ilist2;
	ilist1.push_back(2);
	ilist1.push_back(3);
	ilist1.push_back(6);
	ilist1.push_back(8);
	ilist1.push_back(11);
	ilist1.push_back(4);
	ilist1.push_back(54);

	typename archive_traits::oarchive oa1;
	archive_traits::ocreate(oa1, archive_type);
	oa1 & ilist1;

	typename archive_traits::iarchive ia1;
	archive_traits::icreate(ia1, oa1, archive_type);
	ia1 & ilist2;

	if ( ilist1 != ilist2 ) {
		std::cout << "BOOST::CONTAINER::LIST deserialization error! [1]" << std::endl;
		return false;
	}

	boost::container::list<boost::container::string> slist1, slist2;
	slist1.push_back("23");
	slist1.push_back("54");
	slist1.push_back("91");
	slist1.push_back("246");
	slist1.push_back("976");

	typename archive_traits::oarchive oa2;
	archive_traits::ocreate(oa2, archive_type);
	oa2 & slist1;

	typename archive_traits::iarchive ia2;
	archive_traits::icreate(ia2, oa2, archive_type);
	ia2 & slist2;

	if ( slist1 != slist2 ) {
		std::cout << "BOOST::CONTAINER::LIST deserialization error! [2]" << std::endl;
		return false;
	}

	return true;
}

/***************************************************************************/

#endif // _yas_test__boost_cont_list_hpp__included_
