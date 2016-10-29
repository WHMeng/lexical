#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include <vector>
#include <set>
#include <map>
#include <string>
#include <fstream>

class TextQuery{
public:
	typedef std::vector<std::string>::size_type line_no; // !!!
	void read_file(std::ifstream &is){
		store_file(is); build_map();
	}
	std::set<line_no> run_query(const std::string &) const;
	std::string text_line(line_no) const;
private:
	void store_file(std::ifstream &);
	void build_map();
	std::vector<std::string> lines_of_text;
	// map word to set of the lines on which it occurs
	std::map<std::string, std::set<line_no> > word_map;
};

#endif
