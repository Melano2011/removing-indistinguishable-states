#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <math.h>
#include <map>
const int SIZE = 100;
using namespace std;
vector<string> checkarray(string arr[SIZE][SIZE],int siz,int max) {
	string c = "{";
	string ch = "";
	
	vector<string> s;
	bool t = true;
	for (int i = 0; i < siz - 1; i++) {
		if (ch.find(arr[i][0]) == -1) {
			c += arr[i][0];
		}
		for (int k = i + 1; k < siz ;k++) {
			
			for (int j = 1; j <= max ; j++) {
					
				if (arr[i][j] != arr[k][j]) {
					t = false;
				}
			}
			
			if (t) {
				if (ch.find(arr[k][0]) == -1) {
					c += ","+arr[k][0];
					ch += arr[k][0];
					
				}
			}
			t = true;
		}
		if (ch.find(arr[i][0]) == -1) {
			c += "}";
			s.push_back(c);
			ch += arr[i][0];
		}
		c = "{";
	}
	return s;
}
int main() {

	map<string, string> mymap;
	//cases map
	map<string, string> finalcasesmap;
	int finalcasesmapind = 0;
	map<string, string> nonfinalcasesmap;
	int nonfinalcasesmapind = 0;
	//file name
	int mycount = 1;
	string file = "example.txt";
	string line;
	//save file into array
	string mystring[SIZE];
	//found cases
	vector<string> found;
	
	//result after remove-unreachable-states
	vector<string> result;
	//save cases
	vector<string> se;
	//final cases full
	vector<string> finalcase;
	//non-final cases full
	vector<string> nonfinalcase;
	string finalcasetable[SIZE][SIZE];
	string nonfinalcasetable[SIZE][SIZE];
	//final cases
	vector<string> fc;
	vector<string> cs;
	//non-final cases
	vector<string> nfc;
	vector<string> ncs;
	//checked cases
	vector<string> checked;
	//yet to be checked
	vector<string> working;
	ifstream myfile(file);
	int mi = 0;
	if (myfile.is_open())
	{
		cout << "File Given " << endl;
		while (getline(myfile, line))
		{

			mystring[mi] = line;
			cout << line << endl;
			mi++;
		}
		myfile.close();
		cout << "=======================\n=======================" << endl;
	}
	{
		if (mystring->size() != 0) {
			string s = mystring[0];


			int p = s.find(">");

			found.push_back(mystring[0].substr(0, p - 1));
			s = s.substr(p + 1, s.size() - p);
			int k = s.find("|");
			while (k != -1) {
				se.push_back(s.substr(0, k));
				s = s.substr(k + 1, s.size() - k);
				k = s.find("|");
			}
			se.push_back(s);
			for (int sei = 0;sei < se.size();sei++) {
				int fc = se[sei].find("P");

				if (std::find(found.begin(), found.end(), se[sei].substr(fc, se[sei].size() - fc)) == found.end())
				{
					found.push_back(se[sei].substr(fc, se[sei].size() - fc));
				}

			}
			se.clear();
		}
	}
	for (int j = 1;j < mi; j++) {
		string s = mystring[j];
		int p = s.find(">");
		s = s.substr(p + 1, s.size() - p);
		int k = s.find("|");
		string mycase = mystring[j].substr(0, p - 1);
		if (std::find(found.begin(), found.end(), mycase) != found.end())
		{
			while (k != -1) {
				se.push_back(s.substr(0, k));
				s = s.substr(k + 1, s.size() - k);
				k = s.find("|");
			}
			se.push_back(s);
			for (int sei = 0;sei < se.size();sei++) {
				int fc = se[sei].find("P");

				if (std::find(found.begin(), found.end(), se[sei].substr(fc, se[sei].size() - fc)) == found.end())
				{
					found.push_back(se[sei].substr(fc, se[sei].size() - fc));
					
				}

			}
			se.clear();
		}
	}
	for (int j = 0; j < mi; j++) {
		int p = mystring[j].find(">");
		string mycase = mystring[j].substr(0, p - 1);
		if (std::find(found.begin(), found.end(), mycase) != found.end()) {
			result.push_back(mystring[j]);
		}
	}
	int max = 0;
	int f = 0;
	int nf = 0;
	for (int j = 0; j < result.size();j++) {
		int p = result[j].find(">");
		int numf = 1;
		int numnf = 1;
		string mycase = result[j].substr(0, p - 1);
		if (mycase.find("(f)") != -1) {
			finalcasesmap.insert(pair<string, string>(mycase, to_string(finalcasesmapind)));
			finalcasesmapind++;
			finalcase.push_back(mycase);
			fc.push_back(result[j]);
			finalcasetable[f][0] = mycase;
			
			int p = result[j].find(">");
			string s = result[j].substr(p + 1, result[j].size() - p);
			int k = s.find("|");
			while (k != -1) {
				
				string sf = s.substr(0, k);
				int firstp = sf.find("P");
				finalcasetable[f][numf] = sf.substr(firstp, sf.size() - firstp);
				s = s.substr(k + 1, s.size() - k);
				k = s.find("|");
				numf++;
			}
			if (max < numf)
				max = numf;
			int firstp = s.find("P");
			
			finalcasetable[f][numf] = s.substr(firstp, s.size() - firstp);
	
			f++;
			
		}

		else {
			nonfinalcase.push_back(mycase);
			nonfinalcasesmap.insert(pair<string, string>(mycase, to_string(nonfinalcasesmapind)));
			nonfinalcasesmapind++;
			nfc.push_back(result[j]);
			nonfinalcasetable[nf][0] = mycase;

			int p = result[j].find(">");
			string s = result[j].substr(p + 1, result[j].size() - p);
			int q = s.find("|");
			while (q != -1) {

				string sf = s.substr(0, q);
				int firstp = sf.find("P");

				nonfinalcasetable[nf][numnf] = sf.substr(firstp, sf.size() - firstp);
				s = s.substr(q + 1, s.size() - q);
				q = s.find("|");

				numnf++;
			}
			if (max < numf)
				max = numf;
			int firstp = s.find("P");
			nonfinalcasetable[nf][numnf] = s.substr(firstp, s.size() - firstp);
			nf++;
		}
	}

	if (finalcase.size() > 0) {
		if (finalcase.size() > 1) {
			cs.push_back("{");
			for (int j = 0; j < finalcase.size(); j++) {
				cs[0] += finalcase[j];
				cs[0] += ",";
			}
			cs[0] = cs[0].substr(0, cs[0].size() - 1);
			cs[0] += "}";
	
		}
		else {
			cs.push_back("{");
			cs[0] += finalcase[0] + "}";

		}
	}
	if (nonfinalcase.size() > 0) {
		if (nonfinalcase.size() > 1) {
			ncs.push_back("{");
			for (int j = 0; j < nonfinalcase.size(); j++) {
				ncs[0] += nonfinalcase[j];
				ncs[0] += ",";
			}
			ncs[0] = ncs[0].substr(0, ncs[0].size() - 1);
			ncs[0] += "}";

		}
		else {
			ncs.push_back("{");
			ncs[0] += nonfinalcase[0] + "}";

		}
	}

	for(int i = 0; i < finalcasesmapind;i++)
	working.push_back(finalcase[i]);
	int times = 1;
	vector<string> tr;
	//vector<string> save;
	string save[SIZE][SIZE];
	string csave[SIZE];
	string* tt;
	while (working.size() > 0) {

		vector<int> a;
		int dec = 0;
		int get = dec;
		int l = pow(max, times);
		int w;
		if (working.size() > 0) {
			if (working.size() > 1) {
				for (w = 0; w < working.size(); w++) {
					csave[w] = finalcasetable[w][0];
					save[w][0] = finalcasetable[w][0];
				
					for (int j = 1; j < times; j++)
						a.push_back(0);

					for (int k = 1; k <= l;k++) {

						if (get == 0)
							a.push_back(0);
						else {
							for (int h = 0; get > 0; h++)
							{

								a.push_back(get % 2);

								get = get / 2;
							}
						}
						string start = "0";
						for (int ti = 0; ti < times;ti++)
							start = finalcasetable[w][stoi(start)];
						if (find(finalcase.begin(), finalcase.end(), start) != finalcase.end())
						{
							save[w][k] = '2';
						}
						else {
							save[w][k] = '1';
						}
							dec++;
							get = dec;
						
					}
					dec = 0;
					get = dec;
					a.clear();
				}
				bool mycheck = true;
				for (int z = 0; z < l; z++) {
					if (save[0][z] != save[1][z])
						mycheck = false;
				}
				if (mycheck) {

					string r = "{";
					r += csave[0] + "," + csave[1] + "}";
					mymap.insert(pair<string, string>(r, to_string(mycount)));
					checked.push_back(r);
					mycount++;
				}
				else {
					string r = "{";
					r += csave[0] + "}";
					checked.push_back(r);
					mymap.insert(pair<string, string>(r, to_string(mycount)));
					mycount++;
					string r1 = "{";
					r1 += csave[1] + "}";
					checked.push_back(r1);
					mymap.insert(pair<string, string>(r1, to_string(mycount)));
					mycount++;
				}
			}
			else {
				string r = "{";
				r += finalcasetable[0][0] + "}";
				checked.push_back(r);
				mymap.insert(pair<string, string>(r, to_string(mycount)));
				mycount++;
			}


		}
		working.clear();
	

	}
	mymap.insert(pair<string, string>(ncs[0], to_string(mycount)));
	mycount++;
	for (int i = 0; i < nonfinalcasesmapind;i++)
		working.push_back(nonfinalcase[i]);
	while (working.size()>0)
	{
		vector<string> tt;
		vector<int> a;
		int dec = 0;
		int get = dec;
		int l = pow(max, times);
		int w;
		if (working.size() > 0) {
			if (working.size() > 1) {
				for (w = 0; w < working.size(); w++) {
					
					csave[w] = nonfinalcasetable[stoi(nonfinalcasesmap.find(working[w])->second)][0];
					save[w][0] = nonfinalcasetable[stoi(nonfinalcasesmap.find(working[w])->second)][0];

					for (int j = 1; j < times; j++)
						a.push_back(0);

					for (int k = 1; k <= l;k++) {

						if (get == 0)
							a.push_back(0);
						else {
							for (int h = 0; get > 0; h++)
							{

								a.push_back(get % 2);

								get = get / 2;
							}
						}
						string start = working[w];
					
						for (int ti = 0; ti < times;ti++)
							start = nonfinalcasetable[stoi(nonfinalcasesmap.find(start)->second)][a[0]+1];
						
						for (auto x : mymap) {
							if (x.first.find(start) !=-1)
							{
								save[w][k] = x.second;
							}
							
						}
						a.pop_back();
						dec++;
						get = dec;

					}
					dec = 0;
					get = dec;
					a.clear();
				}
			}
			else {
				string r = "{";
				r += nonfinalcasetable[0][0] + "}";
				checked.push_back(r);
				mymap.insert(pair<string, string>(r, to_string(mycount)));
				mycount++;
			}
		}
		
		tt = checkarray(save, working.size(), l);
		mymap.erase(ncs[0]);
		mycount--;
		working.clear();
		for (int i = 0; i < tt.size(); i++) {
			if (tt[i].find(",") == -1|| tt.size()==1) {
				for (auto x : mymap) {
					if (x.first.find(tt[i]) == -1) {
						mymap.insert(pair<string, string>(tt[i], to_string(mycount)));
						mycount++;
					}
				}
				
			}
			else {
				for (auto x : mymap) {
					if (x.first.find(tt[i]) == -1) {
						mymap.insert(pair<string, string>(tt[i], to_string(mycount)));
						mycount++;
					}
				}
				string s2 = tt[i].substr(1, tt[i].size() - 1);
				
				int p = s2.find(",");
				while (p != -1) {
					
					working.push_back(s2.substr(0,p));
					s2 = s2.substr(p + 1, s2.size() + p);
					
					 p = s2.find(",");
				}
				working.push_back(s2.substr(0, s2.size() - 1));
			}
		}
		tt.clear();
		
	}
	string t1,t2;
	string tr1, tr2;
	cout << "Final Table" << endl;
	for (auto x : mymap) {
		cout << "===============================================" << endl;
		cout << x.first << "  ";
		if (x.first.find(",") == -1) {
			if (finalcasesmap.find(x.first.substr(1, x.first.size() - 2)) != finalcasesmap.end()) {
				t1 = finalcasetable[stoi(finalcasesmap.find(x.first.substr(1, x.first.size() - 2))->second)][1];
				t2 = finalcasetable[stoi(finalcasesmap.find(x.first.substr(1, x.first.size() - 2))->second)][2];
				for (auto y : mymap) {
					if (y.first.find(t1) < y.first.size())
						cout << y.first << "  ";
				}for (auto y : mymap) {
					if (y.first.find(t2) < y.first.size())
						cout << y.first << "  ";
				}
				cout << endl;
			}
			else {
				t1 = nonfinalcasetable[stoi(nonfinalcasesmap.find(x.first.substr(1, x.first.size() - 2))->second)][1];
				t2 = nonfinalcasetable[stoi(nonfinalcasesmap.find(x.first.substr(1, x.first.size() - 2))->second)][2];
				for (auto y : mymap) {
					if (y.first.find(t1) < y.first.size())
						cout << y.first << "  ";
				}for (auto y : mymap) {
					if (y.first.find(t2) < y.first.size())
						cout << y.first << "  ";
				}
				cout << endl;
			}
		}
		else {
			int p = x.first.find(",");
			string smap = x.first.substr(1, p - 1);
			if (finalcasesmap.find(smap) != finalcasesmap.end()) {
				t1 = finalcasetable[stoi(finalcasesmap.find(smap)->second)][1];
				t2 = finalcasetable[stoi(finalcasesmap.find(smap)->second)][2];
				for (auto y : mymap) {
					if (y.first.find(t1) < y.first.size())
						cout << y.first << "  ";
				}for (auto y : mymap) {
					if (y.first.find(t2) < y.first.size())
						cout << y.first << "  ";
				}
				cout << endl;
			}
			else {
				t1 = nonfinalcasetable[stoi(nonfinalcasesmap.find(smap)->second)][1];
				t2 = nonfinalcasetable[stoi(nonfinalcasesmap.find(smap)->second)][2];
				for (auto y : mymap) {
					if (y.first.find(t1) < y.first.size())
						cout << y.first << "  ";
				}for (auto y : mymap) {
					if (y.first.find(t2) < y.first.size())
						cout << y.first << "  ";
				}
				
				cout << endl;
			}
		}
	}

	system("pause");
}
