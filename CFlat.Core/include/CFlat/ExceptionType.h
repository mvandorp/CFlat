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

//! @file ExceptionType.h

#ifndef CFLAT_CORE_EXCEPTIONTYPE_H
#define CFLAT_CORE_EXCEPTIONTYPE_H

#include "CFlat/Language/Pointers.h"

#include "CFlat/String.h"

namespace CFlat {
    class Exception {
    private:
        String _message;
        shared_ptr<Exception> _innerException;

    public:
        static const String Name;

        Exception();
        Exception(const String &message);
        Exception(const String &message, shared_ptr<Exception> innerException);
        virtual ~Exception();

        shared_ptr<Exception> GetInnerException() const;

        virtual String GetName() const;

        virtual String GetMessage() const;
    };

    class SystemException : public Exception {
    public:
        static const String Name;

        SystemException();
        SystemException(const String &message);
        SystemException(const String &message, shared_ptr<Exception> innerException);

        String GetName() const override;
    };

    class ArgumentException : public SystemException {
    public:
        static const String Name;

        ArgumentException();
        ArgumentException(const String &message);
        ArgumentException(const String &message, shared_ptr<Exception> innerException);

        String GetName() const override;
    };

    class IOException : public SystemException {
    public:
        static const String Name;

        IOException();
        IOException(const String &message);
        IOException(const String &message, shared_ptr<Exception> innerException);

        String GetName() const override;
    };

    class ArithmeticException : public SystemException {
    public:
        static const String Name;

        ArithmeticException();
        ArithmeticException(const String &message);
        ArithmeticException(const String &message, shared_ptr<Exception> innerException);

        String GetName() const override;
    };

    class IndexOutOfRangeException : public SystemException {
    public:
        static const String Name;

        IndexOutOfRangeException();
        IndexOutOfRangeException(const String &message);
        IndexOutOfRangeException(const String &message, shared_ptr<Exception> innerException);

        String GetName() const override;
    };

    class NullReferenceException : public SystemException {
    public:
        static const String Name;

        NullReferenceException();
        NullReferenceException(const String &message);
        NullReferenceException(const String &message, shared_ptr<Exception> innerException);

        String GetName() const override;
    };

    class AccessViolationException : public SystemException {
    public:
        static const String Name;

        AccessViolationException();
        AccessViolationException(const String &message);
        AccessViolationException(const String &message, shared_ptr<Exception> innerException);

        String GetName() const override;
    };

    class InvalidOperationException : public SystemException {
    public:
        static const String Name;

        InvalidOperationException();
        InvalidOperationException(const String &message);
        InvalidOperationException(const String &message, shared_ptr<Exception> innerException);

        String GetName() const override;
    };

    class ArgumentNullException : public ArgumentException {
    public:
        static const String Name;

        ArgumentNullException();
        ArgumentNullException(const String &message);
        ArgumentNullException(const String &message, shared_ptr<Exception> innerException);

        String GetName() const override;
    };

    class ArgumentOutOfRangeException : public ArgumentException {
    public:
        static const String Name;

        ArgumentOutOfRangeException();
        ArgumentOutOfRangeException(const String &message);
        ArgumentOutOfRangeException(const String &message, shared_ptr<Exception> innerException);

        String GetName() const override;
    };

    class OutOfMemoryException : public SystemException {
    public:
        static const String Name;

        OutOfMemoryException();
        OutOfMemoryException(const String &message);
        OutOfMemoryException(const String &message, shared_ptr<Exception> innerException);

        String GetName() const override;
    };

    class FileNotFoundException : public IOException {
    public:
        static const String Name;

        FileNotFoundException();
        FileNotFoundException(const String &message);
        FileNotFoundException(const String &message, shared_ptr<Exception> innerException);

        String GetName() const override;
    };

    class FormatException : public SystemException {
    public:
        static const String Name;

        FormatException();
        FormatException(const String &message);
        FormatException(const String &message, shared_ptr<Exception> innerException);

        String GetName() const override;
    };

    class NotImplementedException : public SystemException {
    public:
        static const String Name;

        NotImplementedException();
        NotImplementedException(const String &message);
        NotImplementedException(const String &message, shared_ptr<Exception> innerException);

        String GetName() const override;
    };

    class NotSupportedException : public SystemException {
    public:
        static const String Name;

        NotSupportedException();
        NotSupportedException(const String &message);
        NotSupportedException(const String &message, shared_ptr<Exception> innerException);

        String GetName() const override;
    };

    class OverflowException : public ArithmeticException {
    public:
        static const String Name;

        OverflowException();
        OverflowException(const String &message);
        OverflowException(const String &message, shared_ptr<Exception> innerException);

        String GetName() const override;
    };

    class DivideByZeroException : public ArithmeticException {
    public:
        static const String Name;

        DivideByZeroException();
        DivideByZeroException(const String &message);
        DivideByZeroException(const String &message, shared_ptr<Exception> innerException);

        String GetName() const override;
    };
}

#endif
