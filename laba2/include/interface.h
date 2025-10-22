#include <string>
#include <vector>

using namespace std;
class Decimal
{
private:
    vector<unsigned char> numbers;
    void DeleteZeros();

public:

    Decimal();
    Decimal(const string &str);
    Decimal(const Decimal &other);

    ~Decimal() noexcept;

    Decimal add(const Decimal &other) const;
    Decimal subtract(const Decimal &other) const;

    bool eq(const Decimal &other) const;
    bool lt(const Decimal &other) const;
    bool gt(const Decimal &other) const;

    string toString() const;
    size_t size() const;
};
