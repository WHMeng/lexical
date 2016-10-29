
// 最基本单例模式
class CSingleton{
private:
	CSingleton() {}
	static CSingleton *pInstance;
public:
	static CSingleton *GetInstance(){
		if(pInstance == NULL)
			pInstance = new CSingleton;
		return pInstance;
	}
};

// 程序在结束的时候，系统会自动析构所有的全局变量，也会析构所有类的静态
// 成员变量
class CSingleton{
private:
	CSingleton() {}
	static CSingleton *pInstance;
	class CGarbo{
	public:
		~CGarbo(){
			if(CSingleton::pInstance)
				delete CSingleton::pInstance;
		}
	};
	static CGarbo Garbo;
public:
	static CSingleton *GetInstance(){
		if(pInstance == NULL)
			pInstance = new CSingleton;
		return pInstance;
	}
};
