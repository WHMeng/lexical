#if 0

Context  ---------------------->  Strategy
                                      |
                                      |
                                      |
						-----------------------------------
						|             |                   |
						|             |                   |
				ConcreteStrategyA  ConcreteStrategayB ConcreteStrategayC
#endif

class WeaponBehavior {
public:
	virtual void useWeapon() = 0;
};

class AK47 : public WeaponBehavior {
public:
	void useWeapon() {
		cout << "Use AK47 to shoot!" << endl;
	}
};

class Knife : public WeaponBehavior {
public:
	void useWeapon() {
		cout << "Use Knife to shoot!" << endl;
	}
};

class Context {
public:
	Context() : weapon(NULL) {}
	void setWeapon(WeaponBehavior *w) {
		this->weapon = w;
	}
	void fight(){
		if(this->weapon == NULL){
			cout << "You don't have a weapon! Please set weapon!" << endl;
		}else{
			weapon->useWeapon();
		}
	}
private:
	WeaponBehavior *weapon;
};

int main(){
	WeaponBehavior *ak47 = new AK47();
	WeaponBehavior *knife = new Knife();

	Context *con = new Context();

	con->fight();

	con->setWeapon(ak47);
	con->fight();

	con->setWeapon(knife);
	con->fight();

	return 0;
}

// 以上 Context 为普通策略模式，以下 Context 为策略模式与简单工厂模式结合

enum WEAPON {W_AK47, W_KNIFE};

class Context {
public:
	Context() : weapon(NULL) {}
	void setWeapon(WEAPON w_tag) {
		switch(w_tag){
			case W_AK47 :
				if(weapon)
					delete weapon;
				weapon = new AK47();
				break;
			case W_KNIFE:
				if(weapon)
					delete weapon;
				weapon = new Knife();
				break;
		}
	}
	void fight(){
		if(this->weapon == NULL){
			cout << "You don't have a weapon! Please set weapon!" << endl;
		}else{
			weapon->useWeapon();
		}
	}
private:
	WeaponBehavior *weapon;
};

int main(){
	Context *con = new Context();

	con->fight();

	con->setWeapon(W_AK47);
	con->fight();

	con->setWeapon(W_KNIFE);
	con->fight();
}
