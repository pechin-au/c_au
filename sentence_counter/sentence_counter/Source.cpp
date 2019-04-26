#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdint.h>

using namespace std;

bool is_uppercase(char c) {
	return 'A' <= c && c <= 'Z';
}

bool is_sentence_end(char c) {
	return c == '.' || c == '?' || c == '!';
}

char to_lowercase(char c) {
	if (is_uppercase(c)) {
		c = c + ('a' - 'A');
	}
	return c;
}

int to_index(char c) {
	return to_lowercase(c) - 'a';
}


int main(){
	ifstream inp;
	string s;
	vector<vector<pair<int64_t, int64_t>>> v = vector<vector<pair<int64_t, int64_t>>>(26, vector<pair<int64_t, int64_t>>());
	inp.open("entire_bee_movie_script");
	//inp.open("war-and-peace.txt");
	char c;
	char sent_start;
	char lastchar;
	bool sent_ended = true;;
	int64_t sent_start_i = 0, i = 0;
	while (inp.get(c)) {
		s += c;
		if (is_uppercase(c) && sent_ended) {
			sent_start = to_lowercase(c);
			sent_ended = false;
			sent_start_i = i;
		}
		else if (is_sentence_end(c)) {
			sent_ended = true;
			if (sent_start == lastchar) {
				v[to_index(sent_start)].push_back(pair<int64_t, int64_t>(sent_start_i, i));
			}
		}
		i++;
		lastchar = c;
	}
	i = 0;
	for (vector<vector<pair<int64_t, int64_t>>>::iterator it = v.begin(); it != v.end(); it++) {
		if (!it->empty()) {
			cout << endl << "Sentences starting and ending with " << char('A' + i) << ':' << endl;
		}
		i++;
		for (vector<pair<int64_t, int64_t>>::iterator jt = it->begin(); jt != it->end(); jt++) {
			cout << s.substr(jt->first, jt->second - jt->first + 1) << endl;
		}
	}
	inp.close();
	return 0;
}
