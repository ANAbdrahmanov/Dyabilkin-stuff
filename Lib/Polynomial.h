template<class T> class Polynomial{
	int numbers;
	T* coefficients;
	Polynomial(int num){  //для ф-ий
		numbers = num;
		coefficients = new T[num];
	}
public:
	Polynomial(){
		numbers = 0;
		coefficients = 0;
	}
	Polynomial(int num, T def){
		numbers = num;
		coefficients = new T[num];
		for(int i = 0; i < num; i++){
			coefficients[i] = def;
		}
	}
	Polynomial(int num, const T* vals){
		numbers = num;
		coefficients = new int[num];
		for(int i = 0; i < num; i++){
			coefficients[i] = vals[i];
		}
	}
	Polynomial(const Polynomial& source){
		numbers = source.numbers;
		coefficients = new T[numbers];
		for(int i = 0; i < numbers; i++){
			coefficients[i] = source.coefficients[i];
		}
	}
	~Polynomial(){
		delete[] coefficients;
	}
	int degree() const{
		return this->numbers - 1;
	}
	T operator[](int i) const {
		if(i >= numbers){
			return 0;
		}
		return coefficients[i];
	}
	T operator()(T x){
		T sum = 0;
		for(int i = numbers - 1; i > 0; i--){
			sum += (*this)[i];
			sum *= x;
		}	
		sum += (*this)[0];
		return sum;
	}
	Polynomial operator+(const Polynomial& k){
		int n = this->degree() > k.degree()? this->degree() + 1 : k.degree() + 1;
		Polynomial res(n);
		for(int i = 0; i < n; i++){
			res.coefficients[i] = (*this)[i] + k[i];
		}
		for(int i = n-1; res.coefficients[i] == 0; i--){
			res.numbers--;
		}
		return res;
	}
	Polynomial& operator=(const Polynomial& k){
		this->numbers = k.numbers;
		delete[] this->coefficients;
		this->coefficients = new T[this->numbers];
		for(int i = 0; i < k.numbers; i++){
			this->coefficients[i] = k.coefficients[i];
		}
	}
	Polynomial& operator+=(const Polynomial& k){
		int n = this->degree() > k.degree()? this->degree() + 1 : k.degree() + 1;
		int* res = new T[n];
		for(int i = 0; i < n; i++){
			res[i] = (*this)[i] + k[i];
		}
		for(int i = n-1; res[i] == 0; i--){
			n--;
		}
		this->numbers = n;
		delete[] this->coefficients;
		this->coefficients = res;
		return *this;
	}
	Polynomial operator*(const Polynomial& k){
		if(this->degree == -1 || k.degree() == -1){
			return Polynomial();
		}
		int n = this->degree() + k.degree() + 1;
		Polynomial res(n);
		for(int i = 0; i < n; i++){
			res.coefficients[i] = 0;
		}
		for(int i = 0; i < this->degree() + 1; i++){
			for(int j = 0; j < k.degree() + 1; j++){
				res.coefficients[i+j] += this->coefficients[i] * k.coefficients[j];
			}
		}
		return res;
	}
	Polynomial& operator*=(const Polynomial& k){
		if(this->degree() == -1 || k.degree() == -1){
			this->numbers = 0;
			delete[] this->coefficients;
			this->coefficients = 0;
			return *this;
		}
		int n = this->degree() + k.degree() + 1;
		int* res = new T[n];
		for(int i = 0; i < n; i++){
			res[i] = 0;
		}
		for(int i = 0; i < this->degree() + 1; i++){
			for(int j = 0; j < k.degree() + 1; j++){
				res[i+j] += this->coefficients[i] * k.coefficients[j];
			}
		}	
		this->numbers = n;
		delete this->coefficients;
		this->coefficients = res;
		return *this;
	}
	bool operator==(const Polynomial& k){
		if(this->numbers != k.numbers) return false;
		for(int i = 0; i < k.numbers; i++){
			if(k[i] != (*this)[i]) return false;
		}
		return true;
	}		
	bool operator!=(const Polynomial& k){
		if(this->numbers != k.numbers) return true;
		for(int i = 0; i < k.numbers; i++){
			if(k[i] != (*this)[i]) return true;
		}
		return false;
	}
	Polynomial operator*=(T m){
		for(int i = 0; i < this->numbers; i++){
			this->coefficients[i] *= m;
		}
		return *this;
	}
	Polynomial& operator*(T m){
		Polynomial res(this->numbers);
		for(int i = 0; i < this->numbers; i++){
			res.coefficients[i] = this->coefficients[i] * m;
		}
		return res;
	}
};
