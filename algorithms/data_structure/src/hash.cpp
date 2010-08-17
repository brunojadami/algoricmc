#include<vector>
#include<list>
using namespace std;

template<class T> class Hash{
	vector<list<T>> hash(HASH_SIZE);
	int (*hashFunc)(T key);

	Hash(int (*hashFunc)(T)){ this->hashFunc = hashFunc; };
	void insert(T key);
	list<T>::iterator search(T key);
};

template<class T> void Hash<T>::insert(T key){
	int position = hashFunc(key);
	bool outOfBound( position >= hash.size());
	if( outOfBound )
		hash.resize(position+1, list<T>);
	hash[position].push_front(key);
};

template<class T> list<t> Hash<T>::iterator search(T key){
	int position = hashFunc(key);
	bool outOfBound( position >= hash.size());
	if( outOfBound )
		return 0;
	for(list<T>::iterator it = hash[position].begin(); it != hash[position].end(); it++)
		if( *it == key )
			return it;
	return 0;
};

template<class T> void Hash<T>::print(){
	for(int i = 0; i < hash.size(); i++){
		cout << i << ":\t";
		for(list<T>::iterator it = hash[i].begin(); it != hash[i].end(); it++)
			cout << *it << ", ";
		cout << endl;
	}
};
