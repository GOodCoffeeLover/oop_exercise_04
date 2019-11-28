#include<tuple>
#include<iostream>
#include<string>
#include"Figures_templates.cpp"
/*
Трофимов Максим м8о-201б
вариант 15
Разработать шаблоны классов фигур квадрата, прямоугольника и трапеции. 
Также сделать так, чтобы шаблонные функции для классов так же работа ли для std::tuple .
*/
void print_menu(){
	std::cout
	<<"1.Print menu."<<std::endl
	<<"2.Work with square."<<std::endl
	<<"3.Work with rectangle."<<std::endl
	<<"4.Work with trapeze."<<std::endl
	<<"5.Work with tuple."<<std::endl
	<<"0. Exit or change coordinate grid type."<<std::endl;
	return;
}

bool is_num(std::string a){
	for(int i=0; i<a.size(); ++i)
		if( !((a[i]>='0' && a[i]<='9') || (a[i]=='.') || (a[i]=='-')) )
			return false;
	return true;
}

template <class T>
void work_with_squard(){
	std::cout<<"Input coordinates of two opposite square vertexes."<<std::endl<<">>";
	std::pair<T, T> a[2];
	std::string buf;
	for(int i=0; i<2; ++i){
		std::cin>>buf;
		if(is_num(buf) ){
			a[i].first=std::atof(buf.c_str());
		}else{
			std::cout<<"Wrong input."<<std::endl;
			return;
		}
		std::cin>>buf;
		if(is_num(buf) ){
			a[i].second=std::atof(buf.c_str());
		}else{
			std::cout<<"Wrong input."<<std::endl;
			return;
		}
	}
	
	Square f {a[0],a[1]};
	if(f.p1.first==f.p2.first && f.p1.second==f.p2.second){
		std::cout<<"Vertexes don't belong square."<<std::endl;
		return;
	}
	print_info(f);
	return;
}

template <class T>
void work_with_rectangle(){
	std::cout<<"Input coordinates of three rectangle vertexes, coming one after another."<<std::endl<<">>";
	std::pair<T, T> a[3];
	std::string buf;
	for(int i=0; i<3; ++i){
		std::cin>>buf;
		if(is_num(buf) ){
			a[i].first=std::atof(buf.c_str());
		}else{
			std::cout<<"Wrong input."<<std::endl;
			return;
		}
		std::cin>>buf;
		if(is_num(buf) ){
			a[i].second=std::atof(buf.c_str());
		}else{
			std::cout<<"Wrong input."<<std::endl;
			return;
		}
	}
	Rectangle f {a[0],a[1],a[2]};
	if(f.p1.first==f.p2.first && f.p1.second==f.p2.second){
		std::cout<<"Vertexes don't belong rectangle."<<std::endl;
		return;
	}
	print_info(f);
	return;
}
template <class T>
void work_with_trapeze(){
	std::cout<<"Input coordinates of all trapeze vertexes, coming one after another."<<std::endl<<">>";
	std::pair<T, T> a[4];
	std::string buf;
	for(int i=0; i<4; ++i){
		std::cin>>buf;
		if(is_num(buf) ){
			a[i].first=std::atof(buf.c_str());
		}else{
			std::cout<<"Wrong input."<<std::endl;
			return;
		}
		std::cin>>buf;
		if(is_num(buf) ){
			a[i].second=std::atof(buf.c_str());
		}else{
			std::cout<<"Wrong input."<<std::endl;
			return;
		}
	}
	Trapeze f {a[0],a[1],a[2],a[3]};
	if(f.p1.first==f.p2.first && f.p1.second==f.p2.second){
		std::cout<<"Vertexes don't belong trapeze."<<std::endl;
		return;
	}
	print_info(f);
	return;
}

template<class T>
void work_with_tuple(){
	std::string buf;
	std::cout<<"Input number of vertexes (2-4)."<<std::endl<<">>";
	int size;
	std::cin>>buf;
	if(is_num(buf) ){
		size=std::atoi(buf.c_str());
	}else{
		std::cout<<"Wrong input."<<std::endl;
		return;
	}
	if(size<2 || size>4){
		std::cout<<"Wrong number of vertexes."<<std::endl;
		return;
	}
	std::pair<T,T> a[4];
	std::cout<<"Input vertexes of current figure."
	<<std::endl<<"(for squre: 2 opposite;"
	<<std::endl<<"for rectangle 3, coming one after another;"
	<<std::endl<<"for trapeze 4, coming one after another)"
	<<std::endl<<">>";
	for(int i=0; i<size; ++i){
		std::cin>>buf;
		if(is_num(buf) ){
			a[i].first=std::atof(buf.c_str());
		}else{
			std::cout<<"Wrong input."<<std::endl;
			return;
		}
		std::cin>>buf;
		if(is_num(buf) ){
			a[i].second=std::atof(buf.c_str());
		}else{
			std::cout<<"Wrong input."<<std::endl;
			return;
		}
	}
	switch(size){
		case 2:
			print_info(std::make_tuple(a[0], a[1]));
		break;
		case 3:
			print_info(std::make_tuple(a[0], a[1], a[2]));
		break;
		case 4:
			print_info(std::make_tuple(a[0], a[1], a[2], a[3]));
		break;
	}
	return;
}

template <class T>
void menu(){
	std::string buffer;
	int status=1;
	while(status){
		switch(status){
			case 0:
				return;
			case 1:
				print_menu();
				break;
			case 2:
				work_with_squard<T>();
				break;
			case 3:
				work_with_rectangle<T>();
				break;
			case 4:
				work_with_trapeze<T>();
				break;
			case 5:
				work_with_tuple<T>();
				break;
			default:
				std::cout<<"Wrong input."<<std::endl;
				print_menu();
		}
		std::cout<<">>";
		std::cin>>buffer;
		if(is_num(buffer) ){
			status=std::atoi(buffer.c_str());
		}else{
			status=0;
			return;
		}
	}
}

int main(){
	std::string buffer;
	int axises;
	std::cout<<"Program for work with figures in different coordinates grids."<<std::endl
	<<"Accepted figures: square, rectangle, trapeze."<<std::endl
	<<"Choose type of coordinate grid."<<std::endl
	<<"1. integer."<<std::endl
	<<"2. real."<<std::endl
	<<"0. exit"<<std::endl
	<<">>";
	std::cin>>buffer;
	if(is_num(buffer) ){
		axises=std::atoi(buffer.c_str());
	}else{
		axises=-1;
	}
	while(true){
		switch(axises){
			case 0:
				std::cout<<"exit."<<std::endl;
				return 0;
			case 1 :{
				//code for int
				menu<int>();
				break;
			}
			case 2 :{
				//code for double
				menu<double>();
				break;
			}
			default:{
				std::cout<<"Неправильный ввод."<<std::endl;
			}
		}
		std::cout<<"Choose type of coordinate grid."<<std::endl
		<<"1. integer."<<std::endl
		<<"2. real."<<std::endl
		<<"0. exit"<<std::endl
		<<">>";
		std::cin>>buffer;
		if(is_num(buffer) ){
			axises=std::atoi(buffer.c_str());
		}else{
			axises=-1;
		}
	}
}
