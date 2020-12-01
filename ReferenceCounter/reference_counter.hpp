
// String with a Reference Counter

#ifndef REFERENCE_COUNTER_HPP
#define REFERENCE_COUNTER_HPP

typedef int INT_ARRAY[1 / (1 == sizeof(char))];

typedef struct RCS
{
    char *m_str;
    int m_rc;   //Reference Counter
}rcs_t;

class RCString
{
public:

    RCString(const char* str_ = "");

    RCString(const RCString& o_);

    ~RCString();

    RCString& operator=(const RCString& o_);

    const char* ToCStr() const;

    size_t Length() const;

    char operator[](size_t idx_) const;

    char& operator[](size_t idx_);

    RCString& Concat(const RCString& o_);

private:

    rcs_t *m_rcs;
    enum {ONE = 1};
};

bool operator==(const RCString& s1, const RCString& s2);

bool operator!=(const RCString& s1, const RCString& s2);

bool operator<(const RCString& s1, const RCString& s2);

bool operator>(const RCString& s1, const RCString& s2);

std::ostream& operator<<(std::ostream& os_, const RCString& s_);


#endif // REFERENCE_COUNTER_HPP