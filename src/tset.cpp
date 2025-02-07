// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField)
{
    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf)
{
    MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if ((Elem < 0) || (Elem > MaxPower)) {
        throw out_of_range("Invalid index");
    }

    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if ((Elem < 0) || (Elem > MaxPower)) {
        throw out_of_range("Invalid index");
    }

    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if ((Elem < 0) || (Elem > MaxPower)) {
        throw out_of_range("Invalid index");
    }

    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
    if (*this != s) {
        MaxPower = s.MaxPower;
        BitField = s.BitField;
    }

    return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
    if (s.MaxPower == MaxPower && BitField == s.BitField ) {
        return 1;
    }
    else
    {
        return 0;
    }
}

int TSet::operator!=(const TSet& s) const // сравнение
{
    if (s.MaxPower != MaxPower || BitField != s.BitField) {
        return 1;
    }
    else {
        return 0;
    }
}

TSet TSet::operator+(const TSet& s) // объединение
{
    MaxPower = max(MaxPower, s.MaxPower);
    BitField = BitField | s.BitField;
    return (*this);

}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if ((Elem < 0) || (Elem >= MaxPower)) {
        throw out_of_range("Invalid index");
    }

    this->InsElem(Elem);
    return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if ((Elem < 0) || (Elem >= MaxPower)) {
        throw out_of_range("Invalid index");
    }

    this->DelElem(Elem);
    return *this;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
    return (BitField & s.BitField);
}

TSet TSet::operator~(void) // дополнение
{
    return ~BitField;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
    istr >> s.MaxPower;
    istr >> s.BitField;
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    ostr << s.BitField;
    return ostr;
}
