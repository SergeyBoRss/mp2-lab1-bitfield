// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len < 0) {
        cout << "Negative length";
        return;
    }
    else if (len == 0) {
        BitLen = len;
        pMem = nullptr;
        MemLen = 0;
    }
    else {
        BitLen = len;
        MemLen = (BitLen - 1) / (sizeof(TELEM) * 8) + 1;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = 0;
        }
    }


}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    if (&bf != this) {
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        if (BitLen == 0) {
            pMem = nullptr;
        }
        else {
            pMem = new TELEM[MemLen];
            for (int i = 0; i < MemLen; i++) {
                pMem[i] = bf.pMem[i];
            }
        }

    }
}

TBitField::~TBitField()
{
    if (pMem != nullptr) {
        delete[] pMem;
    }
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if ((n < 0) || (n >= BitLen)) {
        throw out_of_range("Invalid index");
    }

    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if ((n < 0) || (n >= BitLen)) {
        throw out_of_range("Invalid index");
    }

    return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n < 0) || (n >= BitLen)) {
        throw out_of_range("Invalid index");
    }

    pMem[GetMemIndex(n)] |= GetMemMask(n);

}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n < 0) || (n >= BitLen)) {
        throw out_of_range("Invalid index");
    }

    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n<0 || n>BitLen) {
        throw "Invalid index";
    }

    if ((pMem[GetMemIndex(n)] & GetMemMask(n)) == 0) {
        return 0;
    }
    else return 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    if (*this != bf) {
        if (pMem != nullptr) {
            delete[] pMem;
        }
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    }

    return(*this);
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
    if (BitLen != bf.BitLen || MemLen != bf.MemLen) {
        return 0;
    }
    else {
        for (int i = 0; i < MemLen; i++) {
            if (pMem[i] != bf.pMem[i]) {
                return 0;
            }
        }
    }
    return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
    return (~(this->operator==(bf)));
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    TBitField tmp(max(this->BitLen, bf.BitLen));
    for (int i = 0; i < tmp.MemLen; i++) {
        tmp.pMem[i] = this->pMem[i] | bf.pMem[i];
    }

    return tmp;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    TBitField tmp(max(this->BitLen, bf.BitLen));
    for (int i = 0; i < tmp.MemLen; i++) {
        tmp.pMem[i] = this->pMem[i] & bf.pMem[i];
    }

    return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField tmp(*this);

    for (int i = 0; i < BitLen; i++)
    {
        if (tmp.GetBit(i)) {
            tmp.ClrBit(i);
        }
        else {
            tmp.SetBit(i);
        }
    }
    return tmp;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
    for (int i = 0; i < bf.BitLen && (cin.peek() != '\n'); i++) {
        int new_bit;
        cin >> new_bit;
        if ((new_bit != 0) || (new_bit != 1)) {
            throw "Invalid bit";
        }
        else {
            if (new_bit) {
                bf.SetBit(i);
            }
            else {
                bf.ClrBit(i);
            }
        }
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++) {
        cout << bf.GetBit(i);
    }
    return ostr;
}
