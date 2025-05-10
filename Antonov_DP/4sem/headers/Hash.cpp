#include "Hash.cpp"


unsigned int Hash_func(int gr){
	unsigned int n = (unsigned int) ((31 * ((int) (gr / 100)) + 11 * (gr % 100))%max_size);
	return n;
}


void Hash::Add_group(int &gr){
	int st = hash_func(gr);
	int i = 0;
	while (hash_func[st].val_){
		if (i == max_size) { break;}
		st++;
		i++;
	}
	if ( i == max_size){
		std::cout << 1 << "\n";
	}
	else{
		hash_func[st].val_ = gr;
	}
}


