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

//! @file IReadOnlyDictionary.h

#ifndef CFLAT_CORE_COLLECTIONS_IREADONLYDICTIONARY_H
#define CFLAT_CORE_COLLECTIONS_IREADONLYDICTIONARY_H

#include "CFlat/Collections/IReadOnlyCollection.h"
#include "CFlat/Collections/KeyValuePair.h"

#include "CFlat/Language/Integer.h"

namespace CFlat
{
    template <typename TKey, typename TValue>
    class IReadOnlyDictionary : public virtual IReadOnlyCollection<KeyValuePair<TKey, TValue>> {
    public:
        inline virtual ~IReadOnlyDictionary() {}

        virtual TValue operator[](TKey key) const = 0;

        virtual unique_ptr<IReadOnlyCollection<TKey>> Keys() const = 0;

        virtual unique_ptr<IReadOnlyCollection<TValue>> Values() const = 0;

        virtual bool ContainsKey(TKey key) const = 0;

        virtual bool TryGetValue(TKey key, TValue &value) const = 0;
    };
}

#endif
