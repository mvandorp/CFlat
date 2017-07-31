/*
 * Copyright (C) 2017 Martijn van Dorp
 *
 * This file is part of CFlat.Testing.Tests.
 *
 * CFlat.Testing.Tests is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CFlat.Testing.Tests is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file Mock.Verify.h
 */

#ifndef CFLAT_TESTING_MOCK_MATCHERS_H
#define CFLAT_TESTING_MOCK_MATCHERS_H

#include "CFlat/Testing/Mock.h"

#define any(type)               Mock_Match_Any(type)
#define anyFloat()              Mock_Match_AnyFloat()
#define anyInt()                Mock_Match_AnyInt()
#define anyPointer()            Mock_Match_AnyPointer()
#define anyCString()            Mock_Match_AnyCString()
#define anyString()             Mock_Match_AnyString()

#define eq(value)               Mock_Match_Equal(value)
#define eqCString(value)        Mock_Match_EqualCString(value)
#define eqString(value)         Mock_Match_EqualString(value)
#define neq(value)              Mock_Match_NotEqual(value)
#define neqCString(value)       Mock_Match_NotEqualCString(value)
#define neqString(value)        Mock_Match_NotEqualString(value)
#define geq(value)              Mock_Match_GreaterOrEqual(value)
#define gt(value)               Mock_Match_GreaterThan(value)
#define leq(value)              Mock_Match_LessOrEqual(value)
#define lt(value)               Mock_Match_LessThan(value)
#define notNull()               Mock_Match_NotNull()
#define match(type, matcher)    Mock_Match_Custom(type, matcher)

#endif
