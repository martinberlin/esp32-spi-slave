/**
 * Simple.cpp
 *
 *  Created on: Sep 27, 2018
 *       Email: ipas.th@gmail.com
 *      Author: ipas
 */

#include "SimpleArray.h"

/**
 * Constructors / Destructor
 */
template <class T, class SZ>
SimpleArray<T, SZ>::SimpleArray(SZ initSize) {
    dataLength = 0;
    bufferSize   = initSize;
    buffer       = new T[bufferSize];
}

template <class T, class SZ>
SimpleArray<T, SZ>::~SimpleArray() {
    delete[] buffer;
}

/**
 * Accessing / Properties
 */
template <class T, class SZ>
SZ SimpleArray<T, SZ>::length(void) {
    return dataLength;
}

template <class T, class SZ>
SZ SimpleArray<T, SZ>::capacity() {
    return bufferSize;
}

template <class T, class SZ>
T & SimpleArray<T, SZ>::operator [] (SZ index) {
    return buffer[index];
}

template <class T, class SZ>
T * SimpleArray<T, SZ>::getBuffer(void) {
    return buffer;
}

template <class T, class SZ>
SZ SimpleArray<T, SZ>::getBytes(void * buf, SZ size) {
    SZ i;
    for (i = 0; i < dataLength && i < size; i++) {
        ((T *)buf)[i] = buffer[i];
    }
    return i;  // actual read bytes
}

/**
 * Comparators
 */
template <class T, class SZ>
int SimpleArray<T, SZ>::compare(SimpleArray<T, SZ> & array) {
    SZ i;
    for (i = 0; i < dataLength && i < array.length(); i++) {
        if (buffer[i] != array[i])
            break;
    }
    if (dataLength >= array.length())
        return dataLength - i;  // How many items left, NOT be compared nor equal
    else
        return array.length() - i;
}

template <class T, class SZ>
bool SimpleArray<T, SZ>::operator == (SimpleArray<T, SZ> & array) {
    return ((dataLength == array.length()) && (compare(array) == 0));
}

template <class T, class SZ>
bool SimpleArray<T, SZ>::operator != (SimpleArray<T, SZ> & array) {
    return !(*this == array);
}

/**
 * Manipulators
 */
template <class T, class SZ>
SZ SimpleArray<T, SZ>::append(T item) {
    return append(&item, 1);
}

template <class T, class SZ>
SZ SimpleArray<T, SZ>::append(SimpleArray<T, SZ> & array) {
    return append(array.getBuffer(), array.length());
}

template <class T, class SZ>
SZ SimpleArray<T, SZ>::append(void * buf, SZ count) {
    SZ i;
    for (i = 0; i < count && dataLength < bufferSize; i++) {
        buffer[dataLength++] = ((T *)buf)[i];
    }
    return i;
}

template <class T, class SZ>
void SimpleArray<T, SZ>::operator += (T item) {
    append(item);
}

template <class T, class SZ>
void SimpleArray<T, SZ>::operator += (SimpleArray<T, SZ> & array) {
    append(array);
}

template <class T, class SZ>
void SimpleArray<T, SZ>::operator = (T item) {
    clear();
    append(item);
}

template <class T, class SZ>
void SimpleArray<T, SZ>::operator = (SimpleArray<T, SZ> & array) {
    clear();
    append(array);
}

template <class T, class SZ>
SZ SimpleArray<T, SZ>::insert(SZ index, T item) {
    return insert(index, &item, 1);
}

template <class T, class SZ>
SZ SimpleArray<T, SZ>::insert(SZ index, SimpleArray<T, SZ> & array) {
    return insert(index, array.getBuffer(), array.length());
}

template <class T, class SZ>
SZ SimpleArray<T, SZ>::insert(SZ index, void * buf, SZ count) {
    SZ i, j;

    if (count > bufferSize - dataLength)
        count = bufferSize - dataLength;
    if (count == 0)
        return 0;

    // Right alignment
    i = dataLength - 1;
    j = dataLength + count - 1;
    if (i < index)
        return 0;
    while (i >= index) {
        buffer[j--] = buffer[i--];
    }

    // Insert
    i = 0;
    j = index;
    while (i < count) {
        buffer[j++] = ((T *)buf)[i++];
    }
    dataLength += count;

    return count;
}

template <class T, class SZ>
SZ SimpleArray<T, SZ>::remove(SZ index, SZ count) {
    if (index >= dataLength)
        return 0;
    if (index+count >= dataLength)
        count = dataLength - index;

    T * tmp = new T[bufferSize];
    SZ i, j = 0;
    for (i = 0; i < index; i++, j++) {
        tmp[j] = buffer[i];
    }
    for (i = index+count; i < dataLength; i++, j++) {
        tmp[j] = buffer[i];
    }
    delete[] buffer;
    buffer = tmp;
    dataLength = j;
    return count;  // Actual removed
}

template <class T, class SZ>
SZ SimpleArray<T, SZ>::trim(SZ index) {
    SZ count = dataLength - index;
    return remove(index, count);
}

template <class T, class SZ>
void SimpleArray<T, SZ>::clear() {
    dataLength = 0;
}
