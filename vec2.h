#ifndef VEC2_H
#define VEC2_H
// #include <math.h>

template<typename T>
struct vec2{
    static const int AXIS_COUNT = 2;

	enum axis {
		AXIS_X,
		AXIS_Y,
	};


    T x; T y;
    
    // Constructors

    vec2(){x = 0; y = 0;}
    
    vec2(T input_x, T input_y){x = input_x; y = input_y;}

    vec2(T i){x = i; y = i;}

    template<typename OT> void operator=(vec2<OT> v) {x = T(v.x); y = T(v.y);};

    //Operations

    inline T& operator[](T a){return (a == 0) ? x:y;}

    // Addition

    inline vec2<T> operator+(vec2<T>v){
        return vec2<T> (x + T(v.x), y + T(v.y));
    }

    template<typename OT> inline void operator+=(vec2<OT> v){
        x = x + T(v.x);  y = y + T(v.y);
    }

    // Subtraction

    inline vec2<T> operator-(vec2<T>  v){
        return vec2<T>(x - T(v.x), y - T(v.y));
    }
    
    template<typename OT> inline void operator-=(vec2<OT>  v){
        x = x - T(v.x);  y = y - T(v.y);
    }
    
    // Multiplication

    inline vec2<T> operator*(T a){
        return vec2<T>(x*a, y*a);
    }
    inline vec2<T> operator*(vec2<T>  v){
        return vec2<T>(x*T(v.x), y*T(v.y));
    }
    inline void operator*=(T a){
        x = x*a; y = y*a;
    }
    template <typename OT>inline void operator*=(vec2<OT>  v){
        x = x*T(v.x); y = y*T(v.y);
    }

    // Division

    inline vec2<T>  operator/(T a){
        return vec2<T> (x*a, y*a);
    }
    inline vec2<T>  operator/(vec2<T>  v){
        return vec2<T> (x/T(v.x), y/T(v.y));
    }
    inline void operator/=(T a){
        x = x/a; y = y/a;
    }
    template <typename OT> inline void operator/=(vec2<OT> v){
        x = x/T(v.x); y = y/T(v.y);
    }
    
    // Modulus

    inline vec2<T>  operator%(T a){
        return vec2<T> (x%a, y%a);
    }
    inline vec2<T>  operator%(vec2<T>  v){
        return vec2<T> (x%T(v.x), y%T(v.y));
    }
    inline void operator%=(T a){
        x = x%a; y = y%a;
    }
    inline void operator%=(vec2<T>  v){
        x = x%T(v.x); y = y%T(v.y);
    }

    // Other

    inline bool operator==(vec2<T>  v){
        return T(v.x) == x && T(v.y) == y;
    }
    inline bool operator!=(vec2<T>  v){
        return T(v.x) != x || T(v.y) != y;
    }

    //Endregion

    inline double len(){
        return std::sqrt(x*x + y*y);
    }
    inline const std::string str(){return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";}

};

#endif 