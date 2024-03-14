#include<iostream>
#include<memory>
#include<vector>
#include<string>

//smart pointers
//auto_ptr - depricated,c++20 - removed
//unique_ptr:
//		контролирует существование единственной ссылки на объект в памяти
//		является владеющим указателем(его время жизни связано с объектом на который он указывает)
//shared_ptr:
//		ведет учет ссылок на один объект в памяти, которым управляет несколько модулей в программе
//		является владеющим указателем(его время жизни связано с объектом на который он указывает) 
//weal_ptr
//		только хранит адреса внутри себя. не служит ни для чего кроме предачи адресов между частями
//		приложения. невладеющий указатель.


//если не передавать по ссылке то объект на который указывает автомотический указатель будет уничтожен 
//в отличии от unique_ptr auto_ptr не препятствует созданию своих копий. 

void F00(std::auto_ptr<std::string> &obj) { };
void F01(std::unique_ptr<std::string> &obj) { };
void F02(std::shared_ptr<std::string>  obj) {
	std::cout << '\n' << obj.use_count();
};

class Trait{
public:
	Trait(std::string name) :name_(name){ }

	std::string GetName()const {
		return name_;
	}

private:
	std::string name_;

};


class Color:public Trait { 
public:
	Color(std::string name):Trait(name){ }


};

class Material:public Trait {
public:
	Material(std::string name) :Trait(name) { }
};


class Toy {
public:
	Toy(std::string name,
		std::shared_ptr<Color> color,
		std::shared_ptr<Material> material
		) :name_(name),color_(color),material_(material) { }

	std::string GetName()const {
		return name_;
	}

	std::string GetColor()const {
		return color_->GetName();
	}

	std::string GetMaterial()const {
		return material_->GetName();
	}

private:
	std::string name_;
	std::shared_ptr<Trait> color_;
	std::shared_ptr<Trait> material_;

};

std::vector<std::shared_ptr<Color>> g_colors{
	std::make_shared<Color>("Red"),
	std::make_shared<Color>("Green"),
	std::make_shared<Color>("Blue")
};
std::vector<std::shared_ptr<Material>> g_materials{
	std::make_shared<Material>("Glass"),
	std::make_shared<Material>("Stone"),
	std::make_shared<Material>("Wood"),
};

//int main1() {
//
//	auto tmp = new std::string("qwerty");
//	//std::unique_ptr<std::string> p_str (new std::string("qwerty"));
//	//выше пример как не стоит делать, хоть и будет работать
//
//
//	auto u_ptr = std::make_unique<std::string>("qwerty");
//
//	std::auto_ptr<std::string> a_ptr(new std::string("qwerty"));
//
//	std::shared_ptr<std::string> sh_ptr =
//		std::make_shared<std::string>("asasasa");
//	/*F00(a_ptr);
//	F01(u_ptr);*/
//	F02(sh_ptr);
//	return 0;
//}
	int main() {
		std::vector<Toy> toys;
		toys.reserve(9);
		int q{ 1 };

		for  (int i = 0; i < g_colors.size();i++){
			for (int j = 0; j < g_materials.size(); j++) {
				toys.emplace_back(
					std::string("Toy")+std::to_string(q),
					g_colors[i],
					g_materials[j]
				);
			}
		}

		for (auto& i : toys) {
			std::cout<< i.GetColor();
		}



		return 0;
	}

