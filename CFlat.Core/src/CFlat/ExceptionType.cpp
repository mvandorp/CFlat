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

#include "CFlat/ExceptionType.h"

#include "CFlat.h"
#include "CFlat/String.h"

using namespace CFlat;


Exception::Exception() :
    _message(""),
    _innerException(nullptr)
{
}

Exception::Exception(const String &message) :
    _message(message),
    _innerException(nullptr)
{
}

Exception::Exception(const String &message, shared_ptr<Exception> innerException) :
    _message(message),
    _innerException(innerException)
{
}

Exception::~Exception()
{
}

shared_ptr<Exception> Exception::GetInnerException() const
{
    return _innerException;
}

String Exception::GetName() const
{
    return String::Wrap("Exception");
}

String Exception::GetMessage() const
{
    return _message;
}

SystemException::SystemException() : SystemException("System error.", nullptr) {}
SystemException::SystemException(const String &message) : SystemException(message, nullptr) {}
SystemException::SystemException(const String &message, shared_ptr<Exception> innerException) : Exception(message, innerException) {}
String SystemException::GetName() const
{
    return String::Wrap("SystemException");
}

ArgumentException::ArgumentException() : ArgumentException("Value does not fall within the expected range.", nullptr) {}
ArgumentException::ArgumentException(const String &message) : ArgumentException(message, nullptr) {}
ArgumentException::ArgumentException(const String &message, shared_ptr<Exception> innerException) : SystemException(message, innerException) {}
String ArgumentException::GetName() const
{
    return String::Wrap("ArgumentException");
}

IOException::IOException() : IOException("I/O error occurred.", nullptr) {}
IOException::IOException(const String &message) : IOException(message, nullptr) {}
IOException::IOException(const String &message, shared_ptr<Exception> innerException) : SystemException(message, innerException) {}
String IOException::GetName() const
{
    return String::Wrap("IOException");
}

ArithmeticException::ArithmeticException() : ArithmeticException("Arithmetic error.", nullptr) {}
ArithmeticException::ArithmeticException(const String &message) : ArithmeticException(message, nullptr) {}
ArithmeticException::ArithmeticException(const String &message, shared_ptr<Exception> innerException) : SystemException(message, innerException) {}
String ArithmeticException::GetName() const
{
    return String::Wrap("ArithmeticException");
}

IndexOutOfRangeException::IndexOutOfRangeException() : IndexOutOfRangeException("Index was outside the bounds of the array.", nullptr) {}
IndexOutOfRangeException::IndexOutOfRangeException(const String &message) : IndexOutOfRangeException(message, nullptr) {}
IndexOutOfRangeException::IndexOutOfRangeException(const String &message, shared_ptr<Exception> innerException) : SystemException(message, innerException) {}
String IndexOutOfRangeException::GetName() const
{
    return String::Wrap("IndexOutOfRangeException");
}

NullReferenceException::NullReferenceException() : NullReferenceException("Object reference not set to an instance of an object.", nullptr) {}
NullReferenceException::NullReferenceException(const String &message) : NullReferenceException(message, nullptr) {}
NullReferenceException::NullReferenceException(const String &message, shared_ptr<Exception> innerException) : SystemException(message, innerException) {}
String NullReferenceException::GetName() const
{
    return String::Wrap("NullReferenceException");
}

AccessViolationException::AccessViolationException() : AccessViolationException("Attempted to read or write protected memory. This is often an indication that other memory is corrupt.", nullptr) {}
AccessViolationException::AccessViolationException(const String &message) : AccessViolationException(message, nullptr) {}
AccessViolationException::AccessViolationException(const String &message, shared_ptr<Exception> innerException) : SystemException(message, innerException) {}
String AccessViolationException::GetName() const
{
    return String::Wrap("AccessViolationException");
}

InvalidOperationException::InvalidOperationException() : InvalidOperationException("Operation is not valid due to the current state of the object.", nullptr) {}
InvalidOperationException::InvalidOperationException(const String &message) : InvalidOperationException(message, nullptr) {}
InvalidOperationException::InvalidOperationException(const String &message, shared_ptr<Exception> innerException) : SystemException(message, innerException) {}
String InvalidOperationException::GetName() const
{
    return String::Wrap("InvalidOperationException");
}

ArgumentNullException::ArgumentNullException() : ArgumentNullException("Value cannot be null.", nullptr) {}
ArgumentNullException::ArgumentNullException(const String &message) : ArgumentNullException(message, nullptr) {}
ArgumentNullException::ArgumentNullException(const String &message, shared_ptr<Exception> innerException) : ArgumentException(message, innerException) {}
String ArgumentNullException::GetName() const
{
    return String::Wrap("ArgumentNullException");
}

ArgumentOutOfRangeException::ArgumentOutOfRangeException() : ArgumentOutOfRangeException("Specified argument was out of the range of valid values.", nullptr) {}
ArgumentOutOfRangeException::ArgumentOutOfRangeException(const String &message) : ArgumentOutOfRangeException(message, nullptr) {}
ArgumentOutOfRangeException::ArgumentOutOfRangeException(const String &message, shared_ptr<Exception> innerException) : ArgumentException(message, innerException) {}
String ArgumentOutOfRangeException::GetName() const
{
    return String::Wrap("ArgumentOutOfRangeException");
}

OutOfMemoryException::OutOfMemoryException() : OutOfMemoryException("Insufficient memory to continue the execution of the program.", nullptr) {}
OutOfMemoryException::OutOfMemoryException(const String &message) : OutOfMemoryException(message, nullptr) {}
OutOfMemoryException::OutOfMemoryException(const String &message, shared_ptr<Exception> innerException): SystemException(message, innerException) {}
String OutOfMemoryException::GetName() const
{
    return String::Wrap("OutOfMemoryException");
}

FileNotFoundException::FileNotFoundException() : FileNotFoundException("Default message", nullptr) {}
FileNotFoundException::FileNotFoundException(const String &message) : FileNotFoundException(message, nullptr) {}
FileNotFoundException::FileNotFoundException(const String &message, shared_ptr<Exception> innerException) : IOException(message, innerException) {}
String FileNotFoundException::GetName() const
{
    return String::Wrap("FileNotFoundException");
}

FormatException::FormatException() : FormatException("Default message", nullptr) {}
FormatException::FormatException(const String &message) : FormatException(message, nullptr) {}
FormatException::FormatException(const String &message, shared_ptr<Exception> innerException) : SystemException(message, innerException) {}
String FormatException::GetName() const
{
    return String::Wrap("FormatException");
}

NotImplementedException::NotImplementedException() : NotImplementedException("Default message", nullptr) {}
NotImplementedException::NotImplementedException(const String &message) : NotImplementedException(message, nullptr) {}
NotImplementedException::NotImplementedException(const String &message, shared_ptr<Exception> innerException) : SystemException(message, innerException) {}
String NotImplementedException::GetName() const
{
    return String::Wrap("NotImplementedException");
}

NotSupportedException::NotSupportedException() : NotSupportedException("Default message", nullptr) {}
NotSupportedException::NotSupportedException(const String &message) : NotSupportedException(message, nullptr) {}
NotSupportedException::NotSupportedException(const String &message, shared_ptr<Exception> innerException) : SystemException(message, innerException) {}
String NotSupportedException::GetName() const
{
    return String::Wrap("NotSupportedException");
}

OverflowException::OverflowException() : OverflowException("Default message", nullptr) {}
OverflowException::OverflowException(const String &message) : OverflowException(message, nullptr) {}
OverflowException::OverflowException(const String &message, shared_ptr<Exception> innerException) : ArithmeticException(message, innerException) {}
String OverflowException::GetName() const
{
    return String::Wrap("OverflowException");
}

DivideByZeroException::DivideByZeroException() : DivideByZeroException("Default message", nullptr) {}
DivideByZeroException::DivideByZeroException(const String &message) : DivideByZeroException(message, nullptr) {}
DivideByZeroException::DivideByZeroException(const String &message, shared_ptr<Exception> innerException) : ArithmeticException(message, innerException) {}
String DivideByZeroException::GetName() const
{
    return String::Wrap("DivideByZeroException");
}
