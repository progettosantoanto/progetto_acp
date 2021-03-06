#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

class CSVRow{
    private:
        vector<string>    m_data;
    public:
        string const& operator[](unsigned int index) const {
            return m_data[index];
        }
        unsigned int size() {
            return m_data.size();
        }
        void readNextRow(istream& str){
            string line;
            getline(str,line);
            stringstream lineStream(line);
            string cell;
            m_data.clear();
            while(getline(lineStream,cell,',')){
                m_data.push_back(cell);
            }
        }
};

istream& operator>>(istream& str, CSVRow& data) {
    data.readNextRow(str);
    return str;
}

vector<unsigned int> read_first(CSVRow row){
        unsigned int temp;
        vector<unsigned int> it;
        for(int i = 0; i < row.size(); i++){
                if (!row[i].empty()){
                    temp = stoi(row[i]);
                    it.push_back(temp);
                    }
        }
        return it;
}
