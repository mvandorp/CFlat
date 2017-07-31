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
 * @file Mock.When.h
 */

#ifndef CFLAT_TESTING_MOCK_WHEN_H
#define CFLAT_TESTING_MOCK_WHEN_H

#include "CFlat/Language/Macros.h"
#include "CFlat/Testing/Mock.h"

#define when(...) CFLAT_EXPAND(Mock_When(__VA_ARGS__))

#endif
