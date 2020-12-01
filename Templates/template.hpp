
// Getting to know Templates
// Since the class is a template this file is also the functions definitions
// file

#ifndef TEMPLATES_HPP
#define TEMPLATES_HPP

template <typename P>
class Point
{
public:
    Point(): m_x(0), m_y(0)
    {}
    
    Point(P x, P y): m_x(x), m_y(y)
    {}

    inline const P& GetX() const;
    inline const P& GetY() const;

    inline void SetX(const P& x_);
    inline void SetY(const P& y_);

    void operator+=(const Point& other_);
    void operator-=(const Point& other_);

private:
    P m_x;
    P m_y;
};

template <typename P>
const P& Point<P>::GetX() const
{
    return (this->m_x);
}

template <typename P>
const P& Point<P>::GetY() const
{
    return (this->m_y);
}

template <typename P>
void Point<P>::SetX(const P& x_)
{
    this->m_x = x_;
}

template <typename P>
void Point<P>::SetY(const P& y_)
{
    this->m_y = y_;
}

template <typename P>
const Point<P> operator+(const Point<P>& p1_, const Point<P>& p2_)
{
    Point<P> result;

    result.SetX(p1_.GetX() + p2_.GetX());
    result.SetY(p1_.GetY() + p2_.GetY());

    return (result);
}

template <typename P>
const Point<P> operator-(const Point<P>& p1_, const Point<P>& p2_)
{
    Point<P> result;

    result.SetX(p1_.GetX() - p2_.GetX());
    result.SetY(p1_.GetY() - p2_.GetY());

    return (result);
}

template <typename P>
void Point<P>::operator+=(const Point<P>& other_)
{
    this->m_x += other_.m_x;
    this->m_x += other_.m_y;
}

template <typename P>
void Point<P>::operator-=(const Point<P>& other_)
{
    this->m_x -= other_.m_x;
    this->m_x -= other_.m_y;
}

#endif // TEMPLATES_HPP
