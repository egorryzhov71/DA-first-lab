#include <iostream>
#include <utility>
#include <memory>
#include <cmath>
#include <concepts>
#include <vector>
#include <type_traits>

template <typename T>
concept Scalar = std::is_scalar_v<T>;


template<Scalar T>
class Point {
private:
    T x, y;
public:
    Point(T x, T y){
        this -> x = x;
        this -> y = y;

    }
    double distanceTo(const Point<T>& other) const;
    T x() const;
    T y() const;
    void print() const;
};


template <Scalar T>
class Figure{
    public:
        virtual ~Figure() = default;

        virtual double area() const = 0;
        virtual Point<T> center() const = 0;
        virtual void print() const = 0;

        virtual bool operator==(const Figure<T>& other) const = 0;
        explicit operator double() const {return area(); } 
};


template <Scalar T>
class Pentagon: public Figure<T> {
    private:
        std::unique_ptr <Point<T>> center;
        T radius_;
    public:
        Pentagon(T center_x, T center_y , T radius);
        double area() const override;
        Point<T> center() comst override;
        void print() const override;
        bool operator == (const Figure<T>& other) const override;
};


template <Scalar T>
class Hexagon : public Figure<T> {
    private:
        std::unique_ptr <Point<T>> center;
        T radius_;
    public:
        Hexagon(T center_x, T center_y, T radius_);
        double area() const override;
        Point<T> center() const override;
        void print() const override;
        bool operator == (const Figure<T>& other) const override;
};


template <Scalar T>
class Romb : public Figure<T> {
    private:
        std::unique_ptr <Point<T>> center;
        T horizontal_diagonal, vertical_diagonal;
    public:
        Romb(T center_x, T center_y, T horizontal_diagonal, T vertical_diagonal);
        double area() const override;
        Point<T> center() const override;
        void print() const override;
        bool operator == (const Figure<T>& other) const override;
};

template <typename T>
class Array{
    private:
        std::shared_ptr<T[]> data_;
        size_t = size;
        size_t = capacity;
    public:
        Array();
        Array(const Array& other);           
        Array(Array&& other) noexcept;      
        Array& operator=(const Array& other); 
        Array& operator=(Array&& other) noexcept;
        ~Array = default;

        void push_back(const T& value);
        void remove(size_t index);
        void clear();
        size_t capacity const;
        bool empty() const;
        size_t size const;
        double total_area() const;

        T& operator[](size_t, index);
        const T& operator[](size_t, index);
        T& at(size_t index);
        const T& at(size_t index) const;
    private:
        void resize(size_t, new_capacity);
};
