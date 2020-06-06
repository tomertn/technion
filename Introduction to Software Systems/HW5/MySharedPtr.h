#ifndef _MY_SHARED_PTR_H_
#define _MY_SHARED_PTR_H_

template<class Type>
class MySharedPtr {


public:
	//c'tors

	MySharedPtr()  {
		p = new Type;
		cnt = new int;
		*cnt = 1;
	}

	MySharedPtr(Type* t) : p(t) {
		cnt = new int;
		*cnt = 1;
	}

	MySharedPtr(const MySharedPtr& pToCopy) : p(pToCopy.get()) {  // copy c'tor
		pToCopy.getCnt()++;
		cnt = &pToCopy.getCnt();
	}

	//d'tor

	~MySharedPtr() {
		if ((*cnt) == 1) {
			delete cnt; delete p;
		}
		else {
			(*cnt)--;
		}
	}

	//eprators

	MySharedPtr<Type>& operator=(MySharedPtr<Type>& pToSet) {
		if(pToSet.get()!=p){
			if ((*cnt) == 1) {
				delete p; delete cnt;
			}
			else (*cnt)--;
				p = pToSet.get();
				pToSet.getCnt()++;
				cnt = &pToSet.getCnt();
		}
		return (*this);
	}

	Type& operator*() const {
		return *p;
	}

	/*const Type& operator*() const {
		return *p;
	}*/

	Type* operator->() const {
		return p;
	}

	/*const Type* operator->() const {
		return p;
	}*/

	//Methods

	Type* get() const {
		return p;
	}

	int& getCnt() const { return *cnt; }

private:
	int* cnt;
	Type* p;


};





#endif // _MY_SHARED_PTR_H_
