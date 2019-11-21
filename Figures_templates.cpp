#include<iostream>
#include<cmath>
//#include<string>
//#include<vector>
#include<tuple>
template <class T> 
double length(std::pair<T, T> p1, std::pair<T, T> p2){
			return sqrt((p2.first-p1.first)*(p2.first-p1.first) + (p2.second-p1.second)*(p2.second-p1.second));				
}

template <class T>
 double cos(std::pair<T, T> p1, std::pair<T, T> p2, std::pair<T, T> p3, std::pair<T, T> p4){
			return  ( (p2.first-p1.first) * (p4.first-p3.first) 
				+ (p2.second-p1.second) * (p4.second-p3.second) )
				/ ( length(p1, p2) * length( p3, p4) ); 
}

/*template <class T>	
double square(std::pair<T, T> p1, std::pair<T, T> p2, std::pair<T, T> p3){
		//пол кореня от ( произведение длин - скалярное произведение )
			return 0.5*sqrt(
		  	 ( (p2.first-p1.first) * (p2.first-p1.first) + (p2.second-p1.second) * (p2.second-p1.second) )
			*( (p3.first-p1.firts) * (p3.first-p1.firts) + (p3.second-p1.second) * (p3.second-p1.second) )
			-( (p2.first-p1.firts) * (p3.first-p1.firts) + (p2.second-p1.second) * (p3.second-p1.second) )
			*( (p2.first-p1.firts) * (p3.first-p1.firts) + (p3.second-p1.second) * (p2.second-p1.second) ) 
			);
		}
*/
template <class T>
class Square{
public:
	using type = T;
	using vertex = std::pair<T, T>;
	vertex p1, p2;
	Square(vertex a, vertex b){
		if(a.first!=b.first || a.second!=b.second){
			p1 = a; 
			p2 = b;
		}
	}
};

template <class T>
class Rectangle{
public:
	using type = T;
	using vertex = std::pair<T, T>;
	vertex p1, p2, p3;
	Rectangle(vertex a, vertex b, vertex c){
		if( (a.first!=b.first || a.second!=b.second)
		 && (c.first!=b.first || c.second!=b.second)
		 && (a.first!=c.first || a.second!=c.second) 
		 && (cos(a, b, b, c)<=1e-9 && cos(a, b, b, c)>=-1e-9) ) {
			p1=a; 
			p2=b;
			p3=c;
		}
	}
};

template <class T>
class Trapeze{
public:
	using type =T;
	using vertex= std::pair<T, T>;
	vertex p1, p2, p3, p4;
	Trapeze(vertex a, vertex b, vertex c, vertex d){
		if( ( ( length(a, b) - length(c, d)<=1e-9) && ( length(a, b) - length(c, d)>=-1e-9 ) )
		&&!( (length(a, b) <= 1e-9) && (length(a, b) >= -1e-9) ) 
		&& ( ( (cos(a, d, c, b) <= 1+1e-9) && (cos(a, d, c, b) >= 1-1e-9) ) 
		   || ( (cos(a, d, c, b)<=-1+1e-9) && (cos(a, d, c, b)>=-1-1e-9) ) ) 
		) {
			std::cout<<"trapeze"<<std::endl;
			p1=a; 
			p2=b;
			p3=c;
			p4=d;
		}
	}
};

template <class T>
double square( Square<T> a){
	std::pair<T, T> c {
		-a.p2.second + (a.p2.second + a.p1.second + a.p2.first + a.p1.first)/2, 
		a.p2.first + (a.p2.second + a.p1.second - a.p2.first - a.p1.first)/2
	};
	return (double) length( a.p1 , c ) 
	     * length( a.p2 , c );
}

template <class T>
double square(Rectangle<T> a){
	return (double) length( a.p1, a.p2 ) 
	     * length( a.p2, a.p3 );
}

template <class T>
double square(Trapeze<T> a){
	return (double)
	(length(a.p1, a.p4)+length(a.p2, a.p3))/2
	* length(a.p2, std::pair<T, T> {
		a.p1.first + ( length(a.p1, a.p4) - length(a.p2, a.p3) ) / 2 
		* ( length(a.p1, std::pair{ a.p4.first, a.p1.second} ) / length(a.p1, a.p4) ),
		a.p1.second + ( length(a.p1, a.p4)-length(a.p2, a.p3) )/2
		* ( length(a.p4, std::pair{a.p4.first, a.p1.second}) / length(a.p1, a.p4) ) 
		}
	  );
}

template <class T>
std::pair<T, T> center(Square<T> a){
	return std::pair{
		( a.p1.first  + a.p2.first  ) / 2, 
		( a.p1.second + a.p2.second ) / 2 
	};
}

template <class T>
std::pair<T, T> center(Rectangle<T> a){
	return std::pair{
		( a.p1.first  + a.p3.first  ) / 2, 
		( a.p1.second + a.p3.second ) / 2 
	};
}

template <class T>
std::pair<T, T> center(Trapeze<T> a){
	return std::pair{
		( a.p1.first  + a.p2.first  + a.p3.first  + a.p4.first  ) / 4, 
		( a.p1.second + a.p2.second + a.p3.second + a.p4.second ) / 4 
	};
}
template <class T>
std::ostream& operator <<(std::ostream &o, std::pair<T, T>& a){
	o<<" ( "<<a.first<<" , "<<a.second<<" ) ";
	return o;
}
template <class T>
std::ostream& operator <<(std::ostream &o, std::pair<T, T>&& a){
	o<<" ( "<<a.first<<" , "<<a.second<<" ) ";
	return o;
}

template <class T>
void print_info(Square<T> a){
	std::cout<<"It's Square."<<std::endl
		<<"vertexes:"<<std::endl
		<<a.p1<<';'<<std::pair<T, T>{
			-a.p2.second + (a.p2.second + a.p1.second + a.p2.first + a.p1.first)/2, 
			a.p2.first + (a.p2.second + a.p1.second - a.p2.first - a.p1.first)/2
		}<<';'<<a.p2<<';'<<std::pair<T, T>{
			a.p2.second + (a.p2.first + a.p1.first - a.p2.second - a.p1.second)/2, 
			-a.p2.first + (a.p2.second + a.p1.second + a.p2.first + a.p1.first)/2
		}<<'.'<<std::endl
		<<"square: "<<square(a)<<" ."<<std::endl
		<<"center:"<<center(a)<<'.'<<std::endl;
}

template <class T>
void print_info(Rectangle<T> a){
	std::cout<<"It's Rectangle."<<std::endl
		<<"vertexes:"<<std::endl
		<<a.p1<<';'<<a.p2<<';'<<a.p3<<';'<<std::pair<T, T>{
			a.p3.first-a.p2.first+a.p1.first,
			a.p3.second-a.p2.second+a.p1.second
		}<<'.'<<std::endl
		<<"square: "<<square(a)<<" ."<<std::endl
		<<"center:"<<center(a)<<'.'<<std::endl;
}

template <class T>
void print_info(Trapeze<T> a){
	std::cout<<"It's Trapeze."<<std::endl
		<<"vertexes:"<<std::endl
		<<a.p1<<';'<<a.p2<<';'<<a.p3<<';'<<a.p4<<'.'<<std::endl
		<<"square: "<<square(a)<<" ."<<std::endl
		<<"center:"<<center(a)<<'.'<<std::endl;
}

//=============================================================

template <class T>
double square( std::tuple<std::pair<T, T>, std::pair<T, T>> a){
	if(std::get<0>(a).first!=std::get<1>(a).first || std::get<0>(a).second!=std::get<1>(a).second){
		std::pair<T, T> c {
			-std::get<1>(a).second + (std::get<1>(a).second + std::get<0>(a).second + std::get<1>(a).first + std::get<0>(a).first)/2, 
			std::get<1>(a).first + (std::get<1>(a).second + std::get<0>(a).second - std::get<1>(a).first - std::get<0>(a).first)/2
		};
		return (double) length( std::get<0>(a) , c ) 
		     * length( std::get<1>(a) , c );
	}
	return 0.0;
}

template <class T>
double square(std::tuple<std::pair<T, T>, std::pair<T, T>, std::pair<T, T>> a){
	if( (std::get<0>(a).first!=std::get<1>(a).first || std::get<0>(a).second!=std::get<1>(a).second)
	 && (std::get<2>(a).first!=std::get<1>(a).first || std::get<2>(a).second!=std::get<1>(a).second)
	 && (std::get<0>(a).first!=std::get<2>(a).first || std::get<0>(a).second!=std::get<2>(a).second) 
	 && (cos(std::get<0>(a), std::get<1>(a), std::get<1>(a), std::get<2>(a))<=1e-9 
	    && cos(std::get<0>(a), std::get<1>(a), std::get<1>(a), std::get<2>(a))>=-1e-9) ) {
			return (double) length( std::get<0>(a), std::get<1>(a) ) 
	     * length( std::get<1>(a), std::get<2>(a) );
	}
	return 0.0;
}

template <class T>
double square( std::tuple<std::pair<T, T>, std::pair<T, T>, std::pair<T, T>, std::pair<T, T>> a){
	
	if( ( ( length(std::get<0>(a), std::get<1>(a)) - length(std::get<2>(a), std::get<3>(a)) <= 1e-9 ) 
	&& ( length(std::get<0>(a), std::get<1>(a)) - length(std::get<2>(a), std::get<3>(a)) ) >=-1e-9 )
	&&!( (length(std::get<0>(a), std::get<1>(a)) <= 1e-9) && (length(std::get<0>(a), std::get<1>(a)) >= -1e-9) ) 
	&& ( ( (cos(std::get<0>(a), std::get<3>(a), std::get<2>(a), std::get<1>(a)) <= 1+1e-9) 
	&& (cos(std::get<0>(a), std::get<3>(a), std::get<2>(a), std::get<1>(a)) >= 1-1e-9) ) 
	|| ( (cos(std::get<0>(a), std::get<3>(a), std::get<2>(a), std::get<1>(a)) <= -1+1e-9) 
	&& (cos(std::get<0>(a), std::get<3>(a), std::get<2>(a), std::get<1>(a)) >= -1-1e-9) ) ) ) {
		return (double)
		(length(std::get<0>(a), std::get<3>(a))+length(std::get<1>(a), std::get<2>(a)))/2
		* length(std::get<1>(a), std::pair<T, T> {
			std::get<0>(a).first + ( length(std::get<0>(a), std::get<3>(a)) - length(std::get<1>(a), std::get<2>(a)) ) / 2 
			* ( length(std::get<0>(a), std::pair{ std::get<3>(a).first, std::get<0>(a).second} ) / length(std::get<0>(a), std::get<3>(a)) ),
			std::get<0>(a).second + ( length(std::get<0>(a), std::get<3>(a))-length(std::get<1>(a), std::get<2>(a)) )/2
			* ( length(std::get<3>(a), std::pair{std::get<3>(a).first, std::get<0>(a).second}) / length(std::get<0>(a), std::get<3>(a)) ) 
			}
	  	);
	}
	return 0.0;
}

template <class T>
std::pair<T, T> center(std::tuple<std::pair<T, T>, std::pair<T, T>> a){
	if(std::get<0>(a).first!=std::get<1>(a).first || std::get<0>(a).second!=std::get<1>(a).second){
		return std::pair{
			 ( std::get<0>(a).first  + std::get<1>(a).first ) / 2, 
			 ( std::get<0>(a).second + std::get<1>(a).second ) / 2 
		};
	}
	return std::pair<T, T> {0.0, 0.0};
}

template <class T>
std::pair<T, T> center(std::tuple<std::pair<T, T>, std::pair<T, T>, std::pair<T, T>> a){
		if( (std::get<0>(a).first!=std::get<1>(a).first || std::get<0>(a).second!=std::get<1>(a).second)
		 && (std::get<2>(a).first!=std::get<1>(a).first || std::get<2>(a).second!=std::get<1>(a).second)
		 && (std::get<0>(a).first!=std::get<2>(a).first || std::get<0>(a).second!=std::get<2>(a).second) 
		 && (cos(std::get<0>(a), std::get<1>(a), std::get<1>(a), std::get<2>(a))<=1e-9 
		    && cos(std::get<0>(a), std::get<1>(a), std::get<1>(a), std::get<2>(a))>=-1e-9) ) {
			return std::pair{
				 ( std::get<0>(a).first  + std::get<2>(a).first ) / 2, 
				 ( std::get<0>(a).second + std::get<2>(a).second ) / 2 
			};
		}
		return std::pair{0.0, 0.0};
}

template <class T>
std::pair<T, T> center( std::tuple<std::pair<T, T>, std::pair<T, T>, std::pair<T, T>, std::pair<T, T>> a ){

	if( ( ( length(std::get<0>(a), std::get<1>(a)) - length(std::get<2>(a), std::get<3>(a)) <= 1e-9 ) 
	&& ( length(std::get<0>(a), std::get<1>(a)) - length(std::get<2>(a), std::get<3>(a)) ) >=-1e-9 )
	&&!( (length(std::get<0>(a), std::get<1>(a)) <= 1e-9) && (length(std::get<0>(a), std::get<1>(a)) >= -1e-9) ) 
	&& ( ( (cos(std::get<0>(a), std::get<3>(a), std::get<2>(a), std::get<1>(a)) <= 1+1e-9) 
	&& (cos(std::get<0>(a), std::get<3>(a), std::get<2>(a), std::get<1>(a)) >= 1-1e-9) ) 
	|| ( (cos(std::get<0>(a), std::get<3>(a), std::get<2>(a), std::get<1>(a)) <= -1+1e-9) 
	&& (cos(std::get<0>(a), std::get<3>(a), std::get<2>(a), std::get<1>(a)) >= -1-1e-9) ) ) ) {
		return std::pair{
			(std::get<0>(a).first + std::get<1>(a).first + std::get<2>(a).first + std::get<3>(a).first)/4, 
			 (std::get<0>(a).second+ std::get<1>(a).second+ std::get<2>(a).second+ std::get<3>(a).second)/4 
		};
	}
	return std::pair{0.01, 0.01};
}

template <class T>
void print_info(std::tuple<std::pair<T, T>, std::pair<T, T>> a){
	std::cout<<"It's Square."<<std::endl
		<<"vertexes:"<<std::endl
		<<std::get<0>(a)<<';'<<std::pair<T, T>{
			-std::get<1>(a).second + (std::get<1>(a).second + std::get<0>(a).second + std::get<1>(a).first + std::get<0>(a).first)/2, 
			std::get<1>(a).first + (std::get<1>(a).second + std::get<0>(a).second - std::get<1>(a).first - std::get<0>(a).first)/2
		}<<';'
		<<std::get<1>(a)<<';'<<std::pair<T, T>{
			std::get<1>(a).second + (std::get<1>(a).first + std::get<0>(a).first - std::get<1>(a).second - std::get<0>(a).second)/2, 
			-std::get<1>(a).first + (std::get<1>(a).second + std::get<0>(a).second + std::get<1>(a).first + std::get<0>(a).first)/2
		}<<'.'<<std::endl
		<<"square: "<<square(a)<<" ."<<std::endl
		<<"center:"<<center(a)<<'.'<<std::endl;
}

template <class T>
void print_info(std::tuple<std::pair<T, T>, std::pair<T, T>, std::pair<T, T>> a){
	std::cout<<"It's Rectangle."<<std::endl
		<<"vertexes:"<<std::endl
		<<std::get<0>(a)<<';'<<std::get<1>(a)<<';'<<std::get<2>(a)<<';'<<std::pair<T, T>{
			std::get<2>(a).first-std::get<1>(a).first+std::get<0>(a).first,
			std::get<2>(a).second-std::get<1>(a).second+std::get<0>(a).second
		}<<'.'<<std::endl
		<<"square: "<<square(a)<<" ."<<std::endl
		<<"center:"<<center(a)<<'.'<<std::endl;
}

template <class T>
void print_info(std::tuple<std::pair<T, T>, std::pair<T, T>, std::pair<T, T>, std::pair<T, T>> a){
	std::cout<<"It's Trapeze."<<std::endl
		<<"vertexes:"<<std::endl
		<<std::get<0>(a)<<';'<<std::get<1>(a)<<';'<<std::get<2>(a)<<';'<<std::get<3>(a)<<'.'<<std::endl
		<<"square: "<<square(a)<<" ."<<std::endl
		<<"center:"<<center(a)<<'.'<<std::endl;
}
