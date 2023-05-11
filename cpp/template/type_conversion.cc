#include <iostream>

// Please refer to "Effective C++" item 46

template <typename T>
class Rational {
    T numerator_;
    T denominator_;
public:
    Rational(const T& numerator = 0, const T& denominator = 1) : numerator_(numerator), denominator_(denominator) {
    }

    const T numerator() const {
        return numerator_;
    }

    const T denominator() const {
        return denominator_;
    }

    friend const Rational<T> operator*(const Rational<T>& lhs, const Rational<T>& rhs) {
        return Rational<T>(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
    }
};

/*
template <typename T>
const Rational<T> operator*(const Rational<T>& lhs, const Rational<T>& rhs) {
    return Rational<T>(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
}
*/

int main() {
    Rational<int> oneHalf(1, 2);
    Rational<int> result = oneHalf * 2;
    return 0;
}