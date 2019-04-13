#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

template <typename K, typename V>
class MyMultiMap {
public:
	class Key {
	public:
		K key;
		size_t num;
		Key(const K& k, size_t n) {
			key = k;
			num = n;
		}
		bool operator<(const Key& rhs) const {
			if (!(key < rhs.key) && !(rhs.key < key)) {
				return num < rhs.num;
			}
			else {
				return key < rhs.key;
			}
		}
		K* get_k() {
			return &key;
		}
	};
private:
	struct inf {
		size_t max = 1;
		size_t min = 1;
		size_t num = 1;
		size_t cnt = 1;
	};
	map<Key, V> m;
	map<K, inf> km;
	size_t _size;
public:
	typedef typename map<Key, V>::iterator iterator;
	MyMultiMap() {
		m = map<Key, V>();
		km = map<K, inf>();
		_size = 0;
	}
	MyMultiMap(const MyMultiMap<K, V>& x) {
		m = map<Key, V>(x.m);
		km = map<K, inf>(x.km);
		_size = x._size;
	}
	void insert(const K& k, const V& v) {
		typename map<K, inf>::iterator it = km.find(k);
		if (it == km.end()) {
			m.insert(pair<Key, V>(Key (k, 1), v));
			km.insert(pair<K, inf>(k, inf()));
		}
		else {
			size_t n = ++(it->second.num);
			m.insert(pair<Key, V>(Key(k, n), v));
			it->second.max = max(n, it->second.max);
			it->second.cnt++;
		}
		_size++;
	}
	iterator begin() {
		return iterator(m.begin());
	}
	iterator end() {
		return iterator(m.end());
	}
	iterator upper_bound(const K& k) {
		return ++m.find(Key(k, km[k].max));
	}
	iterator lower_bound(const K& k) {
		return m.find(Key(k, km[k].min));
	}
	iterator find(const K& k) {
		return this->lower_bound(k);
	}
	pair<iterator, iterator> equal_range(const K& k) {
		return pair<iterator, iterator>(this->lower_bound(k), this->upper_bound(k));
	}
	void erase(iterator pos) {
		Key k = pos->first;
		inf* in = &km[k.key];
		size_t n = k.num;
		in->cnt--;
		if (in->cnt == 0) {
			km.erase(pos->first.key);
		}
		else if (in->max == n) {
			in->max = (prev(pos))->first.num;
		}
		else if (in->min == n) {
			in->min = (next(pos))->first.num;
		}
		m.erase(pos);
		_size--;
	}
	size_t erase(const K& k) {
		size_t n = km[k].cnt;
		for (size_t i = 0; i < n; i++) {
			this->erase(this->lower_bound(k));
		}
		return n;
	}
	bool empty() const {
		return m.empty();
	}
	bool size() const {
		return _size;
	}
};


int main() {
	MyMultiMap<int, int> v = MyMultiMap<int, int>();
	v.insert(3, 100);
	v.insert(2, 200);
	v.insert(1, 300);
	v.insert(3, 400);
	v.insert(3, 500);
	for (MyMultiMap<int, int>::iterator it = v.begin(); it !=
		v.end(); ++it) {
		cout << (*it).second << endl;
	}
	cout << v.erase(3) << endl;
	for (MyMultiMap<int, int>::iterator it = v.begin(); it !=
		v.end(); ++it) {
		cout << (*it).second << endl;
	}

	return 0;
}

