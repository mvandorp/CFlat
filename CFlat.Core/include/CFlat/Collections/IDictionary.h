/*
* Copyright (C) 2015 Martijn van Dorp
*
* This file is part of CFlat.Core.
*
* CFlat.Core is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* CFlat.Core is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//! @file IDictionary.h

#ifndef CFLAT_CORE_COLLECTIONS_IDICTIONARY_H
#define CFLAT_CORE_COLLECTIONS_IDICTIONARY_H

#include "CFlat/Collections/ICollection.h"
#include "CFlat/Collections/IReadOnlyDictionary.h"
#include "CFlat/Collections/KeyValuePair.h"

#include "CFlat/Language/Integer.h"

namespace CFlat
{
    template <typename TKey, typename TValue>
    class IDictionary : public virtual IReadOnlyDictionary<TKey, TValue>, public virtual ICollection<KeyValuePair<TKey, TValue>> {
    public:
        inline virtual ~IDictionary() {}

        virtual void Add(TKey key, TValue value) = 0;

        virtual bool Remove(TKey key) = 0;
    };
}

#endif
